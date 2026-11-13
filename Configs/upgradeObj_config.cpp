#include "upgradeObj_config.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

const QString OBJ_CONFIG_FILE_NAME = "upgradeObj.json";
class UpGradeObj_ConfigPrivate
{
public:
    UpGradeObj_ConfigPrivate(UpGradeObj_Config* parent);
    virtual ~UpGradeObj_ConfigPrivate();
protected:
    bool Parse(QByteArray &jsonBtAy, QString& error_msg);
    QMap<QString, Config_Obj*> GetConfig_Objs();
    bool IsLoadOK();
private:
    void Release();
    bool Parse_Array(QJsonValue jsonObjArray, QList<Config_Obj*>& obj_list, QString &error_msg);
    bool Parse_SingleObj(QJsonValue jsonObj, Config_Obj*obj , QString &error_msg);
private:
    Q_DECLARE_PUBLIC(UpGradeObj_Config)
private:
    UpGradeObj_Config* q_ptr;
    QList<QString> m_root_module_name_list;
    QMap<QString, Config_Obj*> m_dic_config_objs;
};


UpGradeObj_ConfigPrivate::UpGradeObj_ConfigPrivate(UpGradeObj_Config *parent):
    q_ptr(parent)
{
}

UpGradeObj_ConfigPrivate::~UpGradeObj_ConfigPrivate()
{
    this->Release();
}

bool UpGradeObj_ConfigPrivate::Parse(QByteArray &jsonBtAy, QString &error_msg)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonBtAy, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        error_msg = "json error! =>" + json_error.errorString();
        return false;
    }

    //获取根{}
    QJsonArray roots = jsonDoc.array();
    // 遍历QJsonArray 数组
    for(int i = 0; i < roots.size(); i++)
    {
        QJsonObject root = roots.at(i).toObject();
        // 读取 Product
        QString product = root.value("Product").toString();
        int id = root.value("ID").toInt();
        QString prefix = root.value("Prefix").toString();
        if(product.isEmpty() || id <= 0 || prefix.isEmpty())
        {
            continue;
        }

        Config_Obj *pObj = new Config_Obj(product, id, prefix);
        m_dic_config_objs[product] = pObj;
    }

    return (m_dic_config_objs.count() > 0);
}

QMap<QString, Config_Obj *> UpGradeObj_ConfigPrivate::GetConfig_Objs()
{
    return this->m_dic_config_objs;
}

bool UpGradeObj_ConfigPrivate::IsLoadOK()
{
    return (this->m_dic_config_objs.count() > 0);
}

void UpGradeObj_ConfigPrivate::Release()
{
    if(this->m_dic_config_objs.count() > 0)
    {
        QMap<QString, Config_Obj*>::iterator iter;
        if(this->m_dic_config_objs.size()>0)
        {
            auto it=this->m_dic_config_objs.begin();

            while (it != this->m_dic_config_objs.end())
            {
                delete it.value();
                it = this->m_dic_config_objs.erase(it);
            }
        }
        //this->m_dic_config_objs.clear();
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

UpGradeObj_Config::UpGradeObj_Config() :
    d_ptr(new UpGradeObj_ConfigPrivate(this))
{
}

UpGradeObj_Config *UpGradeObj_Config::Instance()
{
    static UpGradeObj_Config inst;
    return &inst;
}

UpGradeObj_Config::~UpGradeObj_Config()
{
    delete d_ptr;
}

bool UpGradeObj_Config::Load(QString dir, QString& error_msg)
{
    Q_D(UpGradeObj_Config);
    QString filePath = dir + "//" + OBJ_CONFIG_FILE_NAME;
    if(!QFileInfo::exists(filePath))
    {
        error_msg = QString("%1 is not exist!").arg(filePath);
        return false;
    }

    QFile jsonfile(filePath);
    if (!jsonfile.open(QFile::ReadOnly | QFile::Text))
    {
        error_msg = QString("%1 can't open!").arg(filePath);
        return false;
    }

    QByteArray allData = jsonfile.readAll();
    jsonfile.close();

//    // 读取文件的全部内容
//    QTextStream jsonStream(&jsonfile);
//    jsonStream.setCodec("UTF-8");		// 设置读取编码是UTF8
//    QString jsonTotalStr = jsonStream.readAll();
//    jsonfile.close();

    return d->Parse(allData, error_msg);
}

QMap<QString, Config_Obj *> UpGradeObj_Config::GetConfig_Objs()
{
    Q_D(UpGradeObj_Config);
    return d->GetConfig_Objs();
}

quint8 UpGradeObj_Config::GetTypeID(QString objName)
{
    QMap<QString, Config_Obj*> dicmap = this->GetConfig_Objs();
    if(dicmap.contains(objName))
    {
        const Config_Obj *pObj = dicmap.value(objName);
        return pObj->GetID();
    }
    else
    {
        return -1;
    }
}

const Config_Obj *UpGradeObj_Config::GetConfigObj(QString objName)
{
    Q_D(UpGradeObj_Config);
    QMap<QString, Config_Obj*> up_obj_map = d->GetConfig_Objs();
    if(up_obj_map.contains(objName))
    {
        return up_obj_map[objName];
    }
    else
    {
        return nullptr;
    }
}


