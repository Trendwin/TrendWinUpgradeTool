#include "AnalyzerWinFrame.h"
#include "filepathmgr.h"
#include "systempreset.h"
#include "ctrlmenuWidget.h"
#include "statusbarwidget.h"
#include "mainframe.h"
#include "upgradectrlmgr.h"
#include "sysversion.h"
AnalyzerWinFrame::AnalyzerWinFrame(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr,  QWidget *parent)
    : QMainWindow(parent)
    , mp_upgradeMgr(p_ugradeMgr)
    , mp_FilePhMgr(pFilePathMgr)
    , mp_lngMgr(plngMgr)
    , mp_CentralWidget(nullptr)
    , mp_MainPage(nullptr)
    , mp_Vlay(nullptr)
{
    Initialization(pFilePathMgr);
}

AnalyzerWinFrame::~AnalyzerWinFrame()
{
    if(nullptr != this->mp_MainPage)
    {
        delete this->mp_MainPage;
        this->mp_MainPage = nullptr;
    }

    if(nullptr != this->mp_StatusBarWgt)
    {
        delete this->mp_StatusBarWgt;
        this->mp_StatusBarWgt = nullptr;
    }

    if(nullptr != this->mp_Vlay)
    {
        delete this->mp_Vlay;
        this->mp_Vlay = nullptr;
    }

    if(nullptr != this->mp_CentralWidget)
    {
        delete this->mp_CentralWidget;
        this->mp_CentralWidget = nullptr;
    }
}

void AnalyzerWinFrame::Initialization(FilePathMgr* pFilePathMgr)
{
    this->setMaximumSize(776,520);
    this->resize(776,520);

    mp_lngMgr->Initialization(mp_FilePhMgr->GetLanguagePath(), SystemPreset::Instance()->GetString(CPreset::PRT_Language));
    QString title = QStringLiteral("趋盛科技板卡升级工具");
    this->setWindowTitle(title);
    this->mp_CentralWidget = new QWidget;
    this->mp_MainPage = new MainFrame(pFilePathMgr, mp_lngMgr, mp_upgradeMgr);
    this->mp_StatusBarWgt = new StatusBarWidget(mp_lngMgr);
    this->mp_Vlay = new QVBoxLayout;
    this->mp_Vlay->addWidget(mp_MainPage);
    this->mp_Vlay->addWidget(mp_StatusBarWgt);
    this->mp_Vlay->setMargin(0);
    this->mp_Vlay->setSpacing(0);
    //
    this->setCentralWidget(this->mp_CentralWidget);
    this->mp_CentralWidget->setLayout(mp_Vlay);
    //
    connect(this->mp_MainPage, &MainFrame::sigComStatusChanged, this->mp_StatusBarWgt, &StatusBarWidget::on_RefreshComPortStatus);
    this->hide();
}

