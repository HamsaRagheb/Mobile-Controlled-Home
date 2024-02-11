/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     HAL                ***********************/
/****************      SWC:       LCD                ***********************/
/****************      Date:      14/8/2023         ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/
#include <avr/delay.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


void LCD_voidInit()
{
	/******************************** Direction ***************************************/
	/*Data or Command Port Direction as Output*/
	//	DIO_u8SetPortDirection(LCD_DATA_PORT,DIO_u8PORT_OUTPUT);
	/*Set the Control Pins as Output*/
	/*Set Register Select pin Direction as Output*/
	//	DIO_u8SetPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_u8PIN_OUTPUT);
	/*Set Read/Write pin Direction as Output*/
	//	DIO_u8SetPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_u8PIN_OUTPUT);
	/*Set Enable pin Direction as Output*/
	//	DIO_u8SetPinDirection(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8PIN_OUTPUT);
	/***************************************************************************/
	/*Wait more than 30ms after connecting LCD to Power(from DataSheet) */
	_delay_ms(40);

	/*Initialization LCD of 8-Mode*/
	/******** DataSheet*******/
	/*Function Set*/
	/* Initialize LCD Configuration with : 0b000011NFXX
	 * where N: Number of lines, 0: For 1 line   &    1: For 2 line
	 * where F: Font size, 0: For 5*8    &   1: For 5*11
	 * where X: Don't care
	 */
	LCD_voidSendCommand(0b00111000);

	/*Display ON/OFF Control*/
	/*Display Claer(Claer LCD)*/
	/* Display on/off Control: 0b0000001DCB
	 * where D: Display, 0: For Disable   &   1: For Enable
	 * where C: Cursor,  0: For Disable    &    1: For Enable
	 * where B: Blinking Cursor, 0: For Blinking   &   1: For Fixed
	 */
	LCD_voidSendCommand(0b00001100);

	/* Clear the Display */
	LCD_voidSendCommand(0b00000001);
	/*End of LCD Initialization*/

}
/*Function used to send a COMMAND to LCD*/
void LCD_voidSendCommand(u8 Copy_u8Command)
{
	/*To send Command,Set RS pin to LOW*/
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_u8PIN_LOW);

	/*Enable Write mode, Set RW pin to LOW*/
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set the Command Port*/
	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Command);

	/*Enable Puls*/
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8PIN_LOW);

}

void LCD_voidSendData(u8 Copy_u8Character)
{
	/*To send Data,Set RS pin to HIGH*/
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_u8PIN_HIGH);

	/*Enable Write mode, Set RW pin to LOW*/
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set the Data Port*/
	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Character);

	/*Enable Puls*/
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_u8PIN_LOW);


}

void LCD_voidSendString(char * Copy_u8PtrToChar, u8 Copy_u8LengthOfStr){

	for(u8 i = 0; (i<Copy_u8LengthOfStr) && (Copy_u8PtrToChar[i] != '\0'); i++ ){

		LCD_voidSendData(Copy_u8PtrToChar[i]);
	}

}

void LCD_voidPositionSet(u8 Copy_u8RowPos,u8 Copy_u8ColPos)
{

	u8 Local_u8DDRAMAddress;
	/*Check the Row to select the right DDRAM Address*/
	if(Copy_u8RowPos==0)
	{
		/*DDRAN Address for the first ROW*/
		Local_u8DDRAMAddress=Copy_u8ColPos;
	}
	else if(Copy_u8RowPos==1)
	{
		/*DDRAN Address for the second ROW*/
		Local_u8DDRAMAddress=Copy_u8ColPos+0x40;
	}
	/*Select the right Address to write in LCD*/
	/*NOTE!, The MSB must be ONE(Datasheet)*/
	LCD_voidSendCommand(Local_u8DDRAMAddress+128);

}
/*Function to send Speacial Characters to LCD*/
void LCD_voidSendSpeacialCharacter(u8* Copy_u8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8Row,u8 Copy_u8Col)
{
	/*Variable to store the CGRAM Address*/
	u8 Local_u8CGRAMAddress;
	/*Loop Counter*/
	u8 Local_u8Counter;

	/*No overwrite on any Location*/
	/*Calculate the CGRAM Address*/
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;
	/*Set CGRAM Address Command to LCD with Setting Bit 6,and Clearing Bit 7 (Datasheet)*/
	LCD_voidSendCommand(Local_u8CGRAMAddress+64);
	/*Write each Byte of (8 Bytes) in the Pattern(Character)*/
	for(Local_u8Counter=0; Local_u8Counter<8; Local_u8Counter++)
	{
		LCD_voidSendData(Copy_u8Pattern[Local_u8Counter]);
	}
	/*Select the Position that you want to Write on it the Pattern */
	LCD_voidPositionSet(Copy_u8Row,Copy_u8Col);
	/*Write data to CGRAM or DDRAM(Datasheet)*/
	LCD_voidSendData(Copy_u8PatternNumber);

	/*Overwrite Location to Overwrite on it*/
}
/*Function to Send Number to LCD*/
void LCD_voidSendNumber(u32 Copy_u32Number)     //123
{
	u8  Local_u8ArrNumber[LCD_MAX_ARR_SIZE];
	s8 Local_u8Counter=0,Local_u8ArrSize=0;

	if(Copy_u32Number==0)
	{
		LCD_voidSendData(0b00110000);
	}
	else
	{
		while(Copy_u32Number>0)
		{
			Local_u8ArrNumber[Local_u8Counter]=Copy_u32Number % 10; //123%10=3=(ARR[0]) -- 12%10=2=(ARR[1]) -- 1%10=1=(ARR[2])
			Copy_u32Number =Copy_u32Number /10 ;                    //123/10=12-- 12/10=1 -- 1/10=0
			Local_u8Counter++;                                      //1 -- 2 -- 3
			Local_u8ArrSize++;                                      //1 -- 2 -- 3
		}

		for(Local_u8Counter=Local_u8ArrSize-1 ; Local_u8Counter>=0 ; Local_u8Counter--)
		{
			switch(Local_u8ArrNumber[Local_u8Counter])     //ARR[2]=1   -- ARR[1]=2 -- ARR[0]=3
			{
			case 0: LCD_voidSendData(0b00110000);
			break;
			case 1: LCD_voidSendData(0b00110001);
			break;
			case 2: LCD_voidSendData(0b00110010);
			break;
			case 3: LCD_voidSendData(0b00110011);
			break;
			case 4: LCD_voidSendData(0b00110100);
			break;
			case 5: LCD_voidSendData(0b00110101);
			break;
			case 6: LCD_voidSendData(0b00110110);
			break;
			case 7: LCD_voidSendData(0b00110111);
			break;
			case 8: LCD_voidSendData(0b00111000);
			break;
			case 9: LCD_voidSendData(0b00111001);
			break;
			}
		}
	}

}

/*Function to Display Name in Sinwave*/
/*void LCD_SinwaveName(const char* Copy_pu8Name)
{
	u8 Local_u8Row,Local_u8Col,Local_NameLength=0;
	Local_u8Col=0;
	Local_u8Row=0;

	while(Copy_pu8Name[Local_NameLength] != '\0')
	{
		Local_NameLength++;

	}

	for(Local_u8Col=0; Local_u8Col <= 16-Local_NameLength ; Local_u8Col++)
	{
		LCD_voidPositionSet(Local_u8Row,Local_u8Col);
		LCD_voidSendString(Copy_pu8Name);
		_delay_ms(250);
		/* Clear the Display */
//		LCD_voidSendCommand(0b00000001);
/*Toggle the Row*/
/*	Local_u8Row ^=1;
	}

}*/
/*Function to Clear LCD*/
void LCD_voidClearDisplay()
{
	/* Clear the Display */
	LCD_voidSendCommand(0b00000001);
}

void LCD_voidSendString2(const char* Copy_pu8String)
{

	while(*Copy_pu8String!='\0')

	{
		LCD_voidSendData(*Copy_pu8String);
		Copy_pu8String++;
	}

}











