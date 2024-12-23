/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_usart.h"

#if INTERRUPT_USART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*USART_TX_InterruptHandler)(void) = NULL;
#endif
#if INTERRUPT_USART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*USART_RX_InterruptHandler)(void) = NULL;
static void(*USART_FRE_InterruptHandler)(void) = NULL;
static void(*USART_OVRR_InterruptHandler)(void) = NULL;
#endif


pinConfig_t pinRC6;
pinConfig_t pinRC7;

static void PinsConfig(void);
static void EUSART_BaudRateCalculation(const EUSART_Config_t *_EUSART);
static void EUSART_TX_Init     (const EUSART_Config_t *_EUSART);
static void EUSART_RX_Init     (const EUSART_Config_t *_EUSART);

STD_ReturnType   EUSART_ASYNC_Init               (const EUSART_Config_t *_EUSART){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _EUSART){
        ret = E_NOT_OK;
    }
    else{
       /*Serial Port Disable*/
        EUSART_MODULE_OFF();
        /*RC6 and RC7 configurations*/
        PinsConfig();
       /*Baud rate configuration*/
        EUSART_BaudRateCalculation(_EUSART);
       /*Initialize EUSART TX*/
        EUSART_TX_Init(_EUSART);
       /*Initialize EUSART RX*/
        EUSART_RX_Init(_EUSART);
        /*Serial Port Enable*/
        EUSART_MODULE_ON();
        ret = E_OK;
    }
    return ret;
}
STD_ReturnType   EUSART_ASYNC_Deinit             (const EUSART_Config_t *_EUSART){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _EUSART){
        ret = E_NOT_OK;
    }
    else{
       
        /*Serial Port Disable*/
        EUSART_MODULE_OFF();

        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   EUSART_ASYNC_ReadByteBlocking   (uint8 *_Byte){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _Byte){
        ret = E_NOT_OK;
    }
    else{
        while(!(PIR1bits.RCIF));
        *_Byte = RCREG;
        
        ret = E_OK;
    }
    return ret;
}
STD_ReturnType   EUSART_ASYNC_ReadByteNonBlocking   (uint8 *_Byte){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _Byte){
        ret = E_NOT_OK;
    }
    else{
        if(PIR1bits.RCIF)
        *_Byte = RCREG;
        
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   EUSART_ASYNC_Restart            (void){
    STD_ReturnType ret = E_NOT_OK;
    
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
            
    ret = E_OK;
}

STD_ReturnType   EUSART_ASYNC_WriteByteBlocking  (uint8 _Byte){
    STD_ReturnType ret = E_NOT_OK;
    
    while(!(TXSTAbits.TRMT));
#if INTERRUPT_USART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    USART_TX_INTERRUPT_ENABLE();
#endif
    TXREG = _Byte;
            
    ret = E_OK;
}
STD_ReturnType   EUSART_ASYNC_WriteStringBlocking(uint8 *_Byte, uint16 str_len){
    STD_ReturnType ret = E_NOT_OK;
    uint16 char_counter = E_Zero_Init;
    if(NULL == _Byte){
        ret = E_NOT_OK;
    }
    else{
        for(char_counter = E_Zero_Init;char_counter<str_len;char_counter++){
            ret = EUSART_ASYNC_WriteByteBlocking(_Byte[char_counter]);
        }

        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   EUSART_ASYNC_WriteByteNonBlocking  (uint8 _Byte){
    STD_ReturnType ret = E_NOT_OK;   
    if(TXSTAbits.TRMT){
#if INTERRUPT_USART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        USART_TX_INTERRUPT_ENABLE();
#endif
        TXREG = _Byte;
    }
   
    ret = E_OK;
}


STD_ReturnType   EUSART_ASYNC_WriteStringNonBlocking(uint8 *_Byte, uint16 str_len){
    STD_ReturnType ret = E_NOT_OK;
    uint16 char_counter = E_Zero_Init;
    if(NULL == _Byte){
        ret = E_NOT_OK;
    }
    else{
        while(char_counter<str_len){
            if(TXSTAbits.TRMT){
                ret = EUSART_ASYNC_WriteByteNonBlocking(_Byte[char_counter]);
                char_counter++;
            }
        }
        ret = E_OK;
    }
    return ret;
}

static void PinsConfig(void){
    STD_ReturnType ret = E_NOT_OK;
    /*Set RC6*/
    pinRC6.port = portC;
    pinRC6.pin = pin6;
    pinRC6.direction = GPIO_Pin_Direction_INPUT;
    pinRC6.logic = GPIO_Pin_Logic_LOW;
    ret = gpio_pin_initialize(&pinRC6);
   /*Set RC7*/
    pinRC7.port = portC;
    pinRC7.pin = pin7;
    pinRC7.direction = GPIO_Pin_Direction_INPUT;
    pinRC7.logic = GPIO_Pin_Logic_LOW;
    ret |= gpio_pin_initialize(&pinRC7);
}

static void EUSART_BaudRateCalculation(const EUSART_Config_t *_EUSART){
    float baudrate_Val = 0;
    switch(_EUSART->BAUDRAT_CONFIG){
        case EUSART_BAUDRAT_ASYN_8BIT_HIGH_SPEED:
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_8BIT_BAUDRATE();
            EUSART_ASYNCHRONOUS_HIGH_SPEED();
            baudrate_Val = ((_XTAL_FREQ/(float)_EUSART->Baud_rate) / 16) - 1; 
            break;
        case EUSART_BAUDRAT_ASYN_8BIT_LOW_SPEED:
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_8BIT_BAUDRATE();
            EUSART_ASYNCHRONOUS_LOW_SPEED();
            baudrate_Val = ((_XTAL_FREQ/ (float)_EUSART->Baud_rate) / 64) - 1;
            break;
        case EUSART_BAUDRAT_ASYN_16BIT_HIGH_SPEED:
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_16BIT_BAUDRATE();
            EUSART_ASYNCHRONOUS_LOW_SPEED();
            baudrate_Val = ((_XTAL_FREQ/(float)_EUSART->Baud_rate) / 4) - 1;
            break;
        case EUSART_BAUDRAT_ASYN_16BIT_LOW_SPEED:
            EUSART_ASYNCHRONOUS_MODE();
            EUSART_16BIT_BAUDRATE();
            EUSART_ASYNCHRONOUS_LOW_SPEED();
            baudrate_Val = ((_XTAL_FREQ/(float)_EUSART->Baud_rate) / 16) - 1;
            break;
        case EUSART_BAUDRAT_SYN_8BIT:
            EUSART_SYNCHRONOUS_MODE();
            EUSART_8BIT_BAUDRATE();
            baudrate_Val = ((_XTAL_FREQ/(float)_EUSART->Baud_rate) / 4) - 1;
            break;
        case EUSART_BAUDRAT_SYN_16BIT:
            EUSART_SYNCHRONOUS_MODE();
            EUSART_16BIT_BAUDRATE();
            baudrate_Val = ((_XTAL_FREQ/(float)_EUSART->Baud_rate) / 4) - 1;
            break;
        default:
            /*Do Nothing*/;
    }

    SPBRGH = (uint8)(((uint32)(baudrate_Val)) >> 8);
    SPBRG = (uint8)(((uint32)(baudrate_Val)));

}
static void EUSART_TX_Init     (const EUSART_Config_t *_EUSART){
    if(_EUSART->TX_Config.Transmit_Enable){
        /*Transmit Enable*/
        EUSART_ASYNCHRONOUS_TX_ENABLE();
        if(_EUSART->TX_Config.Transmit_Interrupt_Enable){
            /* This routine disable the interrupt feature for USART TX  */
            USART_TX_INTERRUPT_DISABLE();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            /* This routine will enable priority levels on interrupts*/
            INTERRUPT_PriorityLevelsEnable();
            switch(_EUSART->TX_Config.EUSART_TX_Interrupt_Priority){
                case INTERRUPT_LOW_PRIORITY: 
                    /* This routine enable the interrupt low priority for USART TX  */
                    USART_TX_INTERRUPT_LOW_PRIORITY_ENABLE();
                    /* This routine will enable low priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();
                    INTERRUPT_Global_LOW_Priority_Enable();break;
                case INTERRUPT_HIGH_PRIORITY:
                    /* This routine enable the interrupt high priority for USART TX  */
                    USART_TX_INTERRUPT_HIGH_PRIORITY_ENABLE();
                    /* This routine will enable high priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();break;
                default: /*Do nothing*/;
            }
            /*Configure USART TX Interrupt Handler*/
            USART_TX_InterruptHandler = _EUSART->EUSART_TX_InterruptHandler;
            /* This routine enable the interrupt feature for USART TX  */
            USART_TX_INTERRUPT_ENABLE();
#else
            /* This routine will enable global interrupts*/
            INTERRUPT_GlobalEnable();
            /* This routine will enable peripheral interrupts*/
            INTERRUPT_PeripheralEnable();
            /*Configure USART TX Interrupt Handler*/
            USART_TX_InterruptHandler = _EUSART->EUSART_TX_InterruptHandler;
            /* This routine enable the interrupt feature for USART TX  */
            USART_TX_INTERRUPT_ENABLE();
#endif  
        }
        else if(!(_EUSART->TX_Config.Transmit_Interrupt_Enable)){
            /* This routine disable the interrupt feature for USART TX  */
            USART_TX_INTERRUPT_DISABLE();
        }
        else{
            /*Do Nothing*/
        }

        if(_EUSART->TX_Config.Transmit_TX9_Enable){
            EUSART_ASYNCHRONOUS_TX9_ENABLE();
        }
        else if(!(_EUSART->TX_Config.Transmit_TX9_Enable)){
            EUSART_ASYNCHRONOUS_TX9_DISABLE();
        }
        else{
            /*Do Nothing*/
        }
    }
    else{
        /*Do Noting*/
    }
}
static void EUSART_RX_Init     (const EUSART_Config_t *_EUSART){
    if(_EUSART->RX_Config.Receive_Enable){
        EUSART_ASYNCHRONOUS_RX_ENABLE();
        if(_EUSART->RX_Config.Receive_Interrupt_Enable){
            /* This routine disable the interrupt feature for USART RX  */
            USART_RX_INTERRUPT_DISABLE();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            /* This routine will enable priority levels on interrupts*/
            INTERRUPT_PriorityLevelsEnable();
            switch(_EUSART->RX_Config.EUSART_RX_Interrupt_Priority){
                case INTERRUPT_LOW_PRIORITY: 
                    /* This routine enable the interrupt low priority for USART RX  */
                    USART_RX_INTERRUPT_LOW_PRIORITY_ENABLE();
                    /* This routine will enable low priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();
                    INTERRUPT_Global_LOW_Priority_Enable();break;
                case INTERRUPT_HIGH_PRIORITY:
                    /* This routine enable the interrupt high priority for USART RX  */
                    USART_RX_INTERRUPT_HIGH_PRIORITY_ENABLE();
                    /* This routine will enable high priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();break;
                default: /*Do nothing*/;
            }
            /*Configure USART RX Interrupt Handler*/
            USART_RX_InterruptHandler = _EUSART->EUSART_RX_InterruptHandler;
            USART_FRE_InterruptHandler = _EUSART->EUSART_FramingErrorInterruptHandler;
            USART_OVRR_InterruptHandler = _EUSART->EUSART_OverrunErrorInterruptHandler;
            /* This routine enable the interrupt feature for USART RX  */
            USART_RX_INTERRUPT_ENABLE();
#else
            /* This routine will enable global interrupts*/
            INTERRUPT_GlobalEnable();
            /* This routine will enable peripheral interrupts*/
            INTERRUPT_PeripheralEnable();
            /*Configure USART RX Interrupt Handler*/
            USART_RX_InterruptHandler = _EUSART->EUSART_RX_InterruptHandler;
            USART_FRE_InterruptHandler = _EUSART->EUSART_FramingErrorInterruptHandler;
            USART_OVRR_InterruptHandler = _EUSART->EUSART_OverrunErrorInterruptHandler;
            /* This routine enable the interrupt feature for USART RX  */
            USART_RX_INTERRUPT_ENABLE();
#endif  
        }
        else if(!(_EUSART->RX_Config.Receive_Interrupt_Enable)){
            /* This routine disable the interrupt feature for USART RX  */
            USART_RX_INTERRUPT_DISABLE();
        }
        else{
            /*Do Nothing*/
        }

        if(_EUSART->RX_Config.Receive_RX9_Enable){
            EUSART_ASYNCHRONOUS_RX9_ENABLE();
        }
        else if(!(_EUSART->RX_Config.Receive_RX9_Enable)){
            EUSART_ASYNCHRONOUS_RX9_DISABLE();
        }
        else{
            /*Do Nothing*/
        }
    }
    else{
        /*Do Noting*/
    }

}


void EUSART_TX_ISR(void){
    USART_TX_INTERRUPT_DISABLE();
    if(USART_TX_InterruptHandler) USART_TX_InterruptHandler();
}

void EUSART_RX_ISR(void){
    if(USART_RX_InterruptHandler)   USART_RX_InterruptHandler();
    if(USART_FRE_InterruptHandler)  USART_FRE_InterruptHandler();
    if(USART_OVRR_InterruptHandler) USART_OVRR_InterruptHandler();
}