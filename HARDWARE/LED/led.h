#ifndef __LED_H
#define __LED_H	 

#include "sys.h"

//LED�˿ڶ���
#define LED1 PAout(14)
#define LED2 PAout(0)
#define LED3 PBout(9)// PB8
#define LED4 PBout(8)// PB9

#define LED1_ON LED1=1// PC0
#define LED2_ON LED2=1// PB13	
#define LED3_ON LED3=0// PB8
#define LED4_ON LED4=0// PB9

#define LED1_OFF LED1=0// PC0
#define LED2_OFF LED2=0// PB13	
#define LED3_OFF LED3=1// PB8
#define LED4_OFF LED4=1// PB9
	
void LED_Init(void);//��ʼ��

		 				    
#endif
