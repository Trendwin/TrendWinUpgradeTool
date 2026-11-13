#include "statusbarwidget.h"
#include <QQmlContext>
StatusBarWidget::StatusBarWidget(LanguageManager *plngMgr, QWidget *parent)
    : QQuickWidget(parent)
    , mp_lngMgr(plngMgr)
{
    InitLayout(plngMgr);
}

StatusBarWidget::~StatusBarWidget()
{
}

QString StatusBarWidget::comStatus()
{
    return this->m_comStatus;
}

void StatusBarWidget::setComStatus(QString status)
{
    this->m_comStatus = status;
}

void StatusBarWidget::on_RefreshComPortStatus(QString com_name, bool isOpened)
{
    QString status = isOpened ? this->mp_lngMgr->trs("IDS_OPENED") : this->mp_lngMgr->trs("IDS_CLOSED");
    QString info = QString("%1: %2").arg(com_name).arg(status);
    this->setComStatus(info);
    emit sigComStatusChanged();
}

void StatusBarWidget::InitLayout(LanguageManager *lngMgr)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->rootContext()->setContextProperty("StatusBarObj", this);
    setMinimumHeight(30);
    setMaximumHeight(30);
    setSource(QUrl("qrc:/Page/qml/StatusBarWidget.qml"));
}
