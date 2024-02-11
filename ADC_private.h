/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       ADC               ***********************/
/****************      Date:      Aug 29, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/*ADC Reference Voltage Choices*/
#define         VREF_EXT                   1
#define         VREF_AVCC                  2
#define         VREF_INT                   3

/*ADC Prescaler Choices*/
#define         DIV_BY_2                   1
#define         DIV_BY_4                   2
#define         DIV_BY_8                   3
#define         DIV_BY_16                  4
#define         DIV_BY_32                  5
#define         DIV_BY_64                  6
#define         DIV_BY_128                 7

#define         ADC_PRESCALER_MASK        0b11111000

/*ADC Interrupt Choices*/
/*ADC Auto Trigger Choices*/
/*ADC Enable Choices*/
#define         Enabled                    1
#define         Disabled                   2

/*ADC Auto Trigger Source Modes*/
#define        FREE_RUNNING                3
#define        Analog_Comparator           1
#define        EXTI_INT0                   2

#define        ADC_AUTO_TRIGGER_SRC_MASK        0b00001111

/*ADC Busy Stat Flag*/
#define        IDLE               1
#define        BUSY               2

/*ADC Chaneel Mask*/
#define        ADC_CHANNEL_MUX_MASK        0b11100000

/*For Single or Chain Coversions*/
#define        SINGLE_CONVERSION           1
#define        CHAIN_CONVERSION            1


#endif /* ADC_PRIVATE_H_ */
