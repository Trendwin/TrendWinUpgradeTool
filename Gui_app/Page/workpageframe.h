#ifndef WORKPAGEFRAME_H
#define WORKPAGEFRAME_H

#include <QWidget>
#include "languageManager.h"
#include "uistylemanager.h"
#include "filepathmgr.h"
#include <QStackedLayout>

class SystemSettingPage;
class UpgradePage;
class AboutPage;
class UpGradeCtrlMgr;
class WorkPageFrame : public QWidget
{
    Q_OBJECT
public:
    enum EnumWrokPg
    {
        pg_w_Debug,
        pg_w_Upgrade,
        pg_w_Setting,
        pg_w_About,
    };
    explicit WorkPageFrame(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr,  UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent = nullptr);
    virtual ~WorkPageFrame();
public:
signals:
    void sigComStatueChanged(QString com_name, bool status);
public slots:
    void OnSwitchPage(int pageId);

private:
    void InitLayout(FilePathMgr *pFilePathMgr, LanguageManager* plngMgr);
private:
    QStackedLayout *mp_Stacklay;
    UpGradeCtrlMgr* mp_ugradeMgr;
    SystemSettingPage* mp_SettingPg;
    UpgradePage *mp_UpgradePg;
    AboutPage* mp_AboutPg;

};

#endif // WORKPAGEFRAME_H
