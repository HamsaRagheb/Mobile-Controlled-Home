/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       ADC               ***********************/
/****************      Date:      Aug 29, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"
/***************************************************************************/
/**********************************Global Variables**************************/

static u16  *ADC_pu16Reading = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;

static Chain_t*   ADC_psChain = NULL;
static u8   ADC_u8ChainIndex=0;

///Flags
static u8 ADC_u8BusyState= IDLE;
static u8 ADC_u8ConversionState;

/***************************************************************************/
/*Function to Initialize ADC*/
void ADC_voidInit(void)
{
	/*Check Reference Selection of ADC*/
#if  REFERENCE_SELECTION==VREF_EXT
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif REFERENCE_SELECTION==VREF_AVCC
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif REFERENCE_SELECTION==VREF_INT
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);

#else
#error "Wrong Voltage REFERENCE SELECTION! "

#endif
	/***************************************************************************/
	/*Check ADC Left Adjust Result*/
#if   ADC_RESOLUTION==8
	/*Activate ADLAR*/
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif ADC_RESOLUTION==10
	/*Deactivate ADLAR*/
	CLR_BIT(ADMUX,ADMUX_ADLAR);

#else
#error "Wrong ADC_RESOLUTION Option!"

#endif
	/***************************************************************************/
	/*Check the Prescaer*/
#if    ADC_PRESCALER==DIV_BY_2
	ADCSRA &=ADC_PRESCALER_MASK;

#elif  ADC_PRESCALER==DIV_BY_4
	ADCSRA &=ADC_PRESCALER_MASK;
	ADCSRA |=ADC_PRESCALER;

#elif  ADC_PRESCALER==DIV_BY_8
	ADCSRA &=ADC_PRESCALER_MASK;
	ADCSRA |=ADC_PRESCALER;

#elif  ADC_PRESCALER==DIV_BY_16
	ADCSRA &=ADC_PRESCALER_MASK;
	ADCSRA |=ADC_PRESCALER;

#elif  ADC_PRESCALER==DIV_BY_32
	ADCSRA &=ADC_PRESCALER_MASK;
	ADCSRA |=ADC_PRESCALER;

#elif  ADC_PRESCALER==DIV_BY_64
	ADCSRA &=ADC_PRESCALER_MASK;
	ADCSRA |=ADC_PRESCALER;

#elif  ADC_PRESCALER==DIV_BY_128
	ADCSRA &=ADC_PRESCALER_MASK;
	ADCSRA |=ADC_PRESCALER;

#else
#error "Wrong ADC_PRESCALER Option!"

#endif
	/***************************************************************************/
	/*Check ADC Interrupt */
#if ADC_INTERRUPT==Disabled
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

#elif 	ADC_INTERRUPT==Enabled
	SET_BIT(ADCSRA,ADCSRA_ADIE);

#else
#error "Wrong ADC_INTERRUPT Option!"

#endif
	/***************************************************************************/
	/*Check ADC Auto Trigger */
#if ADC_AUTO_TRIGGER==Disabled
	CLR_BIT(ADCSRA,ADCSRA_ADTE);

#elif 	ADC_AUTO_TRIGGER==Enabled
	SET_BIT(ADCSRA,ADCSRA_ADTE);
	/*Check ADC Auto Trigger Source */
#if     ADC_AUTO_TRIGGER_SOURCE==FREE_RUNNING
	SFIOR &=ADC_AUTO_TRIGGER_SRC_MASK;

#elif   ADC_AUTO_TRIGGER_SOURCE==Analog_Comparator
	SFIOR &=ADC_AUTO_TRIGGER_SRC_MASK;
	SFIOR |=ADC_AUTO_TRIGGER_SOURCE;

#elif   ADC_AUTO_TRIGGER_SOURCE==EXTI_INT0
	SFIOR &=ADC_AUTO_TRIGGER_SRC_MASK;
	SFIOR |=ADC_AUTO_TRIGGER_SOURCE;
#else
#error "Wrong ADC_AUTO_TRIGGER_SOURCE Option!"
#endif

#else
#error "Wrong ADC_AUTO_TRIGGER Option!"
#endif
	/***************************************************************************/
	/*Check ADC Enable */
#if ADC_ENABLE==Disabled
	CLR_BIT(ADCSRA,ADCSRA_ADEN);

#elif 	ADC_ENABLE==Enabled
	SET_BIT(ADCSRA,ADCSRA_ADEN);

#else
#error "Wrong ADC_ENABLE Option!"

#endif

}

/***************************************************************************/
/*Synchronous Function to Start Conversion */
/*Take care the TimeOut*/
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16ADCReading)
{

	u32 Local_32Counter=0;
	u8 Local_u8ErrorState=OK;

	/*This function will work if and only if the BusyState is IDLE*/
	if(ADC_u8BusyState==IDLE)
	{
		/*ADC is Busy Now!*/
		/*Make ADC Busy in order not to work until being IDLE*/
		ADC_u8BusyState=BUSY;

		/*Bit Masking*/
		/*Clear the MUX Bits in ADMUX register*/
		ADMUX &=ADC_CHANNEL_MUX_MASK;

		/*Set the required Channel into MUX bits*/
		ADMUX |=Copy_u8Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Polling Mode*/
		/*Busy Waiting until the Convrsion Complete Flag is Set or Counter reaching TIMEOUT*/
		while ((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_32Counter != ADC_32TIMEOUT ))
		{
			Local_32Counter++;
		}
		if(Local_32Counter == ADC_32TIMEOUT)
		{
			//Loop is broken because the timeout is reached
			Local_u8ErrorState=NOK;
		}
		else
		{
			//Loop is broken because flag is raised

			/*Flag Clearing in Polling Mode*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

			/*wanted code*/
			/*Return The Voltage in Digital Value*/
			*Copy_pu16ADCReading=ADCH;
			/*Make ADC is IDLE again*/
			ADC_u8BusyState=IDLE;
		}


	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
/***************************************************************************/
/*Synchronous Function to Start Chain of Conversions */
u8 ADC_u8StartChainConversionSynch(Chain_t* Copy_psADCChain)
{
	u8 Local_u8ErrorState=OK;

	/*This function will work if and only if the BusyState is IDLE*/
	if(ADC_u8BusyState==IDLE)
	{
		u8 Local_32Counter;
		if (Copy_psADCChain != NULL)
		{
			for(Local_32Counter=0;Local_32Counter<Copy_psADCChain->Size ;Local_32Counter++)
			{
				ADC_u8StartConversionSynch(Copy_psADCChain->ChannelArr[Local_32Counter] , Copy_psADCChain->ResultArr[Local_32Counter]);
			}
		}
		else
		{
			Local_u8ErrorState=NULL_POINTER;
		}

	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
/***************************************************************************/
/*Asynchronous Function to Start Conversion */
/*Take care of End of Job Notification */
u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16ADCReading, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;

	/*This function will work if and only if the BusyState is IDLE*/
	if(ADC_u8BusyState==IDLE)
	{
		if((Copy_pu16ADCReading != NULL)&&(Copy_pvNotificationFunc!=NULL))
		{
			/*ADC is Busy Now!*/
			/*Make ADC Busy in order not to work until being IDLE*/
			ADC_u8BusyState=BUSY;

			/*Change ADC Conversion State For ISR Function*/
			ADC_u8ConversionState=SINGLE_CONVERSION;

			//For ISR Function
			/*ADC Reading in Global Variable now*/
			ADC_pu16Reading=Copy_pu16ADCReading;
			/*ADC Notification Function in Global Variable now*/
			ADC_pvCallBackNotificationFunc=Copy_pvNotificationFunc;

			//Set Channel
			/*Bit Masking*/
			/*Clear the MUX Bits in ADMUX register*/
			ADMUX &=ADC_CHANNEL_MUX_MASK;

			/*Set the required Channel into MUX bits*/
			ADMUX |=Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			//do nothing!
			Local_u8ErrorState=NULL_POINTER;
		}

		return Local_u8ErrorState;
	}
	else
	{
		//do nothing
		Local_u8ErrorState=BUSY_FUNC;
	}
}
/***************************************************************************/
/*Asynchronous Function to Start Chain of Conversions*/
u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_psADCChain)
{
	u8 Local_u8ErrorState=OK;

	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_psADCChain != NULL)
		{
			/*Change ADC Conversion State For ISR Function*/
			ADC_u8ConversionState=CHAIN_CONVERSION;

			//Required Data For ISR Function
			/*Assignment the Global Variables*/
			ADC_psChain=Copy_psADCChain;

			/*Set the first Channel*/
			ADC_u8ChainIndex=0;
			ADMUX &=ADC_CHANNEL_MUX_MASK;
			ADMUX |=ADC_psChain->ChannelArr[ADC_u8ChainIndex];

			/*Start Conversion of first Channel*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;

}
/*ISR Function*/
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ConversionState==SINGLE_CONVERSION)
	{
		/*Check the Resolution &
		 *Read the ADC Current Result */
#if ADC_RESOLUTION==8
		*ADC_pu16Reading=ADCH;

#elif ADC_RESOLUTION==10
		*ADC_pu16Reading=ADC;
#endif

		/*Make ADC IDLE to make new calling for Asynchronous Function  */
		ADC_u8BusyState=IDLE;

		/*Invoke the Call Back Notification Function*/
		ADC_pvCallBackNotificationFunc();

		/*Disable ADC Conversion Complete Interrupt
		 *because the Conversion is Done */
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	/***************************************************************************/
	else if(ADC_u8ConversionState==CHAIN_CONVERSION)
	{
		/*Check the Resolution &
		 *Read the ADC Current Result */
#if ADC_RESOLUTION==8
		ADC_psChain->ResultArr[ADC_u8ChainIndex]=ADCH;

#elif ADC_RESOLUTION==10
		ADC_psChain->ResultArr[ADC_u8ChainIndex]=ADC;
#endif

		//Increment the Channel Array Index
		ADC_u8ChainIndex++;

		if(ADC_u8ChainIndex==ADC_psChain->Size)
		{
			/*Invoke the Call Back Notification Function*/
			ADC_psChain->NotiFunc();
			//Clear Array Index
			ADC_u8ChainIndex=0;

			/*Disable ADC Conversion Complete Interrupt
			 *because the Conversion is Done */
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			/*Make ADC IDLE to make new calling for Asynchronous Function  */
			ADC_u8BusyState=IDLE;

		}
		else if(ADC_u8ChainIndex!=ADC_psChain->Size)
		{
			//Set the Next Channel
			ADMUX &=ADC_CHANNEL_MUX_MASK;
			ADMUX |=ADC_psChain->ChannelArr[ADC_u8ChainIndex];

			//Start Next Conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}

	}

}



