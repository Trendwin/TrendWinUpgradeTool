#ifndef CMDEXECUTOR_H
#define CMDEXECUTOR_H

#include <QObject>

class CmdExecutor : public QObject
{
    Q_OBJECT
public:
    explicit CmdExecutor(QObject *parent = nullptr);
    virtual ~CmdExecutor();

signals:
private:

};

#endif // CMDEXECUTOR_H
