#include "mainframe.h"
#include <QHBoxLayout>
#include "ctrlmenuWidget.h"
#include "workpageframe.h"
#include "upgradectrlmgr.h"
MainFrame::MainFrame(FilePathMgr *pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent)
    : QWidget(parent)
    , mp_Hlay(nullptr)
    , mp_CtrlMenu(nullptr)
    , mp_WorkPg(nullptr)
{
    InitLayout(pFilePathMgr, plngMgr, p_ugradeMgr);
}

MainFrame::~MainFrame()
{

}

void MainFrame::InitLayout(FilePathMgr *pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->mp_Hlay = new QHBoxLayout;
    this->mp_CtrlMenu = new CtrlMenuWidget(pFilePathMgr, plngMgr);
    this->mp_Hlay->addWidget(this->mp_CtrlMenu);
    this->mp_WorkPg = new WorkPageFrame(pFilePathMgr, plngMgr, p_ugradeMgr);
    this->mp_Hlay->addWidget(this->mp_WorkPg);

    this->setLayout(this->mp_Hlay);
    this->mp_Hlay->setMargin(0);
    this->mp_Hlay->setSpacing(0);
    connect(this->mp_CtrlMenu, &CtrlMenuWidget::sigSwitchPage, this->mp_WorkPg, &WorkPageFrame::OnSwitchPage);
    connect(this->mp_WorkPg, &WorkPageFrame::sigComStatueChanged, this, &MainFrame::sigComStatusChanged);
}
