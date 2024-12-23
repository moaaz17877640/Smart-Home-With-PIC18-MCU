/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "hal_eeprom.h"
#include "../Interrupts/mcal_interrupt_config.h"



STD_ReturnType Data_EEPROM_WriteByte      (uint16 byteAdd, uint8 byteData){
    STD_ReturnType ret = E_OK;
    /* Read the Interrupt Status "Enabled or Disabled" */
    uint8 Interrupt_Status1 = INTCONbits.GIEH;
    uint8 Interrupt_Status2 = INTCONbits.GIEL;
    /* Update the Address Registers */
    EEADRH = (uint8)((byteAdd>>8)& 0x03);
    EEADR = (uint8)(byteAdd & 0xFF);
    /* Update the Data Registers */
    EEDATA = byteData;
    // This routine will select EEPROM program memory
    ACCESS_EEPROM_MEMORY_PROGRAM();
    // This routine will select  Flash Program/Data EEPROM
    ACCESS_FLASH_EEPROM();
    // This routine Allows write cycles to Flash program/data EEPROM
    ALLOW_WRITE_FLASH_EEPROM();
    /* This routine/s will disable interrupts*/
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will disable high priority global interrupts*/
        INTERRUPT_Global_High_Priority_Disable();
        /* This routine will disable low priority global interrupts*/
        INTERRUPT_Global_LOW_Priority_Disable();
    #else
        /* This routine will disable global interrupts*/
        INTERRUPT_GlobalDisable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralDisable();
    #endif
    /* Write the required sequence : 0x55 and 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    // This routine Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle
    INITIATE_ERASE_WRITE_EEPROM();
    /*Wait for write to complete*/
    while(EECON1bits.WR);
    // This routine Inhibits write cycles to Flash program/data EEPROM
    INHIBIT_WRITE_FLASH_EEPROM();
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIEH = Interrupt_Status1;
    INTCONbits.GIEL = Interrupt_Status2;
    
    return ret;
}



STD_ReturnType Data_EEPROM_ReadByte       (uint16 byteAdd, uint8 *byteData){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == byteData){
        ret = E_NOT_OK;
    }
    else{
        /* Update the Address Registers */
        EEADRH = (uint8)((byteAdd>>8)& 0x03);
        EEADR = (uint8)(byteAdd & 0xFF);
        // This routine will select EEPROM program memory
        ACCESS_EEPROM_MEMORY_PROGRAM();
        // This routine will select  Flash Program/Data EEPROM
        ACCESS_FLASH_EEPROM();
        // This routine Initiates an EEPROM read (Read takes one cycle)
        INITIATE_READ_EEPROM();
        /*Wait for reading process complete*/
        NOP();
        NOP();
        /*Get data*/
        *byteData = EEDATA;
        
        ret = E_OK;
    }
    return ret;
}