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

//Muestra un solo valor decimal
void uart_put_float (float input){

	if (input < 0){
		putchar('-');
		input = -input;
	}

    int valor_aux = input * 10;
    if(input<10)
    {
        serial_put_char((valor_aux/10)+48);
    } else if(input<100){
        serial_put_char(valor_aux/100+48);
        serial_put_char((valor_aux%100)/10+48);
    } else if(input<1000){ //mayores a 100
        serial_put_char(valor_aux/1000+48);
        serial_put_char((valor_aux%1000)/100+48);
        serial_put_char((valor_aux%100)/10+48);
    } else {
        return;
    }
    serial_put_char('.');
    serial_put_char((valor_aux%10)+48);
}


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

		sprintf(msg, "temperatura: %f     humedad: %f \n", temp, humi);
		serial_put_str(msg);
		serial_put_str("\n");
	}
}
