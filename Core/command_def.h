#ifndef COMMAND_DEF_H
#define COMMAND_DEF_H


#include <QtGlobal>
#include "cc_def.h"

//#define PROTOCOL_VER           1  // 协议版本号1.0
//#define DEVICE_ID              2  // 设备类型ID
//// 接收指令段相对偏移地址定义
//#define ADR_HD_DEV_ID          2  // 设备类型
//#define ADR_HD_ADDI            3  // 头附加内容
//#define ADR_TOTAL_LEN          4  // 总帧长
//#define ADR_CMD_ID             6  // 指令ID
//#define ADR_ACK_ID             7  // ACK码
//#define ADR_CMD_LEN            8  // 数据体长度
//#define ADR_DATA              10  // 数据体

const uint8_t REV_HEADS[2] = {CMD_HEAD1, CMD_HEAD2};

/* typedef ------------------------------------------------------------------*/

//![设备ID定义]
//typedef enum
//{
//    Dev_Master     = 0x01,  //![主控板-PC]
//    Dev_Driver     = 0x02,  //![功率驱动板]
//    Dev_COMM       = 0x03,  //![通讯拓展板]
//    Dev_TrComUart0 = 0x80,  //![通讯透传1]
//    Dev_TrComUart1 = 0x81,  //![通讯透传2]
//}DevIDDef;

////- 指令ID 定义 -/
//typedef enum
//{
//    CMD_Program_Update_Start   = 0x71,   //升级启动
//    CMD_Program_Update         = 0x72,   //升级数据
//    CMD_Program_Update_End     = 0x73,   //数据传输接收
//    CMD_Program_Update_Status  = 0x74,   //程序更新状态查询命令
//}COMMAND_ID_Def;

//typedef enum
//{
//    ACK_OK    = 0, // 正常
//    ACK_ER    = 1, // 异常
//}ACK_ID_Def;
// 附加头定义
typedef struct
{
    quint8 : 2;      // 保留
    quint8 ver: 2;   // 版本号
    quint8 : 4;      // 保留
}Addi_Bits_t;

typedef union
{
    Addi_Bits_t bit;
    quint8      all;
}Addi_Def;


//- 指令协议头 -/
typedef struct
{
    uint8_t head[2];
    uint8_t devId;
    Addi_Def additon;
}Pro_Head;

typedef struct
{
    uint16_t len;
    uint8_t  dataBuf[1040];
}USB_DATA;

// 接收数据的通讯格式
typedef struct
{
    Pro_Head   head;      // 协议头
    uint16_t   len;       // 协议总长度
    uint8_t    comandId;  // 指令ID
    USB_DATA   data;      // 数据体：包含长度，和数据内容
    uint16_t   crc;
}USB_Message_recv_Def;




#endif // COMMAND_DEF_H


