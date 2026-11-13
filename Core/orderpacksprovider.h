#ifndef ORDERPACKSPROVIDER_H
#define ORDERPACKSPROVIDER_H

#include <QObject>
#include "Core_global.h"
#include <PackageDef.h>

class OrderPacksProviderPrivate;
class CORE_EXPORT OrderPacksProvider : public QObject
{
    Q_OBJECT
public:
    explicit OrderPacksProvider(QObject *parent = nullptr);
    virtual ~OrderPacksProvider();
    bool LoadPackOrder(QString dir);
    bool LoadPackOrderFromPath(QString filepath);
    QList<GP_PKS::GP_Package> GetExeOrders();
    bool Save(QString dir, QList<GP_PKS::GP_Package> orderPacks);
    bool SaveAs(QString fileName, QList<GP_PKS::GP_Package> orderPacks);
    static QString GetFileSaveName();
signals:
private:
    OrderPacksProviderPrivate* d_ptr;
    Q_DECLARE_PRIVATE(OrderPacksProvider)
    Q_DISABLE_COPY(OrderPacksProvider)
};

#endif // ORDERPACKSPROVIDER_H
