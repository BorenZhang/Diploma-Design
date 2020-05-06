//======================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：苏大arm技术中心（sumcu.suda.edu.cn）
//版本更新：2017.08:1.0, 2019.1:A.10
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//======================================================================
#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//【根据实际需要增删】初始化重新烧录程序后63扇区的值
__attribute__((section (".MacConfig"))) const FlashData flashInit[]=
{
    //①产品信息
    " [金葫芦物联网] 葫芦模板  ",      //产品名称
    "215000-000000-00001 ",     //产品序列号
    "AHL-IoT-GEC   ",           //用户产品型号
    "  金葫芦物联网有限责任制公司  ",   //生产厂家
    "A.50",                     //用户软件版本softVer[4]
	1546272000,                 //生产时间的时间戳2019-01-01
    "苏州大学软件开发人员",          //用户名
    "13000000000",               //手机号
    //②服务器信息
    "121.41.100.186",           //CS-Monitor/CSFS所在的服务器IP
    "26123",                   //CS-Monitor监听的端口号(如使用该句，须将下一句注释)
//    "38978",                 //CSFS监听的端口号(如使用该句，须将上一句注释)
    //③用户存入flash的信息
    30,                          //发送时间间隔
    0,                            //复位次数
    "U0"                          //命令
};
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//【根据实际需要增删】声明使用到的内部函数
//main.c使用的内部函数声明处
void userData_init(UserData *data);   //初始化用户帧结构体data
void userData_get(UserData *data);    //给用户帧结构体data赋值
void LCD_Showfirst();                 //初始化LCD的显示，主要是标签
uint_8 flag;
//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程见书稿）
int main(void)
{
    //（1）启动部分（开头）======
    //（1.1）声明main函数使用的局部变量
    uint_16 mi;                        //主程序使用到的16位循环变量
    uint_64 mTmp;                      //主循环使用的临时变量
    uint_32 mTmp1;                      //主循环使用的临时变量
    uint_64 mLoopCount;                //记录循环次数
    uint_64 mSec,mMin;                 //主循环使用的“秒”、“分”
    uint_32 mTsi;                      //记录当前触摸按键次数
    uint_8  mSendFlag;                 //发送数据标志位;1:发送;0:不发送
    uint_8  mRetdata[100];              //存放uecom初始化返回的结果
    uint_16 mUserLen;                  //需要发送的字节长度
    uint_16 mFlashLen;                 //需要存储flash的字节长度
    uint_64 mRecvCount;                //收到的次数
    uint_8 mString[30];                //数字转文本使用的临时数组
    uint_8 mCmd[2];                    //存储命令
    uint_8 mflag;               //主循环使用的标志判断变量
    uint_8 mFlashFlag;          //表明是否需要将数据写入flash
    uint_8 mLCDFlag;            //表明是否需要更新LCD
    uint_8 mLinkCount;          //表明基站连接次数

    uint_8  mSendData[1000];     //待发送数据缓冲区
    uint_16 mSendLen;           //待发送数据的长度
    uint_8  mLBS[30];           //存储LBS定位信息


    /****自定义功能数据区****/
    uint_8 human; //人体感应传感器
    /****自定义功能数据区****/

    //（1.2）【不变】BIOS中API接口表首地址、用户中断处理程序名初始化
    BIOS_API_Init();
    gTimeSec=1548950401;         //默认2019-02-01 00:00:01
    sysTimeSet(gTimeSec);        //设置系统时间初值
    mTmp=sysTimeGet();            //获得当前系统时间（s)
    //特别注意，（1.2）程序段不能删除，否则系统不能运行

    //（1.3）【不变】关总中断
     DISABLE_INTERRUPTS;

    //（1.4）给主函数使用的局部变量赋初值
    mLoopCount = 0;                    //清空循环次数
    mSec=0;                            //清空“秒”
    mMin=0;                            //清空“分”
    mTsi=0;                            //清空触摸按键次数
    mSendFlag = 1;                     //默认终端发送数据
    mFlashFlag = 0;                    //默认不写入flash
    mLinkCount=0;                      //基站连接次数=0
    mUserLen = sizeof(UserData);      //获得需要发送的字节长度
    mFlashLen = sizeof(FlashData);    //获得存入flash的字节长度
    mRecvCount = 0;                    //清空接收次数
    mLCDFlag = 0;                      //清零LCD更新标志位

    //（1.5）给全局变量赋初值
    gRecvLength = 0;                   //收到数据的长度（单位：字节）
    flag=1;                            //标志位，需要更新模组信息

    //（1.6）用户外设模块初始化
    uecom_power(UECOM_ON);             //给通信模组供电
    //gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_ON);    //初始化红灯
    timer_init(TIMER_LP,500);                   //LPTMR计时器初始化为500毫秒
    tsi_init(TSI_TOUCH,TSI_VALUE);     //初始化触摸按键TSI
    flash_init();                      //初始化flash
    sysTimeSet(gTimeSec);              //设置系统时间初值
    LCD_Init();                        //初始化LCD

//    printf("AHL-IoT-GEC start...  \n");


    //【画瓢处】-初始化
    //新增温度传感器
    adc_init(ADC_PIN4,16);
    //新增光照传感器
    adc_init(ADC_PIN6,16);
    //新增磁传感器
    gpio_init(GPIOC_6,GPIO_INPUT,0);
    gpio_pull(GPIOC_6,1);
    //添加人体感应传感器
    gpio_init(GPIOC_4,GPIO_INPUT,0);
    gpio_pull(GPIOC_4,1);
    //新增声音传感器
    adc_init(ADC_PIN16,16);

    //初始化用电设备
    gpio_init(SWITCH_ELC,GPIO_OUTPUT,SWITCH_OFF);

    //新增led灯
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);


    //图形化编程之外设模块初始化处【Graphic9】


    //（1.7）使能模块中断
    timer_enable_int(TIMER_LP);                //使能LPTMR中断
    tsi_enable_re_int(TSI_TOUCH);               //使能TSI中断
    //图形化编程之外设模块使能中断处【Graphic10】

    //（1.8）【不变】开总中断
    ENABLE_INTERRUPTS;

//    printf("Building NB-IoT communication...  \n");

    //（1.9）【根据实际需要增删】 主循环前的初始化操作
    //（1.9.1）读取flash中的配置信息至gFlashData；初始化用户帧数据gUserData
    //读取Flash中63扇区的参数信息到gFlashData中
    flash_read_logic((uint_8*)(&gFlashData),63,0,sizeof(FlashData));
    userData_init(&gUserData);         //初始化用户帧结构体gUserData
    LCD_Showfirst();                   //LCD显示初始内容
    //（1.9.2）判断复位状态，并将复位状态数据存储到flash中
    mTmp = gFlashData.resetCount;      // 保存当前看门狗复位次数
    if (BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0))     //若为看门狗复位，则加1
        gFlashData.resetCount++;
    else if(BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0))  //若为上电复位，则置零
        gFlashData.resetCount = 0;
    //若复位次数发送变化，则重新写入flash
    if(gFlashData.resetCount!=mTmp)
    {
        flash_erase(63);
        flash_write(63,0,mFlashLen,(uint_8*)(&gFlashData));
    }
    //（1.9.3）初始化通信模组，并在LCD上显示初始化过程
    //LCD上一行最多显示28个字节
    LCD_ShowString(6,300,BLUE,GRAY,    "AHL Init                    ");
    for(;;)                           //初始化通信模组循环
    {
        //通信模组上电并等待延时等待约12秒
        uecom_power(UECOM_ON);        //给通信模组供电
        Delay_ms(6000);               //延时6秒
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init .                  ");
        Delay_ms(6000);               //延时6秒
        //通信模组初始化，包括联网和建立网络连接过程
        //初始化通信模组
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ..                 ");
        mflag =uecom_init();

        if(mflag)
        {
          if (mflag==1)
              LCD_ShowString(6,300,BLUE,GRAY,"AHL Init .. AT Error        ");
          if (mflag==2)
              LCD_ShowString(6,300,BLUE,GRAY,"AHL Init .. sim Error       ");
          uecom_power(UECOM_REBOOT);  //通信模组重启
          continue;
        }
        //显示设备的IMSI号
        uecom_modelInfo(mRetdata);    //获取通信模组信息
        LCD_ShowString(60,85,BLUE,GRAY,mRetdata+20);

        //与基站建立连接
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ...                ");
        mflag =uecom_linkBase();
        while(mflag)
         {
         	mflag =uecom_linkBase();
         	mLinkCount++; //连接次数+1
         	if(mLinkCount>10)
         	{
         		mLinkCount=0;
 				uecom_power(UECOM_OFF);    //通信模组重启
 				uecom_delay_ms(6000);      //延时
 				uecom_power(UECOM_REBOOT); //通信模组重启
 				uecom_delay_ms(6000);      //延时
 				break;
         	}
         }
         if(mflag)
         {
 			LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ...link base Error ");
 			uecom_power(UECOM_OFF);    //通信模组重启
 			uecom_delay_ms(6000);      //延时
 			uecom_power(UECOM_REBOOT); //通信模组重启
 			uecom_delay_ms(6000);      //延时
 			continue;

         }
        //显示信号强度和小区号（基站号）位置信息 LBS
        for(mi=0;mi<5;mi++)
        {
            mflag = uecom_baseInfo(mRetdata);
            if(mflag)
            {
                Delay_ms(1000);
                continue;
            }
            ArrayCopy(mLBS,mRetdata+1,19);  //位置信息保存在mLBS中备用
            LCD_ShowString(60,131,BLUE,GRAY,mRetdata+1);  //基站位置
            LCD_ShowString(170,150,BLUE,GRAY,
                    (uint_8 *)IntConvertToStr(mRetdata[0],mString));
        }
        //与服务器建立连接
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ....               ");
        mflag =uecom_linkCS(gFlashData.serverIP,gFlashData.serverPort);
        if(mflag)
        {
            LCD_ShowString(6,300,BLUE,GRAY,"AHL....Link CS-Monitor Error");
            uecom_power(UECOM_REBOOT);  //通信模组重启
            continue;
        }
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ..... Successfully ");
        break;
    }

     //GNSS初始化
     vuint_8 a=uecom_gnssSwitch (3);
    //图形化编程之主循环开始前的初始化处【Graphic11】

//     printf("NB-IoT communication OK!  \n");

    //（1）启动部分（结尾）======

    //（2）主循环部分（开头）======
    for(;;)
    {

        mLoopCount++;
        //（2.1）一秒到达之后进行的操作
        mTmp=sysTimeGet();              //获得当前系统时间
        mTmp1=mTmp;
        if (mTmp!=gTimeSec)             //1秒到
        {
        	/****自定义功能区(begin)****/
        	human=gpio_get(GPIOC_4);

        	//自动开关风扇功能
        	if(gUserData.isAutoOpenFan==1&&human==1&&gUserData.pre_temp<=gUserData.temp){
        		gpio_set(SWITCH_ELC,SWITCH_ON);
        		printf("开关状态%d\n",gpio_get(SWITCH_ELC));
        	}
        	if(gUserData.isAutoOpenFan==1&&human==0){
        		gpio_set(SWITCH_ELC,SWITCH_OFF);
        	    printf("开关状态%d\n",gpio_get(SWITCH_ELC));
        	}
        	/****自定义功能区(end)****/

            gTimeSec=mTmp;
            gUserData.currentTime = mTmp;
            //（2.1.1）更新当前秒数并在LCD上显示时间(time)
            timeChange(gTimeSec,gTimeString);
            printf(gTimeString);
            printf("  \n");
            LCD_ShowString(49,209,BLUE,GRAY,gTimeString);//LCD上显示时间
            //（2.1.2）控制红灯闪烁
            //gpio_reverse(LIGHT_RED);    //红灯每秒闪烁一次
            //（2.1.3）判断是否到达发送数据的时间
            if(gUserData.currentTime%gFlashData.sendFrequencySec == 0 )
            {
                mSendFlag = 1;                         //发送标志置1；
            }
        }
        //（2.2）触摸一次TSI之后执行的操作
        if (mTsi != gUserData.touchNum)   //触摸1次
        {
            mTsi = gUserData.touchNum;    //更新当前当前TSI触摸次数
            if(gUserData.touchNum%3==0)   //若触摸达到3次，则发送一次数据
                mSendFlag = 1;
        }
        //（2.3）若需要执行发送数据操作，则进行下列操作
        if(mSendFlag == 1)
        {
			//（2.3.1）更新用户数据为最新数据
			userData_get(&gUserData);      //给用户帧结构体gUserData赋值
			//（2.3.2）根据命令，获得需要发送的数据
			if(gFlashData.frameCmd[0]=='U'&&gFlashData.frameCmd[1]=='0')
			{
				mSendLen = mUserLen;
				ArrayCopy(gUserData.cmd,gFlashData.frameCmd,2);
				ArrayCopy(mSendData,(uint_8 *)&gUserData,mSendLen);
			}
			else if(gFlashData.frameCmd[0]=='U'&&gFlashData.frameCmd[1]=='1')
			{
				ArrayCopy(mSendData,gFlashData.frameCmd,2);
				ArrayCopy(mSendData+2,gUserData.IMSI,15);
				ArrayCopy(mSendData+17,(uint_8 *)&gUserData.currentTime,8);
				ArrayCopy(mSendData+25,(uint_8 *)&gUserData.mcuTemp,4);
				ArrayCopy(mSendData+29,(uint_8 *)&gUserData.signalPower,1);
				ArrayCopy(mSendData+30,(uint_8 *)&gUserData.bright,2);
				ArrayCopy(mSendData+32,(uint_8 *)&gUserData.touchNum,2);
				ArrayCopy(mSendData+34,gUserData.lbs_location,25);
				//【画瓢处3】更改“U1”命令发送的数据

			}
			//（2.3.3）显示信号强度
			LCD_ShowString(170,150,BLUE,GRAY,"     ");
			LCD_ShowString(170,150,BLUE,GRAY,
					(uint_8 *)IntConvertToStr(gUserData.signalPower,mString));
			//（2.3.4）UE模块发送数据
			LCD_ShowString(6,300,BLUE,GRAY,"AHL Send .                  ");

            //结构体的地址可直接强制转为数组的地址
            mflag = uecom_send(mSendLen,mSendData);
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Send ..                 ");
            if(mflag)  goto main_loop1;    //数据发送失败，LCD显示提示
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Send Successfully       ");
            goto main_loop;
        main_loop1:
            //数据发送失败提示
            switch(mflag)
            {
                case 1:
                    LCD_ShowString(6,300,BLUE,GRAY,"Send Error:Send Not Start   ");
                    break;
                case 2:
                    LCD_ShowString(6,300,BLUE,GRAY,"Send Error:Send Data Not OK ");
                    break;
            }
            //重新初始化
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit .                ");
            uecom_init();
            Delay_ms(100);
            //进行两次初始化（防错）
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit .                ");
            uecom_init();
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit ..               ");
            uecom_linkBase();
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit ...               ");
            mflag = uecom_linkCS(gFlashData.serverIP,gFlashData.serverPort);
            if(mflag)
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit .... Fail        ");
            else
            {
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit .... Success     ");
                //重新初始化成功后进行数据发送
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Send .                  ");
                //结构体的地址可直接强制转为数组的地址
                mflag = uecom_send(mSendLen,mSendData);
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Send ..                 ");
                if(mflag)  goto main_loop1;    //数据发送失败，LCD显示提示
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Send Successfully       ");
            }

            goto main_loop;
        main_loop:
            mSendFlag = 0;                       //修改发送标记
        }
        //（2.4）判断是否接收到服务器发来数据，回发
        if(uecom_info(gRecvBuf,&gRecvLength)==0)
        {
            mRecvCount++;                        //接收次数+1

            LCD_ShowString(6,300,BLUE,GRAY,"AHL Recv one frame          ");

            mflag = 0xff;
            mSendLen = 0;
            ArrayCopy(mCmd,gRecvBuf,2);
            ArrayCopy(mSendData,gRecvBuf,2);
            if(mCmd[0]=='A'&&mCmd[1]=='0')       //读取flash中的所有信息
            {
                mSendLen = mFlashLen+2;
                ArrayCopy(mSendData+2,(uint_8*)(&gFlashData),mFlashLen);
            }
            else if(mCmd[0]=='A'&&mCmd[1]=='1')  //读取flash中的产品信息
            {
                mSendLen = 145;
                ArrayCopy(mSendData+2,gFlashData.equipName,mSendLen-2);
            }
            else if(mCmd[0]=='A'&&mCmd[1]=='2')  //读取flash中的服务器信息
            {
                mSendLen = 22;
                ArrayCopy(mSendData+2,gFlashData.serverIP,mSendLen-2);
            }
            else if(mCmd[0]=='A'&&mCmd[1]=='3')  //读取用户存入flash的信息
            {
                mSendLen = 10;
                ArrayCopy(mSendData+2,(uint_8*)(&gFlashData.sendFrequencySec),mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='0')   //更改flash中的所有信息
            {
            	ArrayCopy((uint_8 *)(gFlashData.equipName),(uint_8*)&(gRecvBuf[2]),mFlashLen);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='1')   //更改flash中的产品信息
            {
            	ArrayCopy((uint_8 *)(gFlashData.equipName),(uint_8*)&(gRecvBuf[2]),124);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='2')   //更改flash中的服务器信息
            {
            	ArrayCopy((uint_8 *)(gFlashData.serverIP),(uint_8*)&(gRecvBuf[2]),30);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='3')   //更改用户存入flash的信息
            {
            	ArrayCopy((uint_8 *)(&gFlashData.sendFrequencySec),(uint_8*)&(gRecvBuf[2]),8);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='U'&&mCmd[1]=='0')   //获取“U0”命令要发送的数据
            {
            	ArrayCopy(gFlashData.frameCmd,mCmd,2);
                if(gRecvLength == mUserLen)       //若为整帧数据
                {
                	ArrayCopy((uint_8*)(&gUserData),gRecvBuf,mUserLen);
                	ArrayCopy(gFlashData.equipName,gUserData.equipName,30);
                	ArrayCopy(gFlashData.equipID,gUserData.equipID,20);
                	ArrayCopy(gFlashData.equipType,gUserData.equipType,20);
                	ArrayCopy(gFlashData.vendor,gUserData.vendor,30);
                    //[2018.8.18] 发送的软件版本取BIOS
                    bios_version(mString);
                    ArrayCopy(gUserData.softVer,mString,4);
                    sysTimeSet(gUserData.currentTime);
                    ArrayCopy(gFlashData.userName,gUserData.userName,20);
                    ArrayCopy(gFlashData.phone,gUserData.phone,11);
                    ArrayCopy(gFlashData.serverIP,gUserData.serverIP,15);
                    ArrayCopy(gFlashData.serverPort,gUserData.serverPort,5);
                    gFlashData.sendFrequencySec = gUserData.sendFrequencySec;
                    gFlashData.resetCount = gUserData.resetCount;
                    ArrayCopy(gFlashData.frameCmd,gUserData.cmd,2);
                    mLCDFlag==1;
                    mFlashFlag  =1;
                    gpio_set(LIGHT_BLUE,gUserData.led);
                    gpio_set(SWITCH_ELC,gUserData.engine);
                }
                else
                {
                	mFlashFlag  =0;
                }
                mLCDFlag=1;
            }
            else if(mCmd[0]=='U'&&mCmd[1]=='1')  //获取“U1”命令要发送的数据
            {
            	ArrayCopy(gFlashData.frameCmd,mCmd,2);
                if(gRecvLength == 59)
                {
                	ArrayCopy(gUserData.cmd,gRecvBuf,2);
                	ArrayCopy(gUserData.IMSI,gRecvBuf+2,15);
                	ArrayCopy((uint_8 *)&gUserData.currentTime,gRecvBuf+17,8);
                	ArrayCopy((uint_8 *)&gUserData.mcuTemp,gRecvBuf+25,4);
                	ArrayCopy((uint_8 *)&gUserData.signalPower,gRecvBuf+29,1);
                	ArrayCopy((uint_8 *)&gUserData.bright,gRecvBuf+30,2);
                	ArrayCopy((uint_8 *)&gUserData.touchNum,gRecvBuf+32,2);
                	ArrayCopy(gUserData.lbs_location,gRecvBuf+34,25);
                }
                mLCDFlag=1;
            }
            else                                //其他情况
            {
            }
            if(mSendLen>0)                      //若有需要发送的数据
            {
                 mflag = uecom_send(mSendLen,mSendData); //数据发送
            }
            gRecvLength = 0;                    //接收数据长度清零，表明已经读取
            if(mflag==0)
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Reply Successfully      ");
            else if(mflag == 0xff)
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Recv Successfully       ");
            else
                LCD_ShowString(6,300,BLUE,GRAY,"Send Error:Send Data Not OK ");
             //判断是否需要写flash
             if(mFlashFlag == 1)
             {
                flash_erase(63);
                flash_write(63,0,mFlashLen,(uint_8*)(&gFlashData));
                mFlashFlag = 0;
                mLCDFlag=1;
             }
             if(mLCDFlag==1)
             {
                LCD_Showfirst();                //更新LCD上的显示
                //补充显示显示设备的IMSI号、基站位置信息、接收次数
                uecom_modelInfo(mRetdata);      //获取通信模组信息
                LCD_ShowString(60,85,BLUE,GRAY,mRetdata+20);
                LCD_ShowString(60,131,BLUE,GRAY,mLBS);  //基站位置
                LCD_ShowString(90,251,BLUE,GRAY,IntConvertToStr(mRecvCount,mString));
             }
        }
        //图形化编程之主循环流程扫描分支添加处【Graphic12】
    }
    //（2）主循环部分（结尾）======
}


//======以下为主函数调用的子函数======
//=====================================================================
//函数名称：userData_init
//函数返回：无
//参数说明：data：需要初始化的结构体数据
//功能概要：初始化用户帧结构体data
//=====================================================================
void userData_init(UserData *data)            //初始化用户帧结构体
{
    uint_8 mString[10];
    ArrayCopy(data->cmd,"U0",2);
    ArrayCopy(gFlashData.frameCmd,data->cmd,2);
    data->sn = 0;
    ArrayCopy(data->serverIP,gFlashData.serverIP,15);
    ArrayCopy(data->serverPort,gFlashData.serverPort,5);
    data->currentTime = gFlashData.productTime;
    data->resetCount = gFlashData.resetCount;
    data->sendFrequencySec = gFlashData.sendFrequencySec;
    ArrayCopy(data->userName,gFlashData.userName,20);
    //[2018.8.18] 发送的软件版本取BIOS
    bios_version(mString);
    ArrayCopy(data->softVer,mString,4);
    ArrayCopy(data->equipName,gFlashData.equipName,30);
    ArrayCopy(data->equipID,gFlashData.equipID,20);
    ArrayCopy(data->equipType,gFlashData.equipType,20);
    ArrayCopy(data->vendor,gFlashData.vendor,30);
    ArrayCopy(data->phone,gFlashData.phone,11);
    data->touchNum = 0;
    ArrayCopy(data->cmd,gFlashData.frameCmd,2);
}

//=====================================================================
//函数名称：userData_get
//函数返回：无
//参数说明：data：需要赋值的结构体数据
//功能概要：给用户帧结构体data赋值
//=====================================================================
void userData_get(UserData *data)             //给用户帧结构体data赋值
{
    uint_16 tmpAD,brightAD;
    uint_8 tempertature[6];
    uint_8 sTmp[40],i;
    UecomGnssInfo gnss;                        //定义gnss变量
    uint_8 buf[15];                            //临时的缓冲区
    static uint_32 sn = 0;
    data->sn = sn++;
    adc_init(AD_MCU_TEMP,16);
    adc_init(AD_BRIGHT,16);
    tmpAD = adc_read(AD_MCU_TEMP);
    data->mcuTemp = (int_32)((25.0-(tmpAD*0.05-719)/1.715)*10);
    LCD_ShowString(150,105,BLUE,GRAY,
            (uint_8*)DoubleConvertToStr(data->mcuTemp/10.0,1,tempertature));
    //获取光照强度
    brightAD = adc_read(AD_BRIGHT);
    data->bright = brightAD;
	if(flag==1)
	{
		flag=0;
		uecom_modelInfo(sTmp);
		ArrayCopy(data->IMEI,sTmp,15);
		ArrayCopy(data->IMSI,sTmp+20,15);
		uecom_baseInfo(sTmp);
		data->signalPower = sTmp[0];
		ArrayCopy(data->lbs_location,sTmp+1,19);
	}
    //【画瓢处】-传感器数据获取
	//新增温度传感器
	int t;
	float tempAD,Vtemp,Rtemp;
	tempAD=adc_read(ADC_PIN4);  //获取当前温度
	Vtemp=(tempAD*3300.0)/65535;
	Rtemp=Vtemp/(3300.0-Vtemp)*10000.0;
	t=((1/(log(Rtemp/10000.0)/3435.0+(1/(273.15+25))))-273.15+0.5)*10;
	gUserData.temp=(float)t/10.0;
	//新增光照传感器
	gUserData.light=adc_read(ADC_PIN6); //获取光照值
	//新增磁传感器
	gUserData.ml=gpio_get(GPIOC_6);
	//新增人体感应传感器
	gUserData.human=gpio_get(GPIOC_4);
	//新增声音传感器
	gUserData.sound=adc_read(ADC_PIN16); //获取分贝值
	gUserData.engine=gpio_get(SWITCH_ELC);
	gUserData.led=gpio_get(LIGHT_BLUE);
	gUserData.pre_temp=20.0;
	gUserData.pre_light=16162;
	gUserData.isAutoOpenFan=0;
	gUserData.isAutoOpenLed=0;



    if(uecom_gnssGetInfo(&gnss) == 0)          //获取GNSS信息成功
    {
        for(i=0;i<14;i++)                      //获取时间
           data->surpBaseInfo[i]=gnss.time[i];
        DoubleConvertToStr(gnss.latitude,9,buf);           //存储纬度信息(保留6位小数)
        for(i=0;i<=8;i++)
        {
            data->surplusInfo[i]=buf[i];
        }
        data->surplusInfo[9]=',';
        DoubleConvertToStr(gnss.longitude,10,buf);         //存储经度信息(保留6位小数)
        for(i=0;i<=9;i++)
        {
            data->surplusInfo[i+10]=buf[i];
        }
    }
}

//=====================================================================
//函数名称：LCD_Showfirst
//函数返回：无
//参数说明：无
//功能概要：初始化LCD上电显示的内容
//=====================================================================
void LCD_Showfirst()
{
    uint_8 temp[30] = {0};
    uint_16 tmpAD;
    uint_32 mk;
    uint_8 tempertature[6];
    //（1）设置全局底色为灰色
    LCD_DrawSurface(0,0,240,320,GRAY);    //240*320像素LCD
    //（2）设置第一区（标题区）
    LCD_aotu(2,2,238,38,1);               //LCD指定区域凸起
    LCD_ShowString(66,15,RED,GRAY,"金葫芦IoT-GEC"); //红字
    //（3）设置第二区（与通信无关区）
    LCD_aotu(2,43,238,123,0);             //LCD指定区域凹下
    //显示型号
    LCD_ShowString(6,45,BLACK,GRAY,"[Type]                     ");
    uecom_typeGet(temp);
    temp[20]=0;
    LCD_ShowString(60,45,BLUE,GRAY,temp);
    //显示BIOS软件版本
    LCD_ShowString(6,65,BLACK,GRAY,"[BIOS_VER]                  ");
    uecom_version(temp);   //取uecom版本号（作为BIOS版本号）
    LCD_ShowString(88,65,BLUE,GRAY,temp);   //显示BIOS软件版本
    //显示user软件版本
    LCD_ShowString(120,65,BLACK,GRAY,"[USER_VER]    ");
    ArrayCopy(temp,gFlashData.softVer,4);
    temp[5]=0;
    LCD_ShowString(200,65,BLUE,GRAY,temp);
    LCD_ShowString(6,85,BLACK,GRAY,"[IMSI]                      ");
    //显示MCU温度
    LCD_ShowString(6,105,BLACK,GRAY,"[MCU_temperature]           ");
    adc_init(AD_MCU_TEMP,16);
    tmpAD = adc_read(AD_MCU_TEMP);
    mk = (int_32)((25.0-(tmpAD*0.05-719)/1.715)*10); //温度与AD值的换算公式
    LCD_ShowString(150,105,BLUE,GRAY,(uint_8*)DoubleConvertToStr(mk/10.0,1,tempertature));
    //（4）设置第三区（与通信相关）
    LCD_aotu(2,127,238,228,1);            //LCD指定区域凸起
    LCD_ShowString(6,131,BLACK,GRAY,"[LBS]                      ");
    LCD_ShowString(6,149,BLACK,GRAY,"[Signal strength(%)]       ");
    //显示IP:PT (IP:PORT)
    LCD_ShowString(6,169,BLACK,GRAY,"[IP:PT]                    ");
    ArrayCopy(temp,gFlashData.serverIP,15);   //IP
    temp[15]=0;
    LCD_ShowString(65,169,BLUE,GRAY,temp);
    LCD_ShowString(185,169,BLUE,GRAY,":");//PORT
    ArrayCopy(temp,gFlashData.serverPort,5);
    temp[5]=0;
    LCD_ShowString(195,169,BLUE,GRAY,temp);
    //显示发送频率
    LCD_ShowString(6,189,BLACK,GRAY,"TSI:       Freq(s):        ");
    LCD_ShowString(180,189,BLUE,GRAY,"      ");
    LCD_ShowString(180,189,BLUE,GRAY,
            (uint_8 *)IntConvertToStr(gFlashData.sendFrequencySec,temp));
    LCD_ShowString(36,189,BLUE,GRAY,"0"); //显示TSI次数初值0
    LCD_ShowString(6,209,BLACK,GRAY,"Time:                      ");
    LCD_ShowString(49,209,BLUE,GRAY,"2018-07-01 21:55:00" );
    LCD_aotu(2,232,238,271,0);            //LCD指定区域凹下
    LCD_ShowString(6,235,BLACK,GRAY,"Reserved area,you can use it");
    LCD_ShowString(6,253,BLACK,GRAY,"RecvCount:                 ");
    //（5）设置第四区（运行状态显示区）
    LCD_aotu(2,275,238,317,1);            //LCD指定区域凸起
    LCD_ShowString(6,278,BLACK,GRAY,"Run State:                 ");
}
//图形化编程之main文件子函数添加处【Graphic13】



/*
 知识要素：
 1.main.c是一个具体的实例，执行相关程序流程不会涉及任何环境，芯片问题。
 该文件所有代码均不会涉及具体的硬件和环境，它通过调用相关构件来实现与硬件
 系统的交互。
 2.本文件共有两类代码，一类为【根据实际需要增删】，此类代码根据具体
 项目需求进行更改；另一类为【不变】，此类代码与具体项目无关，是通用的，
 无需根据具体项目进行更改。
 3.本文件对宏GLOBLE_VAR进行了定义， 所以在包含"includes.h"头文件时
 会定义全局变量，在其他文件中包含"includes.h"头文件时，仅声明该头文件中
 的全局变量。
 */
