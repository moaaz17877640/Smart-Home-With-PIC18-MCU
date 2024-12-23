/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "ecu_keyPad.h"

uint8 btn_value[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLOUMNS] = {
                                                             {'7','8','9','/'},
                                                             {'4','5','6','*'},
                                                             {'1','2','3','-'},
                                                             {'#','0','=','+'}
                                                        };

STD_ReturnType keyPad_Initialize(const KeyPad_t *keypad){
    STD_ReturnType rt = E_NOT_OK;
    uint8 l_rows_counter = E_Zero_Init;
    uint8 l_coloums_counter =E_Zero_Init;
     if(NULL == keypad ){
        rt = E_NOT_OK;
    }
    else{
         for(l_rows_counter =E_Zero_Init ; l_rows_counter<ECU_KEYPAD_ROWS ; l_rows_counter++){
             rt = gpio_pin_initialize(&(keypad->KeypadRowsConfig[l_rows_counter]));
         }
         for(l_coloums_counter = E_Zero_Init ; l_coloums_counter<ECU_KEYPAD_COLOUMNS ; l_coloums_counter++){
             rt = gpio_pin_direction_initialize(&(keypad->KeypadColoumnsConfig[l_coloums_counter]));
         }
        rt = E_OK;
    }
    return rt;
}


STD_ReturnType keyPad_Read(const KeyPad_t *keypad, uint8 *keypad_value){
    STD_ReturnType rt = E_NOT_OK;
    uint8 l_rows_counter = E_Zero_Init;
    uint8 l_coloumns_counter = E_Zero_Init;
    uint8 l_counter = E_Zero_Init;
    logic_t coloumn_logic;
     if(NULL == keypad || NULL == keypad_value ){
        rt = E_NOT_OK;
    }
    else{
        for(l_rows_counter = E_Zero_Init ; l_rows_counter < ECU_KEYPAD_ROWS ; l_rows_counter++){
            for(l_counter = E_Zero_Init ; l_counter < ECU_KEYPAD_ROWS ; l_counter++){
               rt = gpio_pin_write_logic(&(keypad->KeypadRowsConfig[l_counter]), GPIO_Pin_Logic_LOW );
            }
            gpio_pin_write_logic(&(keypad->KeypadRowsConfig[l_rows_counter]), GPIO_Pin_Logic_HIGH );
            for(l_coloumns_counter = E_Zero_Init ; l_coloumns_counter < ECU_KEYPAD_COLOUMNS ; l_coloumns_counter++){
               rt = gpio_pin_read_logic(&(keypad->KeypadColoumnsConfig[l_coloumns_counter]), &coloumn_logic );
               if(coloumn_logic == GPIO_Pin_Logic_HIGH ){
                   *keypad_value = btn_value[l_rows_counter][l_coloumns_counter];
                   
               }
            }
        }  
        rt = E_OK;
    }
    return rt;
}