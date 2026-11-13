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

void SystemPreset::RegisterAll()
{
    qDebug()<<"SystemPreset::RegisterAll()";

    Register(CPreset::PRT_COMM, "");
    Register(CPreset::PRT_Language, "zh_CN");
}


