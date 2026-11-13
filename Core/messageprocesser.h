#ifndef MESSAGEPROCESSER_H
#define MESSAGEPROCESSER_H

#include <QObject>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QMutex>
const quint16 MIN_FRAME_LEN = 10;

class MessageProcesserPrivate;
class MessageProcesser : public QThread
{
    Q_OBJECT
public:
    explicit MessageProcesser(QSerialPort* pSerial, QObject *parent = nullptr);
    virtual ~MessageProcesser();
    void SyncSerial(QSerialPort* pSerial);
    void SetInterestMsg(quint8 command_id);
signals:
    void sigParse();
    void sigMessageArrived(QByteArray recvArray);
    void sigInterestMsgArrived(quint8 ack);
protected slots:
    void OnReadData();
//    void OnParse();
protected:
    QString ByteArratToHexString(QByteArray recvArray);
    bool PickFrame(QByteArray &array);
    virtual void run();

private:
    bool m_bStop;
    QMutex m_mutex;
//    QThread *m_pParseThread;
    MessageProcesserPrivate* d_ptr;
    Q_DECLARE_PRIVATE(MessageProcesser)
    Q_DISABLE_COPY(MessageProcesser)
};

#endif // MESSAGEPROCESSER_H
