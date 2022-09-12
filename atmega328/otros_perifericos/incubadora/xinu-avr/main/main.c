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

#define TEMP_MAX 25
#define TEMP_MIN 24

process tiempo_y_sensor() {
	minutos = 57;
	dias = 11;
	horas = 23;

	for (;;) {
		/* medir temperatura y humedad */
		am2320_read(&temp, &humi);

		/* prendemos o apagamos foco segun tempertura */
		if (temp > TEMP_MAX)
			apagar_foco();
		else if (temp < TEMP_MIN)
			prender_foco();

		/* esperar un minuto de incubacion */
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


extern process wifi();
void port_b_init();
int button_pressed();
void titilar_cinco();
void apagar_foco();
void prender_foco();


process main() {

	int i;

	port_b_init();

	serial_init(9600);
	twi_init();		/* init i2c */
	sei();
	sleepms(2000);

	resume(create(wifi, 512, 20, "wifi", 0));
	resume(create(tiempo_y_sensor, 128, 20, "sensor", 0));
	// resume(create(tiempo, 64, 20, "tiempo", 0));

	while(1) {

		sleep(1);

		/* intentando reset */
		if (button_pressed()) {
			// prender_led();
			for (i=0; i<10; i++) {
				sleep(1);
				if ( ! button_pressed() )
					break;
			}

			/* si pasaron 10 segundos con el boton presionado: RESET */
			if (i == 10) {
				dias = 0;
				horas = 0;
				minutos = 0;
				titilar_cinco();
			}
			// apagar_led();
		}
	}

}
