/*
 * main.c: little example program for testing garmin lidar lite v4
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */


#include <stddef.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "serial.h"
#include "twi.h"
#include "lidar-lite.h"

#define DELAY_180 450000

void esperar(long curr, long new_pos)
{
	volatile long delay;
	volatile int i;

	if (curr < new_pos)
		delay = ((new_pos - curr) * DELAY_180) / 180;
	else
		delay = ((curr - new_pos) * DELAY_180) / 180;

	for(i=0; i<(int)delay; i++);
}

void main()
{
	/* pin 9 arduino pwm signal output */
        DDRB = 0x02;

	char msg[80];
	uint16_t distance;
	volatile unsigned long i;
	int j;
	int current;

	serial_init(115200);
	twi_init();		/* init i2c */
	lidar_v4_init();	/* init lidar with some specific values (check code) */
	/* servo init */
        timer1_init();
	mover(0);
	current = 0;
//	esperar(180, current);
	for(i = 0; i < 450000;i++);

	while(1) {
		//for (j=0; j<=180; j=j+10) {
		for (j=0; j<=80; j=j+10) {
			mover(j);
			for(i = 0; i < 50000;i++);
			//esperar(current, j);
			current = j;
			distance = lidar_v4_get_distance();
			sprintf(msg, "distance (cm): %i \n", distance);
			serial_put_str(msg);
		}
		for (j=80; j>=0; j=j-10) {
			mover(j);
			for(i = 0; i < 50000;i++);
			//esperar(current, j);
			current = j;
			distance = lidar_v4_get_distance();
			sprintf(msg, "distance (cm): %i \n", distance);
			serial_put_str(msg);
		}

/*
		mover(0);
		for(i = 0; i < 450000;i++);
		distance = lidar_v4_get_distance();
		sprintf(msg, "distance (cm): %i \n", distance);
		serial_put_str(msg);

		mover(180);
		for(i = 0; i < 450000;i++);
		distance = lidar_v4_get_distance();
		sprintf(msg, "distance (cm): %i \n", distance);
		serial_put_str(msg);
*/
	}
}


