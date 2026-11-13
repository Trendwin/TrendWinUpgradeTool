/**********************************************************
 * 功能描述：预置参数项定义
 * 作   者：方国军
 * 创建日期：2022-05-24
 * *******************************************************/
#ifndef PRESETITEMDEF_H
#define PRESETITEMDEF_H
#include <QObject>
#include <QMetaEnum>
#include <QString>
#include "Preset_global.h"

class PRESET_EXPORT CPreset : public QObject
{
    Q_OBJECT

public:
    enum Key
    {
        //![存储到下位机字段]
        PRT_ST_MCU_BEG = 0,
        PRT_Bright,                 //![亮度]
        PRT_Exposure,               //![曝光值]
        PRT_Gain,                   //![增益]

        PRT_LEN,                    //![物镜类型]

        //![存储到下位机字段结束]
        PRT_ST_MCU_END,
        //![非存储到下位机字段开始]
        PRT_COMM,                  //![串口号]
        PRT_AD_COMM,               //![AD模块串口号]
        PRT_Language,              //![语言]
    };
    Q_ENUM(Key)

    static QString EnumToString(CPreset::Key enums)
    {
        QMetaEnum tenum = QMetaEnum::fromType<CPreset::Key>();
        return QString(tenum.valueToKey(enums));
    }

    static CPreset::Key StringToEnum(QString strKey, bool* ret = nullptr)
    {
        QMetaEnum tenum = QMetaEnum::fromType<CPreset::Key>();
        return (CPreset::Key)tenum.keyToValue(strKey.toStdString().data(), ret);
    }
};


#endif // PRESETITEMDEF_H
