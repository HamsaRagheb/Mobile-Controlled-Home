/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       DIO                ***********************/
/****************      Version:   1.00               ***********************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_register.h"
#include"DIO_interface.h"
#include"DIO_config.h"
#include"DIO_private.h"

/*Functions Implementation*/
u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	/* Flag used in debugging and the return of the function will be u8
	 */
	u8 Locl_u8ErrorCode = LOGIC_ZERO ;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Direction == DIO_u8PIN_INPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: CLR_BIT(DDRA,Copy_u8Pin);
			break;

			case DIO_u8PORTB: CLR_BIT(DDRB,Copy_u8Pin);
			break;

			case DIO_u8PORTC: CLR_BIT(DDRC,Copy_u8Pin);
			break;

			case DIO_u8PORTD: CLR_BIT(DDRD,Copy_u8Pin);
			break;

			default: Locl_u8ErrorCode = LOGIC_ONE ;
			break;
			}
		}
		else if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: SET_BIT(DDRA,Copy_u8Pin);
			break;

			case DIO_u8PORTB: SET_BIT(DDRB,Copy_u8Pin);
			break;

			case DIO_u8PORTC: SET_BIT(DDRC,Copy_u8Pin);
			break;

			case DIO_u8PORTD: SET_BIT(DDRD,Copy_u8Pin);
			break;

			default: Locl_u8ErrorCode = LOGIC_ONE;
			break;
			}
		}
		else
		{
			Locl_u8ErrorCode = two;
		}
	}
	else
	{
		Locl_u8ErrorCode = three ;

	}

	return Locl_u8ErrorCode;
}

u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8PortDirection)
{
	/* Flag used in debugging and the return of the function will be u8
	 */
	u8 Locl_u8ErrorCode = LOGIC_ZERO ;

	switch(Copy_u8Port)
	{
	case DIO_u8PORTA: DDRA=Copy_u8PortDirection;
	break;

	case DIO_u8PORTB: DDRB=Copy_u8PortDirection;
	break;

	case DIO_u8PORTC: DDRC=Copy_u8PortDirection;
	break;

	case DIO_u8PORTD: DDRD=Copy_u8PortDirection;
	break;

	default: Locl_u8ErrorCode = LOGIC_ONE;
    break;
	}


	return Locl_u8ErrorCode;
}

u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	/* Flag used in debugging and the return of the function will be u8
	 */
	u8 Locl_u8ErrorCode = LOGIC_ZERO ;

	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		if(Copy_u8Value == DIO_u8PIN_LOW)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: CLR_BIT(PORTA,Copy_u8Pin);
			break;

			case DIO_u8PORTB: CLR_BIT(PORTB,Copy_u8Pin);
			break;

			case DIO_u8PORTC: CLR_BIT(PORTC,Copy_u8Pin);
			break;

			case DIO_u8PORTD: CLR_BIT(PORTD,Copy_u8Pin);
			break;

			default: Locl_u8ErrorCode = LOGIC_ONE;
					break;
			}
		}
		else if(Copy_u8Value == DIO_u8PIN_HIGH)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA: SET_BIT(PORTA,Copy_u8Pin);
			break;

			case DIO_u8PORTB: SET_BIT(PORTB,Copy_u8Pin);
			break;

			case DIO_u8PORTC: SET_BIT(PORTC,Copy_u8Pin);
			break;

			case DIO_u8PORTD: SET_BIT(PORTD,Copy_u8Pin);
			break;

			default: Locl_u8ErrorCode = LOGIC_ONE;
			break;
			}
		}
		else
		{
			Locl_u8ErrorCode = two;
		}
	}
	else
	{
		Locl_u8ErrorCode = three ;

	}

	return Locl_u8ErrorCode;
}
u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	u8 Locl_u8ErrorCode=LOGIC_ZERO;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA: PORTA=Copy_u8Value;
	break;

	case DIO_u8PORTB: PORTB=Copy_u8Value;
	break;

	case DIO_u8PORTC: PORTC=Copy_u8Value;
	break;

	case DIO_u8PORTD: PORTD=Copy_u8Value;
	break;

	default: Locl_u8ErrorCode = LOGIC_ONE;
	break;
	}


	return Locl_u8ErrorCode;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8PinValue)
{
	/* Flag used in debugging and the return of the function will be u8
	 * */
	/*Here we need to make pointer to can return two variables
	from this function*/
	u8 Locl_u8ErrorCode = LOGIC_ZERO;

	if((Copy_pu8PinValue != NULL) && (Copy_u8Pin <= DIO_u8PIN7))
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA: *Copy_pu8PinValue=GET_BIT(PINA,Copy_u8Pin);
		break;

		case DIO_u8PORTB: *Copy_pu8PinValue=GET_BIT(PINB,Copy_u8Pin);
		break;

		case DIO_u8PORTC: *Copy_pu8PinValue=GET_BIT(PINC,Copy_u8Pin);
		break;

		case DIO_u8PORTD: *Copy_pu8PinValue=GET_BIT(PIND,Copy_u8Pin);
		break;

		default: Locl_u8ErrorCode = LOGIC_ONE;
		break;
		}
	}
	else
	{
		Locl_u8ErrorCode = two ;
	}
	return Locl_u8ErrorCode ;

	/*at main
	 * --->>>>>>>>>>>>>Neglecate Locl_u8ErrorCode<<<<<<<<<<<---
	 * u8 Local_u8PinValue=1;
	 *
	 * DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN0,&Local_u8PinValue)
	 *
	 * if(Local_u8PinValue==NULL)
	 * {
	 *
	 * }
	 * else if(Local_u8PinValue==LOGIC_ONE)
	 * {
	 *
	 * }
	 * */

}







