#include "messageprocesser.h"
#include "command_def.h"
#include "cc_def.h"
#include "crccalculater.h"
#include "loggermanager.h"
#include "Core_def.h"
#include <QThread>

USB_Message_recv_Def gRecvMessage;


class MessageProcesserPrivate
{
public:
    MessageProcesserPrivate(QSerialPort* p_SerialPort, MessageProcesser* parent);
    ~MessageProcesserPrivate();
private:
    Q_DECLARE_PUBLIC(MessageProcesser)
private:
    MessageProcesser* q_ptr;
    QSerialPort* m_pSerial;
    QByteArray m_RecvArray;
    QThread *m_pRecvThread;
    quint8 m_interestMsg;
};

MessageProcesserPrivate::MessageProcesserPrivate(QSerialPort* p_SerialPort, MessageProcesser *parent)
    : q_ptr(parent)
    , m_pSerial(p_SerialPort)
    , m_pRecvThread(new QThread())
    , m_interestMsg(0)
{
    QObject::connect(m_pSerial, &QSerialPort::readyRead, q_ptr, &MessageProcesser::OnReadData);

    q_ptr->moveToThread(m_pRecvThread);
    m_pRecvThread->start();
}

MessageProcesserPrivate::~MessageProcesserPrivate()
{
    m_RecvArray.clear();
    m_pRecvThread->requestInterruption();
    m_pRecvThread->quit();
    m_pRecvThread->wait();
    m_pRecvThread = nullptr;
}


////////////////////////////////////////////////////////////////////////
MessageProcesser::MessageProcesser(QSerialPort* pSerial, QObject *parent)
    : QThread(parent)
//    , m_pParseThread(new QThread())
    , m_bStop(false)
    , d_ptr(new MessageProcesserPrivate(pSerial, this))
{    
//    connect(this, &MessageProcesser::sigParse, this, &MessageProcesser::OnParse);
//    this->moveToThread(m_pParseThread);
//    m_pParseThread->start();
    this->start();
}

MessageProcesser::~MessageProcesser()
{
    this->m_bStop = true;
    this->terminate();
    this->wait();
//    m_pParseThread->requestInterruption();
//    m_pParseThread->quit();
//    m_pParseThread->wait();
//    m_pParseThread = nullptr;
}

void MessageProcesser::SyncSerial(QSerialPort *pSerial)
{
}

void MessageProcesser::SetInterestMsg(quint8 command_id)
{
    Q_D(MessageProcesser);
    d->m_interestMsg = command_id;
}

void MessageProcesser::OnReadData()
{
    Q_D(MessageProcesser);
    this->m_mutex.lock();
    d->m_RecvArray.append(d->m_pSerial->readAll());
    this->m_mutex.unlock();

//    emit sigParse();
}

//void MessageProcesser::OnParse()
//{
//    Q_D(MessageProcesser);

//    while(d->m_RecvArray.length() >= MIN_FRAME_LEN)
//    {
//        PickFrame();
//        QThread::msleep(50);
//    }
//}

QString MessageProcesser::ByteArratToHexString(QByteArray recvArray)
{
    QString msgs = "";
    for (int i = 0; i < recvArray.size(); ++i)
    {
        msgs += (QString::number((quint8)recvArray.at(i), 16).toUpper().rightJustified(2, '0') + " ");
    }

    return msgs;
}

bool MessageProcesser::PickFrame(QByteArray &array)
{
    Q_D(MessageProcesser);

    quint16 headIndex = 0;
    quint16 tmpHeadLen = 0;
    quint16 bufLen = d->m_RecvArray.length();
    quint16 crc_calcd = 0;
    quint16 totalLen = 0;
    quint16 dataLen = 0;
//    QByteArray tmpRecvArray;
    if(bufLen < MIN_FRAME_LEN)
    {
        return false;
    }

    while(headIndex < bufLen)
    {
        if((quint8)REV_HEADS[tmpHeadLen] == (quint8)d->m_RecvArray.data()[headIndex])
        {
            tmpHeadLen++;
            if(tmpHeadLen == sizeof(REV_HEADS))
            {
                break;
            }
        }
        else
        {
            tmpHeadLen = 0;
        }

        headIndex++;
    }

    if(tmpHeadLen != sizeof(REV_HEADS))
    {
        return false;
    }

    // 读指针移动到head1处
    headIndex = headIndex - 1;
    // 重新计算buf内数据长度
    bufLen = d->m_RecvArray.length() - headIndex;
    if(bufLen < MIN_FRAME_LEN)
    {
        return false;
    }

    dataLen =  (quint16)(d->m_RecvArray.data()[headIndex + ADR_DATA_LEN]);
    totalLen = dataLen + MIN_FRAME_LEN;

    this->m_mutex.lock();

    if(totalLen > 256)
    {
        d->m_RecvArray.remove(0, 2);
        this->m_mutex.unlock();
        return false;
    }
    else if(bufLen  < totalLen)
    {
        this->m_mutex.unlock();
        return false;
    }

    // CRC 计算
    crc_calcd = usCalcCRC((quint8*)&d->m_RecvArray.data()[headIndex], totalLen);

    if(0 == crc_calcd)
    {
        for(int i = 0; i < totalLen; ++i)
        {
            array.append(d->m_RecvArray.data()[headIndex + i]);
        }

        d->m_RecvArray.remove(0, headIndex + totalLen);
        // 校验通过;
        QString msg = QString("Recv Cmd:%1").arg(ByteArratToHexString(array));
        Logs(msg, ErLevel::eTrace, Core_module);
//        sigMessageArrived(tmpRecvArray);
//        if((quint8)tmpRecvArray.data()[ADR_FUNCTION_ID] == d->m_interestMsg)
//        {
//            quint8 ack = (quint8)tmpRecvArray.data()[ADR_DATA];
//            emit sigInterestMsgArrived(ack);
//        }
        this->m_mutex.unlock();
        return true;
    }
    else
    {
        d->m_RecvArray.remove(0, headIndex + totalLen);
        this->m_mutex.unlock();
        return false;
    }
}

void MessageProcesser::run()
{
    Q_D(MessageProcesser);

    while (!this->m_bStop)
    {
        QByteArray frameArray;
        if(PickFrame(frameArray))
        {
            sigMessageArrived(frameArray);
            if((quint8)frameArray.data()[ADR_FUNCTION_ID] == d->m_interestMsg)
            {
                quint8 ack = (quint8)frameArray.data()[ADR_DATA];
                emit sigInterestMsgArrived(ack);
            }
        }
        QThread::msleep(10);
    }
}

