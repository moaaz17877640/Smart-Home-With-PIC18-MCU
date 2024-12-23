/* 
 * File:   ecu_led.c
 * Author: hp
 *
 * Created on 18 December 2023, 00:28
 */

#include "ecu_led.h"


STD_ReturnType LED_init   (const LED_Config_t* led_config ){
    STD_ReturnType rt = E_OK;
     if(NULL == led_config || led_config->pin_name > maximumNumberOfPins-1 || led_config->port_name > maximumNumberOfPorts-1  ){
        rt = E_NOT_OK;
    }
    else{
        pinConfig_t LED ={
            .port = led_config->port_name,
            .pin = led_config->pin_name,
            .logic = led_config->led_logic,
            .direction = GPIO_Pin_Direction_OUTPUT
        };
        gpio_pin_direction_initialize(&LED);
    }
    
    return rt;
}
STD_ReturnType LED_turnON (const LED_Config_t* led_config ){
    STD_ReturnType rt = E_OK;
     if(NULL == led_config || led_config->pin_name > maximumNumberOfPins-1 || led_config->port_name > maximumNumberOfPorts-1  ){
        rt = E_NOT_OK;
    }
    else{
       pinConfig_t LED ={
            .port = led_config->port_name,
            .pin = led_config->pin_name,
            .logic = led_config->led_logic,
            .direction = GPIO_Pin_Direction_OUTPUT
        };
        gpio_pin_write_logic(&LED , GPIO_Pin_Logic_HIGH);
    }
    
    return rt;
    
}
STD_ReturnType LED_turnOFF(const LED_Config_t* led_config ){
    STD_ReturnType rt = E_OK;
     if(NULL == led_config || led_config->pin_name > maximumNumberOfPins-1 || led_config->port_name > maximumNumberOfPorts-1  ){
        rt = E_NOT_OK;
    }
    else{
       pinConfig_t LED ={
            .port = led_config->port_name,
            .pin = led_config->pin_name,
            .logic = led_config->led_logic,
            .direction = GPIO_Pin_Direction_OUTPUT
        };
        gpio_pin_write_logic(&LED , GPIO_Pin_Logic_LOW);
    }
    
    return rt;
    
}
STD_ReturnType LED_toggle (const LED_Config_t* led_config ){
    STD_ReturnType rt = E_OK;
     if(NULL == led_config || led_config->pin_name > maximumNumberOfPins-1 || led_config->port_name > maximumNumberOfPorts-1  ){
        rt = E_NOT_OK;
    }
    else{
       pinConfig_t LED ={
            .port = led_config->port_name,
            .pin = led_config->pin_name,
            .logic = led_config->led_logic,
            .direction = GPIO_Pin_Direction_OUTPUT
        };
        gpio_pin_toggle_logic(&LED);
    }
    
    return rt;
    
}