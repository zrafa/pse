// #include <stdio.h>
//#include <sys/ioctl.h>
// #include <fcntl.h> 
//#include <linux/i2c-dev.h>
// #include <unistd.h>
//#include <stdint.h>
//#include <stddef.h>
//#include <stdio.h>
//#include <util/delay.h>
#include <xinu.h>

#include "twi.h"
//#include "serial.h"


/* AM2321 ADDRESS 0x5C */
//#define SLAVE 0xB8
#define SLAVE 0x5C


static uint16_t 
_calc_crc16(const uint8_t *buf, size_t len) {
  uint16_t crc = 0xFFFF;
  
  while(len--) {
    crc ^= (uint16_t) *buf++;
    for (unsigned i = 0; i < 8; i++) {
      if (crc & 0x0001) {
	crc >>= 1;
	crc ^= 0xA001;
      } else {
	crc >>= 1;      
      }
    }
  }
  
  return crc;
}

static uint16_t
_combine_bytes(uint8_t msb, uint8_t lsb)
{
  return ((uint16_t)msb << 8) | (uint16_t)lsb;
}

uint8_t data[8];

void leer_medicion(uint8_t address, uint8_t *d)
{
	int i;

	for (i=0; i<8; i++)
        	data[i] = *(d+i);
}

int 
am2320_read(float *out_temperature, float *out_humidity) 
{

 // fd = open(I2C_DEVICE, O_RDWR);
 // if (fd < 0)
 //   return 1;

 // if (ioctl(fd, I2C_SLAVE, AM2321_ADDR) < 0)
 //   return 2;
   
  /* wake AM2320 up, goes to sleep to not warm up and
   * affect the humidity sensor 
   */
  //write(fd, NULL, 0);
  uint8_t c = 0;
  twi_write(SLAVE, &c, 0, NULL); 
  sleepms(100);
  //serial_put_str("hola3\n");
  c = 0;
  twi_write(SLAVE, &c, 0, NULL); 
  sleepms(100);
  
  /* write at addr 0x03, start reg = 0x00, num regs = 0x04 */
  data[0] = 0x03; 
  data[1] = 0x00; 
  data[2] = 0x04;
  //if (write(fd, data, 3) < 0)
   // return 3;
  twi_write(SLAVE, &data[0], 3, NULL); 
  
  /* wait for AM2320 */
  //usleep(1600); /* Wait atleast 1.5ms */
//	sleep (2);
  sleepms(4);
//  sleepms(1000);
  
  /*
   * Read out 8 bytes of data
   * Byte 0: Should be Modbus function code 0x03
   * Byte 1: Should be number of registers to read (0x04)
   * Byte 2: Humidity msb
   * Byte 3: Humidity lsb
   * Byte 4: Temperature msb
   * Byte 5: Temperature lsb
   * Byte 6: CRC lsb byte
   * Byte 7: CRC msb byte
   */
//  if (read(fd, data, 8) < 0)
 //   return 4;
  twi_read(SLAVE, 8, leer_medicion);
  
  //close(fd);

  sleepms(20);
  //printf("[0x%02x 0x%02x  0x%02x 0x%02x  0x%02x 0x%02x  0x%02x 0x%02x]\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7] );

  //serial_put_str("hola3\n");
  /* Check data[0] and data[1] */
  if (data[0] != 0x03 || data[1] != 0x04) {
	serial_put_str("error 9");
    return 9;
}

  /* Check CRC */
  uint16_t crcdata = _calc_crc16(data, 6);
  uint16_t crcread = _combine_bytes(data[7], data[6]);
  if (crcdata != crcread) {
	serial_put_str("error 10");
    return 10;
}

//  uint16_t temp16 = _combine_bytes(data[4], data[5]); 
//  uint16_t humi16 = _combine_bytes(data[2], data[3]);   
  //printf("temp=%u 0x%04x  hum=%u 0x%04x\n", temp16, temp16, humi16, humi16);
  
  /* Temperature resolution is 16Bit, 
   * temperature highest bit (Bit15) is equal to 1 indicates a
   * negative temperature, the temperature highest bit (Bit15)
   * is equal to 0 indicates a positive temperature; 
   * temperature in addition to the most significant bit (Bit14 ~ Bit0)
   *  indicates the temperature sensor string value.
   * Temperature sensor value is a string of 10 times the
   * actual temperature value.
   */
 // if (temp16 & 0x8000)
  //  temp16 = -(temp16 & 0x7FFF);

//  *out_temperature = (float)temp16 / 10.0;
 // *out_humidity = (float)humi16 / 10.0;


  uint16_t t = (((uint16_t) data[4] & 0x7F) << 8) | data[5];
  *out_temperature = t / 10.0;
  *out_temperature = ((data[4] & 0x80) >> 7) == 1 ? *out_temperature * (-1) : *out_temperature;

  uint16_t h = ((uint16_t) data[2] << 8) | data[3];
  *out_humidity = h / 10.0;

  return 0;
}

/*
int main(void) {
  float temp, humi;

  int ret = am2321(&temp, &humi);
  if (ret) {
    printf("Err=%d\n", ret);
    return ret;
  }

  printf( "Temperature %.1f [C]\n", temp);
  printf( "Humidity    %.1f [%%]\n", humi);
  
  return 0;
}
*/
