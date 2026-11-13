#ifndef UISTYLEMANAGER_H
#define UISTYLEMANAGER_H

#include <QObject>
class UiStyleManager : public QObject
{
    Q_OBJECT
public:
    static UiStyleManager* Instance();
    virtual ~UiStyleManager();
    Q_INVOKABLE QString getFontFamily();
    Q_INVOKABLE QString getFontColor();
    Q_INVOKABLE int getBigTitleFontSize();
    Q_INVOKABLE int getTitleFontSize();
    Q_INVOKABLE int getMenuFontSize();
    Q_INVOKABLE int getNormalFontSize();
    Q_INVOKABLE int getButtonFontSize();
signals:
private:
    explicit UiStyleManager(QObject *parent = nullptr);
};

#endif // UISTYLEMANAGER_H
