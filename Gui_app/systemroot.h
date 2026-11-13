#ifndef SYSTEMROOT_H
#define SYSTEMROOT_H
#include <QObject>
class FilePathMgr;
class PresetSvrMgr;
class LanguageManager;
class AnalyzerWinFrame;
class UpGradeCtrlMgr;
class SystemRoot : public QObject
{
    Q_OBJECT
public:
    explicit SystemRoot(QObject* parent = nullptr);
    virtual ~SystemRoot();

    bool Start();
signals:
    void sigStartBoot(bool &ret);
protected:
    void Initialization();
private:
    FilePathMgr* mp_FilePathMgr;
    PresetSvrMgr* mp_PresetSvrMgr;
    LanguageManager* mp_lngMgr;
    AnalyzerWinFrame* mp_Analyzer;
    UpGradeCtrlMgr* mp_upgradeMgr;
};

#endif // SYSTEMROOT_H
