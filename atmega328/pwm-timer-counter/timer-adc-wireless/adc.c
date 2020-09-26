/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include "adc.h"

/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del ADC del atmega328, segun sugerido
   en el apunte */

typedef struct
{
        uint8_t adcl;               /* ADC Data Register Low */
        uint8_t adch;               /* ADC Data Register High */
        uint8_t adcsra;             /* ADC Control and Status Register A */
        uint8_t adcsrb;             /* ADC Control and Status Register B */
        uint8_t admux;              /* ADC Multiplexer Selection Register */
        uint8_t reserved;           /* espacio sin utilizar */ 
        uint8_t didr0;              /* Digital Input Disable Register 0 */
} volatile adc_t;

/* puntero a la estructura de los registros del periferico */
volatile adc_t *adc = (adc_t *) (0x78);

#define REFS1 0x00  /* 0b 1000 0000 - bit 7  */
#define REFS0 0x40  /* 0b 0100 0000 - bit 6  */

#define ENABLE_ADC 0x80  /* 0b 1000 0000 - bit 7  */
#define ADPS2 0x04       /* 0b 0000 0100 - bit 2  */
#define ADPS1 0x02       /* 0b 0000 0010 - bit 1  */
#define ADPS0 0x01       /* 0b 0000 0001 - bit 0  */

void adc_init()
{
        /* Configurar los registros ADMUX y ADCSRA para utilizar el voltaje
        de referencia interno y encender (habilitar) el periferico */

        /* Establecer el prescalar (divisor) */
        adc->admux = (unsigned char) (REFS1 + REFS0);  /* 1100 0000 */
        adc->adcsra = (unsigned char) (ENABLE_ADC + ADPS2 + ADPS1 + ADPS0);    /* 1000 0111 */
}

int adc_get(char input)
{
        int val;
        /* 1. Establecer el multiplexor a la entrada input */
        adc->admux |= input;

        /* 2. Iniciar una conversion ADC */
        adc->adcsra |= 1 << 6;  /* 0100 0000 */

        /* 3. Completar con E/S programada */
        while ( !((adc->adcsra) & (1 << 6)) );

        /* 4. Devolver el valor del registro de datos del ADC (low y high) */
        /* IMPORTANTE: hay que leer el registro L antes del H */
        val = adc->adcl;

        val += (adc->adch << 8);

        return val;
}
