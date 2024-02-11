/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     HAL                ***********************/
/****************      SWC:       KPD                ***********************/
/****************      Date:      17/8/2023          ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/***************************************************************************/
/***************************************************************************/
/* Application Dependent MACROS */
/* Note!,This MACROS can be Changed */

#define        KPD_NO_PRESSED_KEY           0xff
#define        KPD_PORT                     DIO_u8PORTB
#define        KPD_ARRAY                    {{1,2,3,'A'},{4,5,6,'B'},{7,8,9,'C'},{'*',0,'=','D'}}

#define        KPD_COLUMN0_PIN              DIO_u8PIN0
#define        KPD_COLUMN1_PIN              DIO_u8PIN1
#define        KPD_COLUMN2_PIN              DIO_u8PIN2
#define        KPD_COLUMN3_PIN              DIO_u8PIN3

#define        KPD_ROW0_PIN                 DIO_u8PIN4
#define        KPD_ROW1_PIN                 DIO_u8PIN5
#define        KPD_ROW2_PIN                 DIO_u8PIN6
#define        KPD_ROW3_PIN                 DIO_u8PIN7


#endif /* KPD_CONFIG_H_ */
