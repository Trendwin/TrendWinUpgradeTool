#ifndef SYSVERSION_H
#define SYSVERSION_H

#include <QString>
class SysVersion
{
public:
    SysVersion();
    ~SysVersion();
    static QString GetFullVersoin();
    static QString GetBuildDateTime();
};

#endif // SYSVERSION_H
