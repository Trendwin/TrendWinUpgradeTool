/**********************************************************
 * 功能描述：预置数据存储单元定义
 * 作   者：方国军
 * 创建日期：2022-05-24
 * *******************************************************/
#ifndef _PRESETOBJ_H
#define _PRESETOBJ_H
#include <QString>
#include <QVariant>

class PresetObj
{
public:
    PresetObj();

    PresetObj(QString sections, QString keys, QVariant defaults, QVariant values, QVariant mins, QVariant maxs);

    ~PresetObj();

    QString GetKey() const;

    QVariant GetDefaults() const;

    QVariant GetCurValues() const;

    void SetCurValues(QVariant value);

    QVariant GetMin() const;

    QVariant GetMax() const;
private:
    QString section_Name;
    QString key;
    QVariant defaultValue;
    QVariant curValue;
    QVariant min;
    QVariant max;
};

#endif
