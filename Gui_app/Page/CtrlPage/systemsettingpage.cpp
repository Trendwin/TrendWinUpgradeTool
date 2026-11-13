#include "systemsettingpage.h"
#include <QtSerialPort/QSerialPortInfo>
#include "upgradectrlmgr.h"
#include "systempreset.h"
#include "ui_systemsettingpage.h"

SystemSettingPage::SystemSettingPage(FilePathMgr *pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent)
    : QWidget(parent)
    , mp_upgrademgr(p_ugradeMgr)
    , mp_lngMgr(plngMgr)
    , m_comOpened(false)
    , ui(new Ui::SystemSettingPage)
{
    ui->setupUi(this);
    Init();
}

SystemSettingPage::~SystemSettingPage()
{
    delete ui;
}

void SystemSettingPage::Init()
{

    this->ui->label_com->setText(this->mp_lngMgr->trs("IDS_COM_PORT"));
    this->ui->btnOpen->setText(this->mp_lngMgr->trs("IDS_OPEN"));
    this->ui->btnClose->setText(this->mp_lngMgr->trs("IDS_CLOSE"));

    InitComPort();
    RefreshComCtrlButtonState(false);
}

void SystemSettingPage::InitComPort()
{
    QList<QString> portList = this->GetValidComPorts();
    this->ui->cb_Master_ComPort->clear();
    this->ui->cb_Master_ComPort->addItems(portList);

    QString presetCom = SystemPreset::Instance()->GetString(CPreset::PRT_COMM);
    if(portList.contains(presetCom))
    {
        this->ui->cb_Master_ComPort->setCurrentText(presetCom);
    }
}

QList<QString> SystemSettingPage::GetValidComPorts()
{
    QStringList portList = this->mp_upgrademgr->GetComPortList();
    QList<QString> pt_list;
    for (const auto& port : portList)
    {
        pt_list.append(port);
    }

    return pt_list;
}

void SystemSettingPage::RefreshComCtrlButtonState(bool isOpened)
{
    this->ui->btnOpen->setEnabled(!isOpened);
    this->ui->btnClose->setEnabled(isOpened);
    emit sigComStatusChanged(this->ui->cb_Master_ComPort->currentText(), isOpened);
}


void SystemSettingPage::on_btnOpen_clicked()
{
    if((nullptr == this->mp_upgrademgr) || this->mp_upgrademgr->IsComPortOpened())
    {
        return;
    }

    if(-1 != this->ui->cb_Master_ComPort->currentIndex() )
    {
        QString currentPort = this->ui->cb_Master_ComPort->currentText();
        bool status = this->mp_upgrademgr->OpenComPort(currentPort);
        this->m_comOpened = status;
        this->RefreshComCtrlButtonState(status);
    }
}


void SystemSettingPage::on_btnClose_clicked()
{
    if((nullptr == this->mp_upgrademgr))
    {
        return;
    }

    bool status = this->mp_upgrademgr->CloseComPort();
    this->m_comOpened = !status;
    this->RefreshComCtrlButtonState(!status);
}


void SystemSettingPage::on_btnPortRefresh_clicked()
{
    if(!this->m_comOpened)
    {
        InitComPort();
    }
}

