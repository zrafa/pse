/*
 * main.c: little example program for testing am2320 temperature & humidity
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#include <xinu.h>
#include <string.h>

int 	sprintf (char *__s, const char *__fmt,...);

const __flash char mm1[] = "AT";
const __flash char mm2[] = "AT+RST";
const __flash char mm3[] = "AT+CWMODE=3";
const __flash char mm4[] = "AT+CWSAP=\"INCUBADORA\",,1,0";
const __flash char mm5[] = "AT+CIPMUX=1";		/* 0 : una conexion;    1 : hasta 4 conexiones */ 
const __flash char mm6[] = "AT+CIPSERVER=1,80";
//const __flash char mm7[] = "AT+CIPSEND=0,25";  /* en conexion 0 enviaremos 25 bytes */
const __flash char mm7[] = "AT+CIPSEND=%i,25";  /* en conexion 0 enviaremos 25 bytes */
const __flash char mm8[] = "<html><head></head><body>";
//const __flash char mm9[] = "AT+CIPSEND=0,19";
const __flash char mm9[] = "AT+CIPSEND=%i,19";
const __flash char mm10[] = "<h1>Incubadora</h1>";
//const __flash char mm11[] = "AT+CIPSEND=0,45";
const __flash char mm11[] = "AT+CIPSEND=%i,45";
//const __flash char mm12[] = "AT+CIPSEND=0,14";
const __flash char mm12[] = "AT+CIPSEND=%i,14";
const __flash char mm13[] = "</body></html>";
//const __flash char mm14[] = "AT+CIPCLOSE=0";
const __flash char mm14[] = "AT+CIPCLOSE=%i";

const __flash int n2 = 5;

extern float temp, humi;
extern int dias, horas;

int wait_connection() {
	int found = 0;
	char m[3];
	char c;

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
	c = serial_get_char();
	c = serial_get_char();

	return (c-48);
}

void cipsend_n(char * dest2, char * dest, const __flash char src[], int len, int n)
{
	int i;
	for (i=0; i<len; i++)
		dest[i] = src[i];

	dest[len] = 0;
	sprintf(dest2, dest, n);
	serial_put_str(dest2);
	sleepms(400);
}

process wifi() {

	char msg[46], msg2[20];
	int n, i;


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

		n = wait_connection();

	cipsend_n(msg, msg2, mm7, 16, n);
	//serial_put_str2(mm7);
	//serial_put_str(msg);
	//sleepms(300);

	serial_put_str2(mm8);
	sleepms(400);

			      
	cipsend_n(msg, msg2, mm9, 16, n);
	//serial_put_str2(mm9);
	//sleepms(300);


	serial_put_str2(mm10);
	sleepms(400);


	cipsend_n(msg, msg2, mm11, 16, n);

	sprintf(msg, "<h2>temperatura: %2.1f     humedad: %2.1f </h2>", temp, humi);
	serial_put_str(msg);
	sleepms(400);


	cipsend_n(msg, msg2, mm11, 16, n);

	sprintf(msg, "<h2>dias incubando: %2i (dias) y %2i (hs)   </h2>", dias, horas);
	serial_put_str(msg);
	sleepms(400);

	cipsend_n(msg, msg2, mm12, 16, n);
	//serial_put_str2(mm12);
	//sleepms(300);

	serial_put_str2(mm13);
	sleepms(400);

	cipsend_n(msg, msg2, mm14, 14, n);
	//serial_put_str2(mm14);
	//sleepms(300);

	// sleepms(10000);
	}

}

