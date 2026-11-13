/**********************************************************
 * 功能描述：写日志文件类定义
 * 作   者：方国军
 * 创建日期：2022-05-23
 * *******************************************************/
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QString fullDir, QString prefix, QObject *parent = nullptr);
    virtual ~Logger();
    QString GetFileName();
    void Write(QString& msg, QString level, QString module_name);
protected:
    void SetLogFilePathDir(QString dirPath);
signals:
protected:

private:

QString fileName_;
QString filePathName_;
QFile* pFile_;
QString aPrefix_;

};

#endif // LOGGER_H
