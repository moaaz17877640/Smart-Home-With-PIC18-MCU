/* 
 * File:   ecu_relay.h
 * Author: hp
 *
 * Created on 21 February 2024, 23:01
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* ----------------- Includes -----------------*/
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    ECU_RELAY_OFF=0,
    ECU_RELAY_ON
}Relay_Status_t;

typedef struct{
    uint8 Relay_port:3;
    uint8 Relay_pin:3;
    uint8 Relay_status:1;
    uint8 reserved:1;
}Relay_Config_t;

/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType ECU_Relay_Initialize (Relay_Config_t *relay);
STD_ReturnType ECU_Relay_turnON     (Relay_Config_t *relay);
STD_ReturnType ECU_Relay_turnOFF    (Relay_Config_t *relay);
STD_ReturnType ECU_Relay_toggle     (Relay_Config_t *relay);

#endif	/* ECU_RELAY_H */

