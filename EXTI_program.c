/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       EXTI               ***********************/
/****************      Date:      Aug 22, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_register.h"
/***************************************************************************/
/***************************************************************************/
/**************Global Pointer To Function To Hold ISR Address*****************************/
void (*EXTI_pvINT0Func)(void) = NULL;
void (*EXTI_pvINT1Func)(void) = NULL;
void (*EXTI_pvINT2Func)(void) = NULL;

/***************************************************************************/
/***************************************************************************/

/*Function to Initialize INT0 using Pre Build Config.*/
void EXTI_voidINT0Init()
{
	/*1- Check the Sense Control for INT0*/
#if   INT0_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif   INT0_SENSE==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif   INT0_SENSE==FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif   INT0_SENSE==RAISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "Wrong INT0_SENSE Configuration Option"

#endif
	/*2- Check Peripherial Interrupt Enable */
#if INT0_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT0);

#elif INT0_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error "Wrong INT0_INITIAL_STATE Configuration Option"

#endif

}
/*Function to Initialize INT1 Pre Build Config.*/
void EXTI_voidINT1Init()
{
	/*Check the Sense Control of INT1*/
#if INT1_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE==FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE==RAISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error "Wrong INT1_SENSE Configuration Option ";

#endif
	/***************************************************************************/
	/*Check Peripherial Interrupt Enable of INT1*/
#if  INT1_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT1);

#elif  INT1_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
	"Wrong INT1_INITIAL_STATE Configuration Option ";
#endif
}
/*Function to Initialize INT2 Pre Build Config.*/
void EXTI_voidINT2Init()
{
	/*Check Sense Control of INT2*/
#if INT2_SENSE==FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCR_ISC2);

#elif INT2_SENSE==RAISING_EDGE
	SET_BIT(MCUCSR,MCUCR_ISC2);

#else
#error "Wrong INT2_SENSE Configuration Option ";

#endif
	/***************************************************************************/
	/*Check Peripherial Interrupt Enable of INT2*/
#if INT2_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT2);

#elif INT2_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
	"Wrong INT2_INITIAL_STATE Configuration Option ";
#endif
}
/***************************************************************************/
/*Function to Set Sense Control using Post Build Config. */
u8 EXTI_u8INTSetSenseControl(u8 Copy_u8Interrupt,u8 Copy_u8SenseControl)
{
	u8 Local_u8ErrorState=OK;
	/*Set INT0 Sense Control */
	if(Copy_u8Interrupt==EXTI_INT0)
	{
		switch(Local_u8ErrorState)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case RAISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		default:
			Local_u8ErrorState=NOK;
			break;
		}
	}
	/*Set INT1 Sense Control */
	else if(Copy_u8Interrupt==EXTI_INT1)
	{
		switch(Copy_u8SenseControl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		case RAISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		default:
			Local_u8ErrorState=NOK;
			break;
		}
	}
	/*Set INT2 Sense Control */
	else if(Copy_u8Interrupt==EXTI_INT2)
	{
		switch(Copy_u8SenseControl)
		{
		case FALLING_EDGE:
			CLR_BIT(MCUCSR,MCUCR_ISC2);
			break;

		case RAISING_EDGE:
			SET_BIT(MCUCSR,MCUCR_ISC2);
			break;

		default:
			Local_u8ErrorState=NOK;
			break;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

/***************************************************************/
/*Enable the Interrupt using Post Build Config*/
u8 EXTI_u8INTEnable(u8 Copy_u8Int)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8Int==EXTI_INT0)
	{
		SET_BIT(GICR,GICR_INT0);
	}
	else if(Copy_u8Int==EXTI_INT1)
	{
		SET_BIT(GICR,GICR_INT1);
	}
	else if(Copy_u8Int==EXTI_INT2)
	{
		SET_BIT(GICR,GICR_INT2);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
/***************************************************************/
/*Disable the Interrupt using Post Build Config*/
u8 EXTI_u8INTDisable(u8 Copy_u8Int)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8Int==EXTI_INT0)
	{
		CLR_BIT(GICR,GICR_INT0);
	}
	else if(Copy_u8Int==EXTI_INT1)
	{
		CLR_BIT(GICR,GICR_INT1);
	}
	else if(Copy_u8Int==EXTI_INT2)
	{
		CLR_BIT(GICR,GICR_INT2);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/***************************************************************/
/*Call Back Function*/
u8 EXTI_u8Int0SetCallBack(void (*Copy_puINT0Func) (void))
{
	u8 Local_u8ErrorState=OK;
	/*Check if the Pointer is not NULL*/
	if(Copy_puINT0Func != NULL)
	{
		EXTI_pvINT0Func=Copy_puINT0Func;
	}
	else if(Copy_puINT0Func == NULL)
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}
/*ISR Function of INT0*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	if(EXTI_pvINT0Func != NULL)
	{
		/*Address of ISR Function for INT0*/
		EXTI_pvINT0Func();
	}
	else
	{
		/*Do Nothing*/
	}
}
/***************************************************************/
u8 EXTI_u8INT1SetCallBack(void (*Copy_pvINT1Func)(void))
{
	u8 Local_u8ErrorSate=OK;
	if(Copy_pvINT1Func != NULL)
	{
		EXTI_pvINT1Func=Copy_pvINT1Func;
	}
	else
	{
		Local_u8ErrorSate=NULL_POINTER;
	}
	return Local_u8ErrorSate;
}
/*ISR Function of INT1*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pvINT1Func != NULL)
	{
		/*Address of ISR for INT1 */
		EXTI_pvINT1Func();
	}
	else
	{
		//Do nothing
	}
}
/***************************************************************/
u8 EXTI_u8INT2SetCallBack(void (*Copy_pvINT2Func)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvINT2Func != NULL)
	{
		EXTI_pvINT2Func=Copy_pvINT2Func;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}
/*ISR Function of INT2*/
void __vector_3(void) __attribute__ ((signal));
void __vector_3(void)
{
	if(EXTI_pvINT2Func !=NULL)
	{
		EXTI_pvINT2Func();
	}
	else
	{
		//DO Nothing
	}
}
