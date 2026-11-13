#ifndef FILEPATH_H
#define FILEPATH_H
#include <QString>
#include "Core_global.h"
class CORE_EXPORT FilePath
{
public:
    explicit FilePath() {}
    virtual ~FilePath() {}
    virtual QString GetRootPath() = 0;
    virtual QString GetDataPath() = 0;
    virtual QString GetUserPath() = 0;
    virtual QString GetFactoryPath() = 0;
    virtual QString GetFactoryPresetPath() = 0;
    virtual QString GetCurrentPresetPath() = 0;
    virtual QString GetLanguagePath() = 0;
    virtual QString GetLogPath() = 0;
    virtual QString GetDumperPath() = 0;
    virtual QString GetCmdGroupPath() = 0;
    virtual QString GetConfigPath() = 0;
    virtual QString GetUpGradeFilePath() = 0;
};

#endif // FILEPATH_H
