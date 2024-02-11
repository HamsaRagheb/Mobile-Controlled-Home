//***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     HAL                ***********************/
/****************      SWC:       KPD                ***********************/
/****************      Date:      17/8/2023          ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "PORT_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"

#include "KPD_private.h"



u8  KPD_u8GetPressedKey()
{
	u8 Local_u8PinState;
	/*Loop Counters*/
	u8 Local_u8RowCounter,Local_u8ColCounter;
	/*variable to return from this function if no Key Pressed */
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;

	/*Array of Keypad Values*/
	/*Static-> to Stop this Array from Pushing to Stack ans Save the Memory*/
	static u8 Local_u8KPDArr[KPD_ROWS_NUMBER][KPD_COLUMNS_NUMBER]=KPD_ARRAY;

	/*Array of Columns Pins*/
	/*Static-> to Stop this Array from Pushing to Stack ans Save the Memory*/
	static u8 Local_u8ColPinsArr[KPD_COLUMNS_NUMBER]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};

	/*Array of Rows Pins*/
	/*Static-> to Stop this Array from Pushing to Stack ans Save the Memory*/
	 static u8 Local_u8RowPinsArr[KPD_ROWS_NUMBER]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};

	/*Nested Loop to Check the keys*/
	/*Columns Loop*/
	for(Local_u8ColCounter=0; Local_u8ColCounter<KPD_COLUMNS_NUMBER; Local_u8ColCounter++)
	{
		/*Activate current columns*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColPinsArr[Local_u8ColCounter],DIO_u8PIN_LOW);
		/*Rows Loop*/
		for(Local_u8RowCounter=0; Local_u8RowCounter<KPD_ROWS_NUMBER; Local_u8RowCounter++)
		{
			/*Read which Row in corresponding col its key is Pressed*/
			DIO_u8GetPinValue(KPD_PORT,Local_u8RowPinsArr[Local_u8RowCounter],&Local_u8PinState);

			/*Check if the key is Pressed*/
			if(LOGIC_ZERO==Local_u8PinState)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowCounter][Local_u8ColCounter];

				/*Pooling(Busy waiting until the key is Released)*/
				while(LOGIC_ZERO==Local_u8PinState)
				{
					/*Read which Row in corresponding col its key is Pressed*/
					DIO_u8GetPinValue(KPD_PORT,Local_u8RowPinsArr[Local_u8RowCounter],&Local_u8PinState);

				}
				return Local_u8PressedKey;
			}
			/* if the key is not Pressed*/
			else
			{

			}
		}

		/*Deactivate current columns*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColPinsArr[Local_u8ColCounter],DIO_u8PIN_HIGH);

	}
	return Local_u8PressedKey;
}



