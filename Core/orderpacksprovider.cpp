#include "orderpacksprovider.h"
#include <QFileInfo>
#include "loggermanager.h"
#include "Core_def.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTextStream>
const static QString PackOrderFileName = "PackOrderCfg.json";
const static QString PackRootName = "PACK_Exe_Order";
const static QString PackSubName = "PACK";

class OrderPacksProviderPrivate
{
public:
    OrderPacksProviderPrivate(OrderPacksProvider* parent);
    virtual ~OrderPacksProviderPrivate();
private:
    bool LoadPackOrder(QByteArray &jsonTotalBtAy);
    QList<GP_PKS::GP_Package>GetExeOrders();
    bool Save(QString filePathName, QList<GP_PKS::GP_Package> orderPacks);

private:
    Q_DECLARE_PUBLIC(OrderPacksProvider)
private:
    OrderPacksProvider* q_ptr;
    QList<GP_PKS::GP_Package> m_orderPacks_;
};


OrderPacksProviderPrivate::OrderPacksProviderPrivate(OrderPacksProvider *parent):
    q_ptr(parent)
{

}

OrderPacksProviderPrivate::~OrderPacksProviderPrivate()
{
    this->m_orderPacks_.clear();
}

bool OrderPacksProviderPrivate::LoadPackOrder(QByteArray &jsonTotalBtAy)
{
    Q_Q(OrderPacksProvider);
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonTotalBtAy, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        QString error_msg = "json error! =>" + json_error.errorString();
        Logs(error_msg, ErLevel::eError, Core_module)
        return false;
    }

    //获取根{}
    QJsonObject rootObj = jsonDoc.object();
    QJsonValue pack = rootObj.value(PackRootName);
    if(!pack.Null || QJsonValue::Array == pack.type())
    {
        QJsonArray objArray = pack.toArray();
        foreach(QJsonValue obj, objArray)
        {
            bool ret = false;
            QJsonObject jObjObj = obj.toObject();
            QString pk_name = jObjObj.value(PackSubName).toString();
            GP_PKS::GP_Package PK_Item = GP_PKS::StringToEnum(pk_name, &ret);
            this->m_orderPacks_.append(PK_Item);
        }
    }

    return true;
}

QList<GP_PKS::GP_Package> OrderPacksProviderPrivate::GetExeOrders()
{
    Q_Q(OrderPacksProvider);
    return this->m_orderPacks_;
}

bool OrderPacksProviderPrivate::Save(QString filePathName, QList<GP_PKS::GP_Package> orderPacks)
{
    Q_Q(OrderPacksProvider);

    // 定义根节点
    QJsonObject rootObject;
    QJsonArray packGroupObject;

    foreach(GP_PKS::GP_Package pkItem, orderPacks)
    {
        QString pk_Name = GP_PKS::EnumToString(pkItem);
        QJsonObject pkObj;
        pkObj.insert(PackSubName, pk_Name);
        packGroupObject.append(pkObj);
    }

    rootObject.insert(PackRootName, packGroupObject);

    //将Json对象里面的数据转成字符串
    QJsonDocument doc;
    //将rootobject 设置为文本文档的主要对象
    doc.setObject(rootObject);
    QFile file(filePathName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        Logs(QString("%1, Open Failed!").arg(filePathName), ErLevel::eError, Core_module);
        return false;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    // 写入文件
    stream<<doc.toJson();
    file.close();

    return true;
}



/***********************************************************************/
OrderPacksProvider::OrderPacksProvider(QObject *parent) :
    QObject(parent),
    d_ptr(new OrderPacksProviderPrivate(this))
{

}

OrderPacksProvider::~OrderPacksProvider()
{
    delete d_ptr;
    d_ptr = nullptr;
}

bool OrderPacksProvider::LoadPackOrder(QString dir)
{
    Q_D(OrderPacksProvider);
    QString filePathName = QString("%1//%2").arg(dir).arg(PackOrderFileName);
    return LoadPackOrderFromPath(filePathName);
}

bool OrderPacksProvider::LoadPackOrderFromPath(QString filepath)
{
    Q_D(OrderPacksProvider);
    if(!QFileInfo::exists(filepath))
    {
        Logs(QString("%1, is not exist!").arg(filepath), ErLevel::eError, Core_module);
        return false;
    }

    QFile jsonfile(filepath);
    if (!jsonfile.open(QFile::ReadOnly | QFile::Text))
    {
        QString error_msg = QString("%1 can't open!").arg(filepath);
        Logs(error_msg, ErLevel::eError, Core_module)
        return false;
    }

    QByteArray allData = jsonfile.readAll();
    jsonfile.close();
    return d->LoadPackOrder(allData);

}

QList<GP_PKS::GP_Package> OrderPacksProvider::GetExeOrders()
{
    Q_D(OrderPacksProvider);
    return d->GetExeOrders();
}

bool OrderPacksProvider::Save(QString dir, QList<GP_PKS::GP_Package> orderPacks)
{
    Q_D(OrderPacksProvider);
    QString filePathName = QString("%1//%2").arg(dir).arg(PackOrderFileName);
    return d->Save(filePathName, orderPacks);
}

bool OrderPacksProvider::SaveAs(QString fileName, QList<GP_PKS::GP_Package> orderPacks)
{
    Q_D(OrderPacksProvider);
    return d->Save(fileName, orderPacks);
}

QString OrderPacksProvider::GetFileSaveName()
{
    return PackOrderFileName;
}


