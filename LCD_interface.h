/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     HAL                ***********************/
/****************      SWC:       LCD                ***********************/
/****************      Date:      14/8/2023         ***********************/
/****************      Version:   1.00               ***********************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/**************************************************************************/
/***************************** Function Prototypes ************************/
/**************************************************************************/
/*LCD Initialization, NOTE: Must be called before using LCD Functions */
void LCD_voidInit();
/*Function used to send a COMMAND to LCD*/
void LCD_voidSendCommand(u8 Copy_u8Command);
/*Function used to send a DATA to LCD*/
void LCD_voidSendData(u8 Copy_u8Character);
/*Function used to send a STRING to LCD*/
void LCD_voidSendString(char * Copy_u8PtrToChar, u8 Copy_u8LengthOfStr);
void LCD_voidSendString2(const char* Copy_pu8String);
/*Function to Control the POSITION of written characters*/
void LCD_voidPositionSet(u8 Copy_u8RowPos,u8 Copy_u8ColPos);
/*Function to send Speacial Characters to LCD*/
void LCD_voidSendSpeacialCharacter(u8* Copy_u8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8Row,u8 Copy_u8Col);
/*Function to Send Number to LCD*/
void LCD_voidSendNumber(u32 Copy_u8Number);
/*Function to Display Name in Sinwave*/
void LCD_SinwaveName(const char* Copy_pu8Name);
/*Function to Clear LCD*/
void LCD_voidClearDisplay();
/*Function to Clear LCD Locations of CGRAM*/
void ClearCurrentString(u8 RowNo , u8 ColNo );
/**************************************************************************/

#endif /* LCD_INTERFACE_H_ */
