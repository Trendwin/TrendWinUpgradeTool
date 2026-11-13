#include "uistylemanager.h"
#include "systempreset.h"


UiStyleManager *UiStyleManager::Instance()
{
    static UiStyleManager inst;
    return &inst;
}

UiStyleManager::UiStyleManager(QObject *parent) : QObject(parent)
{

}

UiStyleManager::~UiStyleManager()
{

}

QString UiStyleManager::getFontFamily()
{
    if(0 != SystemPreset::Instance()->GetString(CPreset::PRT_Language).compare("zh_CN"))
    {
        return "Microsoft Himalaya";
    }
    else
    {
        return "宋体";
    }
}

QString UiStyleManager::getFontColor()
{
    return "black";
}

int UiStyleManager::getBigTitleFontSize()
{
    return 24;
}

int UiStyleManager::getTitleFontSize()
{
    return 20;
}

int UiStyleManager::getMenuFontSize()
{
    return 20;
}

int UiStyleManager::getNormalFontSize()
{
    return 18;
}

int UiStyleManager::getButtonFontSize()
{
    return 20;
}


