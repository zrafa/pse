/**********************************************************************
 *
 * Filename:    modem.c
 * 
 * Description: The main program file the modem driver example.
 *
 *
 **********************************************************************/

#include "stdint.h"
#include "serial.h"
#include <util/delay.h>
#include <string.h>

#define LED 0x01
volatile unsigned char * puerto_b2 = (unsigned char *) 0x25;
volatile unsigned char * ddr_b2 = (unsigned char *) 0x24; /* direccion de DDR B */


char * cadena = "";
	

void blink_led2(int estado){
	if (estado == 1){
		*puerto_b2 = *puerto_b2 | LED;
	}else{
		*puerto_b2 = *puerto_b2 & (~LED);
	}
}


/*Inicializar modem*/

void modem_init(){
    serial_init();
    
    *ddr_b2=*ddr_b2 | LED;
    /*DDRB = DDRB | LED;*/
    *puerto_b2 = *puerto_b2 & (~LED);
	/*PORTB = PORTB & (~LED);*/

    serial_put_char('a');   _delay_ms(100);
    serial_put_char('t');	_delay_ms(100);
    serial_put_char('a');	_delay_ms(100);
    serial_put_char('t');	_delay_ms(100);
    serial_put_char('a');	_delay_ms(100);
    serial_put_char('t');	_delay_ms(100);
    serial_put_char('a');	_delay_ms(100);
    serial_put_char('t');	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);

	serial_put_str("at");
	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);

	serial_put_str("at");
	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);
	
}

/*** Enviar sms ***/
void modem_enviar_sms(char* mensaje){
	//char fin_sms = toascii(26);
	char fin_sms = 26;
	_delay_ms(2000);

	blink_led2(1);_delay_ms(2000);blink_led2(0);_delay_ms(200);
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	serial_put_str("at");
	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);

	serial_put_str("at");
	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);
	
	serial_put_str("at+cmgf=1");
	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);

	serial_put_str("at+cmgs=\"+5492984648776\"\n\r");
	_delay_ms(1000);
   // serial_put_char('\n');
	//serial_put_char('\r');
	_delay_ms(100);

	serial_put_str(mensaje);
	_delay_ms(100);
	serial_put_char(fin_sms); 	
	_delay_ms(100);
	serial_put_char('\n');	
	_delay_ms(100);
	serial_put_char('\r');
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	_delay_ms(2000);
}

/*** Recibir sms***/
char* modem_leer_sms(){
	_delay_ms(1000);
	serial_put_str("at+cmgf=1");
	_delay_ms(100);
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(100);

	serial_put_str("at+cnmi=1,2,0,0,0");
    serial_put_char('\n');
	serial_put_char('\r');
	_delay_ms(1000);
		
	cadena ="000";
	cadena = serial_get_str();
	
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(1000);

	char c = 'q';
	char c1 = 'q';
	char c2 = 'q';
	char c3 = 'q';
	
	/* Consumo caracteres hasta encontrar un salto de linea*/
	while (c != '\n'){c = serial_get_char();}
	c = 'q';
	/* Consumo caracteres hasta encontrar un salto de linea*/
	while (c != '\n'){c = serial_get_char();}
	
	/* Los 3 siguientes caracteres corresponden al sms recibido*/
	c1 = serial_get_char();
	c2 = serial_get_char();
	c3 = serial_get_char();

	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(200);
	blink_led2(1);_delay_ms(200);blink_led2(0);_delay_ms(1000);
			
	/* cadena = serial_get_str()*/
	cadena ="";
	cadena[0]=c1;
	cadena[1]=c2;
	cadena[2]=c3;
	cadena[3]=0;
				
	c = 'q';
	/* Consumo caracteres restantes hasta encontrar un salto de linea*/
	while (c != '\n'){c = serial_get_char();}
			
    return cadena;
}
