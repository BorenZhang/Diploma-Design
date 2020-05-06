//======================================================================
//�ļ����ƣ�user.h���û�����ͷ�ļ���
//������λ���մ�arm��������(sumcu.suda.edu.cn)
//���¼�¼��2018.12��1.0��2019.1��A.10
//��Ҫ˵�������ļ�������ʹ��GECоƬ����Ӳ�������ʱ����û��岿�����Ŷ��壬
//          GEC���ž��еĹ�����gec.h�ļ���
//======================================================================

#ifndef USER_H   //��ֹ�ظ����壨��ʼ��
#define USER_H
#include"gec.h"
#include"uecom.h"
#include"printf.h"
#include"lcd.h"
#include"Math.h"

//===========================================================
//ָʾ�ƶ˿ڼ����Ŷ���
#define  LIGHT_RED    GPIOA_2  //��ƣ��������ţ�GEC_56��PTA_NUM|5��
#define  LIGHT_GREEN  GPIOA_1  //�̵ƣ� �������ţ�GEC_55��PTA_NUM|12��
#define  LIGHT_BLUE   GPIOA_0  //���ƣ� �������ţ�GEC_54��PTA_NUM|13��
#define  SWITCH_ELC   GPIOB_14  //�õ��豸���ض˿ڼ����Ŷ���
//��״̬�궨�壨�Ƶ�������Ӧ���߼���ƽ��������Ӳ���ӷ�������
#define  LIGHT_ON     0     //����
#define  LIGHT_OFF    1     //�ư�
#define  SWITCH_ON    0     //���ؿ���
#define  SWITCH_OFF   1     //���عر�
//===========================================================
//UARTģ�鶨��
#define UART_USER    UARTA  //TX���ţ�GEC_10��RX���ţ�GEC_8
//UART����ģ�鶨��
#define UART_UE      UARTB  //����ͨѶģ��ͨѶ������δ����
#define UART_UPDATE  UARTC  //���ڳ�����£��޷���ʹ��

//ADCģ�鶨��
#define AD_MCU_TEMP  ADC_PIN17  //MCU�ڲ��¶Ȳɼ�ʹ��ͨ��
#define AD_BRIGHT    ADC_PIN6   //���ղɼ�ʹ��ͨ��

//timerģ�鶨��
#define TIMER_LP     TIMERA     //�͹��Ķ�ʱ��

//TSIģ�鶨��
#define TSI_TOUCH   TSI_PIN9  //������ʹ��ͨ��

#endif//��ֹ�ظ����壨��β��
