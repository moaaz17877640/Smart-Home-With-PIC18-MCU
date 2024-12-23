/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* includes */
#include "../mcal_std_types.h"
/* Data types declarations */

/* Macros declarations */
#define ERASE_WRITE_EEPROM_COMPLETED   0
#define READ_EEPROM_COMPLETED          0

/* MACROS Functions declarations */
// This routine will select Flash program memory
#define ACCESS_FLASH_MEMORY_PROGRAM()    (EECON1bits.EEPGD = 1)
// This routine will select EEPROM program memory
#define ACCESS_EEPROM_MEMORY_PROGRAM()   (EECON1bits.EEPGD = 0)

// This routine will select Configuration Select
#define ACCESS_CONFIG_REGISTERS()        (EECON1bits.CFGS = 1)
// This routine will select  Flash Program/Data EEPROM
#define ACCESS_FLASH_EEPROM()            (EECON1bits.CFGS = 0)

// This routine Allows write cycles to Flash program/data EEPROM
#define ALLOW_WRITE_FLASH_EEPROM()       (EECON1bits.WREN = 1)
// This routine Inhibits write cycles to Flash program/data EEPROM
#define INHIBIT_WRITE_FLASH_EEPROM()     (EECON1bits.WREN = 0)

// This routine Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle
#define INITIATE_ERASE_WRITE_EEPROM()    (EECON1bits.WR = 1)

// This routine Initiates an EEPROM read (Read takes one cycle)
#define INITIATE_READ_EEPROM()           (EECON1bits.RD = 1)


/* Functions declarations */
/**
 * 
 * @param byteAdd
 * @param byteData
 * @return 
 */
STD_ReturnType Data_EEPROM_WriteByte      (uint16 byteAdd, uint8 byteData);
/**
 * 
 * @param byteAdd
 * @param byteData
 * @return 
 */
STD_ReturnType Data_EEPROM_ReadByte       (uint16 byteAdd, uint8 *byteData);
#endif	/* HAL_EEPROM_H */

