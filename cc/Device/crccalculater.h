/**********************************************************
 * 功能描述：CRC 16 校验计算
 * 作   者：方国军
 * 创建日期：2024-08-11
 * *******************************************************/
#ifndef CRCCALCULATER_H
#define CRCCALCULATER_H
#include <QByteArray>
#include "cc_global.h"


CC_EXPORT quint16 usCalcCRC(QByteArray& arrays, quint32 uSize);

CC_EXPORT quint16 usCalcCRC(quint8 * pucData, quint32 uSize);

CC_EXPORT quint32 ucCalcSum(quint8 * pucData, quint32 uSize);
#endif // CRCCALCULATER_H
