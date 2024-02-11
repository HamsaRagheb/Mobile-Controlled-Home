/*
 * ULTRASONIC_interface.h
 *
 *  Created on: Sep 22, 2023
 *      Author: hamsa
 */

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_


typedef struct
{

	u8 TrigPort;
	u8 TrigPin;


}ULTRASONIC_t;

void  ULTRASONIC_u8MeasureDistance(ULTRASONIC_t* Copy_psUltsonicTrigData, u16* Copy_u16Distance);





#endif /* ULTRASONIC_INTERFACE_H_ */
