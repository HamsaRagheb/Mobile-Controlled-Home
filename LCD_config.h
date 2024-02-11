/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     APP                ***********************/
/****************      SWC:       DIO                ***********************/
/****************      Date:      14/8/2023         ***********************/
/****************      Version:   1.00               ***********************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/****************************************************************************/
/******************************* MACRO **************************************/
/****************************************************************************/

/*The LCD Control Port, to be Configured based on project need */
#define        LCD_CONTROL_PORT          DIO_u8PORTD
/*The LCD Data Port, to be Configured based on project need */
#define        LCD_DATA_PORT             DIO_u8PORTC
/*LCD Register Select Pin*/
#define        LCD_RS_PIN                DIO_u8PIN7
/*LCD Read / Write Pin*/
#define        LCD_RW_PIN                DIO_u8PIN4
/*LCD Enable Pin*/
#define        LCD_E_PIN                 DIO_u8PIN3

#define        LCD_MAX_ARR_SIZE          16

/***************************************************************************/
#endif /* LCD_CONFIG_H_ */
