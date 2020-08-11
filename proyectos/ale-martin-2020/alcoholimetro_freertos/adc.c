/* Driver ADC */
#include <avr/io.h>
#include <stdint.h>       /* needed for uint8_t */
#include <util/delay.h>       /* needed for uint8_t */

#define REFS0_A 0X40
#define A_A 0xC7
#define ADSC_A 0x40


typedef struct
{
    uint8_t adcl;  
    uint8_t adch; 
    uint8_t adcsra; /* ADC Control and Status Register A */
    uint8_t adcsrb; 
    uint8_t admux; /* ADC Multiplexer Selection Register */
    uint8_t reserved; 
    uint8_t didr0;    


} volatile adc;

/* Puntero a la estructura de los registros del periferico */
volatile adc *puntero_adc = (adc *) (0x78);

void adc_init(uint8_t pin_to_use) {
	puntero_adc->admux |= (unsigned char) (REFS0_A);
}

int adc_single_read(uint8_t pin_to_use) {
	int val;
	
	puntero_adc->admux |= (unsigned char) (pin_to_use);
	puntero_adc->adcsra = (unsigned char) (A_A);

	while (((puntero_adc->adcsra) & (ADSC_A)));

	val = puntero_adc->adcl;
	val = ((puntero_adc->adch) <<8) + val;

	return val;

}
