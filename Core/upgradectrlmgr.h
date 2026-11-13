#ifndef UPGRADECTRLMGR_H
#define UPGRADECTRLMGR_H

#include <QObject>
#include "Core_global.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "messageprocesser.h"

class UpGradeCtrlMgrPrivate;
class CORE_EXPORT UpGradeCtrlMgr : public QObject
{
    Q_OBJECT
public:
    enum UpGrade_Result_Def
    {
        UPG_SUC              = 0x00,
        UPG_DATA_TRANS       = 0x01,
        UPG_FILE_NOT_EXIST   = 0x02,
        UPG_FILE_OPEN_FAILED = 0x03,
        UPG_TIMEOUT          = 0x04,
        UPG_COMPORT_CLOSED   = 0x05,
        UPG_USER_TERMINATED  = 0x06,
    };
    Q_ENUM(UpGrade_Result_Def);

    explicit UpGradeCtrlMgr(QObject *parent = nullptr);
    virtual ~UpGradeCtrlMgr();
    QStringList GetComPortList();
    bool OpenComPort(QString com);
    bool CloseComPort();
    bool IsComPortOpened();
public slots:
    void onStartInstrUpgrade(QString upgradeFileName, quint8 devId);
    void onTerminateUpgrade();
    void onQueryDevVersionInfo(quint8 devId);
signals:
    void sigComPortStateChanged(QString& portName, bool isOpened);
    void sigUpGradeResult(UpGrade_Result_Def up_result);
    void sigUpdateProgress(quint8 percentage);
    void sigUpdateUpgardeInfo(quint16 totalPacks, quint16 curSucPacks);
    void sigArrivedMesg(QByteArray msg);
protected:
    bool StartUpgrade(quint8 devId, quint32 totalBytes,  quint32 time_out_ms);
    bool StartUpgradeTran(quint8 devId, quint16 pack_No, QByteArray binArray, quint8 max_trytimes, quint32 per_time_out_ms);
    bool FinishUpgradeTran(quint8 devId, quint32 totalSum, quint8 max_trytimes, quint32 time_out_ms);
    void Init();
    bool SendPro(quint8 dstId, uint8_t command_ID, QByteArray &array, quint32 time_out_ms);
private:
    UpGradeCtrlMgrPrivate* d_ptr;
    Q_DECLARE_PRIVATE(UpGradeCtrlMgr)
    Q_DISABLE_COPY(UpGradeCtrlMgr)
};

#endif // UPGRADECTRLMGR_H
