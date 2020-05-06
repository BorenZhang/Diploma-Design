//=====================================================================
//文件名称：uart.h
//功能概要：uart底层驱动构件头文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：KL25、KL26、KL36
//=====================================================================

#ifndef _UART_H         //防止重复定义（ 开头)
#define _UART_H

#include "common.h"    //包含公共要素头文件

//选用自己的驱动还是BIOS内驱动宏定义
#define BIOS_UART (1)  //是（0）使用自己驱动，是（1）使用BIOS内驱动

//#if 条件编译（开始）
#if (BIOS_UART==0)     //是（0），使用自己驱动，编译以下声明

//======================================================================
//函数名称：uart_init
//功能概要：初始化uart模块
//参数说明：uartNo:串口号，详细定义与对应引脚可见04_GEC文件夹下gec.h文件中定义
//          baud:波特率：300、600、1200、2400、4800、9600、19200、115200...
//函数返回：无
//======================================================================
void uart_init(uint_8 uartNo, uint_32 baud_rate);

//======================================================================
//函数名称：uart_send1
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//          ch:要发送的字节
//函数返回：函数执行状态：1=发送成功；0=发送失败。
//功能概要：串行发送1个字节
//======================================================================
uint_8 uart_send1(uint_8 uartNo, uint_8 ch);

//======================================================================
//函数名称：uart_sendN
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//         buff: 发送缓冲区
//         len:发送长度
//函数返回： 函数执行状态：1=发送成功；0=发送失败
//功能概要：串行 接收n个字节
//======================================================================
uint_8 uart_sendN(uint_8 uartNo ,uint_16 len ,uint_8* buff);

//======================================================================
//函数名称：uart_send_string
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//          buff:要发送的字符串的首地址
//函数返回： 函数执行状态：1=发送成功；0=发送失败
//功能概要：从指定UART端口发送一个以'\0'结束的字符串
//======================================================================
uint_8 uart_send_string(uint_8 uartNo, void *buff);

//======================================================================
//函数名称：uart_re1
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//        *fp:接收成功标志的指针:*fp=1:接收成功；*fp=0:接收失败
//函数返回：接收返回字节
//功能概要：串行接收1个字节
//======================================================================
uint_8 uart_re1(uint_8 uartNo,uint_8 *fp);

//======================================================================
//函数名称：uart_reN
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//          buff: 接收缓冲区
//          len:接收长度
//函数返回：函数执行状态 1=接收成功;0=接收失败
//功能概要：串行 接收n个字节,放入buff中
//======================================================================
uint_8 uart_reN(uint_8 uartNo ,uint_16 len ,uint_8* buff);

//======================================================================
//函数名称：uart_enable_re_int
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//函数返回：无
//功能概要：开串口接收中断
//======================================================================
void uart_enable_re_int(uint_8 uartNo);

//======================================================================
//函数名称：uart_disable_re_int
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//函数返回：无
//功能概要：关串口接收中断
//======================================================================
void uart_disable_re_int(uint_8 uartNo);

//======================================================================
//函数名称：uart_get_re_int
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//函数返回：接收中断标志 1=有接收中断;0=无接收中断
//功能概要：获取串口接收中断标志,同时禁用发送中断
//======================================================================
uint_8 uart_get_re_int(uint_8 uartNo);

//======================================================================
//函数名称：uart_deint
//参数说明：uartNo: 串口号，04_GEC文件夹下gec.h文件中定义
//函数返回：无
//功能概要：uart反初始化
//======================================================================
void uart_deint(uint_8 uartNo);

#elif (BIOS_UART==1)     //是（1），使用BIOS内驱动，编译以下声明

#define uart_init  ((void (*)(uint_8 uartNo, uint_32 baud_rate))(bios_fun_point[75]))

#define uart_send1  ((uint_8 (*)(uint_8 uartNo, uint_8 ch))(bios_fun_point[76]))

#define uart_sendN  ((uint_8 (*)(uint_8 uartNo ,uint_16 len ,uint_8* buff))(bios_fun_point[77]))

#define uart_send_string  ((uint_8 (*)(uint_8 uartNo, void *buff))(bios_fun_point[78]))

#define uart_re1  ((uint_8 (*)(uint_8 uartNo,uint_8 *fp))(bios_fun_point[79]))

#define uart_reN  ((uint_8 (*)(uint_8 uartNo ,uint_16 len ,uint_8* buff))(bios_fun_point[80]))

#define uart_enable_re_int  ((void (*)(uint_8 uartNo))(bios_fun_point[81]))

#define uart_disable_re_int  ((void (*)(uint_8 uartNo))(bios_fun_point[82]))

#define uart_get_re_int  ((uint_8 (*)(uint_8 uartNo))(bios_fun_point[83]))

#define uart_deint  ((void (*)(uint_8 uartNo))(bios_fun_point[84]))
//=======================函数定义区结束=====================================
#endif     //#if 条件编译（结尾）

#endif     //防止重复定义（ 结尾）

//=====================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，
//    不足之处，欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏大arm技术中心，0512-65214835，http://sumcu.suda.edu.cn
