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
        char ascii_value;
        int read_adc;
        int scale;

	cli();

	letra = 0;
        serial_init();
        adc_init();
        timer0_init();

        serial_put_str("Start");

	read_adc = adc_get(0);

	char buf[5];

/*
	for (;;) {
		read_adc = adc_get(0);
		sprintf(buf, "%d", read_adc);
		serial_put_str(buf);
	}
*/

        while (1) {
		read_adc = 100;
		while (read_adc < 890) {
			esperar(10);
			read_adc = adc_get(0);
		}

		no_leer = 1;
		letra = 0;
		sei();

		for (i=0; i<8; i++) {

			while (no_leer);

			no_leer = 1;

			letra = (letra << 1);
			read_adc = adc_get(0);
			if (read_adc < 890)
				letra |= 1;
			
		}
		serial_put_char(letra);
		cli();
		ticks=0;
		
        }

        return 0;
}
