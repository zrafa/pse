#include <avr/interrupt.h>

#include "serial.h"
#include "adc.h"
#include "clock.h"

char letra;
volatile int no_leer;
extern volatile int ticks;

void esperar(unsigned long msec)
{
        unsigned long i;
        for (i = 0; i < 450 * msec; i++);
}


int main(void)
{
	int i;
        int adc_val;
	char buf[5];

	/* deshabilitamos interrupciones */
	cli();

	letra = 0;
        serial_init();
        adc_init();
        timer0_init();

        serial_put_str("Start");

	adc_val = adc_get(0);

/*
	for (;;) {
		adc_val = adc_get(0);
		sprintf(buf, "%d", adc_val);
		serial_put_str(buf);
	}
*/

        while (1) {

		/* esperamos el bit de start */
		adc_val = 100;
		while (adc_val < 890) {
			esperar(10);
			adc_val = adc_get(0);
		}

		no_leer = 1;
		letra = 0;
		/* habilitamos las interrupciones (timer/clock) */
		sei();

		/* leemos 8 bits desde el ADC (fotoresistencia) */
		for (i=0; i<8; i++) {

			while (no_leer);

			no_leer = 1;

			letra = (letra << 1);
			adc_val = adc_get(0);
			if (adc_val < 890)
				letra |= 1;
			
		}
		serial_put_char(letra);
		/* deshabilitamos interrupciones */
		cli();
		ticks=0;
		
        }

        return 0;
}
