/*
 * LDR_program.c
 *
 *  Created on: Sep 18, 2023
 *      Author: hamsa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

//MCAL
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"


//HAL
#include "LCD_interface.h"

#include "LDR_interface.h"
#include "LDR_config.h"

#include <avr/delay.h>


/*Function to start the conversion*/
u8 LDR_u8GetDigitalReading(u8 Copy_u8Channel, u16* Copy_pu16ADCDigitalReading)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pu16ADCDigitalReading != NULL)
	{
		switch(Copy_u8Channel)
		{
		case LDR_u8ADC_CHANNEL0:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC0,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL1:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC1,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL2:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC2,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL3:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC3,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL4:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC4,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL5:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC5,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL6:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC6,Copy_pu16ADCDigitalReading); break;
		case LDR_u8ADC_CHANNEL7:ADC_u8StartConversionSynch(ADC_SINGLE_ENDED_ADC7,Copy_pu16ADCDigitalReading); break;
		default: Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}



/*Function to turn ON  LEDs depend on ADC Digital Value*/
u8 LDR_u8TurnedOnLEDsNumber(u16* Copy_pu16ADCDigitalReading)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pu16ADCDigitalReading != NULL)
	{
		u8 Local_u8LEDsMappingNumber,Local_u8ONLEDsNumber,Local_u8Counter;
		/*Function to Calculate Number of LEDs Must be ON*/
		/*Note!
		 *
		 *If the Current ADC Reading value is greater than ADC Max Reading value,
		 *Returned value will be negative number!
		 *
		 **/
		Local_u8LEDsMappingNumber=MATH_s32Map(LDR_MIN_READING,LDR_MAX_READING,LDR_MIN_LEDsNumber,LDR_MAX_LEDsNumber,*Copy_pu16ADCDigitalReading);
		Local_u8ONLEDsNumber=LDR_MAX_LEDsNumber-Local_u8LEDsMappingNumber;

		DIO_u8SetPortValue(LDR_LEDs_PORT,DIO_u8PORT_LOW);
		for(Local_u8Counter=0; Local_u8Counter<Local_u8ONLEDsNumber; Local_u8Counter++)
		{
			DIO_u8SetPinValue(LDR_LEDs_PORT,Local_u8Counter,DIO_u8PIN_HIGH);
		}
		/*Display the Digital value of ADC reading on LCD*/
		LCD_voidSendString2("ADC Reading:");
		LCD_voidPositionSet(0,12);
		LCD_voidSendNumber(*Copy_pu16ADCDigitalReading);
		LCD_voidPositionSet(1,0);
		LCD_voidSendString2("ON LEDs:");
		LCD_voidPositionSet(1,12);
		LCD_voidSendNumber(Local_u8ONLEDsNumber);

		/*Delay in ms using Timer2*/
		Timer_t Timer2= {TIMER_CTC,PRSCLR_DIV_BY_8,OCM_DISCONNECT,INT_DISABLE,INT_DISABLE};
		TIMER2_u8Init(&Timer2);
		TIMER2_delay_ms(&Timer2,250);
		LCD_voidClearDisplay();
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}




