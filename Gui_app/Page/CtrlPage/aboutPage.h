#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QQuickWidget>
#include <QObject>
#include "languageManager.h"
#include "filepathmgr.h"
class SysVersion;
class AboutPage : public QQuickWidget
{
    Q_PROPERTY(QString proVersion READ proVersion NOTIFY sigProVersionChanged)
    Q_OBJECT

public:
    explicit AboutPage(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, QWidget *parent = nullptr);
    virtual ~AboutPage();

    QString proVersion() const;
    void setProVersion(QString version);
signals:
    void sigProVersionChanged();
private:
    void InitLayout(FilePathMgr *pFilePathMgr, LanguageManager* lngMgr);
private:
    SysVersion *m_pSystemVer;
};

#endif // ABOUTPAGE_H
