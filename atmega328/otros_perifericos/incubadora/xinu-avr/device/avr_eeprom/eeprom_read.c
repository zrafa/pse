/* ramread.c  -  ramread */

#include <xinu.h>
#include <avr_eeprom_disk.h>

/*------------------------------------------------------------------------
 * eeprom_read  -  Read a block from a eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_read (
	  const __flash struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer to hold disk block	*/
	  uint32	count		/* Count of the bytes to read */
	)
{
	if ((eeprom_pos + count) >= EEPROM_SIZE)
		return SYSERR;

	eeprom_read_block((void *)buff, (const void*)eeprom_pos, count);
	return OK;
}
