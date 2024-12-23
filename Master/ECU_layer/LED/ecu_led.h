/* 
 * File:   ecu_led.h
 * Author: hp
 *
 * Created on 18 December 2023, 00:28
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Macros declarations */


/* MACROS Functions declarations */


/* Data types declarations */
typedef enum{
    LED_LOW=0,
    LED_HIGH
}LED_Logic_t;

typedef struct{
    uint8 port_name :4;
    uint8 pin_name  :3;
    uint8 led_logic :1;
}LED_Config_t;

/* Functions declarations */
STD_ReturnType LED_init   (const LED_Config_t* led_config );
STD_ReturnType LED_turnON (const LED_Config_t* led_config );
STD_ReturnType LED_turnOFF(const LED_Config_t* led_config );
STD_ReturnType LED_toggle (const LED_Config_t* led_config );

#endif	/* ECU_LED_H */

