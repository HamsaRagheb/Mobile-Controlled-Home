/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       EXTI               ***********************/
/****************      Date:      Aug 22, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/



#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*Sense Control Configuration*/
/*Options:
 *         1-LOW_LEVEL
 *         2-ON_CHANGE
 *         3-FALLING_EDGE
 *         4-RAISING_EDGE    */

#define    INT0_SENSE              FALLING_EDGE
#define    INT1_SENSE              FALLING_EDGE
#define    INT2_SENSE              FALLING_EDGE

/*Peripherial Interrupt Enable*/
/*Options:
 *         1-ENABLE
 *         2-DISABLE         */

#define    INT0_INITIAL_STATE       ENABLED
#define    INT1_INITIAL_STATE       ENABLED
#define    INT2_INITIAL_STATE       ENABLED





#endif /* EXTI_CONFIG_H_ */
