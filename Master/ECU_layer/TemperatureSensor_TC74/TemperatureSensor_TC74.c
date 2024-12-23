/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "TemperatureSensor_TC74.h"


uint8_t TemperatureSensor_TC74_Read_Temp(i2c_address_t TC74_Address){
    uint8_t TC74_TempValue = 0;
    TC74_TempValue = I2C_Read1ByteRegister(TC74_Address, 0x00);
    
    return TC74_TempValue;
}