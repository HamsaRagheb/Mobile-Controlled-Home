/*
 * APP_interface.h
 *
 *  Created on: Sep 19, 2023
 *      Author: hamsa
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_




void APP_voidInit();

void APP_voidLoginSystem();

u8 APP_u8CheckUserID(u16 Copy_u16EnteredData);

u8 APP_u8CheckUserPassword(u16 Copy_u16EnteredData);

u16 APP_u16StringtoNumber(u8* Copy_u8String,u8 Copy_u8StringSize);

void APP_voidLight_ON();

void APP_voidLight_OFF();

void APP_voidCallingPolice();

//void APP_voidTone();
void APP_voidDoorOpen(void);

void APP_voidDoorClose(void);

#endif /* APP_INTERFACE_H_ */
