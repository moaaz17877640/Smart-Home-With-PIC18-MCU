/* 
 * File:   push_button.h
 * Author: hp
 *
 * Created on 20 February 2024, 22:39
 */

#ifndef PUSH_BUTTON_H
#define	PUSH_BUTTON_H

/* ----------------- Includes -----------------*/
#include "push_button_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    BUTTON_PRESSED=0,
    BUTTON_RELEASED
}Button_status_t;

typedef enum{
    BUTTON_ACTIVE_HIGH=0,
    BUTTON_ACTIVE_LOW
}Button_connection_t;

typedef struct{
    pinConfig_t         btn;
    Button_status_t     btn_status;
    Button_connection_t btn_connection;
}Button_Config_t;


/* ----------------- Software Interfaces Declarations -----------------*/

STD_ReturnType ECU_Button_Intalize (const Button_Config_t *btn_Config);

STD_ReturnType ECU_Button_Read     (const Button_Config_t *btn_Config,  Button_status_t *btn_status);

#endif	/* PUSH_BUTTON_H */

