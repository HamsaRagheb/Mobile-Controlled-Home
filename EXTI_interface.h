/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       EXTI               ***********************/
/****************      Date:      Aug 22, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_
/***************************************************************************/
/***************************************************************************/
/*****************************MACROS**************************************/
/*Description: Input Arguments to Functions*/
#define       LOW_LEVEL             1
#define       ON_CHANGE             2
#define       FALLING_EDGE          3
#define       RAISING_EDGE          4

#define       EXTI_INT0             1
#define       EXTI_INT1             2
#define       EXTI_INT2             3

/***************************************************************************/
/***************************************************************************/
/****************************** Function Prototype **************************/
/*Function to Initialize INT0 Pre Build Config.*/
void EXTI_voidINT0Init();
/*Function to Initialize INT1 Pre Build Config.*/
void EXTI_voidINT1Init();
/*Function to Initialize INT2 Pre Build Config.*/
void EXTI_voidINT2Init();
/***************************************************************************/
/*Description: Function to Set INT0 Sense Control using POST_BULID Configuration
 *Input:       Copy_u8SenseControl,
 *Options are: 1-LOW_LEVEL
               2-ON_CHANGE
               3-FALLING_EDGE
               4-RAISING_EDGE
 *Output:      Error State with Type u8
 *                                                */
/*Function to Sense Control using POST_BULID Configuration */
u8 EXTI_u8INTSetSenseControl(u8 Copy_u8Interrupt,u8 Copy_u8SenseControl);
/*Enable the Interrupt using Post Build Config*/
u8 EXTI_u8INTEnable(u8 Copy_u8Int);
/*Disable the Interrupt using Post Build Config*/
u8 EXTI_u8INTDisable(u8 Copy_u8Int);
/*Call Back Functions*/
u8 EXTI_u8Int0SetCallBack(void (*Copy_puINT0Func) (void));
u8 EXTI_u8INT1SetCallBack(void (*Copy_puINT0Func) (void));
u8 EXTI_u8INT2SetCallBack(void (*Copy_puINT0Func) (void));



#endif /* EXTI_INTERFACE_H_ */
