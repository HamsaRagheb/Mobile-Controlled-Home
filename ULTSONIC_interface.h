/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ULTSONIC_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ULTSONIC_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the ULTSONIC sensor module functions.
 * @version 1.00
 */

#ifndef ULTSONIC_INTERFACE_H_
#define ULTSONIC_INTERFACE_H_

typedef struct
{
	u8 TrigPort;
	u8 TrigPin;
}
ULTSONIC_t;

void ULTSONIC_u8MeasureDistance(const ULTSONIC_t *Copy_stUltsonicData, u16 *Copy_u16Distance);

#endif
