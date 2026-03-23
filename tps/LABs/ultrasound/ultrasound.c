/*
 * ultrasound: controla el sensor HC-SR04 para medir distancias en cm
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU   16000000UL
#include <util/delay.h>


/* ultrasound_get_distance()
 * 	devuelve la distancia en cm del objeto delante del sensor
 * 	devuelve -1 si no existe ningun objeto
 */
int ultrasound_get_distance(void)
{
	int i = -1;

	_delay_us(1000);  /* espero 1000 microsegundos (1 milisegundo) */

	/* completar con driver de ultrasonido */

	return i;
}
