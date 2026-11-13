#include "ctrlmenuWidget.h"
#include "uistylemanager.h"
#include <QQmlContext>
#include <QQuickItem>
#include "uistylemanager.h"
CtrlMenuWidget::CtrlMenuWidget(FilePathMgr *pFilePathMgr, LanguageManager *plngMgr, QWidget *parent) :
    QQuickWidget(parent)
{
    InitLayout(pFilePathMgr, plngMgr);
}

CtrlMenuWidget::~CtrlMenuWidget()
{

}

void CtrlMenuWidget::InitLayout(FilePathMgr *pFilePathMgr, LanguageManager *lngMgr)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setMaximumWidth(150);
    setMinimumWidth(150);
    this->rootContext()->setContextProperty("UiStyleMgr", UiStyleManager::Instance());
    this->rootContext()->setContextProperty("LngMgr", lngMgr);
    setSource(QUrl("qrc:/Page/MenuPage/qml/ctrlMenuWidget.qml"));
    //
    QQuickItem* qml = this->rootObject();

    connect(qml, SIGNAL(sigSwitchPage(int)), this, SIGNAL(sigSwitchPage(int)));
}
