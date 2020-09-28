/*
 * send.c : envía una frase vía en forma binaria serial, a través del led 
 *          del teclado NUM
 *
 * Uso: ./send "frase a enviar"
 *
 * 1 segundo 1000 milisegundos
 * 1 milisegundo 1000 microsegundos
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <linux/kd.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#define ERROR -1

int fd; /* File descriptor for console (/dev/tty/) */

void sighandler(int signum);


void main(int argc, char *argv[])
{
	int i;

	if (argc != 2) {
		printf("Error. Usage: ./send \"hola mundo\" \n");
		return;
	}

	/* To be used as the fd in ioctl(). */
	if ((fd = open("/dev/console", O_NOCTTY)) == ERROR) {
		perror("open");
		return;
	}


	if ((ioctl(fd, KDSETLED, 0x2)) == ERROR) {
		perror("ioctl");
		close(fd);
		return;
	}

	
	char *c = argv[1];
	printf("Enviamos: %s\n",c);

	while (*c) {
		//char l = 'A';
		char l = *c;
		int led;

		for (i=0; i<8; i++) {
			if ((l & 0x80) == 0)
				led = 0;   /* TURN OFF LED */
			else
				led = 0x2; /* TURN ON NUM LED */
			l = (l<<1);

			if ((ioctl(fd, KDSETLED, led)) == ERROR) {
				perror("ioctl");
				close(fd);
				return;
			}
			usleep(100000);
		}

		if ((ioctl(fd, KDSETLED, 0x2)) == ERROR) {
			perror("ioctl");
			close(fd);
			return;
		}

		usleep(200000);
		c++;

	}

	close(fd);
}


