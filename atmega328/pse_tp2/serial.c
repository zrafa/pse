#include<avr/io.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    /* demas registros */

    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */;
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_es;    /* udr0 i/o data */



} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);








#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)


void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_h = (BAUD_PRESCALE >> 8);
    puerto_serial->baud_rate_l = BAUD_PRESCALE;

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    // puerto_serial->status_control_c |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
    puerto_serial->status_control_b = 0b00011000;

    
	/* Activar la recepcion y transmicion */
    puerto_serial->status_control_c = 0b00000110;

}

// bit UDRE0 de UCSR0A
#define DATA_EMPTY 0x20

// bit UDRE0 de UCSR0A
#define DATA_UNREAD_READY 0x80

/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    while ( !(puerto_serial->status_control_a & DATA_EMPTY) );
    puerto_serial->data_es = outputChar;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */

        //while ( !(UCSR0A & (1 << UDRE0)) ) // Wait until buffer is empty
        //UDR0 = ReceivedChar;                    // Send the data to the TX buffer

}


char serial_get_char(void)
{
	char letra;
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

    while ( !(puerto_serial->status_control_a & DATA_UNREAD_READY) );
    letra = puerto_serial->data_es;
    
    return letra;
    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */

}



