/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef ECU_STEPPERMOTOR_H
#define	ECU_STEPPERMOTOR_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define STEPPER_Motor_PIN1 0x00U
#define STEPPER_Motor_PIN2 0x01U
#define STEPPER_Motor_PIN3 0x02U
#define STEPPER_Motor_PIN4 0x03U



/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum {
    STEPPER_Motor_OFF=0,
    STEPPER_Motor_ON        
}STEPPER_Motor_Status_t;

typedef struct{
    pinConfig_t stepper_motor_pin[4];
}stepper_Motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType ECU_STEPPER_Motor_initialize (const stepper_Motor_t* _stepper_motor);
STD_ReturnType ECU_STEPPER_Motor_move_right (const stepper_Motor_t* _stepper_motor, uint16 _angle);
STD_ReturnType ECU_STEPPER_Motor_move_left  (const stepper_Motor_t* _stepper_motor, uint16 _angle);
STD_ReturnType ECU_STEPPER_Motor_stop       (const stepper_Motor_t* _stepper_motor);




#endif	/* ECU_STEPPERMOTOR_H */

