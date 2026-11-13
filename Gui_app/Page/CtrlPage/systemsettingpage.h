#ifndef SYSTEMSETTINGPAGE_H
#define SYSTEMSETTINGPAGE_H

#include <QWidget>
#include <QList>
#include "filepathmgr.h"
#include "languageManager.h"
namespace Ui {
class SystemSettingPage;
}
class UpGradeCtrlMgr;
class SystemSettingPage : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingPage(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, UpGradeCtrlMgr* p_ugradeMgr, QWidget *parent = nullptr);
    virtual ~SystemSettingPage();
signals:
    void sigComStatusChanged(QString com_name, bool status);
protected slots:

protected:
    void Init();
    void InitComPort();
    QList<QString> GetValidComPorts();
    void RefreshComCtrlButtonState(bool isOpened);
private slots:

    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnPortRefresh_clicked();

private:
    UpGradeCtrlMgr* mp_upgrademgr;
    LanguageManager* mp_lngMgr;
    bool m_comOpened;
    Ui::SystemSettingPage *ui;
};

#endif // SYSTEMSETTINGPAGE_H
