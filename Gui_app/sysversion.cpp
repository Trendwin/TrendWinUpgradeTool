#include "sysversion.h"
#include "svn_version.h"
const quint8 MajVerion = 0;
const quint8 midVersion = 0;
const quint8 minVersion = 8;

SysVersion::SysVersion()
{

}

SysVersion::~SysVersion()
{

}

QString SysVersion::GetFullVersoin()
{
    return QString("%1.%2.%3").arg(MajVerion).arg(midVersion).arg(minVersion);
//    return QString("%1.%2.%3.%4").arg(MajVerion).arg(midVersion).arg(minVersion).arg(sSvnVer);
}

QString SysVersion::GetBuildDateTime()
{
    return sBuildData;
}
