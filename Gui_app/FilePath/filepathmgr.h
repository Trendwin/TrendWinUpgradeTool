#ifndef FILEPATHMGR_H
#define FILEPATHMGR_H

#include "FilePath.h"
class FilePathMgrPrivate;
//class FilePathMgr : public FilePath
class FilePathMgr
{
public:
    explicit FilePathMgr();
    virtual ~FilePathMgr();
    virtual QString GetRootPath();
    virtual QString GetDataPath();
    virtual QString GetUserPath();
    virtual QString GetFactoryPath();
    virtual QString GetFactoryPresetPath();
    virtual QString GetCurrentPresetPath();
    virtual QString GetLanguagePath();
    virtual QString GetLogPath();
    virtual QString GetDumperPath();
    virtual QString GetCmdGroupPath();
    virtual QString GetConfigPath();
    virtual QString GetUpGradeFilePath();

private:
    Q_DECLARE_PRIVATE(FilePathMgr)
    Q_DISABLE_COPY(FilePathMgr)
    FilePathMgrPrivate* d_ptr;
};

#endif // FILEPATHMGR_H
