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

const __flash char mm1[] = "AT";
const __flash char mm2[] = "AT+RST";
const __flash char mm3[] = "AT+CWMODE=3";
const __flash char mm4[] = "AT+CWSAP=\"INCUBADORA\",,1,0";
const __flash char mm5[] = "AT+CIPMUX=1";		/* 0 : una conexion;    1 : hasta 4 conexiones */ 
const __flash char mm6[] = "AT+CIPSERVER=1,80";
const __flash char mm7[] = "AT+CIPSEND=0,25";
const __flash char mm8[] = "<html><head></head><body>";
const __flash char mm9[] = "AT+CIPSEND=0,19";
const __flash char mm10[] = "<h1>Incubadora</h1>";
const __flash char mm11[] = "AT+CIPSEND=0,45";
const __flash char mm12[] = "AT+CIPSEND=0,14";
const __flash char mm13[] = "</body></html>";
const __flash char mm14[] = "AT+CIPCLOSE=0";

float temp, humi;

process sensor() {
	for (;;) {
		am2320_read(&temp, &humi);
		sleep(1);
	}
}


void wait_connection() {
	int found = 0;
	char m[3];
	m[0] = serial_get_char();
	m[1] = serial_get_char();

	while (!found) {
		m[2] = serial_get_char();
		if ((m[0] == 'I') && (m[1] == 'P') && (m[2] == 'D')) 
			found = 1;
		else {
			m[0]=m[1]; m[1]=m[2]; 
		}

	}
}

process wifi() {

	char msg[46];
	//float temp, humi;
	//float tt = 3.1416;

	serial_put_str2(mm1);
	sleepms(400);
	serial_put_str2(mm2);
	sleepms(400);

	// access point
	serial_put_str2(mm3);
	sleepms(400);

	// canal 1, access point ESP, sin clave (el cero) 
	serial_put_str2(mm4);
	sleepms(400);

	// mult conexiones
	serial_put_str2(mm5);
	sleepms(400);

	// servidor web
	serial_put_str2(mm6);
	sleepms(400);

	while(1) {

		wait_connection();


	serial_put_str2(mm7);
	sleepms(300);

	serial_put_str2(mm8);
	sleepms(300);

			      
	serial_put_str2(mm9);
	sleepms(300);


	serial_put_str2(mm10);
	sleepms(300);

	serial_put_str2(mm11);
	sleepms(300);

	// am2320_read(&temp, &humi);
	//sprintf(msg, "%2.1f", temp);
 	// dtostrf(temp, 2, 1, msg);
	sprintf(msg, "<h2>temperatura: %2.1f     humedad: %2.1f </h2>", temp, humi);
	serial_put_str(msg);
	sleepms(300);

	serial_put_str2(mm12);
	sleepms(300);

	serial_put_str2(mm13);
	sleepms(300);

	serial_put_str2(mm14);
	sleepms(300);

	// sleepms(10000);
	}

}

process main() {

	// char msg[80];
	//uint16_t distance;

	serial_init(115200);
	twi_init();		/* init i2c */
	sei();
	sleepms(2000);
	// am2320_init();	/* init lidar with some specific values (check code) */

	//float temp, humi;

	resume(create(wifi, 128, 20, "wifi", 0));
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
