/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#ifndef TEMPERATURESENSOR_TC74_H
#define	TEMPERATURESENSOR_TC74_H

#include "./../../mcc_generated_files/mcc.h"
#include "./../../mcc_generated_files/examples/i2c_master_example.h"


uint8_t TemperatureSensor_TC74_Read_Temp(i2c_address_t TC74_Address);


#endif	/* TEMPERATURESENSOR_TC74_H */

