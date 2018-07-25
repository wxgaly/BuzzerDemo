
#include "reg52.h"
#include "intrins.h"

/*
**********************************************************************
*                        ���غ궨��
**********************************************************************
*/
#define uint unsigned int
#define uchar unsigned char
typedef unsigned char u8; 		// ����������
typedef unsigned int u16;
sbit voice=P1^5;

#define KEY_PORT		P1		// ���󰴼�����P1�˿�
#define DIG_PORT		P0    // ����������ܶ��뾭74HC573��P0�˿�	

sbit gA = P2^2;					// 38�����������A
sbit gB = P2^3;					// 38�����������B
sbit gC = P2^4;					// 38�����������C

sbit LED = P2^0;	
sbit LED1 = P0^0;

uint C;

/* �������������ʾ0-F�Ķ������ֵ */
unsigned char code gDuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

/*
**********************************************************************
*                        ������
**********************************************************************
*/
#define L_dao 262
#define L_re 294
#define L_mi 330
#define L_fa 349
#define L_sao 392
#define L_la 440
#define L_xi 494

/*
**********************************************************************
*                        ������
**********************************************************************
*/
#define dao 523 // ����1�� Ƶ��Ϊ523HZ��������������
#define re 587  
#define mi 659
#define fa 698
#define sao 784
#define la 880
#define xi 987

/*
**********************************************************************
*                        ������
**********************************************************************
*/
#define H_dao 1064
#define H_re 1175
#define H_mi 1318
#define H_fa 1397
#define H_sao 1586
#define H_la 1760
#define H_xi 1967


/*
**********************************************************************
*                        С���Ǹ���
**********************************************************************
*/
uint code sound_littlestar[]={
									dao, dao, sao, sao, la, la, sao,
									fa, fa, mi, mi, re, re, dao,
									sao, sao, fa, fa, mi, mi, re,
									sao, sao, fa, fa, mi, mi, re,
									dao, dao, sao, sao, la, la, sao,
									fa, fa, mi, mi, re, re, dao,
									0xff};

/*
**********************************************************************
*                        ���տ��ָ���
**********************************************************************
*/
uint code sound_birthday[]={
									L_sao, L_sao, L_la, L_sao, dao, L_xi,
									L_sao, L_sao, L_la, L_sao, re, dao,
									L_sao, L_sao, sao, mi, dao, L_xi, L_la,
									fa, fa, mi, dao, re, dao,
									0xff};

/*
**********************************************************************
*                        ʥ�������
**********************************************************************
*/
uint code sound_christmas[]={
									mi, mi, mi, mi, mi, mi,
									mi, sao, dao, re, mi,
									fa, fa, fa, fa, fa, mi, mi,
									mi, mi, mi, re, re, mi, re, sao,
									0xff};


/*
**********************************************************************
*                        С���ǽ���
**********************************************************************
*/
uchar code JP_littlestar[] = {
									2,2,2,2,2,2,4,
									2,2,2,2,2,2,4,
									2,2,2,2,2,2,4,
									2,2,2,2,2,2,4,
									2,2,2,2,2,2,4,
									2,2,2,2,2,2,4,
									};
									
/*
**********************************************************************
*                        ���տ��ֽ���
**********************************************************************
*/
uchar code JP_birthday[] = {
									1,1,2,2,2,4,
									1,1,2,2,2,4,
									1,1,2,2,2,2,4,
									1,1,2,2,2,4,
									};

/*
**********************************************************************
*                        ʥ�������
**********************************************************************
*/
uchar code JP_christmas[] = {
									1,1,2,1,1,2,
									1,1,1,1,2,
									1,1,2,1,1,2,1,
									1,1,1,1,1,1,2,2,
									};


/*
**********************************************************************
*                        �����ӳ�200ms�ĺ���
**********************************************************************
*/								
void delay200ms(void);

									
void playMusic(uchar i, uchar j,uchar sound[], uchar jp[]);

									
int PWM_Low,Clock=500;
void delay(unsigned int x) 
{
   int i;
   for(i=0;i<x;i++);
} 
/*
**********************************************************************
*                        ����������
**********************************************************************
*/
void main(void)
{
	uchar i, j;
	EA = 1;
	ET0 = 1;
	TMOD = 0x00;
	
	while(1)
  {  
//		  playMusic(i, j, sound_christmas, JP_christmas); 
		LED1 = 1;
		delay200ms();
		delay200ms();
		LED1 = 0;
		delay200ms();
		delay200ms();
		
//		for(PWM_Low=Clock;PWM_Low>0;PWM_Low--) 
//    {
//				 LED = 1;
//         LED1=1;
//         delay(PWM_Low);
//				 LED = 0;
//         LED1=0;
//         delay(Clock-PWM_Low);
//    }
//		
//    for(PWM_Low=0;PWM_Low<Clock;PWM_Low++)       
//		{
//				LED = 1;
//         LED1=1;
//         delay(PWM_Low);
//				 LED = 0;
//         LED1=0;
//         delay(Clock-PWM_Low);
//		}          
		
  } 
}

time0() interrupt 1  using 1
{
	voice = !voice;
  TH0 = (8192 - C) / 32;
	TL0 = (8192 - C) % 32;
}

void delay200ms(void)   //?? 0us
{
    unsigned char a,b,c;
    for(c=4;c>0;c--)
        for(b=116;b>0;b--)
            for(a=214;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}


void playMusic(uchar i, uchar j, uchar sound[], uchar jp[])
{
		i = 0;
	  
		while(sound_littlestar[i] != 0xff)
		{
			C = 460830 / sound_littlestar[i];
			TH0 = (8192 - C) / 32;
			TL0 = (8192 - C) % 32;
			TR0 = 1;
			
			for(j = 0; j < JP_littlestar[i]; j++)
			{
				LED1 = !LED1;
				delay200ms();

			}
			
			TR0 = 0;
			i++;
		}
}

