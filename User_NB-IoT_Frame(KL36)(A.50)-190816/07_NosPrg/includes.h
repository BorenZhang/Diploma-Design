//======================================================================
//文件名称：includes.h（应用工程总头文件）
//框架提供：苏大arm技术中心(sumcu.suda.edu.cn)
//版本更新：2017.01：V1.0， 2019.02：A.12
//功能描述：（1）包含用到的构件；（2）宏常数定义；（3）自定义数据类型；（4）声明全局变量。
//        本文件共有两类代码，一类为【根据实际需要增删】，此类代码根据具体项目需求进行更改；
//        另一类为【不变】，此类代码与具体项目无关，是通用的，无需根据具体项目进行更改。
//======================================================================

#ifndef _INCLUDES_H     //防止重复定义（开头）
#define _INCLUDES_H

//----------------------------------------------------------------------
//（1）【根据实际需要增删】包含用到的构件
#include "user.h"
#include "timeStamp.h"
#include "valueType.h"



//----------------------------------------------------------------------
//（2）【根据实际需要增删】全局使用的宏常数。命名规范见注1。
#define TSI_VALUE 0x00CC0011 //触摸感应阈值（实验获得）


//----------------------------------------------------------------------
//（3）【根据实际需要增删】自定义数据类型
#pragma  pack(push,1)        //取消4字节对齐
//【不动】记录金葫芦硬件的相关配置信息，保存在flash中的信息
typedef struct FlashData
{
	//①产品信息
	uint_8 equipName[30];      //产品名称
	uint_8 equipID[20];        //产品序列号
	uint_8 equipType[20];      //产品型号
	uint_8 vendor[30];         //生产厂家
	uint_8 softVer[4];         //软件版本
	uint_64 productTime;       //生产时间（64位时间戳）
	uint_8 userName[20];       //用户名
	uint_8 phone[11];          //手机号
	//②服务器信息
	uint_8 serverIP[15];       //服务器IP
	uint_8 serverPort[5];      //服务器端口号
    //③用户存入flash的信息
	uint_32 sendFrequencySec;  //发送频率
	uint_32 resetCount;        //复位次数
	uint_8  frameCmd[2];       //命令
}FlashData;
//【根据实际需要增删】存储用户采集的数据
typedef struct UserData
{
	//【不动】这些变量为必须要有的变量
    uint_8 cmd[2];           //用户命令
	uint_16 sn;              //帧号
	uint_8 IMSI[15];         //IMSI号
	uint_8 serverIP[15];     //服务器IP
	uint_8 serverPort[5];    //服务器端口
	uint_64 currentTime;     //发送时间（64位时间戳）
	uint_32 resetCount;      //复位的次数
	uint_32 sendFrequencySec;//发送时间间隔（秒）
	//【根据实际需要增删】此处可按需要增删变量，注意与服务器端帧结构保持一致
	uint_8 userName[20];     //用户名
	uint_8 softVer[4];       //软件版本
	uint_8 equipName[30];    //产品名称
	uint_8 equipID[20];      //产品序列号
	uint_8 equipType[20];    //产品类型
	uint_8 vendor[30];       //生产厂家
	int_32 mcuTemp;          //芯片温度
	uint_8 surpBaseInfo[20]; //备注1
	uint_8 phone[11];        //手机号
	uint_8 IMEI[15];         //IMEI号
	uint_8 signalPower;      //信号强度
	uint_16 bright;          //光线亮度（光敏传感器A/D值）
	uint_16 touchNum;        //触摸按键次数（TSI）
	uint_8 surplusInfo[20];  //备注2
	uint_8 lbs_location[25];
	//【画瓢处】用户自定义添加数据
	float temp; //添加温度传感器
	uint_16 light; //添加光照传感器
	uint_8 ml; //添加添加磁场传感器
	uint_8 human; //添加人体红外传感器
	uint_16 sound; //添加声音传感器
	uint_8 engine; //电机
	uint_8 led; //led灯
	float pre_temp; //开启风扇得温度阈值
	uint_16 pre_light; //开启电灯的光照阈值
	uint_8 isAutoOpenFan; //是否开启自动打开风扇功能
	uint_8 isAutoOpenLed; //是否开启自动打开电灯功能
	//uint8_t humidity; //添加湿度传感器

}UserData;
#pragma  pack(pop)           //恢复4字节对齐

//----------------------------------------------------------------------

//（4）【根据实际需要增删】声明全局变量。命名规范见注2。
//【不动】宏定义全局变量前缀G_VAR_PREFIX。实现原理见注3。
#ifdef GLOBLE_VAR                      //GLOBLE_VAR在main.c文件中有宏定义
  #define G_VAR_PREFIX                 //前缀G_VAR_PREFIX定义为空
#else                                  //GLOBLE_VAR在非main.c文件中无定义
  #define G_VAR_PREFIX extern         //前缀G_VAR_PREFIX定义为"extern"
#endif
//（在此增加全局变量）


G_VAR_PREFIX UserData  gUserData;       //用户信息帧结构体
G_VAR_PREFIX FlashData gFlashData;      //需要写入flash中的数据
G_VAR_PREFIX uint_64   gTimeSec;        //时间戳
G_VAR_PREFIX uint_8    gTimeString[20]; //时间"2019-01-01 00:00:21/0"
G_VAR_PREFIX uint_8    gRecvBuf[1024];  //接收数据缓冲区
G_VAR_PREFIX uint_16   gRecvLength;     //接收到的数据长度
//----------------------------------------------------------------------

#endif                  //防止重复定义（结尾）


/*
 知识要素：
 注1：全局使用的宏常数，使用全大写
 注2：全局变量命名一律以g开头，尽可能保证全工程内唯一性，并且一定要注明
      其含义，（声明时不准赋值）
 注3：全局变量一处声明多处使用处理方法代码段是为了解决全局变量重复声明
 的问题，宏GLOBLE_VAR仅在main.c中声明，所以只有在main.c中包含
 本头文件时才会声明全局变量，在其他文件中包含本文件时，编译时，就会自动加
 上前缀extern，表明是main函数中声明的全局变量，该文件中直接使用。
 */
