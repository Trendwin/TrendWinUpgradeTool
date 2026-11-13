#include "devicebase.h"
#include "commserials.h"
DeviceBase::DeviceBase(CommSerials *comSerials, QObject *parent) :
    QObject(parent),
    pCom_serials_(comSerials)
{
    connect(this, &DeviceBase::sigWriteCmd, comSerials, &CommSerials::OnWrite);
}

DeviceBase::~DeviceBase()
{

}

int DeviceBase::ExecuteCmd(QByteArray &cmdBytes, int ms_time_out)
{
    int ret = 0;
    emit sigWriteCmd(cmdBytes, ms_time_out, ret);
    return ret;
}
