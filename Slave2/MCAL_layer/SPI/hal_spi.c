/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_spi.h"

#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*SPI_InterruptHandler)(void) = NULL;
static STD_ReturnType SPI_Interrupt_Config        (const SPI_Config_t *_SPI);
#endif


pinConfig_t SPI_SDO;
pinConfig_t SPI_SDI;
pinConfig_t SPI_SCK;
pinConfig_t SPI_SS;

static STD_ReturnType PinsConfig                  (const SPI_Config_t *_SPI);
static STD_ReturnType SPI_Mode_Variant_Config     (const SPI_Config_t *_SPI);
static STD_ReturnType SPI_Sample_Mode_Config      (const SPI_Config_t *_SPI);
static STD_ReturnType SPI_Clock_Phase_Config      (const SPI_Config_t *_SPI);
static STD_ReturnType SPI_Clock_polarity_Config   (const SPI_Config_t *_SPI);


STD_ReturnType   SPI_Init                  (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
            ret = E_NOT_OK;
        }
    else{
       /*SPI Disable*/
        SPI_PORT_DISABLE();
        /*Pins configurations*/
        ret = PinsConfig(_SPI);
       /*Configure SPI sample mode*/
        ret = SPI_Sample_Mode_Config(_SPI);
        /*Configure SPI clock phase*/
        ret = SPI_Clock_Phase_Config(_SPI);
        /*Configure SPI sample polarity*/
        ret = SPI_Clock_polarity_Config(_SPI);
        /*Configure mode variant*/
        ret = SPI_Mode_Variant_Config(_SPI);
        /*Configure SPI interrupt*/
#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = SPI_Interrupt_Config(_SPI);
#endif
        /*SPI Enable*/
        SPI_PORT_ENABLE();
    }
    return ret;
}
STD_ReturnType   SPI_Deinit                (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
            ret = E_NOT_OK;
        }
    else{
       /*SPI Disable*/
        SPI_PORT_DISABLE();
        /*Disable SPI interrupt*/
#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MCCP_SPI_INTERRUPT_DISABLE();
#endif

        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   SPI_ReadByteBlocking      (uint8 *_Byte){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _Byte){
            ret = E_NOT_OK;
        }
    else{
       while(!(SPI_CHECK_BUFFER_IF_FULL()));
       *_Byte = SSPBUF; 
       
       ret = E_OK;
    }
    return ret;
}
STD_ReturnType   SPI_ReadByteNonBlocking   (uint8 *_Byte){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _Byte){
            ret = E_NOT_OK;
        }
    else{
        if(SPI_CHECK_BUFFER_IF_FULL()){
        *_Byte = SSPBUF;
        }
        
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   SPI_WriteByteBlocking     (uint8 _Byte){
    STD_ReturnType ret = E_NOT_OK;
    uint8 read_BUF_temp = 0;
    SSPBUF = _Byte;
    while(!SPI_CHECK_BUFFER_IF_FULL());
    read_BUF_temp = SSPBUF;
    
    ret = E_OK;
    
    return ret;
}
STD_ReturnType   SPI_WriteStringBlocking   (uint8 *_Byte, uint16 str_len){
    STD_ReturnType ret = E_NOT_OK;
    uint16 l_Counter_Characters = E_Zero_Init; 
    if(NULL == _Byte){
            ret = E_NOT_OK;
        }
    else{
        for(l_Counter_Characters = E_Zero_Init;l_Counter_Characters<str_len;l_Counter_Characters++){
            ret = SPI_WriteByteBlocking(_Byte[l_Counter_Characters]);
            __delay_us(100);
        }
       
    }
    return ret;
}
STD_ReturnType   SPI_WriteByteNonBlocking  (uint8 _Byte){
    STD_ReturnType ret = E_NOT_OK;
   uint8 read_BUF_temp = 0;
    SSPBUF = _Byte;
    if(SPI_CHECK_BUFFER_IF_FULL());
    read_BUF_temp = SSPBUF;
    
    ret = E_OK;
    return ret;
}
STD_ReturnType   SPI_WriteStringNonBlocking(uint8 *_Byte, uint16 str_len){
    STD_ReturnType ret = E_NOT_OK;
    uint16 l_Counter_Characters = E_Zero_Init; 
    if(NULL == _Byte){
            ret = E_NOT_OK;
        }
    else{
       for(l_Counter_Characters = E_Zero_Init;l_Counter_Characters<str_len;l_Counter_Characters++){
            ret = SPI_WriteByteBlocking(_Byte[l_Counter_Characters]);
            __delay_us(100);
        }
        
        ret = E_OK;
    }
    return ret;
}


static STD_ReturnType PinsConfig(const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
        ret = E_NOT_OK;
    }
    else{
        TRISC5 = 0;
        TRISC4 = 1;
        TRISA5 = 1;
        if(SPI_MASTER_MODE_SELECTED == _SPI->SPI_Mode){
            TRISC3 = 0;
        }
        else if(SPI_SLAVE_MODE_SELECTED == _SPI->SPI_Mode){
            TRISC3 = 1;
        }
        else{
            /*Nothing*/
        }       
        
        
        ret = E_OK;
    }
    return ret;
}

static STD_ReturnType SPI_Mode_Variant_Config     (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
        ret = E_NOT_OK;
    }
    else{
        switch(_SPI->SPI_Mode_Variant){
            case SPI_MASTER_MODE_CLOCK_FOSC_DIV_4:
                SPI_MODE_VARIANT_SELECT(SPI_MASTER_MODE_CLOCK_FOSC_DIV_4);break;
            case SPI_MASTER_MODE_CLOCK_FOSC_DIV_16:
                SPI_MODE_VARIANT_SELECT(SPI_MASTER_MODE_CLOCK_FOSC_DIV_16);break;
            case SPI_MASTER_MODE_CLOCK_FOSC_DIV_64:
                SPI_MODE_VARIANT_SELECT(SPI_MASTER_MODE_CLOCK_FOSC_DIV_64);break;
            case SPI_MASTER_MODE_CLOCK_TMR_DIV_2:
                SPI_MODE_VARIANT_SELECT(SPI_MASTER_MODE_CLOCK_TMR_DIV_2);break;
            case SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED:
                SPI_MODE_VARIANT_SELECT(SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED);break;
            case SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED:
                SPI_MODE_VARIANT_SELECT(SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED);break;
            default:/*Nothing*/;
        }
        ret = E_OK;
    }
    return ret;
}

static STD_ReturnType SPI_Sample_Mode_Config     (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
        ret = E_NOT_OK;
    }
    else{
        switch(_SPI->SPI_Mode){
            case SPI_SLAVE_MODE_SELECTED:
                SPI_SAMPLE_MODE_SELECT(SPI_SAMPLE_AT_MIDDLE_OF_OUTPUT_TIME);break;
            case SPI_MASTER_MODE_SELECTED:
                switch(_SPI->SPI_Sample_mode){
                    case SPI_SAMPLE_AT_END_OF_OUTPUT_TIME:
                        SPI_SAMPLE_MODE_SELECT(SPI_SAMPLE_AT_END_OF_OUTPUT_TIME);break;
                    case SPI_SAMPLE_AT_MIDDLE_OF_OUTPUT_TIME:
                        SPI_SAMPLE_MODE_SELECT(SPI_SAMPLE_AT_MIDDLE_OF_OUTPUT_TIME);break;
                    default:/*Nothing*/;
                }break;   
            default:/*Nothing*/;
        }
       
       ret = E_OK;
    }
    return ret;
}
static STD_ReturnType SPI_Clock_Phase_Config     (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
        ret = E_NOT_OK;
    }
    else{
       switch(_SPI->SPI_Clock_Phase){
            case SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE:
                SPI_CLOCK_PHASE_SELECT(SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE);break;
            case SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE:
                SPI_CLOCK_PHASE_SELECT(SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE);break;
            default:/*Nothing*/;
        }
       ret = E_OK;
    }
    return ret;
}
static STD_ReturnType SPI_Clock_polarity_Config     (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
        ret = E_NOT_OK;
    }
    else{
       switch(_SPI->SPI_Clock_Polarity){
            case SPI_IDLE_STATE_FOR_CLOCK_IS_A_HIGH_LEVEL:
                SPI_CLOCK_POLARITY_SELECT(SPI_IDLE_STATE_FOR_CLOCK_IS_A_HIGH_LEVEL);break;
            case SPI_IDLE_STATE_FOR_CLOCK_IS_A_LOW_LEVEL:
                SPI_CLOCK_POLARITY_SELECT(SPI_IDLE_STATE_FOR_CLOCK_IS_A_LOW_LEVEL);break;
            default:/*Nothing*/;
        }
        
        ret = E_OK;
    }
    return ret;
}

#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType SPI_Interrupt_Config        (const SPI_Config_t *_SPI){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _SPI){
        ret = E_NOT_OK;
    }
    else{
       if(_SPI->SPI_Interrupt_Enable){
            /* This routine disable the interrupt feature for SPI Master  */
            MCCP_SPI_INTERRUPT_DISABLE();
            /* This routine disable the flag the interrupt feature for SPI Master  */
            MCCP_SPI_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            /* This routine will enable priority levels on interrupts*/
            INTERRUPT_PriorityLevelsEnable();
            switch(_SPI->SPI_Interrupt_Priority){
                case INTERRUPT_LOW_PRIORITY: 
                    /* This routine enable the interrupt low priority for SPI Master  */
                    MCCP_SPI_INTERRUPT_LOW_PRIORITY_ENABLE();
                    /* This routine will enable low priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();
                    INTERRUPT_Global_LOW_Priority_Enable();break;
                case INTERRUPT_HIGH_PRIORITY:
                    /* This routine enable the interrupt high priority for SPI Master  */
                    MCCP_SPI_INTERRUPT_HIGH_PRIORITY_ENABLE();
                    /* This routine will enable high priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();break;
                default: /*Do nothing*/;
            }
            /*Configure SPI Master Interrupt Handler*/
            SPI_InterruptHandler = _SPI->SPI_InterruptHandler;
            /* This routine enable the interrupt feature for SPI Master  */
            MCCP_SPI_INTERRUPT_ENABLE();
#else
            /* This routine will enable global interrupts*/
            INTERRUPT_GlobalEnable();
            /* This routine will enable peripheral interrupts*/
            INTERRUPT_PeripheralEnable();
            /*Configure SPI Master Interrupt Handler*/
            SPI_InterruptHandler = _SPI->SPI_InterruptHandler;
            /* This routine enable the interrupt feature for SPI Master  */
            MCCP_SPI_INTERRUPT_ENABLE();
#endif  
        }
        else if(!(_SPI->SPI_Interrupt_Enable)){
            /* This routine disable the interrupt feature for SPI Master  */
            MCCP_SPI_INTERRUPT_DISABLE();
        }
        else{
            /*Do Nothing*/
        }
        ret = E_OK;
    }
    return ret;
}
#endif



#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void MSSP_SPI_ISR(void){
    /* This routine disable the flag the interrupt feature for SPI Master  */
    MCCP_SPI_INTERRUPT_FLAG_CLEAR();
    if(SPI_InterruptHandler) SPI_InterruptHandler();
}
#endif