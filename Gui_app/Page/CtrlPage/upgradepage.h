#ifndef UPGRADEPAGE_H
#define UPGRADEPAGE_H

#include <QWidget>
#include <QMap>
#include "upgradectrlmgr.h"
class UpgradeConfig
{
public:
    UpgradeConfig();
    ~UpgradeConfig();
    bool ReadConfig(QString fileName);
    QStringList GetInstrTypes();
    QString GetBinPrefix(QString type);
private:
    void Init();
};

namespace Ui {
class UpgradePage;
}

class LanguageManager;
class UpGradeCtrlMgr;
class FilePathMgr;

class UpgradePage : public QWidget
{
    Q_OBJECT

public:
    explicit UpgradePage(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent = nullptr);
    ~UpgradePage();
    enum UPGradeCtrlStatus
    {
        UPG_IDLE = 0,
        UPG_WORK,
    };

signals:
    void sigStartUpgrade(QString upgradeFilePath, quint8 devId);
    void sigTermination_upgrade();
    void sigQueryVersion(quint8 devId);
public slots:
    void on_RefreshCtrlStatus(QString com_name, bool comStatus);
    void On_HandleMessage(QByteArray msg);
protected:
    void Init();
    void RefreshUpgradeFile();
    QString GetUpgradeFilePath();
    bool EnumUpGradeFile();
    void RefreshCtrlButton();
    void HandleVersionMsg(QByteArray msg);
    QString ASCII_2_Str(quint8 ch);
private slots:

    void on_btnRefreshUpgradeFile_clicked();

    void on_btn_StartUpgrade_clicked();

    void on_btnStopUpgrade_clicked();

    void on_UpdateUpGradeProcentageInfo(quint16 totalPacks, quint16 curSucPacks);

    void on_RefreshUpGradeResult(UpGradeCtrlMgr::UpGrade_Result_Def up_result);

    void on_btnQueryVersion_clicked();

private:
    Ui::UpgradePage *ui;
    FilePathMgr *mp_filePathMgr;
    LanguageManager *mp_lngMgr;
    UpGradeCtrlMgr* mp_ugradeMgr;
    UPGradeCtrlStatus m_CtrlStauts;
    QMap<QString, QString> m_upgradefile_map;
};

#endif // UPGRADEPAGE_H
