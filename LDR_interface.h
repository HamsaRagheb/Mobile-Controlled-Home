/*
 * LDR_interface.h
 *
 *  Created on: Sep 18, 2023
 *      Author: hamsa
 */

#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_


#define    LDR_u8ADC_CHANNEL0         0
#define    LDR_u8ADC_CHANNEL1         1
#define    LDR_u8ADC_CHANNEL2         2
#define    LDR_u8ADC_CHANNEL3         3
#define    LDR_u8ADC_CHANNEL4         4
#define    LDR_u8ADC_CHANNEL5         5
#define    LDR_u8ADC_CHANNEL6         6
#define    LDR_u8ADC_CHANNEL7         7


/*Function to start the conversion*/
u8 LDR_u8GetDigitalReading(u8 Copy_u8Channel, u16* Copy_pu16ADCDigitalReading);

/*Function to turn ON  LEDs depend on ADC Digital Value*/
u8 LDR_u8TurnedOnLEDsNumber(u16* Copy_pu16ADCDigitalReading);



#endif /* LDR_INTERFACE_H_ */
