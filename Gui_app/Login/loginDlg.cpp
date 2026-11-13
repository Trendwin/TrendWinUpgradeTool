#include "loginDlg.h"
#include <QQuickItem>
#include <QQmlContext>
#include "uistylemanager.h"
LogInDlg::LogInDlg(LanguageManager *plngMgr, QWidget *parent)
    : QDialog(parent)
    , mp_lngMgr(plngMgr)
    , m_ErType(LG_ALL_Er)
    , m_loginOK(false)
{
    Initlization();
}

LogInDlg::~LogInDlg()
{

}

bool LogInDlg::LogInResult()
{
    return m_loginOK;
}

QString LogInDlg::logErMsg() const
{
    return this->m_er_msg;
}

void LogInDlg::setLogErMsg(QString msg)
{
    this->m_er_msg = msg;
    emit sigLogErMsgChanged();
}

LogInDlg::LogErType LogInDlg::logErType()
{
    return this->m_ErType;
}

bool LogInDlg::userLogin(QString usrname, QString passwd)
{
    UserLogin::LogRet ret = this->mp_UsrLogin->LogIn(usrname, passwd);
    this->ChangeToCurErType(ret);
    switch (ret)
    {
        case UserLogin::ELogOK:
            m_loginOK = true;
            break;
        case UserLogin::ELogNameEr:
            this->setLogErMsg(this->mp_lngMgr->trs("IDS_USERNAME_ERROR"));
            break;
        case UserLogin::ELogPWEr:
            this->setLogErMsg(this->mp_lngMgr->trs("IDS_PASSWORD_ERROR"));
            break;
        default:
            break;
    }

    if(m_loginOK)
    {
        this->close();
    }

    return m_loginOK;
}

void LogInDlg::onUserLogIn(QString usrname, QString passwd)
{
    UserLogin::LogRet ret = this->mp_UsrLogin->LogIn(usrname, passwd);
    this->ChangeToCurErType(ret);

    switch (ret)
    {
        case UserLogin::ELogOK:
            m_loginOK = true;
            break;
        case UserLogin::ELogNameEr:
            this->setLogErMsg(this->mp_lngMgr->trs("IDS_USERNAME_ERROR"));
            break;
        case UserLogin::ELogPWEr:
            this->setLogErMsg(this->mp_lngMgr->trs("IDS_PASSWORD_ERROR"));
            break;
        default:
            break;
    }

    if(m_loginOK)
    {
        this->close();
    }
}

void LogInDlg::onExit()
{
    this->close();
}

void LogInDlg::Initlization()
{
    this->setWindowTitle(mp_lngMgr->trs("IDS_LOGIN"));
    this->setWindowModality(Qt::ApplicationModal);//阻挡应用程序
//    qmlRegisterType<LogInDlg>("com.LogInDlg", 1, 0, "MLogInDlg");
    mp_UsrLogin = new UserLogin();
    mp_QuickWidget = new QQuickWidget(this);
    mp_QuickWidget->rootContext()->setContextProperty("LoginParent", this);
    mp_QuickWidget->rootContext()->setContextProperty("LngMgr", this->mp_lngMgr);
    mp_QuickWidget->rootContext()->setContextProperty("UiStyleMgr", UiStyleManager::Instance());

    mp_QuickWidget->setSource(QUrl("qrc:/Login/qml/LogInDlg.qml"));
    mp_QuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    QQuickItem *qmlRoot = mp_QuickWidget->rootObject();
    if(nullptr !=  qmlRoot)
    {
        connect(qmlRoot, SIGNAL(sigLogin(QString, QString)), this, SLOT(onUserLogIn(QString, QString)));
        connect(qmlRoot, SIGNAL(sigExit()), this, SLOT(onExit()));
    }
}

void LogInDlg::ChangeToCurErType(UserLogin::LogRet orgType)
{
    if(UserLogin::ELogOK == orgType)
    {
        this->m_ErType = LogInDlg::LG_OK;
    }
    else if(UserLogin::ELogNameEr == orgType)
    {
        this->m_ErType = LogInDlg::LG_NM_Er;
    }
    else if(UserLogin::ELogPWEr == orgType)
    {
        this->m_ErType = LogInDlg::LG_PW_Er;
    }
    else
    {
        this->m_ErType = LogInDlg::LG_ALL_Er;
    }
}
