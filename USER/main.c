//***********************************************************

#include "sys.h"
#include "plusc2c.h"
	
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	
#include "led.h"  

//***********************************************************
#define GSM_RST PCout(11)
#define STR(A) 	(unsigned char*)(A)



int main ( void )
{
	//uint8_t static active= 0;
	//uint8_t static ledstat;
	SystemInit();//ϵͳʱ�ӵȳ�ʼ��

	if(SysTick_Config(72000*1))	 //���ô��󷵻�1,max 16777216   Ĭ��72Mhz ʱ�� ,1ms��ʱ
	{							
		//LED4_ON; 	//������ 		
		while(1);
	}
	
	LED_Init();	 //LED�˿ڳ�ʼ��
	LED2_ON;
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	
	Uart1Init ( 115200 ); //���ڳ�ʼ��Ϊ115200

	GSM_RST = 0; //����GSMģ��
	
	delay_ms(1800);
	USB_Port_Set(0); 	//USB???
	delay_ms(700);
	USB_Port_Set(1);	//USB????
 	Set_USBClock();   
 	USB_Interrupts_Config();    
 	USB_Init();	
	
	
	Uart2Init ( 115200 ); //���ڳ�ʼ��Ϊ115200
	Uart3Init ( 115200 );//���ڳ�ʼ��Ϊ115200

	//Uart1SendStr(STR("uart1 init\r\n"));

	//Uart2SendStr(STR("uart2 init\r\n"));

	//Uart3SendStr(STR("uart3 init\r\n"));
	
	C_bt_init();
	C_bt_module_reset();
	C_bt_module_init();

	GSM_RST = 1; //����GSMģ��
	while(1)
	{
		
		if(C_bt_device_active())
		{
			LED2_ON;
			if(USB_USART_RX_STA&0x8000){
				//delay_ms(100);
				C_bt_sendBinary((char*)USB_USART_RX_BUF,USB_USART_RX_STA&0x3FFF);
				USB_USART_RX_STA=0;	
			}		
		}
		else
		{
			LED2_OFF;
		}
		
		if((ms_timer %2) == 0){
			C_bt_step();
		}
		
		//ģ���ʼ��
		if(C_bt_selftest()){
			LED2_OFF;
		}else{
			//LED2_ON;			
		}
	}
}
