#include "systemroot.h"
#include "filepathmgr.h"
#include "presetSvrMgr.h"
#include "AnalyzerWinFrame.h"
#include "loggermanager.h"
#include "Gui_def.h"
#include "utility.h"
#include "systempreset.h"
#include "upgradeObj_config.h"
#include "upgradectrlmgr.h"
#include "loginDlg.h"
SystemRoot::SystemRoot(QObject *parent) :
    QObject(parent),
    mp_FilePathMgr(nullptr),
    mp_PresetSvrMgr(nullptr),
    mp_upgradeMgr(nullptr)
{
    Initialization();
}

SystemRoot::~SystemRoot()
{
    if(nullptr !=  mp_FilePathMgr)
    {
        delete mp_FilePathMgr;
    }

    if(nullptr !=  mp_PresetSvrMgr)
    {
        delete mp_PresetSvrMgr;
    }

    if(nullptr !=  mp_upgradeMgr)
    {
        delete mp_upgradeMgr;
    }
}

bool SystemRoot::Start()
{
    //![登录]
    bool ret = Login();
    if(ret)
    {
        mp_Analyzer = new AnalyzerWinFrame(mp_FilePathMgr, mp_lngMgr, this->mp_upgradeMgr);
        mp_Analyzer->show();
    }
    return ret;
}

bool SystemRoot::Login()
{
//    return true;
    LogInDlg *pLogin = new LogInDlg(this->mp_lngMgr);
    pLogin->exec();
    return pLogin->LogInResult();
}

void SystemRoot::Initialization()
{
    mp_FilePathMgr = new FilePathMgr();
    LogMgr->Initialization(mp_FilePathMgr->GetLogPath());

    mp_PresetSvrMgr = new PresetSvrMgr();
    mp_PresetSvrMgr->Init(mp_FilePathMgr->GetFactoryPresetPath(), mp_FilePathMgr->GetCurrentPresetPath());
    mp_lngMgr = new LanguageManager();
    mp_lngMgr->Initialization(mp_FilePathMgr->GetLanguagePath(), SystemPreset::Instance()->GetString(CPreset::PRT_Language));
    QString error_msg;
    bool ret = UpGradeObj_Config::Instance()->Load(mp_FilePathMgr->GetConfigPath(), error_msg);
    if(!ret)
    {
        LogMgr->Log(error_msg, ErLevel::eError, Gui_module);
    }
    else
    {
        LogMgr->Log(error_msg, ErLevel::eTrace, "upgradeObj.json file load OK!");
    }

    this->mp_upgradeMgr = new UpGradeCtrlMgr();
//    mp_Analyzer = new AnalyzerWinFrame(mp_FilePathMgr, mp_lngMgr, this->mp_Core);
//    mp_Analyzer->hide();
    Logs("System StartUp.", ErLevel::eTrace, Gui_module);
//    QList<CommandData> list1 = cmds.GetCommandList(ECC_Def::gp_action_2);
//    QList<CommandData> list2 = cmds.GetCommandList(ECC_Def::gp_action_2);
}


