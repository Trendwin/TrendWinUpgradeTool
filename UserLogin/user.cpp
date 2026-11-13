#include "user.h"

User::User(QObject *parent) :
    QObject(parent),
    m_name(""),
    m_passwd(""),
    m_usertp(eUser)
{
    m_roletpList.clear();
}

User::User(QString name, QString passwd, UserType usrtp, RoleType roletp, QObject *parent) :
    QObject(parent),
    m_name(name),
    m_passwd(passwd),
    m_usertp(usrtp)
{
    m_roletpList.clear();
}

User::User(QString name, QString passwd, User::UserType usrtp, QList<User::RoleType> roletpList, QObject *parent) :
    QObject(parent),
    m_name(name),
    m_passwd(passwd),
    m_usertp(usrtp),
    m_roletpList(roletpList)
{
}

User::~User()
{
}

void User::AddRoles(RoleType roletp)
{
    if(!m_roletpList.contains(roletp))
    {
        m_roletpList.append(roletp);
    }
}

bool User::RemoveRoles(RoleType roletp)
{
    bool ret = false;
    if(m_roletpList.contains(roletp))
    {
        ret = m_roletpList.removeOne(roletp);
    }

    return ret;
}

bool User::HasRoles(RoleType roletp)
{
    return m_roletpList.contains(roletp);
}

QString User::GetUserName() const
{
    return m_name;
}

QString User::GetUserPassWd() const
{
    return m_passwd;
}

User::UserType User::GetUserType() const
{
    return m_usertp;
}

bool User::CheckUserAndPasswd(QString name, QString passwd)
{
    int n = QString::compare(m_name, name, Qt::CaseInsensitive);
    int p = QString::compare(m_passwd, passwd, Qt::CaseInsensitive);

    if((0 == n) && (0 == p))
    {
        return true;
    }
    else
    {
        return false;
    }
}

