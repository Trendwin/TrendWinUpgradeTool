#include "presetObj.h"

PresetObj::PresetObj()
{
    section_Name = "";
    key = "";
    defaultValue = "";
    curValue = "";
    min = "";
    max = "";

}

PresetObj::PresetObj(QString sections, QString keys, QVariant defaults, QVariant values, QVariant mins, QVariant maxs)
{
    section_Name = sections;
    key = keys;
    defaultValue = defaults;
    curValue = values;
    min = mins;
    max = maxs;
}

PresetObj::~PresetObj()
{

}

QString PresetObj::GetKey() const
{
    return key;
}

QVariant PresetObj::GetDefaults() const
{
    return defaultValue;
}

QVariant PresetObj::GetCurValues() const
{
    return curValue;
}

void PresetObj::SetCurValues(QVariant value)
{
    curValue = value;
}

QVariant PresetObj::GetMin() const
{
    return min;
}

QVariant PresetObj::GetMax() const
{
    return max;
}

