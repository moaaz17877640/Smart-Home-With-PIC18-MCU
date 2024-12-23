

#include "ecu_relay.h"

STD_ReturnType ECU_Relay_Initialize (Relay_Config_t *relay){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == relay ){
        rt = E_NOT_OK;
    }
    else{
         pinConfig_t relay_t ={
             .pin = relay->Relay_pin,
             .port = relay->Relay_port,
             .logic = relay->Relay_status,
             .direction = GPIO_Pin_Direction_OUTPUT
         };
         gpio_pin_initialize(&relay_t);

        rt = E_OK;
      
    }
    return rt;
}

STD_ReturnType ECU_Relay_turnON     (Relay_Config_t *relay){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == relay ){
        rt = E_NOT_OK;
    }
    else{
         pinConfig_t relay_t ={
             .pin = relay->Relay_pin,
             .port = relay->Relay_port,
             .logic = relay->Relay_status,
             .direction = GPIO_Pin_Direction_OUTPUT
         };
        gpio_pin_write_logic(&relay_t, GPIO_Pin_Logic_HIGH );

        rt = E_OK;
      
    }
    return rt;
}

STD_ReturnType ECU_Relay_turnOFF(Relay_Config_t *relay){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == relay ){
        rt = E_NOT_OK;
    }
    else{
         pinConfig_t relay_t ={
             .pin = relay->Relay_pin,
             .port = relay->Relay_port,
             .logic = relay->Relay_status,
             .direction = GPIO_Pin_Direction_OUTPUT
         };
        gpio_pin_write_logic(&relay_t, GPIO_Pin_Logic_LOW );

        rt = E_OK;
      
    }
    return rt;
}

STD_ReturnType ECU_Relay_toggle     (Relay_Config_t *relay){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == relay ){
        rt = E_NOT_OK;
    }
    else{
         pinConfig_t relay_t ={
             .pin = relay->Relay_pin,
             .port = relay->Relay_port,
             .logic = relay->Relay_status,
             .direction = GPIO_Pin_Direction_OUTPUT
         };
        gpio_pin_toggle_logic(&relay_t);

        rt = E_OK;
      
    }
    return rt;
}