/*
 * main.c: little example program for testing am2320 temperature & humidity
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */


#include <stddef.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "twi.h"
#include "am2320.h"

void main() {

	char msg[80];
	uint16_t distance;

	serial_init(9600);
	twi_init();		/* init i2c */
	sei();
	_delay_ms(2000);
	// am2320_init();	/* init lidar with some specific values (check code) */

	float temp, humi;

	serial_put_str("hola mundo \n");
	while(1) {
		
		am2320_read(&temp, &humi);
		serial_put_str("hola mundo 2\n");

		sprintf(msg, "temperatura: %.1f     humedad: %.1f \n", temp, humi);
		serial_put_str(msg);
	}
}
