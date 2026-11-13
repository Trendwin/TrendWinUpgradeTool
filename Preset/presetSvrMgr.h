/**********************************************************
 * 功能描述：预置服务器管理类定义
 * 作   者：方国军
 * 创建日期：2022-05-25
 * *******************************************************/
#ifndef PRESETSRMGR_H
#define PRESETSRMGR_H

#include <QObject>
#include "Preset_global.h"
class PRESET_EXPORT PresetSvrMgr : public QObject
{
    Q_OBJECT
public:
    explicit PresetSvrMgr(QObject *parent = nullptr);
    virtual ~PresetSvrMgr();
    void Init(QString factoryPresetPath, QString currentPresetPath);
protected:
    bool HasPresetFile(QString dirPath);
    bool CopyPresetDir(const QString &source, const QString &destination, bool override);
    void InitPreset(QString currentPresetPath);
signals:

};

#endif // PRESETSRMGR_H
