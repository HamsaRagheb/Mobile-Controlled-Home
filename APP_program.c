/*
 * APP_program.c
 *
 *  Created on: Sep 19, 2023
 *      Author: hamsa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "USART_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "KPD_interface.h"
#include "LCD_interface.h"
#include "LDR_interface.h"
#include "SERVO_interface.h"
#include "ULTSONIC_interface.h"

#include "APP_interface.h"
#include "APP_config.h"

#include <avr/delay.h>

/*************************************************************************************************************************/

// extern u16 ReceivedData;

u16 APP_Users[10][2] =
{
		{1234, 1155},
		{1232, 1111},
		{4567, 1112},
		{3321, 1113},
		{1287, 1114},
		{8888, 1115},
		{9856, 1116},
		{7762, 1117},
		{6666, 1118},
		{1208, 1119},
};

static s8 APP_UserIDInx = -1;
static u8 Main_u8ServoFlag  = OPENED;
static u8 Main_u8ServoState = OFF;
u8 Local_u8Counter;
/*Servo using Timer1*/
Timer1_t Timer1=
{
		TIMER1_FAST_PWM_CUSTOM_TOP,
		PRSCLR_DIV_BY_8,
		OCM_FAST_PWM_NON_INVERTED,
		OCM_DISCONNECT,
		INT_DISABLE,
		INT_DISABLE,
		INT_DISABLE,
};
/*************************************************************************************************************************/

void APP_voidInit()
{
	PORT_voidInit();
	LCD_voidInit();
	ADC_voidInit();
	USART_voidInit();
}
/*************************************************************************************************************************/
/* Note!,
 *  any ID or Pass cosistes of 4 digits*/
void APP_voidLoginSystem()
{

	u8 Local_u8KPDKey, Local_u8IDArrSize = 0, Local_u8PassArrSize = 0, Local_u8Counter, Local_u8Counter2, Local_u8CheckID = 0;
	u16 Local_u16ID = NVALID, Local_u16Pass, Local_u8CheckPass = 0;
	u8 Local_u8IDArray[4], Local_u8PassArray[4], Local_u8FlagTrials = 0;

	while (1)
	{
		/*do
		{
			Local_u8KPDKey = KPD_u8GetPressedKey();

		} while (Local_u8KPDKey == 0xff);

		if(Local_u8KPDKey=='A')
		{
			LCD_voidSendString2("**** HELLO ****");
			LCD_voidPositionSet(1,0);
			LCD_voidSendString2("Let's Start ^_^");
			_delay_ms(2000);*/

		LCD_voidClearDisplay();
		LCD_voidSendString2("Enter ID: ");
		for (Local_u8Counter = 0; Local_u8Counter < 4; Local_u8Counter++)
		{
			do
			{
				Local_u8KPDKey = KPD_u8GetPressedKey();

			} while (Local_u8KPDKey == 0xff);

			if(Local_u8KPDKey==0||Local_u8KPDKey==1||Local_u8KPDKey==2||Local_u8KPDKey==3||Local_u8KPDKey==4||Local_u8KPDKey==5||Local_u8KPDKey==6||Local_u8KPDKey==7||Local_u8KPDKey==8||Local_u8KPDKey==9)
			{
				LCD_voidPositionSet(1, Local_u8Counter);
				LCD_voidSendNumber(Local_u8KPDKey);
				Local_u8IDArray[Local_u8IDArrSize++] = Local_u8KPDKey;
			}
			else if (Local_u8KPDKey == 'C')
			{
				LCD_voidClearDisplay();
				for (Local_u8Counter2 = 0; Local_u8Counter2 < Local_u8IDArrSize; Local_u8Counter2++)
				{
					Local_u8IDArray[Local_u8Counter2] = 0;
				}
				Local_u8IDArrSize = 0;
				break;
			}
			else if (Local_u8KPDKey == 'D')
			{
				Local_u8IDArrSize--;
				Local_u8Counter--;
				LCD_voidClearDisplay();
				LCD_voidSendString2("Enter ID: ");
				for (Local_u8Counter2 = 0; Local_u8Counter2 < Local_u8IDArrSize; Local_u8Counter2++)
				{
					LCD_voidPositionSet(1,Local_u8Counter2);
					LCD_voidSendNumber(Local_u8IDArray[Local_u8Counter2]);
				}
				Local_u8Counter=0;
			}
			if (Local_u8Counter == 3)
			{
				_delay_ms(200);
			}
		}
		LCD_voidClearDisplay();

		if (Local_u8IDArrSize != 0)
		{
			Local_u16ID = APP_u16StringtoNumber(Local_u8IDArray, 4);
			Local_u8CheckID = APP_u8CheckUserID(Local_u16ID);
		}
		if (Local_u8CheckID == 1)
		{
			while (Local_u8FlagTrials < 3)
			{
				LCD_voidSendString2("Enter Password: ");
				for (Local_u8Counter2 = 0; Local_u8Counter2 < 4; Local_u8Counter2++)
				{
					do
					{
						Local_u8KPDKey = KPD_u8GetPressedKey();

					} while (Local_u8KPDKey == 0xff);
					if(Local_u8KPDKey==0||Local_u8KPDKey==1||Local_u8KPDKey==2||Local_u8KPDKey==3||Local_u8KPDKey==4||Local_u8KPDKey==5||Local_u8KPDKey==6||Local_u8KPDKey==7||Local_u8KPDKey==8||Local_u8KPDKey==9)
					{
						Local_u8PassArray[Local_u8PassArrSize++] = Local_u8KPDKey;
						LCD_voidPositionSet(1, Local_u8Counter2);
						LCD_voidSendNumber(Local_u8KPDKey);
						_delay_ms(100);
						LCD_voidPositionSet(1, Local_u8Counter2);
						LCD_voidSendData('*');
					}
					else if (Local_u8KPDKey == 'C')
					{
						LCD_voidClearDisplay();
						LCD_voidSendString2("Enter Password: ");
						for (Local_u8Counter = 0; Local_u8Counter < Local_u8PassArrSize; Local_u8Counter++)
						{
							Local_u8PassArray[Local_u8Counter] = 0;
						}
						Local_u8PassArrSize = 0;
						Local_u8Counter2=0;
					}
					if (Local_u8Counter2 == 3)
					{
						_delay_ms(150);
					}
				}
				LCD_voidClearDisplay();
				Local_u16Pass = APP_u16StringtoNumber(Local_u8PassArray, 4);
				Local_u8CheckPass = APP_u8CheckUserPassword(Local_u16Pass);
				if (Local_u8CheckPass == 1)
				{
					break;
				}
				else if (Local_u8CheckPass == 0 && Local_u8FlagTrials < 2)
				{
					LCD_voidSendString2("Incorrect!");
					LCD_voidPositionSet(1, 0);
					LCD_voidSendString2("Try Again..");
					_delay_ms(500);
					LCD_voidClearDisplay();
				}
				Local_u8FlagTrials++;
				Local_u8PassArrSize = 0;
			}

			Local_u8PassArrSize = 0;
			if (Local_u8FlagTrials == 3 && Local_u8CheckPass != 1)
			{
				LCD_voidSendString2("Calling Police...");
				APP_voidCallingPolice();
			}
			/*else
			{

			}*/
			Local_u8FlagTrials = 0;
		}
		else if (Local_u8CheckID == 0 && Local_u8IDArrSize != 0)
		{
			LCD_voidSendString2("Incorrect!");
			LCD_voidPositionSet(1, 0);
			LCD_voidSendString2("Try Again..");
			_delay_ms(500);
			LCD_voidClearDisplay();
		}
		Local_u8IDArrSize = 0;
		if (Local_u8CheckPass == 1 || Local_u8FlagTrials == 3)
		{
			break;

		}
		LCD_voidClearDisplay();
		/*}
		else
		{

		}*/
	}
}
/*************************************************************************************************************************/

u16 APP_u16StringtoNumber(u8 *Copy_u8String, u8 Copy_u8StringSize)
{
	u16 Local_u16Number = 0;
	u8 Local_u8Index = 0;
	u32 Local_u32Val = 0;
	while (Local_u8Index < Copy_u8StringSize)
	{
		Local_u32Val = Copy_u8String[Local_u8Index];
		while (Local_u32Val != 0)
		{
			Local_u32Val = Local_u32Val / 10;
			Local_u16Number = Local_u16Number * 10;
		}
		Local_u16Number = Local_u16Number + Copy_u8String[Local_u8Index];
		Local_u8Index++;
	}

	return Local_u16Number;
}
/*************************************************************************************************************************/

u8 APP_u8CheckUserID(u16 Copy_u16EnteredData)
{
	u8 Local_u8Counter, Local_u8CheckID = NVALID;

	for (Local_u8Counter = 0; Local_u8Counter < 10; Local_u8Counter++)
	{
		if ((APP_Users[Local_u8Counter][0]) == Copy_u16EnteredData)
		{
			Local_u8CheckID = VALID;
			APP_UserIDInx = Local_u8Counter;
			break;
		}
	}
	return Local_u8CheckID;
}
/*************************************************************************************************************************/

u8 APP_u8CheckUserPassword(u16 Copy_u16EnteredData)
{
	u8 Local_u8CheckID = NVALID;

	if (APP_UserIDInx >= 0)
	{
		if ((APP_Users[APP_UserIDInx][1]) == Copy_u16EnteredData)
		{
			Local_u8CheckID = VALID;
			APP_UserIDInx = -1;
		}
	}
	return Local_u8CheckID;
}
/*************************************************************************************************************************/

/*************************************************************************************************************************/
void APP_voidLight_ON()
{
	LCD_voidClearDisplay();
	LCD_voidSendString2("___Light is ON___");

	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN4, DIO_u8PIN_HIGH);
}
/*************************************************************************************************************************/

void APP_voidLight_OFF()
{
	LCD_voidClearDisplay();
	LCD_voidSendString2("__Light is OFF__");

	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN1, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN2, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN3, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(LIGHT_PORT, LIGHT_PIN4, DIO_u8PIN_LOW);
}
/*************************************************************************************************************************/
void APP_voidCallingPolice()
{
	GIE_voidDisable();
	while (1)
	{
		DIO_u8SetPinValue(RED_LIGHT_PORT,RED_LIGHT_PIN, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_HIGH);
		_delay_ms(250);
		DIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_LOW);
		_delay_ms(250);
	}
}
/*************************************************************************************************************************/

void APP_voidDoorOpen(void)
{
	LCD_voidClearDisplay();
	LCD_voidSendString2("   WELCOME ^_^");
	LCD_voidPositionSet(1,0);
	LCD_voidSendString2("_Door is Opened_");
	if(Main_u8ServoFlag==OPENED && Main_u8ServoState==OFF)
	{
		TIMER1_u8Init(&Timer1);
		for(Local_u8Counter=0;Local_u8Counter<=180;Local_u8Counter++)
		{
			SERVO_u8Rotate(Local_u8Counter,&Timer1);
			_delay_ms(1);
		}
	}
	Main_u8ServoState=ON;
}
/*************************************************************************************************************************/

void APP_voidDoorClose(void)
{
	LCD_voidClearDisplay();
	LCD_voidSendString2("_Door is Closed_");
	LCD_voidPositionSet(1,0);
	//	LCD_voidSendString2("   BYE BYE :(");
	Main_u8ServoFlag=OPENED;
	if(Main_u8ServoFlag==OPENED && Main_u8ServoState==ON)
	{
		TIMER1_u8Init(&Timer1);
		for(Local_u8Counter=180;Local_u8Counter>=1;Local_u8Counter--)
		{
			SERVO_u8Rotate(Local_u8Counter,&Timer1);
			_delay_ms(1);
		}
	}
	Main_u8ServoState=OFF;
}
