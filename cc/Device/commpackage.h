#ifndef COMMPACKAGE_H
#define COMMPACKAGE_H
#include "cc_global.h"
#include <QAbstractListModel>
#include "comm485data.h"

class CC_EXPORT CommPackage : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CommPackage(QObject *parent = 0);
    virtual ~CommPackage();
    void addComm(const Comm485Data &commdata);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void clear();

private:
    QList<Comm485Data> m_commDatas;
    QString m_description;

};

#endif // COMMPACKAGE_H
