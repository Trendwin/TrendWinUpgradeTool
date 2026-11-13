#ifndef UPGRADEOBJ_CONFIG_H
#define UPGRADEOBJ_CONFIG_H

#include <QString>
#include <QMap>
#include "Configs_global.h"
#include "config_obj.h"

class UpGradeObj_ConfigPrivate;

class CONFIGS_EXPORT UpGradeObj_Config
{
public:
    static UpGradeObj_Config* Instance();
    virtual ~UpGradeObj_Config();
    bool Load(QString dir, QString& error_msg);
    QMap<QString, Config_Obj*> GetConfig_Objs();
    quint8 GetTypeID(QString objName);
    const Config_Obj* GetConfigObj(QString objName);

protected:
private:
    explicit UpGradeObj_Config();
private:
    UpGradeObj_ConfigPrivate* d_ptr;
    Q_DECLARE_PRIVATE(UpGradeObj_Config)
    Q_DISABLE_COPY(UpGradeObj_Config)
};

#endif // UPGRADEOBJ_CONFIG_H
