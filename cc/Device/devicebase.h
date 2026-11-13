#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include <QObject>
class CommSerials;

class DeviceBase : public QObject
{
    Q_OBJECT
public:
    explicit DeviceBase(CommSerials* comSerials, QObject *parent = nullptr);
    virtual ~DeviceBase();

protected:
    virtual void Initilazation() = 0;

    virtual void SaftStop() = 0;

    int ExecuteCmd(QByteArray& cmdBytes, int ms_time_out);

signals:
    void sigWriteCmd(QByteArray& cmdBytes, int ms_time_out, int&ret);
private:

    CommSerials* pCom_serials_;
};

#endif // DEVICEBASE_H
