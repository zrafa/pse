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

process main() {

	char msg[80];
	//uint16_t distance;

	serial_init(115200);
	twi_init();		/* init i2c */
	sei();
	sleepms(2000);
	// am2320_init();	/* init lidar with some specific values (check code) */

	float temp, humi;

	while(1) {
		
		am2320_read(&temp, &humi);
	//	serial_put_str("hola mundo 2\n");

	 	sprintf(msg, "temperatura: %f     humedad: %f \n", temp, humi);
	 	serial_put_str(msg);
	//	serial_put_str("\n");
	}
}
