/**********************************************************
 * 功能描述：定义指令帧的数据格式
 * 作   者：方国军
 * 创建日期：2022-08-11
 * *******************************************************/
#ifndef COMMFRAMEDATA_H
#define COMMFRAMEDATA_H
#include <qglobal.h>
#include <QByteArray>
#include <QString>
#include "crccalculater.h"

typedef struct CC_EXPORT sComFrame_t
{
    sComFrame_t& operator = (const sComFrame_t& other);

    QByteArray ToByteArray();

    quint8 fid[2];     //![帧头：固定为 0xAA 0xAA]
    quint8 dst;        //![目标地址]
    quint8 src;        //![源地址]
    quint8 len;        //![数据长度(只包含dat[])]
    quint8 nel;        //![len的长度反码，用作简单校验]
    quint8 seq;        //![帧序号，每发一次，seq增1]
    quint8 cmd;        //![命令码]
    QByteArray dat;    //![数据或命令参数，最大256]
    quint16 crc;       //![crc16校验码，对整个数据帧进行crc16运算]
}ComFrame_Def;

inline sComFrame_t &sComFrame_t::operator =(const sComFrame_t &other)
{
    if(this != &other)
    {
        this->fid[0] = other.fid[0];
        this->fid[1] = other.fid[1];
        this->dst = other.dst;
        this->src = other.src;
        this->len = other.len;
        this->nel = other.nel;
        this->seq = other.seq;
        this->cmd = other.cmd;
        this->dat.clear();
        for(int i = 0; i < other.dat.size(); ++i)
        {
            this->dat.append(other.dat.at(i));
        }

        QByteArray array = this->ToByteArray();
        this->crc = usCalcCRC(array, array.size() - 2);
    }

    return *this;
}

inline QByteArray sComFrame_t::ToByteArray()
{
    QByteArray cmdArray;
    cmdArray.append(this->fid[0]);
    cmdArray.append(this->fid[1]);
    cmdArray.append(this->dst);
    cmdArray.append(this->src);
    cmdArray.append(this->len);
    cmdArray.append(this->nel);
    cmdArray.append(this->seq);
    cmdArray.append(this->cmd);
    cmdArray.append(this->dat);
    cmdArray.append((this->crc>>8) & 0xFF);
    cmdArray.append((this->crc) & 0xFF);

    return cmdArray;
}


class CC_EXPORT ComFrameData
{
public:
    explicit ComFrameData();
    ~ComFrameData();

    void SetDst(quint8 dst);
    quint8 GetDst() const;

    void SetSrc(quint8 src);
    quint8 GetSrc() const;

    quint8 GetLen() const;

    void SetSeq(quint8 seq);
    quint8 GetSeq() const;

    void SetCmd(quint8 cmd);
    quint8 GetCmd() const;

    void SetDat(QByteArray& dat);
    QByteArray GetDat() const;
    QString DatToHexString() const;

    void SetDesc(QString desc);
    QString GetDesc() const;

    void SetComFrame(ComFrame_Def& frame);
    ComFrame_Def GetComFrame();

    QByteArray ToByteArray();

    QString PackToHexString();
    void ReCalcCRC();
private:
    QString       m_desc;
    ComFrame_Def  m_cmd;
};

#endif // COMMFRAMEDATA_H
