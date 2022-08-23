/*
 * main.c: little example program for testing am2320 temperature & humidity
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */


#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "twi.h"
#include "am2320.h"

void init_wifi() {
	serial_put_str("AT");
	_delay_ms(400);
	serial_put_str("AT+RST");
	_delay_ms(400);

	// access point
	serial_put_str("AT+CWMODE=3");
	_delay_ms(400);

	// canal 1, access point ESP, sin clave (el cero) 
	serial_put_str("AT+CWSAP=\"ESP2\",,1,0");
	_delay_ms(400);

	// mult conexiones
	serial_put_str("AT+CIPMUX=1");
	_delay_ms(400);

	// servidor web
	serial_put_str("AT+CIPSERVER=1,80");
	_delay_ms(400);

	while(1) {


	//serial_put_str("AT+CIPSEND=0,65");
	serial_put_str("AT+CIPSEND=0,25");
	_delay_ms(200);

	//serial_put_str("<html><head><meta http-equiv=\"refresh\" content=\"10\"></head><body>");
	serial_put_str("<html><head></head><body>");
	_delay_ms(200);

			      
	serial_put_str("AT+CIPSEND=0,26");
	_delay_ms(200);

	serial_put_str("<h1>ESP8266 Webserver</h1>");
	_delay_ms(200);


	serial_put_str("AT+CIPSEND=0,14");
	_delay_ms(200);

	serial_put_str("</body></html>");
	_delay_ms(200);

	serial_put_str("AT+CIPCLOSE=0");
	_delay_ms(200);

	_delay_ms(8000);
	}

}

void main() {

	char msg[80];
	uint16_t distance;

	serial_init(115200);
//	twi_init();		/* init i2c */
//	sei();
	_delay_ms(2000);
	// am2320_init();	/* init lidar with some specific values (check code) */

	float temp, humi;

	init_wifi();

	for (;;);
	serial_put_str("hola mundo \n");
	
	while(1) {
		
		am2320_read(&temp, &humi);
		serial_put_str("hola mundo 2\n");

		sprintf(msg, "temperatura: %f     humedad: %f \n", temp, humi);
		serial_put_str(msg);
		serial_put_str("\n");
	}
}
