/**********************************************************
 * 功能描述：基础工具类
 * 作   者：方国军
 * 创建日期：2022-06-03
 * *******************************************************/
#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QByteArray>
#include <QStringList>
#include "Utility_global.h"
namespace UUTility {

    class UTILITY_EXPORT ByteArrayTool
    {
    public:
        //![转成成16进制格式的，字符串输出，每个字符之间有空格：例：AA BB EE DD]
        static QString ByteArrayToHexString(QByteArray arrays);
        static QByteArray HexStringToByteArray(QString hex, bool* ok);
//        static QByteArray Int2ByteArray(qint32 data);
//        static QByteArray short2ByteArray(qint16 data);
    };

}

#endif // UTILITY_H
