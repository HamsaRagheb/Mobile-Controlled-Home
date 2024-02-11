/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       EXTI               ***********************/
/****************      Date:      Aug 22, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

/*Peripherial Interrupt Enable (PIE) */
#define                 GICR                  *((volatile u8*)0x5B)
#define                 GICR_INT1             7
#define                 GICR_INT0             6
#define                 GICR_INT2             5

/*Peripherial Interrupt Flag (PIf) */
#define                 GIFR                  *((volatile u8*)0x5A)

#define                 MCUCR                 *((volatile u8*)0x55)
/* INT0 */
#define                 MCUCR_ISC00           0
#define                 MCUCR_ISC01           1
/* INT1 */
#define                 MCUCR_ISC10           2
#define                 MCUCR_ISC11           3

/* INT2 */
#define                 MCUCSR                *((volatile u8*)0x54)
#define                 MCUCR_ISC2            6



#endif /* EXTI_REGISTER_H_ */
