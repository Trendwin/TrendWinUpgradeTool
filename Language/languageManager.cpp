#include "languagemanager.h"
#include <QMap>
#include <QSettings>
#include <QFileInfo>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
class LanguageManagerPrivate
{
public:
    LanguageManagerPrivate(LanguageManager* parent);
    virtual ~LanguageManagerPrivate();
private:
    void LoadLngFile(QString dir, QString lng_Name);
    void Load(QString fullPath);
    void ChangeLng(QString lng_Name);
    QString Tranlate(QString origin_id);
private:
    Q_DECLARE_PUBLIC(LanguageManager)
private:
    LanguageManager* q_ptr;
    QString m_lng_dir;
    QString m_lng_Type;
    QMap<QString, QString> m_dic_lng_maps;
};



LanguageManagerPrivate::LanguageManagerPrivate(LanguageManager *parent):
    q_ptr(parent),
    m_lng_dir(""),
    m_lng_Type("zh_CN")
{
}

LanguageManagerPrivate::~LanguageManagerPrivate()
{
    m_dic_lng_maps.clear();
}

void LanguageManagerPrivate::LoadLngFile(QString dir, QString lng_Name)
{
    Q_Q(LanguageManager);
    m_lng_dir = dir;
    m_lng_Type = lng_Name;
    QString fullPath = QString("%1//%2.%3").arg(m_lng_dir, m_lng_Type, "lng");
    QFileInfo fileInfo(fullPath);
    if(fileInfo.isFile() && fileInfo.exists())
    {
        Load(fullPath);
    }
    else
    {
        QString msg = QString("%1, not exist!").arg(fullPath);
        q->Log(msg, 1);
    }
}

void LanguageManagerPrivate::Load(QString fullPath)
{
    Q_Q(LanguageManager);
    QFile f(fullPath);
    QString msg = "";
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        msg = QString("%1, Open failed!").arg(fullPath);
        q->Log(msg, 1);
        return;
    }

    m_dic_lng_maps.clear();
    QTextStream txtinput(&f);
    txtinput.setCodec("UTF-8");
    QString lineStr = "";
    while (!txtinput.atEnd())
    {
        lineStr = txtinput.readLine();
        QStringList strlist = lineStr.split("|-=-|");
        if(2 == strlist.length())
        {
            m_dic_lng_maps[strlist.at(0).trimmed()] = strlist.at(1).trimmed();
        }
    }

    f.close();

    if(0 == m_dic_lng_maps.count())
    {
        msg = QString("%1, not have valid content").arg(fullPath);
        q->Log(msg, 2);

    }
    else
    {
        msg = QString("%1, load successd").arg(fullPath);
        q->Log(msg, 1);
    }
}

void LanguageManagerPrivate::ChangeLng(QString lng_Name)
{
    LoadLngFile(m_lng_dir, lng_Name);
}

QString LanguageManagerPrivate::Tranlate(QString origin_id)
{
    QString langs = "";
    if(m_dic_lng_maps.contains(origin_id))
    {
        langs = m_dic_lng_maps[origin_id];
    }

    return  langs;
}

/******************************************************************/
LanguageManager::LanguageManager(QObject* parent) :
    QObject(parent),
    d_ptr(new LanguageManagerPrivate(this))
{
}

LanguageManager::~LanguageManager()
{
    if(nullptr == d_ptr)
    {
        delete d_ptr;
    }
}

void LanguageManager::Initialization(QString dir, QString lng_name)
{
    Q_D(LanguageManager);
    d->LoadLngFile(dir, lng_name);
}

QString LanguageManager::trs(QString orgin_id)
{
    qDebug()<<"LanguageManager::trs(" << orgin_id << ")";
    Q_D(LanguageManager);
    QString res = "";
    res = d->Tranlate(orgin_id);
    qDebug()<<"trs =" <<res;

    if(res.isNull() || res.isEmpty())
    {
        res = "#" + orgin_id + "#";
    }

    return res;
}

QString LanguageManager::curLngType()
{
    Q_D(LanguageManager);

    return d->m_lng_Type;
}

void LanguageManager::Log(QString &msg, int level, QString module_name)
{

}

void LanguageManager::OnLoadLanguage(QString lng_name)
{
    Q_D(LanguageManager);
    d->ChangeLng(lng_name);
    emit sigLanguageChanged();
}


