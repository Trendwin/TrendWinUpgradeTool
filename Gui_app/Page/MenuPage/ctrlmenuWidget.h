#ifndef CTRLMENUWIDGET_H
#define CTRLMENUWIDGET_H

#include <QQuickWidget>
#include "languageManager.h"
#include "filepathmgr.h"

class QStackedLayout;
class MicroSettingPage;
class CtrlMenuWidget : public QQuickWidget
{
    Q_OBJECT
public:
    explicit CtrlMenuWidget(FilePathMgr* pFilePathMgr, LanguageManager *plngMgr, QWidget *parent = nullptr);
    virtual ~CtrlMenuWidget();

signals:
    void sigSwitchPage(int pgId);
private:
    void InitLayout(FilePathMgr *pFilePathMgr, LanguageManager* lngMgr);
private:

};

#endif // CTRLMENUWIDGET_H
