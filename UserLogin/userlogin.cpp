#include "userlogin.h"

UserLogin::UserLogin(QString userDir, QObject *parent) :
    QObject(parent)
{
    Initialization();
}

UserLogin::UserLogin(QObject *parent) :
    QObject(parent)
{
    Initialization();
}

UserLogin::~UserLogin()
{
    qDeleteAll(m_map_usr);
}

UserLogin::LogRet UserLogin::LogIn(QString name, QString passwd)
{
    User* pUsr = nullptr;
    if(this->m_map_usr.contains(name))
    {
        pUsr = this->m_map_usr[name];
        if(pUsr->CheckUserAndPasswd(name, passwd))
        {
            return ELogOK;
        }
        else
        {
            return ELogPWEr;
        }
    }
    else
    {
        return ELogNameEr;
    }
}

void UserLogin::Initialization()
{
    this->m_map_usr["engineer"] = new User("engineer", "trendwin2024", User::eEngineer, User::eR_Ad_Setting);
}
