/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init(void);
void serial_put_char(char outputChar);
char serial_get_char(void);
void serial_put_str(char * outputStr);
char* serial_get_str(void);
void serial_put_int (int valor, int cant_digitos);
void serial_put_long_int (long int valor, int cant_digitos);
void serial_put_double (double valor, char digitos_enteros, char digitos_fraccionarios);
char serial_recibido(void);


#endif /* _SERIAL_H */
