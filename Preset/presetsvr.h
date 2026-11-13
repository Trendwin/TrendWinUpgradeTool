/**********************************************************
 * 功能描述：预置服务器基类定义
 * 作   者：方国军
 * 创建日期：2022-05-25
 * *******************************************************/
#ifndef PRESETSVR_H
#define PRESETSVR_H
#include <QObject>
#include "presetObj.h"
#include "PresetItemDef.h"
#include "Preset_global.h"
#include <QSettings>
#include <QVariant>
#include <QString>
#include <QMap>
class PresetSvrPrivate;
class PRESET_EXPORT PresetSvr
{
public:
    PresetSvr(QString fileName);
    virtual ~PresetSvr();

    //![不指定Section，则使用默认的General]
    int GetInt(CPreset::Key key);
    int GetInt(QString Section, CPreset::Key key);

    //![不指定Section，则使用默认的General]
    bool GetBool(CPreset::Key key);
    bool GetBool(QString Section, CPreset::Key key);

    //![不指定Section，则使用默认的General]
    bool GetDouble(CPreset::Key key);
    bool GetDouble(QString Section, CPreset::Key key);

    //![不指定Section，则使用默认的General]
    QString GetString(CPreset::Key key);
    QString GetString(QString Section, CPreset::Key key);

    //![不指定Section，则使用默认的General]
    bool SetValue(CPreset::Key key, QVariant value);
    bool SetValue(QString Section, CPreset::Key key, QVariant value);

    //![初始化预置目录]
    void InitPresetDir(QString dir);

    bool GetMinMax(QString Section, CPreset::Key key, int& min, int& max);
    bool GetMinMax(QString Section, CPreset::Key key, double& min, double& max);

protected:
    void Initializing(QString dir);
    virtual void RegisterAll() = 0;
    void Register(CPreset::Key key, QVariant defaultValue, QVariant min = "", QVariant max = "");
    void Register(QString section, CPreset::Key key, QVariant defaultValue, QVariant min = "", QVariant max = "");

    QString GetSect_key_Names(QString Section, CPreset::Key key);
    QString Read(QString Section, CPreset::Key key);

    QVariant GetData(QString Section, CPreset::Key key);
private:
    PresetSvrPrivate* d_ptr;
    Q_DECLARE_PRIVATE(PresetSvr)
    Q_DISABLE_COPY(PresetSvr)
};

#endif // PRESETSVR_H
