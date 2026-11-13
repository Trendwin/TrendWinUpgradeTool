#include "upgradectrlmgr.h"
#include <QFileInfo>
#include <QEventLoop>
#include <QTimer>
#include "command_def.h"
#include "ComFramedata.h"
#include "crccalculater.h"
#include <QByteArray>

const quint16 PACK_SIZE = 240;
class UpGradeCtrlMgrPrivate
{
public:
    UpGradeCtrlMgrPrivate(UpGradeCtrlMgr* parent);
    ~UpGradeCtrlMgrPrivate();
private:
    Q_DECLARE_PUBLIC(UpGradeCtrlMgr);

private:
    UpGradeCtrlMgr* q_ptr;
    QSerialPort *m_pSerial;
    MessageProcesser* m_pMsgProcesser;
    QByteArray m_UpgFileContent;
    QByteArray m_send_array;
    QString m_curPortName;
    bool m_upgradeDo;
    quint8 m_devId;
};

UpGradeCtrlMgrPrivate::UpGradeCtrlMgrPrivate(UpGradeCtrlMgr* parent)
    : q_ptr(parent)
    , m_pSerial(nullptr)
    , m_pMsgProcesser(nullptr)
    , m_curPortName("")
    , m_upgradeDo(false)
    , m_devId(0xFF)
{
    m_UpgFileContent.clear();
    m_send_array.clear();
    this->m_pSerial = new QSerialPort();
    this->m_pMsgProcesser = new MessageProcesser(this->m_pSerial);
}

UpGradeCtrlMgrPrivate::~UpGradeCtrlMgrPrivate()
{
    if(nullptr != m_pSerial)
    {
        if(m_pSerial->isOpen())
        {
            m_pSerial->close();
        }

        delete m_pSerial;
        m_pSerial = nullptr;
    }

    if(nullptr != m_pMsgProcesser)
    {
        delete m_pMsgProcesser;
        m_pMsgProcesser = nullptr;
    }
}

////////////////////////////////////////////
UpGradeCtrlMgr::UpGradeCtrlMgr(QObject *parent)
    : QObject(parent)
    , d_ptr(new UpGradeCtrlMgrPrivate(this))
{
    Init();
}

UpGradeCtrlMgr::~UpGradeCtrlMgr()
{
    delete d_ptr;
}

QStringList UpGradeCtrlMgr::GetComPortList()
{
    QStringList comportList;
    QList<QSerialPortInfo> port_list = QSerialPortInfo::availablePorts();
    for (const auto& port : port_list)
    {
        comportList.append(port.portName());
    }

    return comportList;
}

bool UpGradeCtrlMgr::OpenComPort(QString com)
{
    Q_D(UpGradeCtrlMgr);
    bool ret = false;
    QStringList comportList = GetComPortList();
    if(comportList.contains(com))
    {
        //设置串口名字
        d->m_pSerial->setPortName(com);
        //设置波特率
        d->m_pSerial->setBaudRate(QSerialPort::Baud115200);
        //设置数据位
        d->m_pSerial->setDataBits(QSerialPort::Data8);
        //设置奇偶校验位
        d->m_pSerial->setParity(QSerialPort::NoParity);
        //设置停止位
        d->m_pSerial->setStopBits(QSerialPort::OneStop);
        //设置流控
        d->m_pSerial->setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        if (d->m_pSerial->open(QIODevice::ReadWrite))
        {
            ret = true;
            d->m_curPortName = com;
        }

        emit sigComPortStateChanged(com, ret);
    }

    return ret;
}

bool UpGradeCtrlMgr::CloseComPort()
{
    Q_D(UpGradeCtrlMgr);
    d->m_pSerial->close();

    emit sigComPortStateChanged(d->m_curPortName, false);

    return true;
}

bool UpGradeCtrlMgr::IsComPortOpened()
{
    Q_D(UpGradeCtrlMgr);
    return d->m_pSerial->isOpen();
}

void UpGradeCtrlMgr::onStartInstrUpgrade(QString upgradeFileName, quint8 devId)
{
    Q_D(UpGradeCtrlMgr);
    QByteArray singlePack;
    bool ret = false;
    quint32 remainLength = 0;
    quint32 sums = 0;
//    QFileInfo fileInfo(upgradeFileName);
//    if(!fileInfo.exists())
//    {
//        emit sigUpGradeResult(UPG_FILE_NOT_EXIST);
//        return;
//    }

    QFile file(upgradeFileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        emit sigUpGradeResult(UPG_FILE_OPEN_FAILED);
        return;
    }
    d->m_devId = devId;
    d->m_upgradeDo = true;
    d->m_UpgFileContent.clear();
    d->m_UpgFileContent = file.readAll();
    if(!d)
    {
        return;
    }
    quint32 realTotalLen = d->m_UpgFileContent.length();
    if(0 != realTotalLen % 4)
    {
        quint8 adds =  realTotalLen % 4;
        quint8 addValue = 0;
        //![补足长度]
        for(int i = 0; i < adds; ++i)
        {
            d->m_UpgFileContent.append(addValue);
        }
    }

    qint16 packs_count = (d->m_UpgFileContent.length() / PACK_SIZE);
    if(0 != (d->m_UpgFileContent.length() % PACK_SIZE))
    {
        packs_count++;
    }

    sums = ucCalcSum((uint8_t *)d->m_UpgFileContent.data(), d->m_UpgFileContent.length());
    if(d->m_UpgFileContent.length() > 0)
    {
        ret = StartUpgrade(devId, d->m_UpgFileContent.length(), 10000);
        if(!ret)
        {
            emit sigUpGradeResult(UPG_TIMEOUT);
            return;
        }
    }

    if(!d->m_upgradeDo)
    {
        emit sigUpGradeResult(UPG_USER_TERMINATED);
        return;
    }

    emit sigUpGradeResult(UPG_DATA_TRANS);
    quint16 validSendLen = 0;
    remainLength = d->m_UpgFileContent.length();

    for(qint16 i = 0; i < packs_count; ++i)
    {
        validSendLen = remainLength > PACK_SIZE ? PACK_SIZE : remainLength;
        remainLength -= PACK_SIZE;
        singlePack.clear();
        singlePack.append(d->m_UpgFileContent.data(), validSendLen);

        d->m_UpgFileContent.remove(0, validSendLen);
        ret = StartUpgradeTran(devId, i, singlePack, 2, 5000);
        if(!ret)
        {
            emit sigUpGradeResult(UPG_TIMEOUT);
            return;
        }
        else
        {
            emit sigUpdateUpgardeInfo(packs_count, i + 1);
        }

        if(!d->m_upgradeDo)
        {
            emit sigUpGradeResult(UPG_USER_TERMINATED);
            return;
        }
    }

   ret = FinishUpgradeTran(devId, sums, 2, 10000);
   if(ret)
   {
       emit sigUpGradeResult(UPG_SUC);
   }
   else
   {
       emit sigUpGradeResult(UPG_TIMEOUT);
   }
}

void UpGradeCtrlMgr::onTerminateUpgrade()
{
    Q_D(UpGradeCtrlMgr);
    QByteArray array;
    FinishUpgradeTran(d->m_devId, 0, 1, 1000);
    d->m_upgradeDo = false;
}

void UpGradeCtrlMgr::onQueryDevVersionInfo(quint8 devId)
{
    Q_D(UpGradeCtrlMgr);
    quint32 time_out_ms = 5000;
    quint8 data = 0;
    QByteArray array;
    array.append(data);
    array.append(data);

    SendPro(devId, CMD_DeviceImfo_Query, array, time_out_ms);
}

bool UpGradeCtrlMgr::StartUpgrade(quint8 devId, quint32 totalBytes,  quint32 time_out_ms)
{
    QByteArray array;
    array.append((quint8)((totalBytes >> 24) & 0xFF));
    array.append((quint8)((totalBytes >> 16) & 0xFF));
    array.append((quint8)((totalBytes >>  8) & 0xFF));
    array.append((quint8)((totalBytes >>  0) & 0xFF));

    return SendPro(devId, CMD_Program_Update_Start, array, time_out_ms);
}

bool UpGradeCtrlMgr::StartUpgradeTran(quint8 devId, quint16 pack_No, QByteArray binArray, quint8 max_trytimes, quint32 per_time_out_ms)
{
    bool ucResult = false;
    QByteArray dataArray;
    dataArray.append((quint8)((pack_No >> 8) & 0xFF));
    dataArray.append((quint8)((pack_No >> 0) & 0xFF));
    dataArray.append(binArray);

    for(int i = 0; i < max_trytimes; ++i)
    {
        ucResult = SendPro(devId, CMD_Program_Update, dataArray, per_time_out_ms);
        if(ucResult)
        {
            break;
        }
    }

    return ucResult;
}

bool UpGradeCtrlMgr::FinishUpgradeTran(quint8 devId, quint32 totalSum, quint8 max_trytimes, quint32 time_out_ms)
{
    bool ucResult = false;

    QByteArray array;
    array.append((totalSum >> 24) & 0xFF);
    array.append((totalSum >> 16) & 0xFF);
    array.append((totalSum >> 8)  & 0xFF);
    array.append((totalSum >> 0)  & 0xFF);

    for(int i = 0; i < max_trytimes; ++i)
    {
        ucResult = SendPro(devId, CMD_Program_Update_End, array, time_out_ms);
        if(ucResult)
        {
            break;
        }
    }

    return ucResult;
}

void UpGradeCtrlMgr::Init()
{
    Q_D(UpGradeCtrlMgr);
    connect(d->m_pMsgProcesser, &MessageProcesser::sigMessageArrived, this, &UpGradeCtrlMgr::sigArrivedMesg);

}

bool UpGradeCtrlMgr::SendPro(quint8 dstId, uint8_t command_ID,  QByteArray& array, quint32 time_out_ms)
{
    Q_D(UpGradeCtrlMgr);
    bool uc_Result = false;
    if((NULL == d->m_pSerial) || (!d->m_pSerial->isOpen()))
    {
        return false;
    }

    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);

    ComFrameData cmdFrame;
    cmdFrame.SetDst(dstId);
    cmdFrame.SetSrc(Dev_Master);
    cmdFrame.SetSeq(1);
    cmdFrame.SetCmd(command_ID);
    cmdFrame.SetDat(array);

    cmdFrame.ReCalcCRC();

    // 设置监听
    d->m_pMsgProcesser->SetInterestMsg(command_ID);
    timer.setSingleShot(true);

    connect(d->m_pMsgProcesser, &MessageProcesser::sigInterestMsgArrived, [&](quint8 ret_ack){
        uc_Result = (0 == ret_ack);
        loop.quit();
    });

    connect(&timer, &QTimer::timeout, [&]{
        uc_Result = false;
        loop.quit();
     });

    // 发送
    QByteArray cmdarray = cmdFrame.ToByteArray();
    d->m_pSerial->write(cmdarray);

    timer.start(time_out_ms);

    loop.exec();
    timer.stop();

    disconnect(d->m_pMsgProcesser, &MessageProcesser::sigInterestMsgArrived, nullptr, nullptr);
    timer.disconnect();

    return uc_Result;
}


