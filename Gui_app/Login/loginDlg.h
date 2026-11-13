#ifndef LOGINDLG_H
#define LOGINDLG_H
#include <QObject>
#include <QString>
#include <QQuickItem>
#include <QDialog>
#include <QQuickWidget>
#include "userlogin.h"
#include "languageManager.h"

class LogInDlg : public QDialog
{
    Q_OBJECT
public:
    Q_PROPERTY(QString logErMsg READ logErMsg WRITE setLogErMsg NOTIFY sigLogErMsgChanged);
    enum LogErType
    {
        LG_OK    = 0,
        LG_NM_Er = 1,
        LG_PW_Er = 2,
        LG_ALL_Er = LG_NM_Er | LG_PW_Er,
    };
    Q_ENUM(LogErType);

    explicit LogInDlg(LanguageManager* plngMgr, QWidget* parent = nullptr);
    virtual ~LogInDlg();
    bool LogInResult();
    QString logErMsg() const;
    void setLogErMsg(QString msg);
    Q_INVOKABLE LogErType logErType();

    Q_INVOKABLE bool userLogin(QString usrname, QString passwd);
signals:
    void sigLogErMsgChanged();
protected slots:
    void onUserLogIn(QString usrname, QString passwd);
    void onExit();
private:
    void Initlization();
    void ChangeToCurErType(UserLogin::LogRet orgType);
private:
    QQuickWidget* mp_QuickWidget;
    UserLogin* mp_UsrLogin;
    LanguageManager* mp_lngMgr;
    LogErType m_ErType;
    bool m_loginOK;
    QString m_er_msg;
};

#endif // LOGINDLG_H
