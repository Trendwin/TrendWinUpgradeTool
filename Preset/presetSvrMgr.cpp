#include "presetSvrMgr.h"
#include <QFileInfo>
#include <QDir>
#include <QStringList>
#include "systempreset.h"
#include <QDebug>
PresetSvrMgr::PresetSvrMgr(QObject *parent) : QObject(parent)
{
}

PresetSvrMgr::~PresetSvrMgr()
{
//    SystemPreset::Instance()->~SystemPreset();
}

void PresetSvrMgr::Init(QString factoryPresetPath, QString currentPresetPath)
{
    qDebug() <<"factoryPresetPath : "<<factoryPresetPath << "factoryPresetPath :"<<currentPresetPath;
    //![判定出厂目录中是否有preset的文件夹]
    bool hasFactoryPreset = HasPresetFile(factoryPresetPath);
    bool hasCurrentPreset = HasPresetFile(currentPresetPath);
    if (hasFactoryPreset && !hasCurrentPreset)
    {
        //![此时可记录日志从Factory 复制了数据 到Current]
        CopyPresetDir(factoryPresetPath, currentPresetPath, true);
    }

    InitPreset(currentPresetPath);
}

bool PresetSvrMgr::HasPresetFile(QString dirPath)
{
    QDir cdir(dirPath);
    QFileInfo finfo(dirPath);
    if (finfo.isDir() && cdir.exists())
    {
        //目录存在
        QStringList filters;
        filters << "*.ini"<<"*.xml";
        cdir.setNameFilters(filters);
        cdir.setFilter(QDir::Files | QDir::NoSymLinks);
        return (cdir.count() > 0);
    }
    else
    {
        return false;
    }
}

bool PresetSvrMgr::CopyPresetDir(const QString &source, const QString &destination, bool override)
{
    QDir directory(source);
    if (!directory.exists())
    {
         return false;
    }

    QString srcPath = QDir::toNativeSeparators(source);
    if (!srcPath.endsWith(QDir::separator()))
    {
         srcPath += QDir::separator();
    }
    QString dstPath = QDir::toNativeSeparators(destination);
    if (!dstPath.endsWith(QDir::separator()))
    {
         dstPath += QDir::separator();
    }

     bool error = false;
     QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
     for (QStringList::size_type i=0; i != fileNames.size(); ++i)
     {
         QString fileName = fileNames.at(i);
         QString srcFilePath = srcPath + fileName;
         QString dstFilePath = dstPath + fileName;
         QFileInfo fileInfo(srcFilePath);
         if (fileInfo.isFile() || fileInfo.isSymLink())
         {
             if (override)
             {
                 QFile::setPermissions(dstFilePath, QFile::WriteOwner);
             }
             QFile::copy(srcFilePath, dstFilePath);
         }
         else if (fileInfo.isDir())
         {
             QDir dstDir(dstFilePath);
             dstDir.mkpath(dstFilePath);
             if (!CopyPresetDir(srcFilePath, dstFilePath, override))
             {
                 error = true;
             }
         }
    }

    return !error;
}

void PresetSvrMgr::InitPreset(QString currentPresetPath)
{
    SystemPreset::Instance()->InitPresetDir(currentPresetPath);
}
