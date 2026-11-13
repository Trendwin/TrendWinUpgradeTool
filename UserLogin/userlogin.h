/**********************************************************
 * 功能描述：用户登录验证
 * 作   者：方国军
 * 创建日期：2022-05-25
 * *******************************************************/
#ifndef USERLOGIN_H
#define USERLOGIN_H
#include <QObject>
#include <QMap>
#include "UserLogin_global.h"
#include "user.h"
class UserLoginPrivate;

class USERLOGIN_EXPORT UserLogin : public QObject
{
    Q_OBJECT
public:
    enum LogRet
    {
        ELogOK     =  0,     //![验证通过]
        ELogNameEr =  1,     //![用户名错误]
        ELogPWEr   =  2,     //![密码错误]
        ELogAllEr  = ELogNameEr | ELogPWEr,
    };
    Q_ENUM(LogRet)

    explicit UserLogin(QString userDir, QObject* parent = nullptr);
    explicit UserLogin(QObject* parent = nullptr);

    virtual ~UserLogin();
    LogRet LogIn(QString name, QString passwd);
protected:
    void Initialization();
private:
    QMap<QString, User*> m_map_usr;
};

#endif // USERLOGIN_H
