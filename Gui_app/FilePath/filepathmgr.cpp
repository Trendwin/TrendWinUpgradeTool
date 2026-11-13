#include "filepathmgr.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
class FilePathMgrPrivate
{
public:
    explicit FilePathMgrPrivate(FilePathMgr* parent = nullptr);
    ~FilePathMgrPrivate();
protected:
    void Initilization();
private:
    FilePathMgr* q_ptr;
    QString root_dir_;
    QString user_dir_;
    Q_DECLARE_PUBLIC(FilePathMgr)
};

FilePathMgrPrivate::FilePathMgrPrivate(FilePathMgr *parent):
    q_ptr(parent)
{
    Initilization();
}

FilePathMgrPrivate::~FilePathMgrPrivate()
{

}

void FilePathMgrPrivate::Initilization()
{
    QString run_dir = QCoreApplication::applicationDirPath();
    QDir dir(run_dir);
    if(dir.cdUp())
    {
        root_dir_ = dir.path();
        qDebug()<<"root_dir_ : " <<root_dir_;
    }

    user_dir_ = "D://LumigenxTool";
}

/***************************************************/
FilePathMgr::FilePathMgr()
{
    d_ptr= new FilePathMgrPrivate(this);
}

FilePathMgr::~FilePathMgr()
{
    if(nullptr != d_ptr)
    {
        delete d_ptr;
    }
}

QString FilePathMgr::GetRootPath()
{
    Q_D(FilePathMgr);
    return d->root_dir_;
}

QString FilePathMgr::GetDataPath()
{
    return QString("%1//%2").arg(GetRootPath(), "Data");
}

QString FilePathMgr::GetUserPath()
{
    Q_D(FilePathMgr);
    return d->user_dir_;
}

QString FilePathMgr::GetFactoryPath()
{
    return QString("%1//%2").arg(GetDataPath(), "Factory");
}

QString FilePathMgr::GetFactoryPresetPath()
{
    return QString("%1//%2").arg(GetFactoryPath(), "Preset");
}

QString FilePathMgr::GetCurrentPresetPath()
{
    return QString("%1//%2").arg(GetUserPath(), "Current");
}

QString FilePathMgr::GetLanguagePath()
{
    return QString("%1//%2").arg(GetDataPath(), "Language");
}

QString FilePathMgr::GetLogPath()
{
    return QString("%1//%2").arg(GetUserPath(), "Log");
}

QString FilePathMgr::GetDumperPath()
{
    return QString("%1//%2").arg(GetUserPath(), "Dumper");
}

QString FilePathMgr::GetCmdGroupPath()
{
    return QString("%1//%2").arg(GetDataPath(), "CmdGroup");
}

QString FilePathMgr::GetConfigPath()
{
    return QString("%1//%2").arg(GetDataPath(), "Config");
}

QString FilePathMgr::GetUpGradeFilePath()
{
    return QString("%1//%2").arg(GetDataPath(), "UpgradeBin");
}

