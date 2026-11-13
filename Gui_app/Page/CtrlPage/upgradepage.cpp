#include "upgradepage.h"
#include "ui_upgradepage.h"
#include "languageManager.h"
#include "upgradeObj_config.h"
#include "config_obj.h"
#include "filepathmgr.h"
#include <QMap>
#include <QList>
#include <QDir>
#include <QDateTime>
#include "cc_def.h"
#include <QString>

namespace {
const QString PowerBoardType = QStringLiteral("功率驱动板");
}

UpgradePage::UpgradePage(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr *p_ugradeMgr, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UpgradePage)
    , mp_filePathMgr(pFilePathMgr)
    , mp_lngMgr(plngMgr)
    , mp_ugradeMgr(p_ugradeMgr)
    , m_CtrlStauts(UPG_IDLE)
{
    ui->setupUi(this);
    Init();
}


UpgradePage::~UpgradePage()
{
    delete ui;
}

void UpgradePage::on_RefreshCtrlStatus(QString com_name, bool comStatus)
{
    RefreshCtrlButton();
}

void UpgradePage::On_HandleMessage(QByteArray msg)
{
    quint8 functionId = msg.at(ADR_FUNCTION_ID);
    if(CMD_DeviceImfo_Query == functionId)
    {
        HandleVersionMsg(msg);
    }
}

void UpgradePage::Init()
{
    m_upgradefile_map.clear();
    this->ui->upgrade_rogressBar->setVisible(false);
    this->ui->upgrade_rogressBar->setMinimum(0);
    this->ui->upgrade_rogressBar->setMaximum(100);

    connect(mp_ugradeMgr, &UpGradeCtrlMgr::sigUpdateUpgardeInfo, this, &UpgradePage::on_UpdateUpGradeProcentageInfo);
    connect(this, &UpgradePage::sigStartUpgrade, mp_ugradeMgr, &UpGradeCtrlMgr::onStartInstrUpgrade, Qt::QueuedConnection);
    connect(this, &UpgradePage::sigTermination_upgrade, mp_ugradeMgr, &UpGradeCtrlMgr::onTerminateUpgrade, Qt::QueuedConnection);
    connect(mp_ugradeMgr, &UpGradeCtrlMgr::sigUpGradeResult, this, &UpgradePage::on_RefreshUpGradeResult);
    connect(this, &UpgradePage::sigQueryVersion, mp_ugradeMgr, &UpGradeCtrlMgr::onQueryDevVersionInfo);
    connect(mp_ugradeMgr, &UpGradeCtrlMgr::sigArrivedMesg, this, &UpgradePage::On_HandleMessage);
    RefreshUpgradeFile();
    RefreshCtrlButton();
}

void UpgradePage::RefreshUpgradeFile()
{
    this->ui->upBinFile_combox->clear();

    if(this->EnumUpGradeFile())
    {
        QList<QString> fileNameList = m_upgradefile_map.keys();
        for(int i = 0; i < fileNameList.count(); ++i)
        {
            this->ui->upBinFile_combox->insertItem(i, fileNameList.at(i));
        }
    }
}

QString UpgradePage::GetUpgradeFilePath()
{
    return QString("%1/%2").arg(this->mp_filePathMgr->GetUpGradeFilePath()).arg(PowerBoardType);
}

// 不遍历子文件夹
bool UpgradePage::EnumUpGradeFile()
{
    QString fileDir = this->GetUpgradeFilePath();
    QDir updir(fileDir);
    m_upgradefile_map.clear();

    if(updir.exists(fileDir))
    {
        const Config_Obj *pConfigObj = UpGradeObj_Config::Instance()->GetConfigObj(PowerBoardType);
        if(nullptr == pConfigObj)
        {
            return false;
        }
        QStringList filters;
        filters<<QString("*.bin");
        updir.setFilter (QDir::Files | QDir::NoSymLinks); // 设置类型过滤器，只为文件格式
        updir.setNameFilters (filters);  // 设置文件名称过滤器，只为 filters 格式（后缀为.jpeg 等图片格式）

        int dir_count = updir.count();
        if(dir_count <= 0)
        {
            return false;
        }

        // 获取分隔符
        QChar separator = QChar('/');
        if(!fileDir.contains(separator))
        {
            separator = QChar('\\');
        }
        QChar last_char = fileDir.at(fileDir.length()-1);
        if(last_char == separator)
        {
            separator = QChar();
        }

        for(int i=0; i<dir_count; i++)
        {
            QString file_name = updir[i];  // 文件名称
            if(file_name.startsWith(pConfigObj->GetPrefix()))
            {
                QString file_path = fileDir + separator + file_name;   // 文件全路径
                m_upgradefile_map[file_name] = file_path;
            }
        }
    }

    return (m_upgradefile_map.count() > 0);
}

void UpgradePage::RefreshCtrlButton()
{
    if(!this->mp_ugradeMgr->IsComPortOpened())
    {
        this->m_CtrlStauts = UPG_IDLE;
        this->ui->btn_StartUpgrade->setEnabled(false);
        this->ui->btnStopUpgrade->setEnabled(false);
        this->ui->btnQueryVersion->setEnabled(false);
    }
    else
    {
        if(UPG_IDLE == this->m_CtrlStauts)
        {
            this->ui->btn_StartUpgrade->setEnabled(true);
            this->ui->btnStopUpgrade->setEnabled(false);
            this->ui->btnQueryVersion->setEnabled(true);
        }
        else
        {
            this->ui->btn_StartUpgrade->setEnabled(false);
            this->ui->btnStopUpgrade->setEnabled(true);
            this->ui->btnQueryVersion->setEnabled(false);
        }
    }
}

void UpgradePage::HandleVersionMsg(QByteArray msg)
{
    QString str_hard_ver = "";
    QString str_iap_ver = "";
    QString str_app_ver = "";
    QString str_UID = "";


    quint16 h_ver = 0 ;
    quint16 m_ver = 0;
    quint16 l_ver = 0;

    quint8 VER_Start = ADR_DATA + 4;
    //![硬件版本号]
    h_ver = msg.at(VER_Start);
    m_ver = msg.at(VER_Start + 1);
    l_ver = msg.at(VER_Start + 2) << 8 | msg.at(VER_Start + 3);

    str_hard_ver = QString("V%1.%2.%3").arg(h_ver).arg(m_ver).arg(l_ver);

    //![IAP 版本]
    h_ver = msg.at(VER_Start + 4);
    m_ver = msg.at(VER_Start + 5);
    l_ver = msg.at(VER_Start + 6) << 8 | msg.at(VER_Start + 7);
    str_iap_ver = QString("V%1.%2.%3").arg(h_ver).arg(m_ver).arg(l_ver);

    //![APP 版本号]
    h_ver = msg.at(VER_Start + 8);
    m_ver = msg.at(VER_Start + 9);
    l_ver = msg.at(VER_Start + 10) << 8 | msg.at(VER_Start + 11);
    str_app_ver = QString("V%1.%2.%3").arg(h_ver).arg(m_ver).arg(l_ver);


    //![UID]
    str_UID = "";
    for(int i = 0; i < 12; i++)
    {
        quint8 temp1 = 0;
        temp1 = (quint8)msg.at(VER_Start + 12 + i);
        str_UID += QString("%1").arg(temp1, 1, 16).toUpper().rightJustified(2, '0');
        if((i != 0) && (0 == (i + 1) % 4))
        {
            str_UID += "-";
        }
    }

    if(str_UID.endsWith('-'))
    {
        str_UID = str_UID.mid(0, str_UID.length() - 1);
    }

    this->ui->lineEdit_hard_Ver->setText(str_hard_ver);
    this->ui->lineEdit_IAP_Ver->setText(str_iap_ver);
    this->ui->lineEdit_APP_Ver->setText(str_app_ver);
    this->ui->lineEdit_mac->setText(str_UID);
}

QString UpgradePage::ASCII_2_Str(quint8 ch)
{
    int value = 0;
    if ((ch >= '0') && (ch <= '9'))
    {
        value = ch - 0x30;
    }
    else if ((ch >= 'A') && (ch <= 'F'))
    {
        value = ch - 'A' + 10;
    }
    else if ((ch >= 'a') && (ch <= 'f'))
    {
        value = ch - 'a' + 10;
    }
    else
    {
        value = (-1);
    }

    if(value != -1)
    {
        return QString::number(value, 16).toUpper();
    }
    else
    {
        return "";
    }
}

void UpgradePage::on_btnRefreshUpgradeFile_clicked()
{
    RefreshUpgradeFile();
}


void UpgradePage::on_btn_StartUpgrade_clicked()
{
    QString upgradeFile = this->ui->upBinFile_combox->currentText();
    if(upgradeFile.isNull() || upgradeFile.isEmpty())
    {
        return;
    }
    this->m_CtrlStauts = UPG_WORK;
    this->RefreshCtrlButton();
    this->ui->lineEdit_upgradeStatus->setText("");
    this->ui->lineEdit_upgrade_precentage->setText("");
    QString upgradeFilePath = "";
    if(this->m_upgradefile_map.contains(upgradeFile))
    {
        upgradeFilePath = this->m_upgradefile_map.value(upgradeFile);
        this->ui->upgrade_rogressBar->setValue(0);
        this->ui->upgrade_rogressBar->setVisible(true);
        this->ui->lineEdit_upgradeStatus->setText(mp_lngMgr->trs("IDS_START_UPGRADE"));
        emit sigStartUpgrade(upgradeFilePath, Dev_Driver);
    }
}


void UpgradePage::on_btnStopUpgrade_clicked()
{
    this->m_CtrlStauts = UPG_IDLE;
    emit sigTermination_upgrade();
    this->RefreshCtrlButton();
    this->ui->upgrade_rogressBar->setVisible(false);
    this->ui->lineEdit_upgradeStatus->setText(mp_lngMgr->trs("IDS_UPG_USER_TERMINATED"));
}

void UpgradePage::on_UpdateUpGradeProcentageInfo(quint16 totalPacks, quint16 curSucPacks)
{
    this->ui->upgrade_rogressBar->setValue(100 * curSucPacks / totalPacks);
    QDateTime nows = QDateTime::currentDateTime();
//    QString strCurDateTime = nows.toString("yyyy-MM-dd hh:mm:ss");
    QString info = QString("Upgrading: %2/%3 ......").arg(curSucPacks).arg(totalPacks);
    this->ui->lineEdit_upgrade_precentage->setText(info);
}

void UpgradePage::on_RefreshUpGradeResult(UpGradeCtrlMgr::UpGrade_Result_Def up_result)
{
    QString up_info = "";
    bool upgradeStoped = false;
    switch((quint16)up_result)
    {
        case UpGradeCtrlMgr::UPG_SUC:
            upgradeStoped = true;
            up_info = this->mp_lngMgr->trs("IDS_UPG_SUCCESS");
            break;
        case UpGradeCtrlMgr::UPG_DATA_TRANS:
            upgradeStoped = false;
            up_info = this->mp_lngMgr->trs("IDS_UPGRADING");
            break;
        case UpGradeCtrlMgr::UPG_FILE_NOT_EXIST:
            upgradeStoped = true;
            up_info = this->mp_lngMgr->trs("IDS_UPG_FILE_NOT_EXIST");
            break;
        case UpGradeCtrlMgr::UPG_FILE_OPEN_FAILED:
            upgradeStoped = true;
            up_info = this->mp_lngMgr->trs("IDS_UPG_FILE_OPEN_FAILED");
            break;
        case UpGradeCtrlMgr::UPG_TIMEOUT:
            upgradeStoped = true;
            up_info = this->mp_lngMgr->trs("IDS_UPG_COMM_TIMEOUT");
            break;
        case UpGradeCtrlMgr::UPG_COMPORT_CLOSED:
            upgradeStoped = true;
            up_info = this->mp_lngMgr->trs("IDS_UPG_COMM_TERM_CLOSED");
            break;
        case UpGradeCtrlMgr::UPG_USER_TERMINATED:
            upgradeStoped = true;
            up_info = this->mp_lngMgr->trs("IDS_UPG_USER_TERMINATED");
            break;
    }

    if(upgradeStoped)
    {
        this->m_CtrlStauts =  UPG_IDLE;
        this->ui->upgrade_rogressBar->setVisible(false);
    }
    this->ui->lineEdit_upgradeStatus->setText(up_info);
    this->RefreshCtrlButton();
}


void UpgradePage::on_btnQueryVersion_clicked()
{
    emit sigQueryVersion(Dev_Driver);
}

