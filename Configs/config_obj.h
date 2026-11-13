#ifndef CONFIG_OBJ_H
#define CONFIG_OBJ_H
#include <QString>
#include "Configs_global.h"

class CONFIGS_EXPORT Config_Obj
{
public:
    explicit Config_Obj();
    explicit Config_Obj(QString product, quint8 id, QString prefix);
    virtual ~Config_Obj();

    void SetProductName(QString product);
    QString GetProductName() const;

    void SetID(quint8 id);
    quint8 GetID() const;

    void SetPrefix(QString prefix);
    QString GetPrefix() const;
private:
    QString m_productName;
    quint8 m_TypeId;
    QString m_BinPrefix;
};

#endif // CONFIG_OBJ_H
