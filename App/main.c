#define F_CPU 16000000UL
#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"



int main(void)
{
	uint8 KPD_u8NO_PRESSEDKEY_VAL=0xff;
	uint8 num_one = 0;
	uint8 num_two = 0;
	uint8 oper = 0;
	uint8 flag = 0;
		
	PORT_voidInit();
	
	CLCD_voidInit();
	while (1)
	{
		num_one=0;
		num_two=0;
		oper=0;
		
		while(1)  // take n_1 from user
		{
			flag=1;
			
			KPD_u8NO_PRESSEDKEY_VAL=KPD_u8GetPressedKey();
			if(KPD_u8NO_PRESSEDKEY_VAL != 0xff)
			{
				switch(KPD_u8NO_PRESSEDKEY_VAL)
				{
					case 'N' : CLCD_voidClearLCD();break;
					case '+' :
					case '-' :
					case '*' :
					case '/' :
					          CLCD_voidSendData(KPD_u8NO_PRESSEDKEY_VAL);
							  oper=KPD_u8NO_PRESSEDKEY_VAL;
							  flag=0;
							  break;
					case '=' :
						     break;
					default:
					      CLCD_voidSendData(KPD_u8NO_PRESSEDKEY_VAL);
						  num_one=(num_one*10)+(KPD_u8NO_PRESSEDKEY_VAL-48);
						  flag=1;
						  break;
					  
				}
			}
			if(flag==0)
			{
				break;
			}
		}
		while(1)  //take n_2 from user 
		{
			flag=1;
			KPD_u8NO_PRESSEDKEY_VAL=KPD_u8GetPressedKey();
			if(KPD_u8NO_PRESSEDKEY_VAL != 0xff)
			{
				switch(KPD_u8NO_PRESSEDKEY_VAL)
				{
					case 'N' : CLCD_voidClearLCD();flag=0;break;
					case '+' : 
					case '-' :
					case '*' :
					case '/' :
					         break;
     				case '=' :
					      flag=0;
						  break;
					default:
					      CLCD_voidSendData(KPD_u8NO_PRESSEDKEY_VAL);
						  num_two= (num_two*10) + (KPD_u8NO_PRESSEDKEY_VAL-48);
						  flag=1;
						  break; 	  
				}
			}
			if(flag==0)
			{
				break;
			}
		}
		if((flag==0)&&(KPD_u8NO_PRESSEDKEY_VAL=='='))
		{
			CLCD_voidSendData('=');
			switch(oper)
			{
				case '+' : CLCD_voidWriteNumber((num_one+num_two));break;
				case '-' :CLCD_voidWriteNumber((num_one-num_two));break;
				case '*' :CLCD_voidWriteNumber((num_one*num_two));break;
				case '/' :CLCD_voidWriteNumber((num_one/num_two));break;
			

			}
		}
	}
}
