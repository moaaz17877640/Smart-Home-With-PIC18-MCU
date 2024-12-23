/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "EEPROM_20C02C.h"


void EEPROM_20C02C_Write_Byte   (i2c_address_t EEPROM_Adress, i2c_address_t Byte_Adress, uint8_t _Byte){
    I2C_Write1ByteRegister(EEPROM_Adress, Byte_Adress, _Byte);
}


uint8_t EEPROM_20C02C_Read_Byte (i2c_address_t EEPROM_Adress, i2c_address_t Byte_Adress){
    uint8_t Get_Value;
    Get_Value = I2C_Read1ByteRegister(EEPROM_Adress, Byte_Adress);
    return Get_Value;
}
