/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       GIE               ***********************/
/****************      Date:      Aug 22, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_register.h"

/*Function to Enable Global Interrupt*/
void GIE_voidEnable()
{
	SET_BIT(SREG,SREG_I);
}
/*Function to Disable Global Interrupt*/
void GIE_voidDisable()
{
	CLR_BIT(SREG,SREG_I);
}


