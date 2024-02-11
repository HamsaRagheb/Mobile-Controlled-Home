/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     MCAL               ***********************/
/****************      SWC:       ADC               ***********************/
/****************      Date:      Aug 29, 2023       ***********************/
/****************      Version:   1.00               ***********************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

/*First Register*/
//ADC Multiplexer selecton register
#define          ADMUX                 *((volatile u8*)0x27)
//Bits
#define          ADMUX_MUX0               0     //MUX Slection Line 0
#define          ADMUX_MUX1               1     //MUX Slection Line 1
#define          ADMUX_MUX2               2     //MUX Slection Line 2
#define          ADMUX_MUX3               3     //MUX Slection Line 3
#define          ADMUX_MUX4               4     //MUX Slection Line 4

#define          ADMUX_ADLAR              5     //ADC Left Adjust Result

#define          ADMUX_REFS0              6     //Referece Selection bit0
#define          ADMUX_REFS1              7     //Referece Selection bit1

/*Second Register*/
//ADC Control and Status Register A
#define          ADCSRA                *((volatile u8*)0x26)
//Bits
#define          ADCSRA_ADPS0             0       //Prescaler bit0
#define          ADCSRA_ADPS1             1       //Prescaler bit1
#define          ADCSRA_ADPS2             2       //Prescaler bit2

#define          ADCSRA_ADIE              3       //Interrupt Enable
#define          ADCSRA_ADIF              4       //Interrupt Flag
#define          ADCSRA_ADTE              5       //Auto Trigger Enable
#define          ADCSRA_ADSC              6       //Start Conversion
#define          ADCSRA_ADEN              7       //ADC Enable

/*Third Register*/
/*ADC Data Register High Byte*/
#define          ADCH                  *((volatile u8*)0x25)

/*Fourth Register*/
/*ADC Data Register Low Byte*/
#define          ADCL                  *((volatile u8*)0x24)

/*Fifth Register*/
#define          SFIOR                 *((volatile u8*)0x50)
//Bits
#define          SFIOR_ADTS0              0
#define          SFIOR_ADTS1              1
#define          SFIOR_ADTS2              2

/*ADC:- To store the result of ADC Reading,for: 10-bit Resolution Mode*/
/*ADC Data Register Low & High Byte*/
#define          ADC                      *((volatile u16*)0x24)

#endif /* ADC_REGISTER_H_ */
