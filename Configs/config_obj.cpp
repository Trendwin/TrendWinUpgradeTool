#include "config_obj.h"

Config_Obj::Config_Obj()
  : m_productName("Lumigenx"),
    m_TypeId(0),
    m_BinPrefix("Lumi")
{

}

Config_Obj::Config_Obj(QString product, quint8 id, QString prefix)
    : m_productName(product),
      m_TypeId(id),
      m_BinPrefix(prefix)
{

}

Config_Obj::~Config_Obj()
{

}

void Config_Obj::SetProductName(QString product)
{
    m_productName = product;
}

void Config_Obj::SetID(quint8 id)
{
    this->m_TypeId = id;
}

quint8 Config_Obj::GetID() const
{
    return this->m_TypeId;
}

void Config_Obj::SetPrefix(QString prefix)
{
    m_BinPrefix = prefix;
}

QString Config_Obj::GetPrefix() const
{
    return m_BinPrefix;
}
