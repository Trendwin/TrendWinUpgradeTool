#include "commpackage.h"

CommPackage::CommPackage(QObject *parent):
     QAbstractListModel(parent)
{

}

CommPackage::~CommPackage()
{
    this->m_commDatas.clear();
}

void CommPackage::addComm(const Comm485Data &commdata)
{

}

int CommPackage::rowCount(const QModelIndex &parent) const
{

}

QVariant CommPackage::data(const QModelIndex &index, int role) const
{

}

void CommPackage::clear()
{

}
