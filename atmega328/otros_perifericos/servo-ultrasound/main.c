#include <avr/interrupt.h>
#include "timer.h"
#include "usound.h"

int main(void)
{
	uint32_t d;
	
	DDRB = 0x02;

	usound_init();
	timer1_init();
	volatile unsigned long i;
	d = 0;

	mover_der();

	while(1){
		d = readDistance();
		if (d < 20) {
			mover_izq();
			for(i = 0; i < 1550000;i++);
			while (d< 20) d = readDistance();
//			for(i = 0; i < 450000;i++);
			mover_der();
			d = 0;
		}
		/*mover_izq();:
		for(i = 0; i < 450000;i++);
		apagar();
		for(i = 0; i < 450000;i++);
		mover_der();*/
//		mover();
	//	for(i = 0; i < 450000;i++);
	//	mover_der();
		
	}
}




