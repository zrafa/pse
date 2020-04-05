#include "motor.h"
#include "modem.h"

/**********************************************************************
Protocolo de mensajes para comunicarse con el motor:
H10 (llevar motor hastra la posicion 10)
F05 (avanzar 5 pasos)
B05 (retroceder 5 pasos)
GET (que devuelva un int con la posicion actual del motor)
RES (para hacer el INIT a la posicion 00)
 **********************************************************************/
int main(void){

    /* Lleva el motor a la posicion inicial */
    motor_init();
    modem_init();
    //modem_enviar_sms("UNO");

    char rcvChar = 0, pos;
    char *comandoRecibido;
	char posicion[3];
    char tipoComando;

    /* Configure the UART for the serial driver. */

  char d,u; //Decena y Unidad, para calcular el valor pasado en el comando (posicion destino o cant de desplazamientos)
    while (1)
    {
		comandoRecibido="";
        comandoRecibido = modem_leer_sms();

        tipoComando = comandoRecibido[0]; //Primer caracter del mensaje: indica qué msj es dentro del protocolo

        switch (tipoComando) {
          case 'H':
            d = (comandoRecibido[1] - 48)*10; //Primer digito (decena)
            u = comandoRecibido[2]-48; //Segundo digito (unidad)
            ir_hasta_pos(d+u); 
            break;
          case 'F':
            d = (comandoRecibido[1] - 48)*10;
            u = comandoRecibido[2]-48;
            avanzar_n_pasos(d+u);
            break;
          case 'B':
            d = (comandoRecibido[1] - 48)*10;
            u = comandoRecibido[2]-48;
            retroceder_n_pasos(d+u);
            break;
          case 'G':
            pos = get_posicion(); //La posicion llega como un char, hay que pasarlo al valor correspondiente en ascii
			if(pos<10){ //Si es un solo caracter, se utiliza put_char
				/*serial_put_char(pos+48);*/
				posicion[0] = 58;
				posicion[1] = pos+48;
				posicion[2] = 0;
			}else{//Si es un numero de dos digitos, se debe utilizar put_str
				d = pos / 10; //Decena
				u = pos % 10; //Unidad
				posicion[0] = 58;
				posicion[1] =  d + 48;
				posicion[2] = u + 48;
				posicion[3] = 0; //Para que finalice la cadena de texto
				/*serial_put_str(posicion);*/
			} 
			modem_enviar_sms(posicion);
            break;
          case 'R':
            motor_init();
            break;
        }

    }

    return 0;
}
