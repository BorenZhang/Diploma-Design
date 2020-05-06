【程序名称】    User_NB-IoT-Frame 
【版本号】        VA.50   2019/4/26
【程序介绍】    
                本程序为金葫芦NB通信模板工程，每间隔一段时间(见07_NosPrg/main.c起始处结构体中配置)，会向
        特定服务器(见07_NosPrg/main.c起始处结构体中配置)发送一帧数据，该数据包含终端配置信息、传感器数
        据及时间等(见07_NosPrg/include.hz中UserData结构体)。
【构件使用事项】    
  (1)本程序在03_MCU文件夹下的MCU_Driver文件夹中存放了部分构件接口，用户可根据注释区参数与返回介绍
     直接调用。 另有部分构件存放在光盘目录\04-Soft\01-UE\USER下MCU_Driver文件夹中,使用时可将对应
      构件文件夹中的.h与.c文件放到工程目录下的03_MCU\MCU_drivers文件夹中，并在04_GEC/gec.h中添
      加头文件包含即可使用。
  (2)本程序所提供的任何构件，在使用时必须先进行初始化，否则程序将发生错误。
  (3)对本程序所有构件，可在04_GEC文件夹下的gec.h中找到其通道号/模块号的宏定义。使用构件函数时，可将
      这些宏定义作为参数来直接代入。不推荐使用未出现在gec.h文件中的定义或是代入直接整数作为参数。
  (4)可用中断模块的构件中一定包含其中断使能的函数接口，在使用中断时，必须在模块初始化后，将对应中断使能。
     本程序还在07_NosPrg下isr.c中统一定义了可用中断的中断服务例程(中断处理函数)，中断处理须在其中实现
     （添加处见注释提示）。部分中断在使用时，须清除其中断标志，否则程序将出错。
     
 【GEC可用资源】
   硬件模块                                 可用资源                                                对应中断服务例程                              备注         
 GPIO             GPIOA_0~GPIOA_4             GPIOA_Handler        中断标志须清除
                  GPIOB_0~GPIOB_15            GPIOB_Handler        中断标志须清除
                  GPIOC_0~GPIOC_15              无中断  
                        
 UART             UARTA                       UARTA_Handler        可不清除中断标志
 
 TIMER            TIMERA(定时范围 ：0~65535ms)   TIMERA_Handler       中断标志须清除,低功耗
                  TIMERB(定时范围： 0~21845ms)   TIMERB_Handler       中断标志须清除
                  TIMERC(定时范围： 0~21845ms)   TIMERC_Handler       中断标志须清除
                  
 SPI              SPIA                        SPIA_Handler         可不清除中断标志
                  SPIB                        SPIB_Handler         可不清除中断标志
 
 I2C              I2CA                        I2CA_Handler         中断标志须清除
                  I2CB                        I2CB_Handler         中断标志须清除

 
 INCAP            INCAP_PIN0~INCAP_PIN5       INCAP_Handler        中断标志须清除
 
 PWM              PWM_PIN0~PWM_PIN5                无                 INCAP/OUTCMP/PWM同属一个模块，有共同引脚
 
 OUTCMP           OUTCMP_PIN0~OUTCMP_PIN5          无                  INCAP/OUTCMP/PWM同属一个模块，有共同引脚
 
 TSI              TSI_PIN0~TSI_PIN10          TSI_Handler          中断标志须清除
 
 DMA              DMA_CH0~DMA_CH3                  无                                     须结合UARTA进行使用