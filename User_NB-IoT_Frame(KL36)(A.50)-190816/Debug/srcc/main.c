//======================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ���մ�arm�������ģ�sumcu.suda.edu.cn��
//�汾���£�2017.08:1.0, 2019.1:A.10
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//======================================================================
#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�

//----------------------------------------------------------------------
//������ʵ����Ҫ��ɾ����ʼ��������¼�����63������ֵ
__attribute__((section (".MacConfig"))) const FlashData flashInit[]=
{
    //�ٲ�Ʒ��Ϣ
    " [���«������] ��«ģ��  ",      //��Ʒ����
    "215000-000000-00001 ",     //��Ʒ���к�
    "AHL-IoT-GEC   ",           //�û���Ʒ�ͺ�
    "  ���«���������������ƹ�˾  ",   //��������
    "A.50",                     //�û�����汾softVer[4]
	1546272000,                 //����ʱ���ʱ���2019-01-01
    "���ݴ�ѧ���������Ա",          //�û���
    "13000000000",               //�ֻ���
    //�ڷ�������Ϣ
    "121.41.100.186",           //CS-Monitor/CSFS���ڵķ�����IP
    "26123",                   //CS-Monitor�����Ķ˿ں�(��ʹ�øþ䣬�뽫��һ��ע��)
//    "38978",                 //CSFS�����Ķ˿ں�(��ʹ�øþ䣬�뽫��һ��ע��)
    //���û�����flash����Ϣ
    30,                          //����ʱ����
    0,                            //��λ����
    "U0"                          //����
};
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//������ʵ����Ҫ��ɾ������ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������
void userData_init(UserData *data);   //��ʼ���û�֡�ṹ��data
void userData_get(UserData *data);    //���û�֡�ṹ��data��ֵ
void LCD_Showfirst();                 //��ʼ��LCD����ʾ����Ҫ�Ǳ�ǩ
uint_8 flag;
//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{
    //��1���������֣���ͷ��======
    //��1.1������main����ʹ�õľֲ�����
    uint_16 mi;                        //������ʹ�õ���16λѭ������
    uint_64 mTmp;                      //��ѭ��ʹ�õ���ʱ����
    uint_32 mTmp1;                      //��ѭ��ʹ�õ���ʱ����
    uint_64 mLoopCount;                //��¼ѭ������
    uint_64 mSec,mMin;                 //��ѭ��ʹ�õġ��롱�����֡�
    uint_32 mTsi;                      //��¼��ǰ������������
    uint_8  mSendFlag;                 //�������ݱ�־λ;1:����;0:������
    uint_8  mRetdata[100];              //���uecom��ʼ�����صĽ��
    uint_16 mUserLen;                  //��Ҫ���͵��ֽڳ���
    uint_16 mFlashLen;                 //��Ҫ�洢flash���ֽڳ���
    uint_64 mRecvCount;                //�յ��Ĵ���
    uint_8 mString[30];                //����ת�ı�ʹ�õ���ʱ����
    uint_8 mCmd[2];                    //�洢����
    uint_8 mflag;               //��ѭ��ʹ�õı�־�жϱ���
    uint_8 mFlashFlag;          //�����Ƿ���Ҫ������д��flash
    uint_8 mLCDFlag;            //�����Ƿ���Ҫ����LCD
    uint_8 mLinkCount;          //������վ���Ӵ���

    uint_8  mSendData[1000];     //���������ݻ�����
    uint_16 mSendLen;           //���������ݵĳ���
    uint_8  mLBS[30];           //�洢LBS��λ��Ϣ


    /****�Զ��幦��������****/
    uint_8 human; //�����Ӧ������
    /****�Զ��幦��������****/

    //��1.2�������䡿BIOS��API�ӿڱ��׵�ַ���û��жϴ����������ʼ��
    BIOS_API_Init();
    gTimeSec=1548950401;         //Ĭ��2019-02-01 00:00:01
    sysTimeSet(gTimeSec);        //����ϵͳʱ���ֵ
    mTmp=sysTimeGet();            //��õ�ǰϵͳʱ�䣨s)
    //�ر�ע�⣬��1.2������β���ɾ��������ϵͳ��������

    //��1.3�������䡿�����ж�
     DISABLE_INTERRUPTS;

    //��1.4����������ʹ�õľֲ���������ֵ
    mLoopCount = 0;                    //���ѭ������
    mSec=0;                            //��ա��롱
    mMin=0;                            //��ա��֡�
    mTsi=0;                            //��մ�����������
    mSendFlag = 1;                     //Ĭ���ն˷�������
    mFlashFlag = 0;                    //Ĭ�ϲ�д��flash
    mLinkCount=0;                      //��վ���Ӵ���=0
    mUserLen = sizeof(UserData);      //�����Ҫ���͵��ֽڳ���
    mFlashLen = sizeof(FlashData);    //��ô���flash���ֽڳ���
    mRecvCount = 0;                    //��ս��մ���
    mLCDFlag = 0;                      //����LCD���±�־λ

    //��1.5����ȫ�ֱ�������ֵ
    gRecvLength = 0;                   //�յ����ݵĳ��ȣ���λ���ֽڣ�
    flag=1;                            //��־λ����Ҫ����ģ����Ϣ

    //��1.6���û�����ģ���ʼ��
    uecom_power(UECOM_ON);             //��ͨ��ģ�鹩��
    //gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_ON);    //��ʼ�����
    timer_init(TIMER_LP,500);                   //LPTMR��ʱ����ʼ��Ϊ500����
    tsi_init(TSI_TOUCH,TSI_VALUE);     //��ʼ����������TSI
    flash_init();                      //��ʼ��flash
    sysTimeSet(gTimeSec);              //����ϵͳʱ���ֵ
    LCD_Init();                        //��ʼ��LCD

//    printf("AHL-IoT-GEC start...  \n");


    //����ư����-��ʼ��
    //�����¶ȴ�����
    adc_init(ADC_PIN4,16);
    //�������մ�����
    adc_init(ADC_PIN6,16);
    //�����Ŵ�����
    gpio_init(GPIOC_6,GPIO_INPUT,0);
    gpio_pull(GPIOC_6,1);
    //��������Ӧ������
    gpio_init(GPIOC_4,GPIO_INPUT,0);
    gpio_pull(GPIOC_4,1);
    //��������������
    adc_init(ADC_PIN16,16);

    //��ʼ���õ��豸
    gpio_init(SWITCH_ELC,GPIO_OUTPUT,SWITCH_OFF);

    //����led��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);


    //ͼ�λ����֮����ģ���ʼ������Graphic9��


    //��1.7��ʹ��ģ���ж�
    timer_enable_int(TIMER_LP);                //ʹ��LPTMR�ж�
    tsi_enable_re_int(TSI_TOUCH);               //ʹ��TSI�ж�
    //ͼ�λ����֮����ģ��ʹ���жϴ���Graphic10��

    //��1.8�������䡿�����ж�
    ENABLE_INTERRUPTS;

//    printf("Building NB-IoT communication...  \n");

    //��1.9��������ʵ����Ҫ��ɾ�� ��ѭ��ǰ�ĳ�ʼ������
    //��1.9.1����ȡflash�е�������Ϣ��gFlashData����ʼ���û�֡����gUserData
    //��ȡFlash��63�����Ĳ�����Ϣ��gFlashData��
    flash_read_logic((uint_8*)(&gFlashData),63,0,sizeof(FlashData));
    userData_init(&gUserData);         //��ʼ���û�֡�ṹ��gUserData
    LCD_Showfirst();                   //LCD��ʾ��ʼ����
    //��1.9.2���жϸ�λ״̬��������λ״̬���ݴ洢��flash��
    mTmp = gFlashData.resetCount;      // ���浱ǰ���Ź���λ����
    if (BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0))     //��Ϊ���Ź���λ�����1
        gFlashData.resetCount++;
    else if(BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0))  //��Ϊ�ϵ縴λ��������
        gFlashData.resetCount = 0;
    //����λ�������ͱ仯��������д��flash
    if(gFlashData.resetCount!=mTmp)
    {
        flash_erase(63);
        flash_write(63,0,mFlashLen,(uint_8*)(&gFlashData));
    }
    //��1.9.3����ʼ��ͨ��ģ�飬����LCD����ʾ��ʼ������
    //LCD��һ�������ʾ28���ֽ�
    LCD_ShowString(6,300,BLUE,GRAY,    "AHL Init                    ");
    for(;;)                           //��ʼ��ͨ��ģ��ѭ��
    {
        //ͨ��ģ���ϵ粢�ȴ���ʱ�ȴ�Լ12��
        uecom_power(UECOM_ON);        //��ͨ��ģ�鹩��
        Delay_ms(6000);               //��ʱ6��
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init .                  ");
        Delay_ms(6000);               //��ʱ6��
        //ͨ��ģ���ʼ�������������ͽ����������ӹ���
        //��ʼ��ͨ��ģ��
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ..                 ");
        mflag =uecom_init();

        if(mflag)
        {
          if (mflag==1)
              LCD_ShowString(6,300,BLUE,GRAY,"AHL Init .. AT Error        ");
          if (mflag==2)
              LCD_ShowString(6,300,BLUE,GRAY,"AHL Init .. sim Error       ");
          uecom_power(UECOM_REBOOT);  //ͨ��ģ������
          continue;
        }
        //��ʾ�豸��IMSI��
        uecom_modelInfo(mRetdata);    //��ȡͨ��ģ����Ϣ
        LCD_ShowString(60,85,BLUE,GRAY,mRetdata+20);

        //���վ��������
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ...                ");
        mflag =uecom_linkBase();
        while(mflag)
         {
         	mflag =uecom_linkBase();
         	mLinkCount++; //���Ӵ���+1
         	if(mLinkCount>10)
         	{
         		mLinkCount=0;
 				uecom_power(UECOM_OFF);    //ͨ��ģ������
 				uecom_delay_ms(6000);      //��ʱ
 				uecom_power(UECOM_REBOOT); //ͨ��ģ������
 				uecom_delay_ms(6000);      //��ʱ
 				break;
         	}
         }
         if(mflag)
         {
 			LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ...link base Error ");
 			uecom_power(UECOM_OFF);    //ͨ��ģ������
 			uecom_delay_ms(6000);      //��ʱ
 			uecom_power(UECOM_REBOOT); //ͨ��ģ������
 			uecom_delay_ms(6000);      //��ʱ
 			continue;

         }
        //��ʾ�ź�ǿ�Ⱥ�С���ţ���վ�ţ�λ����Ϣ LBS
        for(mi=0;mi<5;mi++)
        {
            mflag = uecom_baseInfo(mRetdata);
            if(mflag)
            {
                Delay_ms(1000);
                continue;
            }
            ArrayCopy(mLBS,mRetdata+1,19);  //λ����Ϣ������mLBS�б���
            LCD_ShowString(60,131,BLUE,GRAY,mRetdata+1);  //��վλ��
            LCD_ShowString(170,150,BLUE,GRAY,
                    (uint_8 *)IntConvertToStr(mRetdata[0],mString));
        }
        //���������������
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ....               ");
        mflag =uecom_linkCS(gFlashData.serverIP,gFlashData.serverPort);
        if(mflag)
        {
            LCD_ShowString(6,300,BLUE,GRAY,"AHL....Link CS-Monitor Error");
            uecom_power(UECOM_REBOOT);  //ͨ��ģ������
            continue;
        }
        LCD_ShowString(6,300,BLUE,GRAY,"AHL Init ..... Successfully ");
        break;
    }

     //GNSS��ʼ��
     vuint_8 a=uecom_gnssSwitch (3);
    //ͼ�λ����֮��ѭ����ʼǰ�ĳ�ʼ������Graphic11��

//     printf("NB-IoT communication OK!  \n");

    //��1���������֣���β��======

    //��2����ѭ�����֣���ͷ��======
    for(;;)
    {

        mLoopCount++;
        //��2.1��һ�뵽��֮����еĲ���
        mTmp=sysTimeGet();              //��õ�ǰϵͳʱ��
        mTmp1=mTmp;
        if (mTmp!=gTimeSec)             //1�뵽
        {
        	/****�Զ��幦����(begin)****/
        	human=gpio_get(GPIOC_4);

        	//�Զ����ط��ȹ���
        	if(gUserData.isAutoOpenFan==1&&human==1&&gUserData.pre_temp<=gUserData.temp){
        		gpio_set(SWITCH_ELC,SWITCH_ON);
        		printf("����״̬%d\n",gpio_get(SWITCH_ELC));
        	}
        	if(gUserData.isAutoOpenFan==1&&human==0){
        		gpio_set(SWITCH_ELC,SWITCH_OFF);
        	    printf("����״̬%d\n",gpio_get(SWITCH_ELC));
        	}
        	/****�Զ��幦����(end)****/

            gTimeSec=mTmp;
            gUserData.currentTime = mTmp;
            //��2.1.1�����µ�ǰ��������LCD����ʾʱ��(time)
            timeChange(gTimeSec,gTimeString);
            printf(gTimeString);
            printf("  \n");
            LCD_ShowString(49,209,BLUE,GRAY,gTimeString);//LCD����ʾʱ��
            //��2.1.2�����ƺ����˸
            //gpio_reverse(LIGHT_RED);    //���ÿ����˸һ��
            //��2.1.3���ж��Ƿ񵽴﷢�����ݵ�ʱ��
            if(gUserData.currentTime%gFlashData.sendFrequencySec == 0 )
            {
                mSendFlag = 1;                         //���ͱ�־��1��
            }
        }
        //��2.2������һ��TSI֮��ִ�еĲ���
        if (mTsi != gUserData.touchNum)   //����1��
        {
            mTsi = gUserData.touchNum;    //���µ�ǰ��ǰTSI��������
            if(gUserData.touchNum%3==0)   //�������ﵽ3�Σ�����һ������
                mSendFlag = 1;
        }
        //��2.3������Ҫִ�з������ݲ�������������в���
        if(mSendFlag == 1)
        {
			//��2.3.1�������û�����Ϊ��������
			userData_get(&gUserData);      //���û�֡�ṹ��gUserData��ֵ
			//��2.3.2��������������Ҫ���͵�����
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
				//����ư��3�����ġ�U1������͵�����

			}
			//��2.3.3����ʾ�ź�ǿ��
			LCD_ShowString(170,150,BLUE,GRAY,"     ");
			LCD_ShowString(170,150,BLUE,GRAY,
					(uint_8 *)IntConvertToStr(gUserData.signalPower,mString));
			//��2.3.4��UEģ�鷢������
			LCD_ShowString(6,300,BLUE,GRAY,"AHL Send .                  ");

            //�ṹ��ĵ�ַ��ֱ��ǿ��תΪ����ĵ�ַ
            mflag = uecom_send(mSendLen,mSendData);
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Send ..                 ");
            if(mflag)  goto main_loop1;    //���ݷ���ʧ�ܣ�LCD��ʾ��ʾ
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Send Successfully       ");
            goto main_loop;
        main_loop1:
            //���ݷ���ʧ����ʾ
            switch(mflag)
            {
                case 1:
                    LCD_ShowString(6,300,BLUE,GRAY,"Send Error:Send Not Start   ");
                    break;
                case 2:
                    LCD_ShowString(6,300,BLUE,GRAY,"Send Error:Send Data Not OK ");
                    break;
            }
            //���³�ʼ��
            LCD_ShowString(6,300,BLUE,GRAY,"AHL Reinit .                ");
            uecom_init();
            Delay_ms(100);
            //�������γ�ʼ��������
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
                //���³�ʼ���ɹ���������ݷ���
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Send .                  ");
                //�ṹ��ĵ�ַ��ֱ��ǿ��תΪ����ĵ�ַ
                mflag = uecom_send(mSendLen,mSendData);
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Send ..                 ");
                if(mflag)  goto main_loop1;    //���ݷ���ʧ�ܣ�LCD��ʾ��ʾ
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Send Successfully       ");
            }

            goto main_loop;
        main_loop:
            mSendFlag = 0;                       //�޸ķ��ͱ��
        }
        //��2.4���ж��Ƿ���յ��������������ݣ��ط�
        if(uecom_info(gRecvBuf,&gRecvLength)==0)
        {
            mRecvCount++;                        //���մ���+1

            LCD_ShowString(6,300,BLUE,GRAY,"AHL Recv one frame          ");

            mflag = 0xff;
            mSendLen = 0;
            ArrayCopy(mCmd,gRecvBuf,2);
            ArrayCopy(mSendData,gRecvBuf,2);
            if(mCmd[0]=='A'&&mCmd[1]=='0')       //��ȡflash�е�������Ϣ
            {
                mSendLen = mFlashLen+2;
                ArrayCopy(mSendData+2,(uint_8*)(&gFlashData),mFlashLen);
            }
            else if(mCmd[0]=='A'&&mCmd[1]=='1')  //��ȡflash�еĲ�Ʒ��Ϣ
            {
                mSendLen = 145;
                ArrayCopy(mSendData+2,gFlashData.equipName,mSendLen-2);
            }
            else if(mCmd[0]=='A'&&mCmd[1]=='2')  //��ȡflash�еķ�������Ϣ
            {
                mSendLen = 22;
                ArrayCopy(mSendData+2,gFlashData.serverIP,mSendLen-2);
            }
            else if(mCmd[0]=='A'&&mCmd[1]=='3')  //��ȡ�û�����flash����Ϣ
            {
                mSendLen = 10;
                ArrayCopy(mSendData+2,(uint_8*)(&gFlashData.sendFrequencySec),mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='0')   //����flash�е�������Ϣ
            {
            	ArrayCopy((uint_8 *)(gFlashData.equipName),(uint_8*)&(gRecvBuf[2]),mFlashLen);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='1')   //����flash�еĲ�Ʒ��Ϣ
            {
            	ArrayCopy((uint_8 *)(gFlashData.equipName),(uint_8*)&(gRecvBuf[2]),124);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='2')   //����flash�еķ�������Ϣ
            {
            	ArrayCopy((uint_8 *)(gFlashData.serverIP),(uint_8*)&(gRecvBuf[2]),30);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='B'&&mCmd[1]=='3')   //�����û�����flash����Ϣ
            {
            	ArrayCopy((uint_8 *)(&gFlashData.sendFrequencySec),(uint_8*)&(gRecvBuf[2]),8);
                mFlashFlag = 1;
                mSendLen = 9;
                ArrayCopy(mSendData+2,"success",mSendLen-2);
            }
            else if(mCmd[0]=='U'&&mCmd[1]=='0')   //��ȡ��U0������Ҫ���͵�����
            {
            	ArrayCopy(gFlashData.frameCmd,mCmd,2);
                if(gRecvLength == mUserLen)       //��Ϊ��֡����
                {
                	ArrayCopy((uint_8*)(&gUserData),gRecvBuf,mUserLen);
                	ArrayCopy(gFlashData.equipName,gUserData.equipName,30);
                	ArrayCopy(gFlashData.equipID,gUserData.equipID,20);
                	ArrayCopy(gFlashData.equipType,gUserData.equipType,20);
                	ArrayCopy(gFlashData.vendor,gUserData.vendor,30);
                    //[2018.8.18] ���͵�����汾ȡBIOS
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
            else if(mCmd[0]=='U'&&mCmd[1]=='1')  //��ȡ��U1������Ҫ���͵�����
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
            else                                //�������
            {
            }
            if(mSendLen>0)                      //������Ҫ���͵�����
            {
                 mflag = uecom_send(mSendLen,mSendData); //���ݷ���
            }
            gRecvLength = 0;                    //�������ݳ������㣬�����Ѿ���ȡ
            if(mflag==0)
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Reply Successfully      ");
            else if(mflag == 0xff)
                LCD_ShowString(6,300,BLUE,GRAY,"AHL Recv Successfully       ");
            else
                LCD_ShowString(6,300,BLUE,GRAY,"Send Error:Send Data Not OK ");
             //�ж��Ƿ���Ҫдflash
             if(mFlashFlag == 1)
             {
                flash_erase(63);
                flash_write(63,0,mFlashLen,(uint_8*)(&gFlashData));
                mFlashFlag = 0;
                mLCDFlag=1;
             }
             if(mLCDFlag==1)
             {
                LCD_Showfirst();                //����LCD�ϵ���ʾ
                //������ʾ��ʾ�豸��IMSI�š���վλ����Ϣ�����մ���
                uecom_modelInfo(mRetdata);      //��ȡͨ��ģ����Ϣ
                LCD_ShowString(60,85,BLUE,GRAY,mRetdata+20);
                LCD_ShowString(60,131,BLUE,GRAY,mLBS);  //��վλ��
                LCD_ShowString(90,251,BLUE,GRAY,IntConvertToStr(mRecvCount,mString));
             }
        }
        //ͼ�λ����֮��ѭ������ɨ���֧��Ӵ���Graphic12��
    }
    //��2����ѭ�����֣���β��======
}


//======����Ϊ���������õ��Ӻ���======
//=====================================================================
//�������ƣ�userData_init
//�������أ���
//����˵����data����Ҫ��ʼ���Ľṹ������
//���ܸ�Ҫ����ʼ���û�֡�ṹ��data
//=====================================================================
void userData_init(UserData *data)            //��ʼ���û�֡�ṹ��
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
    //[2018.8.18] ���͵�����汾ȡBIOS
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
//�������ƣ�userData_get
//�������أ���
//����˵����data����Ҫ��ֵ�Ľṹ������
//���ܸ�Ҫ�����û�֡�ṹ��data��ֵ
//=====================================================================
void userData_get(UserData *data)             //���û�֡�ṹ��data��ֵ
{
    uint_16 tmpAD,brightAD;
    uint_8 tempertature[6];
    uint_8 sTmp[40],i;
    UecomGnssInfo gnss;                        //����gnss����
    uint_8 buf[15];                            //��ʱ�Ļ�����
    static uint_32 sn = 0;
    data->sn = sn++;
    adc_init(AD_MCU_TEMP,16);
    adc_init(AD_BRIGHT,16);
    tmpAD = adc_read(AD_MCU_TEMP);
    data->mcuTemp = (int_32)((25.0-(tmpAD*0.05-719)/1.715)*10);
    LCD_ShowString(150,105,BLUE,GRAY,
            (uint_8*)DoubleConvertToStr(data->mcuTemp/10.0,1,tempertature));
    //��ȡ����ǿ��
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
    //����ư����-���������ݻ�ȡ
	//�����¶ȴ�����
	int t;
	float tempAD,Vtemp,Rtemp;
	tempAD=adc_read(ADC_PIN4);  //��ȡ��ǰ�¶�
	Vtemp=(tempAD*3300.0)/65535;
	Rtemp=Vtemp/(3300.0-Vtemp)*10000.0;
	t=((1/(log(Rtemp/10000.0)/3435.0+(1/(273.15+25))))-273.15+0.5)*10;
	gUserData.temp=(float)t/10.0;
	//�������մ�����
	gUserData.light=adc_read(ADC_PIN6); //��ȡ����ֵ
	//�����Ŵ�����
	gUserData.ml=gpio_get(GPIOC_6);
	//���������Ӧ������
	gUserData.human=gpio_get(GPIOC_4);
	//��������������
	gUserData.sound=adc_read(ADC_PIN16); //��ȡ�ֱ�ֵ
	gUserData.engine=gpio_get(SWITCH_ELC);
	gUserData.led=gpio_get(LIGHT_BLUE);
	gUserData.pre_temp=20.0;
	gUserData.pre_light=16162;
	gUserData.isAutoOpenFan=0;
	gUserData.isAutoOpenLed=0;



    if(uecom_gnssGetInfo(&gnss) == 0)          //��ȡGNSS��Ϣ�ɹ�
    {
        for(i=0;i<14;i++)                      //��ȡʱ��
           data->surpBaseInfo[i]=gnss.time[i];
        DoubleConvertToStr(gnss.latitude,9,buf);           //�洢γ����Ϣ(����6λС��)
        for(i=0;i<=8;i++)
        {
            data->surplusInfo[i]=buf[i];
        }
        data->surplusInfo[9]=',';
        DoubleConvertToStr(gnss.longitude,10,buf);         //�洢������Ϣ(����6λС��)
        for(i=0;i<=9;i++)
        {
            data->surplusInfo[i+10]=buf[i];
        }
    }
}

//=====================================================================
//�������ƣ�LCD_Showfirst
//�������أ���
//����˵������
//���ܸ�Ҫ����ʼ��LCD�ϵ���ʾ������
//=====================================================================
void LCD_Showfirst()
{
    uint_8 temp[30] = {0};
    uint_16 tmpAD;
    uint_32 mk;
    uint_8 tempertature[6];
    //��1������ȫ�ֵ�ɫΪ��ɫ
    LCD_DrawSurface(0,0,240,320,GRAY);    //240*320����LCD
    //��2�����õ�һ������������
    LCD_aotu(2,2,238,38,1);               //LCDָ������͹��
    LCD_ShowString(66,15,RED,GRAY,"���«IoT-GEC"); //����
    //��3�����õڶ�������ͨ���޹�����
    LCD_aotu(2,43,238,123,0);             //LCDָ��������
    //��ʾ�ͺ�
    LCD_ShowString(6,45,BLACK,GRAY,"[Type]                     ");
    uecom_typeGet(temp);
    temp[20]=0;
    LCD_ShowString(60,45,BLUE,GRAY,temp);
    //��ʾBIOS����汾
    LCD_ShowString(6,65,BLACK,GRAY,"[BIOS_VER]                  ");
    uecom_version(temp);   //ȡuecom�汾�ţ���ΪBIOS�汾�ţ�
    LCD_ShowString(88,65,BLUE,GRAY,temp);   //��ʾBIOS����汾
    //��ʾuser����汾
    LCD_ShowString(120,65,BLACK,GRAY,"[USER_VER]    ");
    ArrayCopy(temp,gFlashData.softVer,4);
    temp[5]=0;
    LCD_ShowString(200,65,BLUE,GRAY,temp);
    LCD_ShowString(6,85,BLACK,GRAY,"[IMSI]                      ");
    //��ʾMCU�¶�
    LCD_ShowString(6,105,BLACK,GRAY,"[MCU_temperature]           ");
    adc_init(AD_MCU_TEMP,16);
    tmpAD = adc_read(AD_MCU_TEMP);
    mk = (int_32)((25.0-(tmpAD*0.05-719)/1.715)*10); //�¶���ADֵ�Ļ��㹫ʽ
    LCD_ShowString(150,105,BLUE,GRAY,(uint_8*)DoubleConvertToStr(mk/10.0,1,tempertature));
    //��4�����õ���������ͨ����أ�
    LCD_aotu(2,127,238,228,1);            //LCDָ������͹��
    LCD_ShowString(6,131,BLACK,GRAY,"[LBS]                      ");
    LCD_ShowString(6,149,BLACK,GRAY,"[Signal strength(%)]       ");
    //��ʾIP:PT (IP:PORT)
    LCD_ShowString(6,169,BLACK,GRAY,"[IP:PT]                    ");
    ArrayCopy(temp,gFlashData.serverIP,15);   //IP
    temp[15]=0;
    LCD_ShowString(65,169,BLUE,GRAY,temp);
    LCD_ShowString(185,169,BLUE,GRAY,":");//PORT
    ArrayCopy(temp,gFlashData.serverPort,5);
    temp[5]=0;
    LCD_ShowString(195,169,BLUE,GRAY,temp);
    //��ʾ����Ƶ��
    LCD_ShowString(6,189,BLACK,GRAY,"TSI:       Freq(s):        ");
    LCD_ShowString(180,189,BLUE,GRAY,"      ");
    LCD_ShowString(180,189,BLUE,GRAY,
            (uint_8 *)IntConvertToStr(gFlashData.sendFrequencySec,temp));
    LCD_ShowString(36,189,BLUE,GRAY,"0"); //��ʾTSI������ֵ0
    LCD_ShowString(6,209,BLACK,GRAY,"Time:                      ");
    LCD_ShowString(49,209,BLUE,GRAY,"2018-07-01 21:55:00" );
    LCD_aotu(2,232,238,271,0);            //LCDָ��������
    LCD_ShowString(6,235,BLACK,GRAY,"Reserved area,you can use it");
    LCD_ShowString(6,253,BLACK,GRAY,"RecvCount:                 ");
    //��5�����õ�����������״̬��ʾ����
    LCD_aotu(2,275,238,317,1);            //LCDָ������͹��
    LCD_ShowString(6,278,BLACK,GRAY,"Run State:                 ");
}
//ͼ�λ����֮main�ļ��Ӻ�����Ӵ���Graphic13��



/*
 ֪ʶҪ�أ�
 1.main.c��һ�������ʵ����ִ����س������̲����漰�κλ�����оƬ���⡣
 ���ļ����д���������漰�����Ӳ���ͻ�������ͨ��������ع�����ʵ����Ӳ��
 ϵͳ�Ľ�����
 2.���ļ�����������룬һ��Ϊ������ʵ����Ҫ��ɾ�������������ݾ���
 ��Ŀ������и��ģ���һ��Ϊ�����䡿����������������Ŀ�޹أ���ͨ�õģ�
 ������ݾ�����Ŀ���и��ġ�
 3.���ļ��Ժ�GLOBLE_VAR�����˶��壬 �����ڰ���"includes.h"ͷ�ļ�ʱ
 �ᶨ��ȫ�ֱ������������ļ��а���"includes.h"ͷ�ļ�ʱ����������ͷ�ļ���
 ��ȫ�ֱ�����
 */
