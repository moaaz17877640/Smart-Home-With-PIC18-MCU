
#include "push_button.h"

STD_ReturnType ECU_Button_Intalize(const Button_Config_t *btn_Config){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == btn_Config ){
        rt = E_NOT_OK;
    }
    else{
        
        gpio_pin_direction_initialize (&(btn_Config->btn));
        rt = E_OK;
      
    }
    return rt;
}

STD_ReturnType ECU_Button_Read(const Button_Config_t *btn_Config, Button_status_t *btn_status){
    STD_ReturnType rt = E_NOT_OK;
    logic_t Get_buuton_logic = GPIO_Pin_Logic_LOW;
     if(NULL == btn_Config || NULL == btn_status){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn_Config->btn), &Get_buuton_logic );
        if(BUTTON_ACTIVE_HIGH == btn_Config->btn_connection){
            if(GPIO_Pin_Logic_HIGH == Get_buuton_logic ){
                *btn_status = BUTTON_PRESSED;
            }
            else{
                *btn_status = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn_Config->btn_connection){
            if(GPIO_Pin_Logic_LOW == Get_buuton_logic){
                *btn_status = BUTTON_PRESSED;
            }
            else{
                *btn_status = BUTTON_RELEASED;
            }
        }
        else{
            /*Do Nothing*/
        }
        rt = E_OK;
    }
    return rt;
}