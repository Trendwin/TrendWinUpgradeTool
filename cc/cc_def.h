#ifndef CC_DEF_H
#define CC_DEF_H
#include <QString>
static const QString CC_module = "CC";

#define CMD_HEAD1    0xAA
#define CMD_HEAD2    0xAA


#define ADR_DEVICE_ID          2  // 设备类型ID
#define ADR_DEVICE_DST         2  // 目标设备ID
#define ADR_DEVICE_SRC         3  // 源设备ID
#define ADR_DATA_LEN           4  // 指令数据体长度
#define ADR_CMD_SEQ            6  // 指令序号
#define ADR_FUNCTION_ID        7  // 指令功能ID
#define ADR_DATA               8  // 数据体部分

//![设备ID定义]
typedef enum
{
    Dev_Master     = 0x01,  //![主控板]
    Dev_Driver     = 0x02,  //![功率驱动板]
    Dev_COMM       = 0x03,  //![通讯拓展板]
    Dev_TrComUart0 = 0x80,  //![通讯透传1]
    Dev_TrComUart1 = 0x81,  //![通讯透传2]
}DevIDDef;

typedef enum
{
    CMD_DeviceImfo_Query       = 0x04,   //![设备信息查询]
    CMD_Program_Update_Start   = 0x71,   //![升级启动]
    CMD_Program_Update         = 0x72,   //![升级数据]
    CMD_Program_Update_End     = 0x73,   //![数据传输接收]
    CMD_Program_Update_Status  = 0x74,   //![程序更新状态查询命令]
}COMMAND_ID_Def;

typedef enum
{
    ACK_OK    = 0, // 正常
    ACK_ER    = 1, // 异常
}ACK_ID_Def;

#endif // CC_DEF_H
