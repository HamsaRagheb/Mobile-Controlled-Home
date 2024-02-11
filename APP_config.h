/*
 * APP_config.h
 *
 *  Created on: Sep 19, 2023
 *      Author: hamsa
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_



/*Set UART Messages Macros*/
#define        OPEN_THE_DOOR				     '1'
#define        CLOSE_THE_DOOR				     '2'
#define        TURN_ON_LIGHT				     '3'
#define        CONTROL_LIGHT_LEDs		         '4'
#define        TURN_OFF_LIGHT				     '5'
#define        ALARM                             '6'
#define        OPEN_THE_FAN				         '7'
#define        CONTROL_THE_FAN_SPEED		     '8'
#define        CLOSE_THE_FAN				     '9'







#define        LIGHT_PORT                         DIO_u8PORTA
#define        LIGHT_PIN1                         DIO_u8PIN0
#define        LIGHT_PIN2                         DIO_u8PIN1
#define        LIGHT_PIN3                         DIO_u8PIN2
#define        LIGHT_PIN4                         DIO_u8PIN3

#define         LDR_MAX_READING                   240
#define         LDR_MIN_READING                   0

#define         LDR_MAX_LEDsNumber                4
#define         LDR_MIN_LEDsNumber                0


#define         LDR_LEDs_PORT                      DIO_u8PORTA

#define         CLOSED                              0
#define         OPENED                              1
#define         ON                                  2
#define         OFF                                 3


#define         BUZZER_PORT                         DIO_u8PORTA
#define         BUZZER_PIN                          DIO_u8PIN5

#define         RED_LIGHT_PORT                      DIO_u8PORTA
#define         RED_LIGHT_PIN                       DIO_u8PIN0


#define         FAN_PORT                            DIO_u8PORTA
#define         FAN_PIN                             DIO_u8PIN6

//#define

#endif /* APP_CONFIG_H_ */
