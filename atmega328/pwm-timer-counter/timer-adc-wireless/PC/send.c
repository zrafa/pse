/*
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

void prender_led() 
{

}

void apagar_led() 
{

}


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


/*
	  signal(SIGINT,  sighandler);
	  signal(SIGTERM, sighandler);
	  signal(SIGQUIT, sighandler);
	  signal(SIGTSTP, sighandler);

	  printf("w00w00!\n\n");
	  printf("To exit hit Control-C.\n");

	  while (1) {
	     for (i = 0x01; i <= 0x04; i++) {
	         /* We do this because there is no LED for 0x03. */
/*
        	 if (i == 0x03) continue; 

	         usleep(50000);

	         if ((ioctl(fd, KDSETLED, i)) == ERROR) {
	            perror("ioctl");
	            close(fd);
	            // exit(ERROR);
		return;
	         }
	     }
	  }
*/

	  close(fd);
}


void sighandler(int signum)
{
	  /* Turn off all leds. No LED == 0x0. */
	  if ((ioctl(fd, KDSETLED, 0x0)) == ERROR) { 
	    perror("ioctl");
	    close(fd);
	    //exit(ERROR);
		return;
	  }

	  printf("\nw00w00!\n");
	  close(fd);
	  //exit(0);
		return;
}

