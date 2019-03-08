#include <avr/io.h>
#include <util/delay.h>               // for _delay_ms()

/* Motores usando portb del atmega328 */

/*
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los pines 8-13 de
 *  arduino
 */
#define LED 0x01

volatile unsigned char * puerto_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

const int  v= 30;
const int MAX=62;
char pos_actual;

void blink_led(int estado){
	if (estado == 1){
		*puerto_b = *puerto_b | LED;
	}else{
		*puerto_b = *puerto_b & (~LED);
	}
}


void avanzar_un_paso(){
		if (pos_actual < MAX){

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00100100;
				_delay_ms(v);              

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00101000;
				_delay_ms(v);               

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00011000;
				_delay_ms(v);               

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00010100;
				_delay_ms(v);              

				pos_actual++;
		}
}

void retroceder_un_paso(){
		volatile unsigned char entrada; // sensor de tope
		entrada = *pin_b & 0b10;
		if (entrada == 0b10){

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00010100;
				_delay_ms(v);           

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00011000;
				_delay_ms(v);               

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00101000;
				_delay_ms(v);             

				*puerto_b = *puerto_b & 0b11000011;
				*puerto_b = *puerto_b | 0b00100100;
				_delay_ms(v);               
					

				pos_actual--;
		}
}

void motor_init(){
		volatile unsigned char entrada; // sensor de tope
		*puerto_b = 0b10; // pin 9 se usa como entrada
		*(ddr_b) = *(ddr_b) | 0b00111101;
		entrada = *pin_b & 0b10;
		blink_led(1);/*enciendo led hasta que el motor vaya a la posicion inicial*/
			do{
				retroceder_un_paso();
				entrada = *pin_b & 0b10;
			}while (entrada == 0b10);
		pos_actual=0;
		blink_led(0);/*apago led*/
}

char get_posicion(){
	char i;
	return pos_actual;
}

void ir_hasta_pos(int pos){
	if (pos_actual != pos){
		if (pos_actual < pos){
			do{
				avanzar_un_paso();
			}while (pos_actual < pos);
		}else{
			do{
				retroceder_un_paso();
			}while (pos_actual > pos);
		}
	}
}

void avanzar_n_pasos(char p){
		char i;
		for (i = 0; i < p; i++) {
			avanzar_un_paso();
		}
}

void retroceder_n_pasos(char p){
		char i;
		for (i = 0; i < p; i++) {
			retroceder_un_paso();
		}
}
	
