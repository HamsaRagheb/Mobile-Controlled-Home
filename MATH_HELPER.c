/*
 * MATH_HELPER.c
 *
 *  Created on: Sep 11, 2023
 *      Author: hamsa
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH_HELPER.h"

s32 MATH_s32Map(s32 Copy_s32InputMin,s32 Copy_s32InputMax,s32 Copy_s32OutputMin,s32 Copy_s32OutputMax,s32 Copy_s32InputVal){

	s32 Local_s32OutputVal;

    Local_s32OutputVal=(((Copy_s32OutputMax-Copy_s32OutputMin)*(Copy_s32InputVal-Copy_s32InputMin))/(Copy_s32InputMax-Copy_s32InputMin))+Copy_s32OutputMin;

    return Local_s32OutputVal;
}
