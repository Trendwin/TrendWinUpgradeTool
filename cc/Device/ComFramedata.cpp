#include "ComFramedata.h"
#include "cc_def.h"

ComFrameData::ComFrameData()
{
    m_cmd.fid[0] = CMD_HEAD1;
    m_cmd.fid[1] = CMD_HEAD2;
    m_cmd.seq = 0;
}

ComFrameData::~ComFrameData()
{

}

void ComFrameData::SetDst(quint8 dst)
{
    this->m_cmd.dst = dst;
}

quint8 ComFrameData::GetDst() const
{
    return this->m_cmd.dst;
}

void ComFrameData::SetSrc(quint8 src)
{
    this->m_cmd.src = src;
}

quint8 ComFrameData::GetSrc() const
{
    return this->m_cmd.src;
}

quint8 ComFrameData::GetLen() const
{
    return this->m_cmd.len;
}

void ComFrameData::SetSeq(quint8 seq)
{
    this->m_cmd.seq = seq;
}

quint8 ComFrameData::GetSeq() const
{
    return this->m_cmd.seq;
}

void ComFrameData::SetCmd(quint8 cmd)
{
    this->m_cmd.cmd = cmd;
}

quint8 ComFrameData::GetCmd() const
{
    return this->m_cmd.cmd;
}

void ComFrameData::SetDat(QByteArray &dat)
{
    this->m_cmd.dat.clear();
    for(int i = 0; i < dat.size(); ++i)
    {
        this->m_cmd.dat.append(dat.at(i));
    }

    this->m_cmd.len = dat.length();
    this->m_cmd.nel = ~dat.length();
}

QByteArray ComFrameData::GetDat() const
{
    return this->m_cmd.dat;
}

QString ComFrameData::DatToHexString() const
{
    QString arrayStr = "";
    qint16 len = this->GetDat().length();
    QByteArray ary = this->GetDat();
    for(int i = 0; i < len; ++i)
    {
        QString str;
        arrayStr += (QString::number((quint8)ary.at(i), 16).toUpper().rightJustified(2, '0') + " ");
    }

    return arrayStr;
}

void ComFrameData::SetDesc(QString desc)
{
    this->m_desc = desc;
}

QString ComFrameData::GetDesc() const
{
    return this->m_desc;
}


void ComFrameData::SetComFrame(ComFrame_Def &frame)
{
    this->m_cmd = frame;
}

ComFrame_Def ComFrameData::GetComFrame()
{
    return this->m_cmd;
}

QByteArray ComFrameData::ToByteArray()
{
    return this->m_cmd.ToByteArray();
}

QString ComFrameData::PackToHexString()
{
    QString arrayStr = "";
    QByteArray array = this->m_cmd.ToByteArray();
    qint16 len = array.length();

    for(int i = 0; i < len; ++i)
    {
        QString str;
        arrayStr += (QString::number((quint8)array.at(i), 16).toUpper().rightJustified(2, '0') + " ");
    }

    return arrayStr;
}

void ComFrameData::ReCalcCRC()
{
    QByteArray array = this->m_cmd.ToByteArray();
    this->m_cmd.crc = usCalcCRC(array, array.size() - 2);
}
