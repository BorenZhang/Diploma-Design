
#include "lcd.h"

uint_32 mypow(uint_8 m,uint_8 n);
void LCD_WR_DATA8(uint_8 da); //��������-8λ����
void LCD_WR_DATA(uint_16 da);
void LCD_WR_REG(uint_8 da);
void LCD_WR_REG_DATA(uint_8 reg,uint_16 da);
void Address_set(uint_16 x1,uint_16 y1,uint_16 x2,uint_16 y2);

//=====================================================================
//�������ƣ�Lcd_Init��
//�������أ���
//����˵������
//���ܸ�Ҫ��LCD��ʼ��
//�޸ļ�¼�����˻���2018��7��23�գ����ó������飬��LCD_Init���
//=====================================================================
const uint_8 cmdA[15]={0x0F,0x20,0x1E,0x09,0x12,0x0B,0x50,0XBA,
		0x44,0x09,0x14,0x05,0x23,0x21,0x00};
const uint_8 cmdB[15]={0x00,0x19,0x19,0x00,0x12,0x07,0x2D,0x28,
		0x3F,0x02,0x0A,0x08,0x25,0x2D,0x0F};
const uint_8 cmdC[4]={0x64,0x03,0X12,0X81};

void LCD_Init(void)     //LCD��ʼ��
{
	uint_8 i;

	spi_init(SPIA,1,6000,0,0);
	gpio_init(LCD_RS,1,0);
	gpio_init(LCD_DC,1,0);
	gpio_init(PTD_NUM|0,1,1);

	LCD_WR_REG_DATA(0,0);

	gpio_set(LCD_RS,0);
	Delay_ms(20);
	gpio_set(LCD_RS,1);
	Delay_ms(20);
//==========ILI9341VоƬ��ʼ������========================
//	//************* Start Initial Sequence **********//
//	LCD_WR_REG(0xCF);   //���Ŀ���
//	LCD_WR_DATA8(0x00);
//	LCD_WR_DATA8(0xD9);
//	LCD_WR_DATA8(0X30);
//
//	LCD_WR_REG(0xED);  //��Դ���п���
//	for (i=0;i<4;i++) LCD_WR_DATA8(cmdC[i]);
//
//	LCD_WR_REG(0xE8);  //����ʱ�����A
//	LCD_WR_DATA8(0x85);
//	LCD_WR_DATA8(0x10);
//	LCD_WR_DATA8(0x78);
//
//	LCD_WR_REG(0xCB);   //���Ŀ���A
//	LCD_WR_DATA8(0x39);
//	LCD_WR_DATA8(0x2C);
//	LCD_WR_DATA8(0x00);
//	LCD_WR_DATA8(0x34);
//	LCD_WR_DATA8(0x02);
//
//	LCD_WR_REG(0xF7);   //�ñȿ���
//	LCD_WR_DATA8(0x20);
//
//	LCD_WR_REG(0xEA);   //����ʱ�����B
//	LCD_WR_DATA8(0x00);
//	LCD_WR_DATA8(0x00);
//
//	LCD_WR_REG(0xC0);    //���Ŀ���1
//	LCD_WR_DATA8(0x21);   //VRH[5:0]
//
//	LCD_WR_REG(0xC1);    //���Ŀ���2
//	LCD_WR_DATA8(0x12);   //SAP[2:0];BT[3:0]
//
//	LCD_WR_REG(0xC5);    //VCOM����
//	LCD_WR_DATA8(0x32);
//	LCD_WR_DATA8(0x3C);
//
//	LCD_WR_REG(0xC7);    //VCOM����2
//	LCD_WR_DATA8(0XC1);
//

	LCD_WR_REG(0x36);    //�洢�����ʿ��ƣ���ʾ��������ʾд0x00/0x08,��ʾ��������ʾд0xD0/0xD8
	LCD_WR_DATA8(0x00);  //0x00��ST7789V����LCD��������ILI9341V�����ߵ�
	                     //0x08��ILI9341V����LCD��������ST7789V������ɫ�ߵ�
//
//	LCD_WR_REG(0x3A);    //���ظ�ʽ����
//	LCD_WR_DATA8(0x55);
//
//	LCD_WR_REG(0xB1);    //֡���ʿ���
//	LCD_WR_DATA8(0x00);
//	LCD_WR_DATA8(0x18);
////
	LCD_WR_REG(0xB6);    //��ʾ���ܿ���
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0xA2);

//	LCD_WR_REG(0xF2);    //ʹ��3٤�����
//	LCD_WR_DATA8(0x00);  //����
//
//	LCD_WR_REG(0x26);    //٤������
//	LCD_WR_DATA8(0x01);
//
//	LCD_WR_REG(0xE0);    //����٤��У׼
//    for (i=0;i<15;i++) LCD_WR_DATA8(cmdA[i]);
//
//	LCD_WR_REG(0XE1);    //����٤��У׼
//	for (i=0;i<15;i++) LCD_WR_DATA8(cmdB[i]);

//	LCD_WR_REG(0x11);    //�˳�
//	Delay_ms(120);
//	LCD_WR_REG(0x29);    //Display on
	//===========================================================


	//==========ST7789VоƬ��ʼ������========================
    //TFT:CTC2.8
	//------------------------------display and color format setting--------------------------------//
//	LCD_WR_REG(0x36);  //����ɨ�跽ʽ
//	LCD_WR_DATA8(0x00); //���϶��£��������
	LCD_WR_REG(0x3a);  //����RGBͼ�����ݸ�ʽ
	LCD_WR_DATA8(0x05);//16λ/����
//	//--------------------------------ST7789V Frame rate setting----------------------------------//
//	LCD_WR_REG(0xb2);  //�ƹ����ã�5������
//	LCD_WR_DATA8(0x0c);//���ú󱳹�
//	LCD_WR_DATA8(0x0c);//����ǰ����
//	LCD_WR_DATA8(0x00);//0��������ǰ�󱳹⣻1������ǰ����
//	LCD_WR_DATA8(0x33);
//	LCD_WR_DATA8(0x33);
//	LCD_WR_REG(0xb7);//�����ŵ�ѹ
//	LCD_WR_DATA8(0x35);//���õ�ѹΪ-10.43��13.26
//	//---------------------------------ST7789V Power setting--------------------------------------//
//	LCD_WR_REG(0xbb);    //����VCOM��ѹ
//	LCD_WR_DATA8(0x28);  //1.1V
//	LCD_WR_REG(0xc0);    //LCM����
//	LCD_WR_DATA8(0x2c);  //default
//	LCD_WR_REG(0xc2);     //VDV��VRH����ʹ��
//	LCD_WR_DATA8(0x01);   //VDV��VRH�Ĵ�����ֵΪ����д��
//	LCD_WR_REG(0xc3);     //����VRH
//	LCD_WR_DATA8(0x0b);   //4.1+( vcom+vcom offset+vdv)
//
//	LCD_WR_REG(0xc4);     //����VDV
//	LCD_WR_DATA8(0x20);   //VDV=0V
//	LCD_WR_REG(0xc6);     //����ģʽ�µ�֡�ʿ���
//	LCD_WR_DATA8(0x0f);   //60HZ
//	LCD_WR_REG(0xd0);     //��Դ����
//	LCD_WR_DATA8(0xa4);
//	LCD_WR_DATA8(0xa1);   //AVDD=6.8V��AVCL=-4.8V��VDDS=2.3V��
//	//--------------------------------ST7789V gamma setting---------------------------------------//
//	LCD_WR_REG(0xe0);     //����ѹgamma����
//	LCD_WR_DATA8(0xd0);
//	LCD_WR_DATA8(0x01);
//	LCD_WR_DATA8(0x08);
//	LCD_WR_DATA8(0x0f);
//	LCD_WR_DATA8(0x11);
//	LCD_WR_DATA8(0x2a);
//	LCD_WR_DATA8(0x36);
//	LCD_WR_DATA8(0x55);
//	LCD_WR_DATA8(0x44);
//	LCD_WR_DATA8(0x3a);
//	LCD_WR_DATA8(0x0b);
//	LCD_WR_DATA8(0x06);
//	LCD_WR_DATA8(0x11);
//	LCD_WR_DATA8(0x20);
//
//	LCD_WR_REG(0xe1);     //����ѹgamma����
//	LCD_WR_DATA8(0xd0);
//	LCD_WR_DATA8(0x02);
//	LCD_WR_DATA8(0x07);
//	LCD_WR_DATA8(0x0a);
//	LCD_WR_DATA8(0x0b);
//	LCD_WR_DATA8(0x18);
//	LCD_WR_DATA8(0x34);
//	LCD_WR_DATA8(0x43);
//	LCD_WR_DATA8(0x4a);
//	LCD_WR_DATA8(0x2b);
//	LCD_WR_DATA8(0x1b);
//	LCD_WR_DATA8(0x1c);
//	LCD_WR_DATA8(0x22);
//	LCD_WR_DATA8(0x1f);

	LCD_WR_REG(0x11);     //�˳�˯��ģʽ
	Delay_ms(120);        //Delay_ms 120ms
	LCD_Clear(WHITE);
	LCD_WR_REG(0x29);

//	LCD_WR_REG(0x10);
//	LCD_Clear(WHITE);
//	LCD_WR_REG(0x11);



}

//=====================================================================
//�������ƣ�LCD_Clear
//�������أ���
//����˵����background:������ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ��LCD����
//=====================================================================
void LCD_Clear(uint_16 background)  //LCD����
{
	uint_16 i,j;
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	 {
	  for (j=0;j<LCD_H;j++) LCD_WR_DATA(background);
     }
}


//=====================================================================
//�������ƣ�LCD_DrawPoint
//�������أ���
//����˵����x,y:������(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ�û�һ����
//=====================================================================
void LCD_DrawPoint(uint_16 x,uint_16 y,uint_16 color)    //����
{
	Address_set(x,y,x,y);//���ù��λ��
	LCD_WR_DATA(color);
}


//=====================================================================
//�������ƣ�LCD_DrawPoint_big
//�������أ���
//����˵����x,y:������(240*320)
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ�û�һ�����,���ķ�Χʵ����һ����x-1,y-1Ϊ���Ͻ⣬x+1,y+1Ϊ���½ǵ�С����
//       ����9���㣨3*3���Ĵ�㡣
//=====================================================================
void LCD_DrawPoint_big(uint_16 x,uint_16 y,uint_16 color) //��һ�����
{
	LCD_DrawSurface(x-1,y-1,x+1,y+1,color);
}

//=====================================================================
//�������ƣ�Draw_Circle
//�������أ���
//����˵����x,y:���ĵ�����(240*320),
//       r:Բ�İ뾶,
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ�û�һ��ָ����С��Բ
//=====================================================================
void LCD_DrawCircle(uint_16 x,uint_16 y,uint_8 r,uint_16 color)    //��Բ
{
	int a,b;
	int di;
	a=0;b=r;
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x-b,y-a,color);             //3
		LCD_DrawPoint(x+b,y-a,color);             //0
		LCD_DrawPoint(x-a,y+b,color);             //1
		LCD_DrawPoint(x-b,y-a,color);             //7
		LCD_DrawPoint(x-a,y-b,color);             //2
		LCD_DrawPoint(x+b,y+a,color);             //4
		LCD_DrawPoint(x+a,y-b,color);             //5
		LCD_DrawPoint(x+a,y+b,color);             //6
		LCD_DrawPoint(x-b,y+a,color);
		a++;
		//ʹ��Bresenham�㷨��Բ
		if(di<0)di +=4*a+6;
		else
		{
			di+=10+4*(a-b);
			b--;
		}
		LCD_DrawPoint(x+a,y+b,color);
	}
}


//=====================================================================
//�������ƣ�LCD_DrawRectangle
//�������أ���
//����˵����x1,y1:���Ͻǵ�����(240*320),x2,y2:���½ǵ�����(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ�����Ͻ������½ǻ�һ��ָ��������ɫ�ľ���
//=====================================================================
void LCD_DrawRectangle(uint_16 x1, uint_16 y1,
     uint_16 x2, uint_16 y2,uint_16 color)    //������
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


//=====================================================================
//�������ƣ�LCD_ShowCharactor
//�������أ���
//����˵����x,y:�������(240*320),index���������ֿ��е�����,fontcolor:������ɫ,
//       groundbackcolor:������ɫ��p:�ֿ���ʼ��ַ
//���ܸ�Ҫ����ָ��λ����ʾһ������(16*16��С),������Ҫ���д��ֿ���ȡ
//=====================================================================
void LCD_ShowCharactor(uint_16  x,uint_16 y,uint_16 fontcolor,
	 uint_16 groundbackcolor,const uint_8 *p)    //��ʾ16*16����
{
	uint_8 i,j;
	const uint_8 *temp=p;
    Address_set(x,y,x+15,y+15); //��������
	for(j=0;j<32;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((*temp&(1<<i))!=0)
				LCD_WR_DATA(fontcolor);
			else

				LCD_WR_DATA(groundbackcolor);
		}
		temp++;
	 }
}


//=====================================================================
//�������ƣ�LCD_ShowString
//�������أ���
//����˵����x,y:�������(240*320),p:�ַ�����ʼ��ַ�����԰������ģ���Ӧ�����ں�����ģ�У�
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ����ʾ�ַ�������ָ����ʾ������ɫ�ͱ�����ɫ��
//        ���Ĵ�СΪ��16*16��,Ӣ�Ĵ�СΪ��8*16��
//=====================================================================
void LCD_ShowString(uint_16  x,uint_16 y,uint_16 fontcolor,
	 uint_16 groundbackcolor,const uint_8 *p)
{
	uint_8 i,j,k;
	const uint_8 *temp;
	k = 0;
	while(*p != 0)
	{
		__disable_irq();
		if(*p>=0x20 && *p<=0x7e)
		{
			temp=nAsciiDot;
		    Address_set(x+8*k,y,x+7+8*k,y+15); //��������
			temp+=(*p-0x20)*16;
			for(j=0;j<16;j++)
			{
				for(i=0;i<8;i++)
				{
				 	if((*temp&(1<<i))!=0)
					{
						LCD_WR_DATA(fontcolor);
					}
					else
					{
						LCD_WR_DATA(groundbackcolor);
					}
				}
				temp++;
			 }
			k++;
		}
		else if(*p > 0x7e)
		{
             for(i=0;i<ChineseCharacterLength;i++)
             {
            	 uint_8 a = *p;
            	 uint_8 b = *(p+1);
            	 uint_8 c = GB_16[i].Index[0];
            	 uint_8 d = GB_16[i].Index[1];
                 if( (a == c) && (b == d))
                 {
                	 LCD_ShowCharactor(x+8*k,y,fontcolor,groundbackcolor,GB_16[i].Msk);
                	 break;
                 }
             }
             k+=1;
		}
		p++;
		__enable_irq();
	}
}

//=====================================================================
//�������ƣ�LCD_aotu
//�������أ���
//����˵����x,y:��������(240*320),x1,y1:���½�����(240*320)
//���ܸ�Ҫ����ָ��λ����ʾһ����͹��ť
//=====================================================================
void LCD_aotu(uint_16 x,uint_16 y,uint_16 x1,uint_16 y1,uint_8 s) //��͹��ť
{
   uint_8 i,n;
   uint_16 color;
   color = GRAY;
   LCD_DrawSurface(x,y,x1,y1,color);
   n=2;
   color = BLACK;
   LCD_DrawLine(x,y,x1,y,color);
   LCD_DrawLine(x,y,x,y1,color);
   color = BLACK;
   LCD_DrawLine(x1,y,x1,y1,color);
   LCD_DrawLine(x,y1,x1,y1,color);

   for(i=1;i<n;i++)
   {

   color=(s==0?BLACK:WHITE);  //

   LCD_DrawLine(x+i,y+i,x1-i,y+i,color);
   LCD_DrawLine(x+i,y+i,x+i,y1-i,color);

   color=(s==0?WHITE:BLACK);

   LCD_DrawLine(x1-i,y+i,x1-i,y1-i,color);
   LCD_DrawLine(x+i,y1-i,x1-i,y1-i,color);
   };
};

//=====================================================================
//�������ƣ�LCD_DrawLine
//�������أ���
//����˵����x1,y1:�������(240*320),x2,y2:�յ�����(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ������仭һ��ָ����ɫ��ֱ��
//=====================================================================
void LCD_DrawLine(uint_16 x1,uint_16 y1,
	 uint_16 x2, uint_16 y2,uint_16 color)    //����
{
	uint_16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;

	delta_x=x2-x1; //������������
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//ˮƽ��
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//�������
	{
		LCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

//=====================================================================
//�������ƣ�LCD_DrawSurface
//�������أ���
//����˵����x1,y1:�������(240*320),x2,y2:�յ�����(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ��ָ����ɫ����������Ҫȷ��x2>x1,y2>y1�������������ִ��
//=====================================================================
void LCD_DrawSurface(uint_16 x1,uint_16 y1,
     uint_16 x2,uint_16 y2,uint_16 color)    //����������
{
	uint_16 i,j;
	Address_set(x1,y1,x2,y2);      //���ù��λ��
	for(i=y1;i<=y2;i++)
	{
		for(j=x1;j<=x2;j++)LCD_WR_DATA(color);//����
	}
}

//=====================================================================
//�ڲ�����
//=====================================================================

//=====================================================================
//�������ƣ�mypow
//�������أ�m^n
//����˵����m����,nָ��
//���ܸ�Ҫ������m^n
//=====================================================================
uint_32 mypow(uint_8 m,uint_8 n)
{
	uint_32 result=1;
	while(n--)result*=m;
	return result;
}
void LCD_WR_DATA8(uint_8 da) //��������-8λ����
{
	gpio_set(LCD_DC,1);
	gpio_init(PTD_NUM|0,1,0);
	spi_send1(0,da);
	gpio_init(PTD_NUM|0,1,1);
}
 void LCD_WR_DATA(uint_16 da)
{
	gpio_set(LCD_DC,1);
	gpio_init(PTD_NUM|0,1,0);
    spi_send1(0,da>>8);
    spi_send1(0,da);
    gpio_init(PTD_NUM|0,1,1);
}
void LCD_WR_REG(uint_8 da)
{
	gpio_set(LCD_DC,0);
	gpio_init(PTD_NUM|0,1,0);
	spi_send1(0,da);
	gpio_init(PTD_NUM|0,1,1);
}
//void LCD_WR_REG_DATA(uint_16 reg,uint_16 da)
 void LCD_WR_REG_DATA(uint_8 reg,uint_16 da)
{
    LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
void Address_set(uint_16 x1,uint_16 y1,uint_16 x2,uint_16 y2)
{
	LCD_WR_REG(0x2a);      //д�е�ַ����
	LCD_WR_DATA8(x1>>8);   //д��ʼ�е�ַ
	LCD_WR_DATA8(x1);
	LCD_WR_DATA8(x2>>8);   //д�����е�ַ
	LCD_WR_DATA8(x2);

	LCD_WR_REG(0x2b);     //д�е�ַ����
	LCD_WR_DATA8(y1>>8);  //д����ʼ��ַ
	LCD_WR_DATA8(y1);
	LCD_WR_DATA8(y2>>8);  //д�����е�ַ
	LCD_WR_DATA8(y2);

	LCD_WR_REG(0x2C);     //д�洢������
}







