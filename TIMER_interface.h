/*************************************************************************************************************************/
/*************************************************************************************************************************/
/******************************       Author:  Hamsa Ragheb       ********************************************************/
/******************************       Layer:   MCAL               ********************************************************/
/******************************       SWC:     TIMER              ********************************************************/
/******************************       Date:    Sep 10, 2023        ********************************************************/
/******************************       Version: 1.00               ********************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/*************************************************************************************************************************/
/*Macros For input Arguments*/
/*************************************************************************************************************************/

//Timer0,2 Wave Generation Modes

#define TIMER_NORMAL								    1
#define TIMER_PHC_PWM								    2
#define TIMER_CTC									    3
#define TIMER_FAST_PWM								    4

//Timer1 Wave Generation Modes

#define TIMER1_NORMAL                                   1
#define TIMER1_PHC_PWM_8_BIT                            2
#define TIMER1_PHC_PWM_9_BIT                            3
#define TIMER1_PHC_PWM_10_BIT                           4
#define TIMER1_CTC                                      5
#define TIMER1_FAST_PWM_8_BIT                           6
#define TIMER1_FAST_PWM_9_BIT                           7
#define TIMER1_FAST_PWM_10_BIT                          8
#define TIMER1_PHFC_PWM_CUSTOM_TOP                      9
#define TIMER1_PHFC_PWM                                 10
#define TIMER1_PHC_PWM_CUSTOM_TOP                       11
#define TIMER1_PHC_PWM                                  12
#define TIMER1_CTC_CUSTOM_TOP                           13
#define TIMER1_FAST_PWM_CUSTOM_TOP                      14
#define TIMER1_FAST_PWM                                 15

//Prescaler

#define  PRSCLR_DISABLE_CLOCK                        	0
#define  PRSCLR_DIV_BY_1                             	1
#define  PRSCLR_DIV_BY_8                             	2
#define  PRSCLR_DIV_BY_64                            	3
#define  PRSCLR_DIV_BY_256                           	4
#define  PRSCLR_DIV_BY_1024                   		 	5
#define  PRSCLR_EXT_CLK_FALLING_EDGE           			6
#define  PRSCLR_EXT_CLK_RISING_EDGE           		 	7

//Compare Match Output Mode

#define OCM_DISCONNECT									0
#define OCM_CTC_TOGGLE									1
#define OCM_CTC_CLR										2
#define OCM_CTC_SET										3
#define OCM_FAST_PWM_NON_INVERTED						2
#define OCM_FAST_PWM_INVERTED							3
#define OCM_PHC_PWM_NON_INVERTED	   					2
#define OCM_PHC_PWM_INVERTED			   				3


//Interrupt Enable/Disable

#define INT_ENABLE							 			1
#define INT_DISABLE										2


//Interrupt IDs

#define	INT_TIMER0_OVF									7
#define	INT_TIMER0_COMP									6
#define INT_TIMER1_OVF									5
#define INT_TIMER1_CAPT									4
#define INT_TIMER1A_COMP								3
#define INT_TIMER1B_COMP								2
#define INT_TIMER2_OVF									1
#define INT_TIMER2_COMP									0

//Timer IDs

#define TIMER0											0
#define TIMER1A											1
#define TIMER1B											2
#define TIMER1											3
#define TIMER2											4


//Input Capture Edge Select Options

#define FALLING_EDGE									0
#define RISING_EDGE										1

//SCHEDULE REPEATABILITY

#define REPEAT_ONCE										1
#define REPEAT_PERIODIC									2

/*************************************************************************************************************************/
/***********************************STRUCTS*********************************************************************/
/*************************************************************************************************************************/
//Timer0,2 Struct
typedef struct timer{
	u8 WaveGenMode;
	u8 Prescaler;
	u8 CompareMatchOutputMode;
	u8 CompareMatchInterrupt;
	u8 OverFlowInterrupt;
}Timer_t;


//Timer1 Struct
typedef struct timer1{
	u8 WaveGenMode;
	u8 Prescaler;
	u8 CompareMatchOutputMode_A;
	u8 CompareMatchOutputMode_B;
	u8 CompareMatchInterrupt_A;
	u8 CompareMatchInterrupt_B;
	u8 OverFlowInterrupt;
}Timer1_t;
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/***********************************FUNCTIONS PROTOTYPE*******************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/***********************************GENERAL TIMER FUNCTIONS****************************************************************/
/*************************************************************************************************************************/
u8 TIMER_u8SetTimerVal(u8 Copy_u8TimerID,u16 Copy_u16Value);

u8 TIMER_u8GetTimerVal(u8 Copy_u8TimerID,u16* Copy_pu16Value);

u8 TIMER_u8SetCompMatch(u8 Copy_u8TimerID,u16 Copy_u16Value);

u8 TIMER_u8SetIntStatus(u8 Copy_u8InterruptID, u8 Copy_u8Status);

u8 TIMER_u8SetCallBack(u8 Copy_u8InterruptID,void(*Copy_pvCallBackFunc)(void));
/*************************************************************************************************************************/
/**********************************************TIMER0*********************************************************************/
/*************************************************************************************************************************/
/*Timer0 Initialization*/
u8 TIMER0_u8Init(Timer_t* Copy_psTimer);
/*Timer0 delay_ms[Polling]*/
u8 TIMER0_delay_ms(Timer_t* Copy_psTimer,u16 Copy_u16Time);
/*************************************************************************************************************************/
/**********************************************TIMER1*********************************************************************/
/*************************************************************************************************************************/
/*Timer1 Initialization*/
u8 TIMER1_u8Init(Timer1_t* Copy_psTimer);
/*Timer1 Set Top Value*/
void TIMER1_voidSetTopValue(u16 Copy_u16Value);
/*Servo Function, Mode: TIMER1_FAST_PWM_CUSTOM_TOP*/ 
u8 TIMER1_u8HWPWMGenerate(Timer1_t* Copy_psTimer,u16 Copy_u16PeriodTime,u16 Copy_u16OnTime);
/*************************************************************************************************************************/
/**********************************************TIMER2*********************************************************************/
/*************************************************************************************************************************/
/*Timer2 Initialization*/
/*ICU Settings*/
u8 TIMER2_u8Init(Timer_t* Copy_psTimer);
/*Function to generate HW PWM Signal*/
u8 TIMER2_u8HWPWMGenerate(Timer_t* Copy_psTimer,u8 Copy_u8DutyCycle);
/*Timer2 delay_ms[Polling]*/
u8 TIMER2_delay_ms(Timer_t* Copy_psTimer,u16 Copy_u16Time);
/*Timer2 delay_us[Polling]*/
u8 TIMER2_delay_us(Timer_t* Copy_psTimer,u16 Copy_u16Time);
/*Timer2 Schedule Function[Interrupt]*/
u8 TIMER2_u8Schedule(u16 Copy_u16msDelayTime,void(*Copy_pvFunc)(void),u8 Copy_u8Repeatability);
/*************************************************************************************************************************/
/**********************************************ICU*********************************************************************/
/*************************************************************************************************************************/
/*Function to Initialize Input Capture Unit*/
u8 ICU_u8Init(u8 Copy_u8Edge,u8 Copy_u8InterruptStatus);
/*Function to Change Trigger of Input Capture Unit*/
u8 ICU_u8SetEdge(u8 Copy_u8Edge);
/*Function to Read Input Capture Unit Register*/
u16 ICU_u16ReadInputCapture(void);


#endif
