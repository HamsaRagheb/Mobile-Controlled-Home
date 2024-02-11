/*
 * ULTRASONIC_program.c
 *
 *  Created on: Sep 22, 2023
 *      Author: hamsa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"

#include <util/delay.h>

#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_config.h"


static void ULTSONIC_voidCaptureISR(void);

static void ULTSONIC_voidOvfISR(void);

static u16 ULTSONIC_u16Capture1Reading = 0;
static u16 ULTSONIC_u16Capture2Reading = 0;

static u16 ULTSONIC_u16OvfCounter = 0;
static u16 ULTSONIC_u16EchoOvfCounter = 0;


void  ULTRASONIC_u8MeasureDistance(ULTRASONIC_t* Copy_psUltsonicTrigData, u16* Copy_u16Distance)
{

	/*Define Variables*/
	u8 Local_u8ErrorState = OK;
	u8 Local_u8ErrorFounder = OK;
	u32 Local_u32EchoTime = 0u;
	u32 Local_u32TimeoutCounter = 0u;

	/*Initialize and Enable Capture Unit and Overflow Interrupts of timer 1*/
	TIMER_u8SetCallBack(INT_TIMER1_OVF,&ULTSONIC_voidOvfISR);
	TIMER_u8SetCallBack(INT_TIMER1_CAPT,&ULTSONIC_voidCaptureISR);
	TIMER_u8SetIntStatus(INT_TIMER1_OVF,INT_ENABLE);
	ICU_u8Init(RISING_EDGE,INT_ENABLE);

	/*Trigger the ultrasonic to return its echo*/
	DIO_u8SetPinValue(Copy_psUltsonicTrigData -> TrigPort, Copy_psUltsonicTrigData -> TrigPin, DIO_u8PIN_HIGH);
	_delay_us(100);
	DIO_u8SetPinValue(Copy_psUltsonicTrigData -> TrigPort, Copy_psUltsonicTrigData -> TrigPin, DIO_u8PIN_LOW);

	/*Polling until the echo time is measured*/
	while(((ULTSONIC_u16Capture1Reading == 0u) || (ULTSONIC_u16Capture2Reading == 0u)) && (Local_u32TimeoutCounter < ULTSOINC_u32TIMEOUT))
	{
		Local_u32TimeoutCounter++;
	}

	/*Disable timer 1 and overflow interrupt of it*/
	TIMER_u8SetIntStatus(INT_TIMER1_OVF,INT_DISABLE);
	TIMER_u8SetIntStatus(INT_TIMER1_CAPT,INT_DISABLE);
	//	TIMER_u8SetIntStatus(TIMER1);

	/*Check if there was overflow interrupts or not*/
	if(ULTSONIC_u16EchoOvfCounter == 0)
	{
		/*Calculate Echo Time in microseconds*/
		Local_u32EchoTime = ULTSONIC_u16Capture2Reading - ULTSONIC_u16Capture1Reading;
	}
	else
	{
		/*Calculate Echo Time in microseconds*/
		if(ULTSONIC_u16Capture2Reading >= ULTSONIC_u16Capture1Reading)
		{
			Local_u32EchoTime = (ULTSONIC_u16Capture2Reading - ULTSONIC_u16Capture1Reading) + (ULTSONIC_u16EchoOvfCounter * 65536);
		}
		else if(ULTSONIC_u16Capture2Reading < ULTSONIC_u16Capture1Reading)
		{
			Local_u32EchoTime = (ULTSONIC_u16Capture1Reading - ULTSONIC_u16Capture2Reading) + (ULTSONIC_u16EchoOvfCounter * 65536);
		}
	}

	/*Measure Distance using Echo Time*/
	*Copy_u16Distance = (((f32) Local_u32EchoTime / 2.0) * (34.0 / 1000.0));

	/*Reset the global variables*/
	ULTSONIC_u16Capture1Reading = 0u;
	ULTSONIC_u16Capture2Reading = 0u;
	ULTSONIC_u16OvfCounter = 0u;
	ULTSONIC_u16EchoOvfCounter = 0u;

}

static void ULTSONIC_voidCaptureISR(void)
{

	static u8 Local_u8Counter = 0;
	if(Local_u8Counter == 1)
	{
		/*Enable Overflow interrupt of timer1*/
		TIMER_u8SetIntStatus(INT_TIMER1_OVF,INT_ENABLE);
		ULTSONIC_u16Capture1Reading = ICU_u16ReadInputCapture();
		ICU_u8SetEdge(FALLING_EDGE);
	}
	else if(Local_u8Counter == 2)
	{
		ULTSONIC_u16Capture2Reading = ICU_u16ReadInputCapture();
		ULTSONIC_u16EchoOvfCounter = ULTSONIC_u16OvfCounter;
		Local_u8Counter = 0;
	}

}


/*Overflow ISR*/
static void ULTSONIC_voidOvfISR(void)
{
	ULTSONIC_u16OvfCounter++;
}

