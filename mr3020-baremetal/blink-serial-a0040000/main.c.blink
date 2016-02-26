/*
 * Copyright (C) 2015 Facultad de Informática Universidad Nacional del Comahue.
 * 
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */
void start_baremetal(void);
void togle_led(void);
void wait(int seconds);

#define KSEG1			0xa0000000

#define KSEG1ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG1))

/*
 * Address map
 */

#define AR7240_APB_BASE						0x18000000  /* 384M */

/*
 * APB block
 */

#define AR7240_GPIO_BASE					AR7240_APB_BASE+0x00040000

/*
 * gpio configs
 */

#define AR7240_GPIO_OUT					AR7240_GPIO_BASE+0x8

/* LED's GPIOs on MR3020:
 *
 * 0	=> WLAN
 * 17	=> ETH
 * 26	=> WPS
 * 27	=> INTERNET
 *
 */

#define GPIO_INTERNET_LED_BIT               27
#define GPIO_INTERNET_LED_ON                 0
#define GPIO_WLAN_LED_BIT                    0
#define GPIO_WLAN_LED_ON                     1
#define GPIO_WPS_LED_BIT                    26
#define GPIO_WPS_LED_ON                      0
#define GPIO_ETH_LED_BIT                    17
#define GPIO_ETH_LED_ON                      0

#define ar7240_reg_rd(_phys)			(*(volatile unsigned int *)KSEG1ADDR(_phys))
#define ar7240_reg_wr_nf(_phys, _val)	((*(volatile unsigned int *)KSEG1ADDR(_phys)) = (_val))
#define ar7240_reg_wr(_phys, _val)		do { ar7240_reg_wr_nf(_phys, _val); ar7240_reg_rd(_phys); } while(0);

int wait_loop0 = 18200;
int wait_loop1 = 60;


void wait(int seconds)
{
    int i, j, k;

    for(i = 0; i < seconds; i++)
    {
        for(j = 0; j < wait_loop0; j++)
        {
            for(k = 0; k < wait_loop1; k++)
            {   // waste function, volatile makes sure it is not being optimized out by compiler
                int volatile t = 120 * j * i + k;
                t = t + 5;
            }
        }
    }
}

void togle_led()
{
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);

	gpio ^= 1 << GPIO_WPS_LED_BIT;
	gpio ^= 1 << GPIO_WLAN_LED_BIT;
	gpio ^= 1 << GPIO_ETH_LED_BIT;
	gpio ^= 1 << GPIO_INTERNET_LED_BIT;

	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);

}

void main()
{
	unsigned int gpio;

	gpio = ar7240_reg_rd(AR7240_GPIO_OUT);
	gpio &= ~(1 << GPIO_WPS_LED_BIT);
	gpio &= ~(1 << GPIO_WLAN_LED_BIT);
	gpio &= ~(1 << GPIO_ETH_LED_BIT);
	gpio &= ~(1 << GPIO_INTERNET_LED_BIT);
	ar7240_reg_wr(AR7240_GPIO_OUT, gpio);


    for(;;)
    {
        togle_led();
        wait(2);
    }
}
