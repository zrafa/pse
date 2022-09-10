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

process sensor() {
	for (;;) {
		am2320_read(&temp, &humi);
		sleep(1);
	}
}


extern process wifi();

process main() {

	// char msg[80];
	//uint16_t distance;

	serial_init(115200);
	twi_init();		/* init i2c */
	sei();
	sleepms(2000);
	// am2320_init();	/* init lidar with some specific values (check code) */

	//float temp, humi;

	resume(create(wifi, 512, 20, "wifi", 0));
	resume(create(sensor, 256, 20, "sensor", 0));

	//init_wifi, ();

	for (;;);
	//serial_put_str("hola mundo \n");
	
	while(1) {
		
	//	am2320_read(&temp, &humi);
	//	serial_put_str("hola mundo 2\n");

	// 	sprintf(msg, "temperatura: %f     humedad: %f \n", temp, tt);
	// 	serial_put_str(msg);
	//	serial_put_str("\n");
	}
}
