/**********************************************************
 * 功能描述：用户信息类
 * 作   者：方国军
 * 创建日期：2022-05-25
 * *******************************************************/
#ifndef USER_H
#define USER_H
#include <QString>
#include <QObject>
#include <QList>
#include "UserLogin_global.h"
class USERLOGIN_EXPORT User : public QObject
{
    Q_OBJECT
public:
    enum UserType
    {
        eSuperAdmin = 0,  //![超级管理员]
        eProducter,       //![生产工程师]
        eEngineer,        //![用服工程师]
        eAdmin,           //![医院管理员]
        eUser,            //![普通用户]
    };
    Q_ENUM(UserType)

    enum RoleType
    {
        eR_Ad_Setting       = 0, //![高级设置权限]
        eR_View_ATFocus,         //![查看自动调焦权限]
        eR_SKIP_Boot_Step,       //![开机跳过步骤权限]
        eR_Audit,                //![审核权限]
    };
    Q_ENUM(RoleType)

    explicit User(QObject *parent = nullptr);
    explicit User(QString name, QString passwd, User::UserType usrtp, User::RoleType roletp, QObject *parent = nullptr);
    explicit User(QString name, QString passwd, User::UserType usrtp, QList<User::RoleType> roletpList, QObject *parent = nullptr);

    virtual ~User();
    void AddRoles(User::RoleType roletp);
    bool RemoveRoles(User::RoleType roletp);
    bool HasRoles(User::RoleType roletp);

    QString GetUserName() const;
    QString GetUserPassWd() const;
    UserType GetUserType() const;
    bool CheckUserAndPasswd(QString name, QString passwd);
signals:

private:
    QString  m_name;
    QString  m_passwd;
    UserType m_usertp;
    QList<RoleType> m_roletpList;
};

#endif // USER_H
