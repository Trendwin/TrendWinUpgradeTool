#include "presetsvr.h"
#include "presetObj.h"
#include <QSettings>
#include <QTextCodec>
#include <QDebug>
QString COMM_SECTION_NAME = "General";

class PresetSvrPrivate
{
public:
    explicit PresetSvrPrivate(QString fileName, PresetSvr *parent);
    ~PresetSvrPrivate();
protected:
    void Initliaztion(QString dir);
    void Register(QString section, QString key, QVariant defaultValue, QVariant min, QVariant max);
    QString GetSect_key_Names(QString Section, QString key);

    void Loads();

    PresetObj* Read(QString Section, QString key);
    bool Write(QString Section, QString key, QVariant value);
private:
    PresetSvr* q_ptr;
    QSettings *iniRWer;
    QMap<QString, PresetObj*> dicPrestObjs;
    QString fileName_;
    QString filePathName_;
    Q_DECLARE_PUBLIC(PresetSvr)
};


PresetSvrPrivate::PresetSvrPrivate(QString fileName, PresetSvr *parent):
    q_ptr(parent),
    fileName_(fileName)
{
}

PresetSvrPrivate::~PresetSvrPrivate()
{
    if(nullptr != iniRWer)
    {
        delete iniRWer;
        iniRWer = nullptr;
    }

    qDeleteAll(dicPrestObjs);
    dicPrestObjs.clear();
}

void PresetSvrPrivate::Initliaztion(QString dir)
{
    filePathName_ = QString("%1//%2").arg(dir, fileName_);
    iniRWer = new QSettings(filePathName_, QSettings::IniFormat);
    iniRWer->setIniCodec(QTextCodec::codecForName("UTF-8"));
}

void PresetSvrPrivate::Register(QString section, QString key, QVariant defaultValue, QVariant min, QVariant max)
{
    QString sec_keys = GetSect_key_Names(section, key);
    PresetObj *obj = new PresetObj(section, key, defaultValue, defaultValue, min, max);
    dicPrestObjs[sec_keys] = obj;
    qDebug()<<"PresetSvrPrivate::Register:" <<sec_keys;
}

QString PresetSvrPrivate::GetSect_key_Names(QString Section, QString key)
{
    return QString("/%1/%2").arg(Section, key);
}

void PresetSvrPrivate::Loads()
{
    qDebug()<<"PresetSvrPrivate::Loads() Start.";
    QMap<QString, PresetObj*>::Iterator iter = dicPrestObjs.begin();
    for (iter = dicPrestObjs.begin(); iter != dicPrestObjs.end(); ++iter)
    {
        QString sec_key = iter.key();
        PresetObj* obj = iter.value();
        QString strvalue = iniRWer->value(sec_key).toString();
        QVariant value = iniRWer->value(sec_key).toString();
        if(value.isValid())
        {
            obj->SetCurValues(value);
        }
//        qDebug()<<"sec_key : " <<sec_key <<"; value : " <<value;
    }
}

PresetObj *PresetSvrPrivate::Read(QString Section, QString key)
{
    PresetObj *obj = nullptr;
    QString sec_key = GetSect_key_Names(Section, key);
    if(dicPrestObjs.contains(sec_key))
    {
        obj = dicPrestObjs[sec_key];
    }

    return obj;
}

bool PresetSvrPrivate::Write(QString Section, QString key, QVariant value)
{
    bool ret = false;
    QString sec_key = GetSect_key_Names(Section, key);
    if(dicPrestObjs.contains(sec_key))
    {
        PresetObj *obj = dicPrestObjs[sec_key];
        obj->SetCurValues(value);
        iniRWer->setValue(sec_key, value.toString());
        ret = true;
    }

    return ret;
}

/***************************************************************/

PresetSvr::PresetSvr(QString fileName)
{
    d_ptr = new PresetSvrPrivate(fileName, this);
}

PresetSvr::~PresetSvr()
{
    if(nullptr != d_ptr)
    {
        delete d_ptr;
    }
}

int PresetSvr::GetInt(CPreset::Key key)
{
    return GetInt(COMM_SECTION_NAME, key);
}

int PresetSvr::GetInt(QString Section, CPreset::Key key)
{
    QVariant data = GetData(Section, key);
    return data.toInt();
}

bool PresetSvr::GetBool(CPreset::Key key)
{
    return GetBool(COMM_SECTION_NAME, key);
}

bool PresetSvr::GetBool(QString Section, CPreset::Key key)
{
    QVariant data = GetData(Section, key);
    return data.toBool();
}

bool PresetSvr::GetDouble(CPreset::Key key)
{
    return GetDouble(COMM_SECTION_NAME, key);
}

bool PresetSvr::GetDouble(QString Section, CPreset::Key key)
{
    QVariant data = GetData(Section, key);
    return data.toDouble();
}

QString PresetSvr::GetString(CPreset::Key key)
{
    return GetString(COMM_SECTION_NAME, key);
}

QString PresetSvr::GetString(QString Section, CPreset::Key key)
{
    QVariant data = GetData(Section, key);
    return data.toString();
}

bool PresetSvr::SetValue(CPreset::Key key, QVariant value)
{
   return  SetValue(COMM_SECTION_NAME, key, value);
}

bool PresetSvr::SetValue(QString Section, CPreset::Key key, QVariant value)
{
    //![不做判定是否查询到，有问题直接dump]
    Q_D(PresetSvr);
    return d->Write(Section, CPreset::EnumToString(key), value);
}

void PresetSvr::InitPresetDir(QString dir)
{
    Q_D(PresetSvr);
    d->Initliaztion(dir);
    //![完成注册]
    RegisterAll();
    //![加载所有数据到内存]
    d->Loads();
}

bool PresetSvr::GetMinMax(QString Section, CPreset::Key key, int &min, int &max)
{
    bool ret = false;
    Q_D(PresetSvr);
    PresetObj *obj = d->Read(Section, CPreset::EnumToString(key));
    if(nullptr != obj)
    {
        min = obj->GetMin().toInt();
        max = obj->GetMax().toInt();
        ret = true;
    }

    return ret;
}

bool PresetSvr::GetMinMax(QString Section, CPreset::Key key, double &min, double &max)
{
    bool ret = false;
    Q_D(PresetSvr);
    PresetObj *obj = d->Read(Section, CPreset::EnumToString(key));
    if(nullptr != obj)
    {
        min = obj->GetMin().toDouble();
        max = obj->GetMax().toDouble();
        ret = true;
    }

    return ret;
}

void PresetSvr::Initializing(QString dir)
{
    Q_D(PresetSvr);
    d->Initliaztion(dir);
    //![完成注册]
    RegisterAll();
    //![加载所有数据到内存]
    d->Loads();
}

void PresetSvr::Register(CPreset::Key key, QVariant defaultValue, QVariant min, QVariant max)
{
    Register(COMM_SECTION_NAME, key, defaultValue, min, max);
}

void PresetSvr::Register(QString section, CPreset::Key key, QVariant defaultValue, QVariant min, QVariant max)
{
    Q_D(PresetSvr);

    d->Register(section, CPreset::EnumToString(key), defaultValue, min, max);
}

QVariant PresetSvr::GetData(QString Section, CPreset::Key key)
{
    Q_D(PresetSvr);
    PresetObj *obj = d->Read(Section, CPreset::EnumToString(key));
    if(!obj->GetCurValues().isNull())
    {
        return obj->GetCurValues();
    }
    else
    {
        return obj->GetDefaults();
    }
}


