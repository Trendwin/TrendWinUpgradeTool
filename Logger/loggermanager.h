/**********************************************************
 * 功能描述：日志管理器定义
 * 作   者：方国军
 * 创建日期：2022-05-23
 * *******************************************************/
#ifndef LOGGERMANAGER_H
#define LOGGERMANAGER_H
#include <QString>
#include "LoggerManager_global.h"
#include "LoggerLevel.h"
class Logger;

#define LogMgr LoggerManager::Instance()
#define Logs(message, level, module) {\
    QString nal = QString("%1\nFUNC: %2, LINE: %3, FILE: %4").arg(message).arg(__FUNCTION__).arg(__LINE__).arg(__FILE__); \
    LogMgr->Log(nal, level, module); } \

#define AD_Log(message, module) {\
    LogMgr->Log(message, ErLevel::eAD, module); } \

class LOGGER_EXPORT LoggerManager
{
public:
    static LoggerManager* Instance();
    virtual ~LoggerManager();
    void Initialization(QString rootDir);
    void Log(QString msg, int level, QString modeule_name);

protected:
    void TryToChangeLogHandle(QString rootDir);
    Logger* GetLogHander(ErLevel::Level level);
private:
    explicit LoggerManager();
    Logger* pLog_;
    Logger* pADLog_;
    QString rootDir_;
};

#endif // LOGGERMANAGER_H
