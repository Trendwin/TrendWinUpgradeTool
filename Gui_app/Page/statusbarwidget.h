#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QQuickWidget>
#include "languageManager.h"
#include "uistylemanager.h"
#include <QString>
class StatusBarWidget : public QQuickWidget
{
    Q_OBJECT

    Q_PROPERTY(QString comStatus READ comStatus WRITE setComStatus NOTIFY sigComStatusChanged)
public:
    explicit StatusBarWidget(LanguageManager *plngMgr, QWidget *parent = nullptr);
    virtual ~StatusBarWidget();

    QString comStatus();
    void setComStatus(QString status);

signals:
    void sigComStatusChanged();
public slots:
    void on_RefreshComPortStatus(QString com_name, bool isOpened);
private:
    void InitLayout(LanguageManager* lngMgr);
private:
    LanguageManager* mp_lngMgr;
    QString m_comStatus;
};

#endif // STATUSBARWIDGET_H
