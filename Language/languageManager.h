/**********************************************************
 * 功能描述：多语言翻译器定义
 * 作   者：方国军
 * 创建日期：2022-05-22
 * *******************************************************/
#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H
#include <QObject>
#include <QString>
#include "language_def.h"
#include "Language_global.h"


class LanguageManagerPrivate;
class LANGUAGE_EXPORT LanguageManager : public QObject
{
    Q_OBJECT
public:
    explicit LanguageManager(QObject* parent = nullptr);
    virtual ~LanguageManager();
    void Initialization(QString dir, QString lng_name);
    Q_INVOKABLE QString trs(QString orgin_id);
    Q_INVOKABLE QString curLngType();

    void Log(QString& msg, int level, QString module_name = Lng_module);
signals:
    void sigLanguageChanged();
public slots:
    void OnLoadLanguage(QString lng);
private:
    LanguageManagerPrivate* d_ptr;
    Q_DECLARE_PRIVATE(LanguageManager)
    Q_DISABLE_COPY(LanguageManager)
};

#endif // LANGUAGEMANAGER_H

