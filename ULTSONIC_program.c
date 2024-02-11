/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ULTSONIC_program.c	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ULTSONIC_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the ULTSONIC sensor module functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "DIO_interface.h"

#include "util/delay.h"

#include "ULTSONIC_config.h"
#include "ULTSONIC_private.h"
#include "ULTSONIC_interface.h"

static void ULTSONIC_voidCaptureISR(void);
static void ULTSONIC_voidOvfISR(void);

static u16 ULTSONIC_u16Capture1 = 0;
static u16 ULTSONIC_u16Capture2 = 0;

static u16 ULTSONIC_u16OvfCounter = 0;
static u16 ULTSONIC_u16EchoOvfCounter = 0;

/**
 * @brief A function to measure the distance with ultrasonic using input capture unit of timer 1.
 * @param Copy_stUltsonicData Pointer to struct that carry the ultrasonic data.
 * @param Copy_u16Distance Pointer to return the distance in cm.
 * @return Error State.
 */
void ULTSONIC_u8MeasureDistance(const ULTSONIC_t *Copy_stUltsonicData, u16 *Copy_u16Distance)
{
	/*Define Variables*/
	u8 Local_u8ErrorState = OK;
	u8 Local_u8ErrorFounder = OK;
	u32 Local_u32EchoTime = 0;
	u32 Local_u32TimeoutCounter = 0;

	/*Initialize timer 1*/
	Timer1_t Local_stTimer1Cfg=
	{
		TIMER1_NORMAL,
		PRSCLR_DIV_BY_8,
		OCM_DISCONNECT,
		OCM_DISCONNECT,
		INT_DISABLE,
		INT_DISABLE,
		INT_ENABLE,
	};


//	if(Local_u8ErrorFounder == OK)
//	{
		/*Initialize and Enable Capture Unit and Overflow Interrupts of timer 1*/
		TIMER_u8SetCallBack(INT_TIMER1_CAPT,&ULTSONIC_voidCaptureISR);
		TIMER_u8SetCallBack(INT_TIMER0_OVF,&ULTSONIC_voidOvfISR);

		ICU_u8Init(RISING_EDGE,INT_ENABLE);
		TIMER1_u8Init(&Local_stTimer1Cfg);

		/*Trigger the ultrasonic to return its echo*/
		DIO_u8SetPinValue(Copy_stUltsonicData -> TrigPort, Copy_stUltsonicData -> TrigPin, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(Copy_stUltsonicData -> TrigPort, Copy_stUltsonicData -> TrigPin, DIO_u8PIN_LOW);


		/*Polling until the echo time is measured*/
		while(((ULTSONIC_u16Capture1 == 0) || (ULTSONIC_u16Capture2 == 0)) && (Local_u32TimeoutCounter < ULTSOINC_u32TIMEOUT))
		{
			Local_u32TimeoutCounter++;
		}

		/*Disable timer 1 and overflow interrupt of it*/
		TIMER_u8SetIntStatus(INT_TIMER1_OVF,INT_DISABLE);
		TIMER_u8SetIntStatus(INT_TIMER1_CAPT,INT_DISABLE);


		/*Check if there was overflow interrupts or not*/
		if(ULTSONIC_u16EchoOvfCounter == 0)
		{
			/*Calculate Echo Time in microseconds*/
			Local_u32EchoTime = ULTSONIC_u16Capture2 - ULTSONIC_u16Capture1;
		}
		else
		{
			/*Calculate Echo Time in microseconds*/
			if(ULTSONIC_u16Capture2 >= ULTSONIC_u16Capture1)
			{
				Local_u32EchoTime = (ULTSONIC_u16Capture2 - ULTSONIC_u16Capture1) + (ULTSONIC_u16EchoOvfCounter * 65536u);
			}
			else if(ULTSONIC_u16Capture2 < ULTSONIC_u16Capture1)
			{
				Local_u32EchoTime = (ULTSONIC_u16Capture1 - ULTSONIC_u16Capture2) + (ULTSONIC_u16EchoOvfCounter * 65536u);
			}
		}

		/*Measure Distance using Echo Time*/
		*Copy_u16Distance = (((f32) Local_u32EchoTime / 2.0) * (34.0 / 1000.0));

		/*Reset the global variables*/
		ULTSONIC_u16Capture1 = 0;
		ULTSONIC_u16Capture2 = 0;
		ULTSONIC_u16OvfCounter = 0;
		ULTSONIC_u16EchoOvfCounter = 0;
//	}
//	else
//	{
//		Local_u8ErrorState = NOK;
//	}

	/*Return Error State*/
//	return Local_u8ErrorState;
}

/*Input Capture ISR*/
static void ULTSONIC_voidCaptureISR(void)
{
	static u8 Local_u8Counter = 0;

	Local_u8Counter++;

	if(Local_u8Counter == 1)
	{
		/*Enable Overflow interrupt of timer1*/
//		TIMER_u8SetIntStatus(INT_TIMER1_CAPT,INT_ENABLE);
		ULTSONIC_u16Capture1 = ICU_u16ReadInputCapture();
		ICU_u8SetEdge(FALLING_EDGE);
	}
	else if(Local_u8Counter == 2)
	{
		ULTSONIC_u16Capture2 = ICU_u16ReadInputCapture();
		ULTSONIC_u16EchoOvfCounter = ULTSONIC_u16OvfCounter;
		Local_u8Counter = 0;
	}
}

/*Overflow ISR*/
static void ULTSONIC_voidOvfISR(void)
{

	ULTSONIC_u16OvfCounter++;
}






























