#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
#include "languageManager.h"
#include "uistylemanager.h"
#include "filepathmgr.h"
class QHBoxLayout;
class CtrlMenuWidget;
class WorkPageFrame;
class  UpGradeCtrlMgr;
class MainFrame : public QWidget
{
    Q_OBJECT
public:
    explicit MainFrame(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr,  UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent = nullptr);
    virtual ~MainFrame();
signals:
    void sigComStatusChanged(QString com_name, bool status);
private:
    void InitLayout(FilePathMgr *pFilePathMgr, LanguageManager* plngMgr, UpGradeCtrlMgr *p_ugradeMgr);
private:
    QHBoxLayout* mp_Hlay;
    CtrlMenuWidget* mp_CtrlMenu;
    WorkPageFrame* mp_WorkPg;
};

#endif // MAINFRAME_H
