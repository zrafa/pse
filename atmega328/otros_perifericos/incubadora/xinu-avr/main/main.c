/*
 * main.c: little example program for testing am2320 temperature & humidity
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#include <xinu.h>
//#include <stddef.h>
//#include <stdio.h>
#include <string.h>
//#include <util/delay.h>
#include <avr/interrupt.h>

//#include "serial.h"
#include "twi.h"
#include "am2320.h"

int 	sprintf (char *__s, const char *__fmt,...);

float temp, humi;
int dias, horas, minutos;

/*
process sensor() {
	for (;;) {
		am2320_read(&temp, &humi);
		sleep(1);
	}
}
*/

process tiempo_y_sensor() {
	minutos = 57;
	dias = 11;
	horas = 23;

	for (;;) {
		am2320_read(&temp, &humi);

		sleep(59);
		minutos++;

		if (minutos == 60) {
			minutos = 0;
			horas++;
		}

		if (horas == 24) {
			horas = 0;
			dias++;
		}
	}
}

/*
process tiempo() {

	minutos = 57;
	dias = 11;
	horas = 23;

	sleep(60);
	minutos++;

	if (minutos == 60) {
		minutos = 0;
		horas++;
	}

	if (horas == 24) {
		horas = 0;
		dias++;
	}
}
*/


extern process wifi();
void port_b_init();
int button_get();
void titilar_cinco();


process main() {

	int i;

	port_b_init();

	serial_init(9600);
	twi_init();		/* init i2c */
	sei();
	sleepms(2000);
	// am2320_init();	/* init lidar with some specific values (check code) */

	//float temp, humi;

	resume(create(wifi, 512, 20, "wifi", 0));
	resume(create(tiempo_y_sensor, 128, 20, "sensor", 0));
	// resume(create(tiempo, 64, 20, "tiempo", 0));

	while(1) {

		sleep(1);

		/* intentando reset */
		if (button_get()) {
			for (i=0; i<10; i++) {
				sleep(1);
				if ( ! button_get() )
					break;
			}

			if (i == 10) {
				dias = 0;
				horas = 0;
				minutos = 0;
				titilar_cinco();
			}
		}
	}

}
