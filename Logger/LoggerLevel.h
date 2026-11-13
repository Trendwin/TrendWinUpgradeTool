/**********************************************************
 * 功能描述：日志级别定义
 * 作   者：方国军
 * 创建日期：2022-05-23
 * *******************************************************/
#ifndef LOGGERLEVEL_H
#define LOGGERLEVEL_H
#include <QObject>
#include <QMetaEnum>

class ErLevel : public QObject
{
    Q_OBJECT
public:
    enum Level
    {
        eDebug = 0,   //![调试日志，RELEASE 版本不会记录]
        eAD,          //![AD采集]
        eTrace,       //![一般性跟踪日志]
        eError,       //![故障日志]
        eCritical,    //![崩溃日志]
    };
    Q_ENUM(Level)

   static QString ToString(Level lv)
   {
       QMetaEnum metas = QMetaEnum::fromType<ErLevel::Level>();
       return QString(metas.valueToKey(lv));
   }

   static Level ToEnum(QString strlev, bool& ret)
   {
       QMetaEnum metas = QMetaEnum::fromType<ErLevel::Level>();
       return (ErLevel::Level)metas.keyToValue(strlev.toStdString().data(), &ret);
   }
};


#endif // LOGGERLEVEL_H
