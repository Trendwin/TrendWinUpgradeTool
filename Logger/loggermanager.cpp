#include "loggermanager.h"
#include <QDateTime>
#include "logger.h"
#include "LoggerLevel.h"
#include <QDir>
#include <QDebug>
LoggerManager *LoggerManager::Instance()
{
    static LoggerManager inst;
    return &inst;
}

LoggerManager::LoggerManager():
    pLog_(nullptr),
    rootDir_("")
{
}

LoggerManager::~LoggerManager()
{
    if(nullptr != pLog_)
    {
        delete pLog_;
    }

    if(nullptr != pADLog_)
    {
        delete pADLog_;
    }
}

void LoggerManager::Initialization(QString rootDir)
{
    TryToChangeLogHandle(rootDir);
}

void LoggerManager::Log(QString msg, int level, QString modeule_name)
{
    TryToChangeLogHandle(rootDir_);
    ErLevel::Level lv = (ErLevel::Level)level;
    QString strLv = ErLevel::ToString(lv);
    Logger* logHander = this->GetLogHander(lv);
    logHander->Write(msg, modeule_name, strLv);
}

void LoggerManager::TryToChangeLogHandle(QString rootDir)
{
    this->rootDir_ = rootDir;
    QDateTime qtime = QDateTime::currentDateTime();
    QString qYear = qtime.toString("yyyy");
    QString qYearMonth = qtime.toString("yyyy-MM");
    QString qYMD = qtime.toString("yyyy-MM-dd");
    QString fullDir = QString("%1//%2//%3").arg(rootDir, qYear, qYearMonth);
    QDir logDir(fullDir);
    if(!logDir.exists())
    {
        logDir.mkpath(fullDir);
    }

    if(nullptr == pLog_)
    {
        pLog_ = new Logger(fullDir,"");
    }
    else
    {
        if( 0 != QString::compare( pLog_->GetFileName(), qYMD))
        {
            qDebug()<<"fullname"<<pLog_->GetFileName()<<":"<<fullDir<<"\r\n";
            delete pLog_;
            pLog_ = new Logger(fullDir,"");
        }
    }

    if(nullptr == pADLog_)
    {
        pADLog_ = new Logger(fullDir, "AD_");
    }
    else
    {
        if( 0 != QString::compare( pADLog_->GetFileName(), qYMD))
        {
            qDebug()<<"fullname"<<pADLog_->GetFileName()<<":"<<fullDir<<"\r\n";
            delete pADLog_;
            pADLog_ = new Logger(fullDir,"AD_");
        }
    }
}

Logger *LoggerManager::GetLogHander(ErLevel::Level level)
{
    if(ErLevel::Level::eAD == level)
    {
        return this->pADLog_;
    }
    else
    {
        return this->pLog_;
    }
}
