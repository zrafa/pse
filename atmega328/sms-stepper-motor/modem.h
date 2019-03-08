/**********************************************************************
 *
 * Filename:    modem.h
 * 
 * API para la aplicacion embebida 
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _MODEM_H
#define _MODEM_H

void modem_init(void);
void modem_enviar_sms(char * mensaje);
char* modem_leer_sms(void);


#endif /* _MODEM_H */
