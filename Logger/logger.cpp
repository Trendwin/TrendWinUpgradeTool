#include "logger.h"
#include <QDateTime>
#include <QDir>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>
Logger::Logger(QString fullDir, QString prefix, QObject *parent) :
    QObject(parent),
    fileName_(""),
    filePathName_(""),
    pFile_(nullptr),
    aPrefix_(prefix)
{
    SetLogFilePathDir(fullDir);
}

Logger::~Logger()
{
    if(nullptr != pFile_)
    {
        if(pFile_->isOpen())
        {
            pFile_->flush();
            pFile_->close();
        }

        delete pFile_;

        qDebug()<<"Logger::~Logger()"<<"\r\n";
    }
}

QString Logger::GetFileName()
{
    return fileName_;
}

void Logger::Write(QString &msg, QString level, QString module_name)
{
    QString qstrTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh::mm::ss::zzz");
    QTextStream out(pFile_);
    out.setCodec("UTF-8");
    out<<qstrTime<<"["<<module_name<<"]"<<"["<<level<<"]"<<":"<<msg<<"\n";
    out.flush();

    qDebug()<<"log: "<<msg;
}

void Logger::SetLogFilePathDir(QString dirPath)
{
    bool ret = true;
    QString qstrTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    fileName_ = qstrTime;
    filePathName_ = QString("%1//%2%3.log").arg(dirPath).arg(aPrefix_).arg(fileName_);
    QDir dir(dirPath);
    if(!dir.exists())
    {
        ret = dir.mkdir(dirPath);
    }

    if (ret)
    {
        pFile_ = new QFile(filePathName_);
        if(!pFile_->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            delete pFile_;
            pFile_ = nullptr;
            qDebug()<<"Log file Name:"<<filePathName_<<"falied";

        }
        qDebug()<<"Log file Name:"<<filePathName_<<"handle::"<<pFile_;
    }
}
