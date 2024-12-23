/* 
 * File:   DC_Motor.h
 * Author: hp
 *
 * Created on 22 February 2024, 01:34
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/* ----------------- Includes -----------------*/
#include "DC_Motor_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define DC_Motor_PIN1 0x00U
#define DC_Motor_PIN2 0x01U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    DC_Motor_OFF=0,
    DC_Motor_ON        
}DC_Motor_Status_t;

typedef struct{
    pinConfig_t dc_motor_pin[2];
}DC_Motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType ECU_DC_Motor_initialize (const DC_Motor_t* _dc_motor);
STD_ReturnType ECU_DC_Motor_move_right (const DC_Motor_t* _dc_motor);
STD_ReturnType ECU_DC_Motor_move_left  (const DC_Motor_t* _dc_motor);
STD_ReturnType ECU_DC_Motor_stop       (const DC_Motor_t* _dc_motor);


#endif	/* DC_MOTOR_H */

