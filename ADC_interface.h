/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       ADC               ***********************/
/****************      Date:      Aug 29, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


/*You Must Enable Global Interrupt,
 *before calling these Functions in APP Layer
 *
 *
 *
 *
 *                                 */

/***************************************************************************/
/***************************************************************************/
/**************************************MACRO****************************/
//ADC Chaneels
#define       ADC_SINGLE_ENDED_ADC0                     0
#define       ADC_SINGLE_ENDED_ADC1                     1
#define       ADC_SINGLE_ENDED_ADC2                     2
#define       ADC_SINGLE_ENDED_ADC3                     3
#define       ADC_SINGLE_ENDED_ADC4                     4
#define       ADC_SINGLE_ENDED_ADC5                     5
#define       ADC_SINGLE_ENDED_ADC6                     6
#define       ADC_SINGLE_ENDED_ADC7                     7

#define       ADC_DIFF_PADC0_NADC0_G10x                 8
#define       ADC_DIFF_PADC1_NADC0_G10x                 9
#define       ADC_DIFF_PADC0_NADC0_G200x                10
#define       ADC_DIFF_PADC1_NADC0_G200x                11
#define       ADC_DIFF_PADC2_NADC2_G10x                 12
#define       ADC_DIFF_PADC3_NADC2_G10x                 13
#define       ADC_DIFF_PADC2_NADC2_G200x                14
#define       ADC_DIFF_PADC3_NADC2_G200x                15
#define       ADC_DIFF_PADC0_NADC1_G1x                  16
#define       ADC_DIFF_PADC1_NADC1_G1x                  17
#define       ADC_DIFF_PADC2_NADC1_G1x                  18
#define       ADC_DIFF_PADC3_NADC1_G1x                  19
#define       ADC_DIFF_PADC4_NADC1_G1x                  20
#define       ADC_DIFF_PADC5_NADC1_G1x                  21
#define       ADC_DIFF_PADC6_NADC1_G1x                  22
#define       ADC_DIFF_PADC7_NADC1_G1x                  23
#define       ADC_DIFF_PADC0_NADC2_G1x                  24
#define       ADC_DIFF_PADC1_NADC2_G1x                  25
#define       ADC_DIFF_PADC2_NADC2_G1x                  26
#define       ADC_DIFF_PADC3_NADC2_G1x                  27
#define       ADC_DIFF_PADC4_NADC2_G1x                  28
#define       ADC_DIFF_PADC5_NADC2_G1x                  29
#define       ADC_SINGLE_ENDED_VBG                      30
#define       ADC_SINGLE_ENDED_GND                      31
/***************************************************************************/
/*****************************Global Struct*************************************/
typedef struct Chain
{
	u8*  ChannelArr;
	u16* ResultArr;
	u8 Size;
	void (*NotiFunc)(void);

}Chain_t;

/***************************************************************************/
/***************************************************************************/
/*********************************Function Prototype*******************************/
/*Function to Initialize ADC*/
void ADC_voidInit(void);
/*Synchronous Function to Start Single Conversion */
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16ADCReading);
/*Asynchronous Function to Start Single Conversion */
u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu8ADCReading, void (*Copy_Fun)(void));
/*Synchronous Function to Start Chain of Conversions*/
u8 ADC_u8StartChainConversionSynch(Chain_t* Copy_psADCChain);
/*Asynchronous Function to Start Chain of Conversions*/
u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_psADCChain);







#endif /* ADC_INTERFACE_H_ */
