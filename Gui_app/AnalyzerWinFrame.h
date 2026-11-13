#ifndef ANALYZERWINFRAME_H
#define ANALYZERWINFRAME_H

#include <QMainWindow>
#include "languageManager.h"
#include <QVBoxLayout>
class FilePathMgr;
class MainFrame;
class StatusBarWidget;
class UpGradeCtrlMgr;
class AnalyzerWinFrame : public QMainWindow
{
    Q_OBJECT

public:
    AnalyzerWinFrame(FilePathMgr* pFilePathMgr, LanguageManager* plngMgr, UpGradeCtrlMgr* p_upgradeMgr, QWidget *parent = nullptr);
    ~AnalyzerWinFrame();
protected:
    void Initialization(FilePathMgr* pFilePathMgr);
private:
    UpGradeCtrlMgr* mp_upgradeMgr;
    FilePathMgr* mp_FilePhMgr;
    LanguageManager* mp_lngMgr;
    QWidget *mp_CentralWidget;
    MainFrame* mp_MainPage;
    StatusBarWidget* mp_StatusBarWgt;
    QVBoxLayout* mp_Vlay;

};
#endif // ANALYZERWINFRAME_H
