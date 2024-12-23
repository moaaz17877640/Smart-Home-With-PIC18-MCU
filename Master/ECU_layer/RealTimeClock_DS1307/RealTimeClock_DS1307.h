/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef REALTIMECLOCK_DS1307_H
#define	REALTIMECLOCK_DS1307_H

#include "./../../MCAL_layer/GPIO/hal_gpio.h"
#include "./../../MCAL_layer/USART/hal_usart.h"
#include "./../../mcc_generated_files/mcc.h"
#include "./../../mcc_generated_files/examples/i2c_master_example.h"

typedef struct {
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 days;
    uint8 months;
    uint8 years;
}REALTIMECLOCK_DS1307_t;

REALTIMECLOCK_DS1307_t  REALTIMECLOCK_DS1307_Get_Data(void);
uint8  *REALTIMECLOCK_DS1307_print_Data(void);





#endif	/* REALTIMECLOCK_DS1307_H */

