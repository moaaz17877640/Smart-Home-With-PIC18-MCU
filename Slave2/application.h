/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* includes */
#include "ECU_layer/ECU_init.h"
#include "MCAL_layer/Interrupts/mcal_external_interrupts.h"
#include "MCAL_layer/EEPROM/hal_eeprom.h"
#include "MCAL_layer/ADC/hal_adc.h"
#include "MCAL_layer/Timer0/hal_timer0.h"
#include "MCAL_layer/Timer1/hal_timer1.h"
#include "MCAL_layer/Timer2/hal_timer2.h"
#include "MCAL_layer/Timer3/hal_timer3.h"
#include "MCAL_layer/CCP/hal_ccp.h"
#include "MCAL_layer/USART/hal_usart.h"
#include "MCAL_layer/SPI/hal_spi.h"
#include "MCAL_layer/I2C/hal_i2c.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/i2c_slave.h"


/* Macros declarations */


/* MACROS Functions declarations */


/* Data types declarations */


/* Functions declarations */
void GPIO_intialization(void);


#endif	/* APPLICATION_H */

