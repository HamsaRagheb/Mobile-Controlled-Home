/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       ADC               ***********************/
/****************      Date:      Aug 29, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*Reference Voltage Options:-
 *                                  1-VREF_EXT
 *                                  2-VREF_AVCC
 *                                  3-VREF_INT
 *
 *                                       */
#define    REFERENCE_SELECTION            VREF_AVCC

/*ADC Left Adjust Result Options:-
 *                                  1-(8  Bits) Resolution
 *                                  2-(10 Bits) Resolution
 *                                    */
#define     ADC_RESOLUTION                8

/*ADC Prescaler Options:-
 *                                 1-DIV_BY_2
 *                                 2-DIV_BY_4
 *                                 3-DIV_BY_8
 *                                 4-DIV_BY_16
 *                                 5-DIV_BY_32
 *                                 6-DIV_BY_64
 *                                 7-DIV_BY_128    */

#define     ADC_PRESCALER          DIV_BY_128

/*ADC Interrupt & Auto Trigger Options:-
 *                                 1-Enabled
 *                                 2-Disabled      */

#define    ADC_INTERRUPT           Disabled
#define    ADC_AUTO_TRIGGER        Disabled
#define    ADC_ENABLE              Enabled

/*ADC Auto Trigger Source Options:-
 *                                  1-FREE_RUNNING
 *                                  2-Analog_Comparator
 *                                  3-EXTI_INT0
 *                                                 */
#define    ADC_AUTO_TRIGGER_SOURCE   FREE_RUNNING


#define           ADC_32TIMEOUT            50000



#endif /* ADC_CONFIG_H_ */
