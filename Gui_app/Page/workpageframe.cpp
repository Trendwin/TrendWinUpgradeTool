#include "workpageframe.h"
#include "systemsettingpage.h"
#include "upgradepage.h"
#include "upgradectrlmgr.h"
#include "aboutPage.h"
#include <QVBoxLayout>
#include <QDebug>
WorkPageFrame::WorkPageFrame(FilePathMgr *pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent) :
    QWidget(parent)
  , mp_ugradeMgr(p_ugradeMgr)
{
    this->InitLayout(pFilePathMgr, plngMgr);
    this->OnSwitchPage(pg_w_Debug);
}

WorkPageFrame::~WorkPageFrame()
{
    if(nullptr != this->mp_Stacklay)
    {
        delete this->mp_Stacklay;
        this->mp_Stacklay = nullptr;
    }
}

void WorkPageFrame::OnSwitchPage(int pageId)
{
    qDebug()<<"OnSwitchPage=>"<<pageId;
    this->mp_Stacklay->setCurrentIndex(pageId);
}

void WorkPageFrame::InitLayout(FilePathMgr *pFilePathMgr, LanguageManager *plngMgr)
{
    this->mp_UpgradePg = new UpgradePage(pFilePathMgr, plngMgr, mp_ugradeMgr);
    this->mp_SettingPg = new SystemSettingPage(pFilePathMgr, plngMgr, this->mp_ugradeMgr,  nullptr);
    this->mp_AboutPg = new AboutPage(pFilePathMgr, plngMgr, nullptr);
    this->mp_Stacklay = new QStackedLayout();
    this->mp_Stacklay->insertWidget(pg_w_Upgrade, this->mp_UpgradePg);
    this->mp_Stacklay->insertWidget(pg_w_Setting, this->mp_SettingPg);
    this->mp_Stacklay->insertWidget(pg_w_About, this->mp_AboutPg);

    connect(this->mp_SettingPg, &SystemSettingPage::sigComStatusChanged, this->mp_UpgradePg, &UpgradePage::on_RefreshCtrlStatus);
    connect(this->mp_SettingPg, &SystemSettingPage::sigComStatusChanged, this, &WorkPageFrame::sigComStatueChanged);
    QVBoxLayout *pageMainLayout = new QVBoxLayout;
    pageMainLayout->addLayout(this->mp_Stacklay);
    setLayout(pageMainLayout);
}
