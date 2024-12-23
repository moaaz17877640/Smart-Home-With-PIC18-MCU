/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "ecu_stepperMotor.h"

STD_ReturnType ECU_STEPPER_Motor_initialize(const stepper_Motor_t* _stepper_motor){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _stepper_motor ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_direction_initialize(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]));
        gpio_pin_direction_initialize(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]));
        gpio_pin_direction_initialize(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]));
        gpio_pin_direction_initialize(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]));
        
        rt = E_OK;
    }
    return rt;
}

STD_ReturnType ECU_STEPPER_Motor_move_left(const stepper_Motor_t* _stepper_motor, uint16 _angle){
    STD_ReturnType rt = E_NOT_OK;
    uint16 noOfSteps , noOfIterations,iter;
    if(NULL == _stepper_motor){
        rt = E_NOT_OK;
    }
    else{
        noOfSteps = (_angle * 2048UL) / 360;
        noOfIterations = noOfSteps / 4;
        for(iter = 0 ; iter < noOfIterations ; iter++){
            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_LOW);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);

            __delay_ms(10);

            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_LOW);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);

            __delay_ms(10);

            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_LOW);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);

            __delay_ms(10);

            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_LOW);

            __delay_ms(10);
        }

        rt = E_OK;
    }
    return rt;
}

STD_ReturnType ECU_STEPPER_Motor_move_right(const stepper_Motor_t* _stepper_motor, uint16 _angle){
    STD_ReturnType rt = E_NOT_OK;
    uint16 noOfSteps , noOfIterations,iter;
    if(NULL == _stepper_motor){
        rt = E_NOT_OK;
    }
    else{
        noOfSteps = (_angle * 2048UL) / 360;
        noOfIterations = noOfSteps / 4;
        for(iter = 0 ; iter < noOfIterations ; iter++){
            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_LOW);

            __delay_ms(10);

            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_LOW);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);

            __delay_ms(10);

            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_LOW);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);

            __delay_ms(10);

            rt  = gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_LOW);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
            rt |= gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);

            __delay_ms(10);
        }

        rt = E_OK;
    }
    return rt;
}


STD_ReturnType ECU_STEPPER_Motor_stop(const stepper_Motor_t* _stepper_motor){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _stepper_motor ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
        gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
        gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN3]), GPIO_Pin_Logic_HIGH);
        gpio_pin_write_logic(&(_stepper_motor->stepper_motor_pin[STEPPER_Motor_PIN4]), GPIO_Pin_Logic_HIGH);
        
        rt = E_OK;
    }
    return rt;
}
