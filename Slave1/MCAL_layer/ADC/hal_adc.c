/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_adc.h"

#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void ADC_Select_Specific_Channel(ADC_Channel_t _ADC_Channel);
static inline void ADC_Voltage_Reference_Control(const ADC_Config_t *_ADC_config);
static inline void ADC_Result_Format_Control(const ADC_Config_t *_ADC_config);
static inline void ADC_Interrupt_Configuration(const ADC_Config_t *_ADC_config);



STD_ReturnType ADC_Init (const ADC_Config_t *_ADC_config){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        /*Disable A/D Converter*/
        ADC_CONVERSION_DISABLE();
        /*Configure A/D Acquisition Time*/
        ADCON2bits.ACQT = _ADC_config->Acquisition_Time;
        /*Configure A/D Conversion Clock*/
        ADCON2bits.ADCS = _ADC_config->Conversion_Clock;
        /*Configure input Channel*/
        ADCON0bits.CHS = _ADC_config->Channel;
        ADC_Select_Specific_Channel(_ADC_config->Channel);
        /*Configure A/D Interrupt*/
#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_Interrupt_Configuration(_ADC_config);
#endif
        /*Configure A/D Result_Format*/
        ADC_Result_Format_Control(_ADC_config);
        /*Configure Voltage reference*/
        ADC_Voltage_Reference_Control(_ADC_config);
        /*Enable A/D Converter*/
        ADC_CONVERSION_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType ADC_Deinit (const ADC_Config_t *_ADC_config){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        /*Disable A/D Converter*/
        ADC_CONVERSION_DISABLE();
       /* This routine disable the interrupt feature for ADC module */
#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType ADC_Select_Channel (const ADC_Config_t *_ADC_config, ADC_Channel_t _ADC_Channel){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = _ADC_Channel;
        ADC_Select_Specific_Channel(_ADC_Channel);
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType ADC_Start_Conversion (const ADC_Config_t *_ADC_config){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        ADC_CONVERSION_START();
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType ADC_Is_Conversion_Done (const ADC_Config_t *_ADC_config, uint8 *_Conversion_status){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        *_Conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType ADC_Conversion_Result (const ADC_Config_t *_ADC_config, ADC_Result_t *_ADC_Result){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_FORMAT_RIGHT == _ADC_config->Result_Format){
            *_ADC_Result = (ADC_Result_t)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_FORMAT_LEFT == _ADC_config->Result_Format){
            *_ADC_Result = (ADC_Result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
            *_ADC_Result = (ADC_Result_t)((ADRESH << 8) + ADRESL);
        }
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType ADC_Get_Conversion_Result_Block (const ADC_Config_t *_ADC_config, ADC_Channel_t _ADC_Channel,
                                                                                ADC_Result_t *_ADC_Result){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        /*Configure input Channel*/
        ADC_Select_Channel (_ADC_config, _ADC_Channel);
        /* start A/D conversion*/
        ADC_Start_Conversion (_ADC_config);
        /*Check is conversion complete*/
        while(ADCON0bits.GO_nDONE);
        /*Get the conversion result*/
        ADC_Conversion_Result (_ADC_config, _ADC_Result);
        ret = E_OK;
    }
    return ret;
}

#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
STD_ReturnType ADC_Start_Interrupt (const ADC_Config_t *_ADC_config, ADC_Channel_t _ADC_Channel){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _ADC_config){
        ret = E_NOT_OK;
    }
    else{
        /* This routine clears the interrupt flag for ADC module */
        ADC_INTERRUPT_FLAG_CLEAR();
        /*Configure input Channel*/
        ADC_Select_Channel (_ADC_config, _ADC_Channel);
        /* start A/D conversion*/
        ADC_Start_Conversion (_ADC_config);

        ret = E_OK;
    }
    return ret;
}
#endif



static inline void ADC_Select_Specific_Channel(ADC_Channel_t _ADC_Channel){
    switch(_ADC_Channel){
        case ADC_CHANNEL_AN0: setBit(TRISA, pin0);break;
        case ADC_CHANNEL_AN1: setBit(TRISA, pin1);break;
        case ADC_CHANNEL_AN2: setBit(TRISA, pin2);break;
        case ADC_CHANNEL_AN3: setBit(TRISA, pin3);break;
        case ADC_CHANNEL_AN4: setBit(TRISA, pin5);break;
        case ADC_CHANNEL_AN5: setBit(TRISE, pin0);break;
        case ADC_CHANNEL_AN6: setBit(TRISE, pin1);break;
        case ADC_CHANNEL_AN7: setBit(TRISE, pin2);break;
        case ADC_CHANNEL_AN8: setBit(TRISB, pin2);break;
        case ADC_CHANNEL_AN9: setBit(TRISB, pin3);break;
        case ADC_CHANNEL_AN10: setBit(TRISB, pin1);break;
        case ADC_CHANNEL_AN11: setBit(TRISB, pin4);break;
        case ADC_CHANNEL_AN12: setBit(TRISB, pin0);break;
        default: /*Nothing*/;
    }
}

static inline void ADC_Voltage_Reference_Control(const ADC_Config_t *_ADC_config){
    switch(_ADC_config->Voltage_Reference){
        case DISABLE_VOLTAGE_REFERENCE: ADC_DISABLE_VOLTAGE_REFERENCE();break;
        case ENABLE_VOLTAGE_REFERENCE:  ADC_ENABLE_VOLTAGE_REFERENCE();break;
        default: /*Do Nothing*/;
    }
}

static inline void ADC_Result_Format_Control(const ADC_Config_t *_ADC_config){
    switch(_ADC_config->Result_Format){
        case ADC_RESULT_FORMAT_LEFT: ADC_RESULT_LEFT_FORMAT();break;
        case ADC_RESULT_FORMAT_RIGHT:  ADC_RESULT_RIGHT_FORMAT();break;
        default: /*Do Nothing*/;
    }
}

#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void ADC_Interrupt_Configuration(const ADC_Config_t *_ADC_config){
        /* This routine disable the interrupt feature for ADC module */
        ADC_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for ADC module */
        ADC_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_ADC_config->Interrupt_Priority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for ADC module */
                ADC_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for ADC module */
                ADC_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure A/D Interrupt Handler*/
        ADC_InterruptHandler = _ADC_config->ADC_InterruptHandler;
        /* This routine enable the interrupt feature for ADC module */
        ADC_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure A/D Interrupt Handler*/
        ADC_InterruptHandler = _ADC_config->ADC_InterruptHandler;
        /* This routine enable the interrupt feature for ADC module */
        ADC_INTERRUPT_ENABLE();
#endif  
}
#endif

#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void ADC_ISR(void){
    /* This routine clears the interrupt flag for ADC module */
        ADC_INTERRUPT_FLAG_CLEAR();
        if(ADC_InterruptHandler) ADC_InterruptHandler();
}
#endif