/*
 * KPD_Program.c
 *
 *  Created on: Mar 20, 2024
 *      Author: User
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "KPD_Interface.h"
#include "KPD_Config.h"
#include "KPD_Private.h"
#include <util/delay.h>


void KPD_Init(void)
{
	DIO_ReturnType_State_t_Connect_Pullup(KPD_PORT,KPD_R0,DIO_PIN_HIGH);
	DIO_ReturnType_State_t_Connect_Pullup(KPD_PORT,KPD_R1,DIO_PIN_HIGH);
	DIO_ReturnType_State_t_Connect_Pullup(KPD_PORT,KPD_R2,DIO_PIN_HIGH);
	DIO_ReturnType_State_t_Connect_Pullup(KPD_PORT,KPD_R3,DIO_PIN_HIGH);

	DIO_u8SetPinDirection(KPD_PORT,KPD_C0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C1,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C2,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C3,DIO_PIN_OUTPUT);


	DIO_u8SetPinValue(KPD_PORT,KPD_C0,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C1,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C2,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C3,DIO_PIN_HIGH);
}
u8 KPD_u8GetPressed(void)
{
	u8 local_u8ReturnData=NOTPRESSED;
	u8 local_u8GetPressed;
	u8 local_u8col;
	u8 local_u8Row;
	for(local_u8col=KPD_COL_INIT ;local_u8col <KPD_COL_END+1;local_u8col++)
	{
		DIO_u8SetPinValue(KPD_PORT,local_u8col,DIO_PIN_LOW);
		for(local_u8Row=KPD_ROW_INIT;local_u8Row<KPD_ROW_END+1;local_u8Row++)
		{
			DIO_u8GetPinValue(KPD_PORT,local_u8Row,&local_u8GetPressed);
			if(local_u8GetPressed==0)
			{
				_delay_ms(5);
				DIO_u8GetPinValue(KPD_PORT,local_u8Row,&local_u8GetPressed);
				if(local_u8GetPressed==0)
				{
					local_u8ReturnData=KPD_buttons[local_u8Row-KPD_ROW_INIT][local_u8col-KPD_COL_INIT];
				}
				DIO_u8GetPinValue(KPD_PORT,local_u8Row,&local_u8GetPressed);
				while(local_u8GetPressed==0)
				{
					DIO_u8GetPinValue(KPD_PORT,local_u8Row,&local_u8GetPressed);

				}
				break;
			}
		}
		DIO_u8SetPinValue(KPD_PORT,local_u8col,DIO_PIN_HIGH);

	}
	return local_u8ReturnData;
}

