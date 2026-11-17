#include "systempreset.h"
#include <QDebug>
SystemPreset::SystemPreset() :
    PresetSvr("System.ini")
{
}

SystemPreset *SystemPreset::Instance()
{
    static SystemPreset inst;
    return &inst;
}

SystemPreset::~SystemPreset()
{

}

quint8 SystemPreset::GetDeviceID()
{
    bool valid = false;
    const int deviceID = GetString(CPreset::PRT_DeviceID).toInt(&valid);
    if(!valid || deviceID < 0 || deviceID > 0xFF)
    {
        return 0x02;
    }
    return static_cast<quint8>(deviceID);
}

void SystemPreset::RegisterAll()
{
    qDebug()<<"SystemPreset::RegisterAll()";

    Register(CPreset::PRT_COMM, "");
    Register(CPreset::PRT_Language, "zh_CN");
    Register(CPreset::PRT_DeviceID, 0x02, 0, 0xFF);
}


