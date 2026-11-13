/**********************************************************
 * 功能描述：系统预置类定义
 * 作   者：方国军
 * 创建日期：2022-05-25
 * *******************************************************/
#ifndef SYSTEMPRESET_H
#define SYSTEMPRESET_H

#include "presetsvr.h"
#include "Preset_global.h"
#include "PresetItemDef.h"
class PRESET_EXPORT SystemPreset : public PresetSvr
{
public:
    static SystemPreset *Instance();
    virtual ~SystemPreset();
    void Release();
protected:
    virtual void RegisterAll();

private:
    SystemPreset();
};

#endif // SYSTEMPRESET_H
