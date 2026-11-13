#include "aboutPage.h"
#include "uistylemanager.h"
#include <QQmlContext>
#include <QQuickItem>
#include "uistylemanager.h"
#include "sysversion.h"
AboutPage::AboutPage(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, QWidget *parent)
    : QQuickWidget(parent)
    , m_pSystemVer(new SysVersion)
{
    InitLayout(pFilePathMgr, plngMgr);
}

AboutPage::~AboutPage()
{

}

QString AboutPage::proVersion() const
{
    return this->m_pSystemVer->GetFullVersoin();
}

void AboutPage::InitLayout(FilePathMgr *pFilePathMgr, LanguageManager *lngMgr)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    setMaximumWidth(150);
//    setMinimumWidth(150);
    this->rootContext()->setContextProperty("UiStyleMgr", UiStyleManager::Instance());
    this->rootContext()->setContextProperty("LngMgr", lngMgr);
    this->rootContext()->setContextProperty("AboutPage", this);
    setSource(QUrl("qrc:/Page/CtrlPage/qml/aboutWiget.qml"));
    //
    QQuickItem* qml = this->rootObject();

//    connect(qml, SIGNAL(sigSwitchPage(int)), this, SIGNAL(sigSwitchPage(int)));
}
