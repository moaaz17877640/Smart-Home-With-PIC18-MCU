
#include "DC_Motor.h"

STD_ReturnType ECU_DC_Motor_initialize(const DC_Motor_t* _dc_motor){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _dc_motor ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_Motor_PIN1]));
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_Motor_PIN2]));
        
        rt = E_OK;
    }
    return rt;
}

STD_ReturnType ECU_DC_Motor_move_right(const DC_Motor_t* _dc_motor){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _dc_motor ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_Motor_PIN1]), GPIO_Pin_Logic_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_Motor_PIN2]), GPIO_Pin_Logic_LOW);
        
        rt = E_OK;
    }
    return rt;
}

STD_ReturnType ECU_DC_Motor_move_left(const DC_Motor_t* _dc_motor){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _dc_motor ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_Motor_PIN1]), GPIO_Pin_Logic_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_Motor_PIN2]), GPIO_Pin_Logic_HIGH);
        
        rt = E_OK;
    }
    return rt;
}


STD_ReturnType ECU_DC_Motor_stop (const DC_Motor_t* _dc_motor){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _dc_motor ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_Motor_PIN1]), GPIO_Pin_Logic_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_Motor_PIN2]), GPIO_Pin_Logic_LOW);
        
        rt = E_OK;
    }
    return rt;
}