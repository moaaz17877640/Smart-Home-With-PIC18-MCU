/* 
 * File:   hal_gpio.c
 * Author: hp
 *
 * Created on 17 December 2023, 23:50
 */

#include "hal_gpio.h"


/* Reference to the Data Direction Control Register */
volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/* Reference to the Data Latch Register */
volatile uint8 *lat_registers[] =  {&LATA,&LATB,&LATC,&LATD,&LATE}; 
/* Reference to the Port Status Register */
volatile uint8 *port_registers[] =  {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};


#if GPIO_Port_Pin_Configuration == config_Enable
STD_ReturnType gpio_pin_direction_initialize (const pinConfig_t* pinConfig ){
    STD_ReturnType rt = E_OK;
    if(NULL == pinConfig || pinConfig ->pin > maximumNumberOfPins-1 ){
        rt = E_NOT_OK;
    }
    else{
        switch(pinConfig->direction){
            case GPIO_Pin_Direction_OUTPUT:
                switch(pinConfig->port){
                    case portA:
                        TRISA &= ~(1 << pinConfig ->pin);break;
                    case portB:
                        TRISB &= ~(1 << pinConfig ->pin);break;
                    case portC:
                        TRISC &= ~(1 << pinConfig ->pin);break;
                    case portD:
                        TRISD &= ~(1 << pinConfig ->pin);break;
                    case portE:
                        TRISE &= ~(1 << pinConfig ->pin);break;
                    default: rt = E_NOT_OK;
                }
                break;
//                clearBit(*tris_registers[pinConfig->port],pinConfig->pin);break;
            case GPIO_Pin_Direction_INPUT:
//                setBit(*tris_registers[pinConfig->port],pinConfig->pin);break;
                switch(pinConfig->port){
                    case portA:
                        TRISA |= (1 << pinConfig ->pin);break;
                    case portB:
                        TRISB |= (1 << pinConfig ->pin);break;
                    case portC:
                        TRISC |= (1 << pinConfig ->pin);break;
                    case portD:
                        TRISD |= (1 << pinConfig ->pin);break;
                    case portE:
                        TRISE |= (1 << pinConfig ->pin);break;
                    default: rt = E_NOT_OK;
                }
            default: rt = E_NOT_OK;
        }
    }
    return rt;
}
#endif


#if GPIO_Port_Pin_Configuration == config_Enable
STD_ReturnType gpio_pin_get_direction_status (const pinConfig_t* pinConfig, direction_t* getDirection ){
    STD_ReturnType rt = E_OK;
    if(NULL == pinConfig || pinConfig ->pin > maximumNumberOfPins-1 || NULL == getDirection  ){
        rt = E_NOT_OK;
    }
    else{
        switch(pinConfig->port){
                    case portA:
                        *getDirection = ((TRISA >> pinConfig->pin)&1);break;
                    case portB:
                        *getDirection = ((TRISB >> pinConfig->pin)&1);break;
                    case portC:
                        *getDirection = ((TRISC >> pinConfig->pin)&1);break;
                    case portD:
                        *getDirection = ((TRISD >> pinConfig->pin)&1);break;
                    case portE:
                        *getDirection = ((TRISE >> pinConfig->pin)&1);break;
                    default: rt = E_NOT_OK;
        }
    }
    return rt;
}
#endif


#if GPIO_Port_Pin_Configuration == config_Enable
STD_ReturnType gpio_pin_write_logic   (const pinConfig_t* pinConfig, logic_t logic ){
    STD_ReturnType rt = E_OK;
    if(NULL == pinConfig || pinConfig ->pin > maximumNumberOfPins-1 ){
        rt = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_Pin_Logic_LOW:
                switch(pinConfig->port){
                    case portA:
                        LATA &= ~(1 << pinConfig ->pin);break;
                    case portB:
                        LATB &= ~(1 << pinConfig ->pin);break;
                    case portC:
                        LATC &= ~(1 << pinConfig ->pin);break;
                    case portD:
                        LATD &= ~(1 << pinConfig ->pin);break;
                    case portE:
                        LATE &= ~(1 << pinConfig ->pin);break;
                    default: rt = E_NOT_OK;
                }
                break;
            case GPIO_Pin_Logic_HIGH:
                switch(pinConfig->port){
                    case portA:
                        LATA |= (1 << pinConfig ->pin);break;
                    case portB:
                        LATB |= (1 << pinConfig ->pin);break;
                    case portC:
                        LATC |= (1 << pinConfig ->pin);break;
                    case portD:
                        LATD |= (1 << pinConfig ->pin);break;
                    case portE:
                        LATE |= (1 << pinConfig ->pin);break;
                    default: rt = E_NOT_OK;
                }
                break;
            default: rt = E_NOT_OK;
        }
    }
    return rt;
}
#endif


#if GPIO_Port_Pin_Configuration == config_Enable
STD_ReturnType gpio_pin_read_logic    (const pinConfig_t* pinConfig, logic_t* logic ){
    STD_ReturnType rt = E_OK;
    if(NULL == pinConfig || pinConfig ->pin > maximumNumberOfPins-1 || NULL == logic ){
        rt = E_NOT_OK;
    }
    else{
        switch(pinConfig->port){
                    case portA:
                        *logic = ((PORTA >> pinConfig->pin)&1);break;
                    case portB:
                        *logic = ((PORTB >> pinConfig->pin)&1);break;
                    case portC:
                        *logic = ((PORTC >> pinConfig->pin)&1);break;
                    case portD:
                        *logic = ((PORTD >> pinConfig->pin)&1);break;
                    case portE:
                        *logic = ((PORTE >> pinConfig->pin)&1);break;
                    default: rt = E_NOT_OK;
        }
        }
    
    return rt;
}
#endif




#if GPIO_Port_Pin_Configuration == config_Enable
STD_ReturnType gpio_pin_toggle_logic  (const pinConfig_t* pinConfig){
    STD_ReturnType rt = E_OK;
    if(NULL == pinConfig || pinConfig ->pin > maximumNumberOfPins-1 ){
        rt = E_NOT_OK;
    }
    else{
        switch(pinConfig->port){
                    case portA:
                        LATA ^= (1 << pinConfig ->pin);break;
                    case portB:
                        LATB ^= (1 << pinConfig ->pin);break;
                    case portC:
                        LATC ^= (1 << pinConfig ->pin);break;
                    case portD:
                        LATD ^= (1 << pinConfig ->pin);break;
                    case portE:
                        LATE ^= (1 << pinConfig ->pin);break;
                    default: rt = E_NOT_OK;
                } 
        }
    
    return rt;
}
#endif




#if GPIO_Port_Pin_Configuration == config_Enable
STD_ReturnType gpio_pin_initialize    (const pinConfig_t* pinConfig){
    STD_ReturnType rt = E_OK;
    if(NULL == pinConfig || pinConfig ->pin > maximumNumberOfPins-1 ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_direction_initialize (pinConfig);
        gpio_pin_write_logic(pinConfig,GPIO_Pin_Logic_LOW);
        }
    
    return rt;
}
#endif





#if GPIO_Port_Configuration == config_Enable
STD_ReturnType gpio_port_direction_initialize   (portIndex_t port, uint8  direction  ){
    STD_ReturnType rt = E_OK;
    if( port > maximumNumberOfPorts-1 ){
        rt = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
        }
    return rt;
}
#endif




#if GPIO_Port_Configuration == config_Enable
STD_ReturnType gpio_port_get_direction_status   (portIndex_t port, uint8* direction  ){
    STD_ReturnType rt = E_OK;
    if( port > maximumNumberOfPorts-1 ){
        rt = E_NOT_OK;
    }
    else{
        *direction = *tris_registers[port];
        }
    return rt;
}
#endif




#if GPIO_Port_Configuration == config_Enable
STD_ReturnType gpio_port_write_logic            (portIndex_t port, uint8 logic ){
    STD_ReturnType rt = E_OK;
    if( port > maximumNumberOfPorts-1 ){
        rt = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic; 
        }
    return rt;
}
#endif




#if GPIO_Port_Configuration == config_Enable
STD_ReturnType gpio_port_read_logic             (portIndex_t port, uint8* logic ){
    STD_ReturnType rt = E_OK;
    if( port > maximumNumberOfPorts-1 ){
        rt = E_NOT_OK;
    }
    else{
        *logic = *port_registers[port];
        }
    return rt;
}
#endif




#if GPIO_Port_Configuration == config_Enable
STD_ReturnType gpio_port_toggle_logic           (portIndex_t port){
    STD_ReturnType rt = E_OK;
    if( port > maximumNumberOfPorts-1 ){
        rt = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= GPIO_Port_Mask;
        }
    return rt;
}
#endif