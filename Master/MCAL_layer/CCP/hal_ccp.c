/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_ccp.h"

#if (INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*CCP1_InterrptHandle)(void);
#endif
#if (INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*CCP2_InterrptHandle)(void);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
static void CCPx_Capture_mode_config(CCPx_t *_CCPx);
#endif
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
static void CCPx_Compare_mode_config(CCPx_t *_CCPx);
#endif
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
static void CCPx_PWM_mode_config(CCPx_t *_CCPx);
#endif

#if (INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) || (INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
static void CCPx_Interrupt_Configuration(CCPx_t *_CCPx);
#endif

static void CCPx_Timer_Config(CCPx_t *_CCPx);



STD_ReturnType CCPx_Init (CCPx_t *_CCPx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        /* CCP Module Disable */
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCP1_SET_MODE(CCPx_MODULE_DISABLE_SELECTED);
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCP2_SET_MODE(CCPx_MODULE_DISABLE_SELECTED);
        }
        else{
            /* Do nothing */
        }
        
        /* CCP module mode configuration */
        if(CCPx_CFG_CAPTURE_MODE == _CCPx->CCPx_MODE){
#if (CCP_CFG_CAPTURE_MODE_SELECTED == CCP1_CFG_MODE_SELECTED) || (CCP_CFG_CAPTURE_MODE_SELECTED == CCP2_CFG_MODE_SELECTED)
    CCPx_Capture_mode_config(_CCPx);
#endif
        }
        else if(CCPx_CFG_COMPARE_MODE == _CCPx->CCPx_MODE){
#if (CCP_CFG_COMPARE_MODE_SELECTED == CCP1_CFG_MODE_SELECTED) || (CCP_CFG_COMPARE_MODE_SELECTED == CCP2_CFG_MODE_SELECTED)
     CCPx_Compare_mode_config(_CCPx);
#endif
        }
        else if(CCPx_CFG_PWM_MODE == _CCPx->CCPx_MODE){
#if (CCP_CFG_PWM_MODE_SELECTED == CCP1_CFG_MODE_SELECTED) || (CCP_CFG_PWM_MODE_SELECTED == CCP2_CFG_MODE_SELECTED)
     CCPx_PWM_mode_config(_CCPx);
#endif
        }
        else{
            /*Do nothing*/
        }
        
    /* CCP module pin configuration */
    ret = gpio_pin_initialize(&(_CCPx->CCPx_PIN));  
    /* CCP module interrupt configuration */
#if (INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) || (INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    CCPx_Interrupt_Configuration(_CCPx);
#endif
          
        
    ret = E_OK;
    }
    return ret;
    
}
STD_ReturnType CCPx_Deinit  (CCPx_t *_CCPx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCP1_SET_MODE(CCPx_MODULE_DISABLE_SELECTED);
#if (INTERRUPT_FEATURE_ENABLE == INTERRUPT_CCP1_FEATURE_ENABLE)
            CCP1_INTERRUPT_DISABLE();
#endif
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCP2_SET_MODE(CCPx_MODULE_DISABLE_SELECTED);
#if (INTERRUPT_FEATURE_ENABLE == INTERRUPT_CCP2_FEATURE_ENABLE)
            CCP2_INTERRUPT_DISABLE();
#endif
        }
        else{
            /*Do nothing*/
        }
        ret = E_OK;
    }
    return ret;
    
}
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
STD_ReturnType CCPx_CaptureMode_IsData_Ready  (const CCPx_t *_CCPx, uint8 *isData_ready){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            if(CCPx_CAPTURE_READY == PIR1bits.CCP1IF){
                *isData_ready = CCPx_CAPTURE_READY;
                /* This routine clears the interrupt flag for CCP1 module */
                CCP1_INTERRUPT_FLAG_CLEAR();
            }
            else{
                *isData_ready = CCPx_CAPTURE_NOT_READY;
            }
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            if(CCPx_CAPTURE_READY == PIR2bits.CCP2IF){
                *isData_ready = CCPx_CAPTURE_READY;
                /* This routine clears the interrupt flag for CCP2 module */
                CCP2_INTERRUPT_FLAG_CLEAR();
            }
            else{
                *isData_ready = CCPx_CAPTURE_NOT_READY;
            }
        }
        else{
            /*Do nothing*/
        }
        
        ret = E_OK;
    }
    return ret;
    
}
STD_ReturnType CCPx_CaptureMode_GetData       (const CCPx_t *_CCPx, uint16 *_Data){
    CCPx_reg_t CCPx_reg;
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCPx_reg.CCPR_LOW = CCPR1L;
            CCPx_reg.CCPR_HIGH = CCPR1H;
            *_Data = CCPx_reg.CCPR_16BIT;
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCPx_reg.CCPR_LOW = CCPR2L;
            CCPx_reg.CCPR_HIGH = CCPR2H;
            *_Data = CCPx_reg.CCPR_16BIT;
        }
        else{
            /*Do nothing*/
        }

        ret = E_OK;
    }
            
    return ret;
    
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
STD_ReturnType CCPx_CompareMode_IsComplete      (const CCPx_t *_CCPx, uint8 *IsComplete){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            if(CCPx_COMPARE_READY == PIR1bits.CCP1IF){
                *IsComplete = CCPx_COMPARE_READY;
                /* This routine clears the interrupt flag for CCP1 module */
                CCP1_INTERRUPT_FLAG_CLEAR();
            }
            else{
                *IsComplete = CCPx_COMPARE_NOT_READY;
            }
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            if(CCPx_COMPARE_READY == PIR2bits.CCP2IF){
                *IsComplete = CCPx_COMPARE_READY;
                /* This routine clears the interrupt flag for CCP2 module */
                CCP2_INTERRUPT_FLAG_CLEAR();
            }
            else{
                *IsComplete = CCPx_COMPARE_NOT_READY;
            }
        }
        else{
            /*Do nothing*/
        }
        
        ret = E_OK;
    }
    return ret;
    
}
STD_ReturnType CCPx_CompareMode_WriteData       (const CCPx_t *_CCPx, uint16 _Data){
    CCPx_reg_t CCPx_reg;
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        CCPx_reg.CCPR_16BIT = _Data;
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCPR1L = CCPx_reg.CCPR_LOW;
            CCPR1H = CCPx_reg.CCPR_HIGH;   
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCPR2L = CCPx_reg.CCPR_LOW;
            CCPR2H = CCPx_reg.CCPR_HIGH; 
        }
        else{
            /*Do nothing*/
        } 
        ret = E_OK;
    }
    return ret;
    
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
STD_ReturnType CCPx_PWM_Mode_setDutyCycle       (const CCPx_t *_CCPx, uint8 _Duty){
    STD_ReturnType ret = E_NOT_OK;
    uint16 l_tempVar = 0; 
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        l_tempVar = (uint16)(4.0 * (PR2 + 1) * (_Duty / 100.0));
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCP1CONbits.DC1B = (uint8)(l_tempVar & 0x03);
            CCPR1L = (uint8)(l_tempVar >> 2);
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCP2CONbits.DC2B = (uint8)(l_tempVar & 0x03);
            CCPR2L = (uint8)(l_tempVar >> 2);
        }
        else{
            /*Do nothing*/
        }
        
        ret = E_OK;
    }
    return ret;
    
}
STD_ReturnType CCPx_PWM_Mode_Start       (const CCPx_t *_CCPx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCP1CONbits.CCP1M = CCPx_MODULE_PWM_MODE_SELECTED;
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCP2CONbits.CCP2M = CCPx_MODULE_PWM_MODE_SELECTED;
        }
        else{
            /*Do nothing*/
        }
        
        ret = E_OK;
    }
    return ret;
}
STD_ReturnType CCPx_PWM_Mode_Stop       (const CCPx_t *_CCPx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _CCPx){
        ret = E_NOT_OK;
    }
    else{
        
        if(CCP1_SELECTED == _CCPx->CCPx_Instance){
            CCP1CONbits.CCP1M = CCPx_MODULE_DISABLE_SELECTED;
        }
        else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
            CCP2CONbits.CCP2M = CCPx_MODULE_DISABLE_SELECTED;
        }
        else{
            /*Do nothing*/
        }
        
        ret = E_OK;
    }
    return ret;
}
#endif


#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
static void CCPx_Capture_mode_config(CCPx_t *_CCPx){
    if(CCP1_SELECTED == _CCPx->CCPx_Instance){
        switch(_CCPx->CCPx_Variant){
            case CCPx_MODULE_CAPTURE_MODE_EVERY_FALLING_EDGE:
                CCP1_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_FALLING_EDGE);break;
            case CCPx_MODULE_CAPTURE_MODE_EVERY_RISING_EDGE:
                CCP1_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_RISING_EDGE);break;
            case CCPx_MODULE_CAPTURE_MODE_EVERY_4TH_RISING_EDGE:
                CCP1_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_4TH_RISING_EDGE);break;
            case CCPx_MODULE_CAPTURE_MODE_EVERY_16TH_RISING_EDGE:
                CCP1_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_16TH_RISING_EDGE);break;
            default:
                /*Do nothing*/;        
        }
    }
    else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
        switch(_CCPx->CCPx_Variant){
            case CCPx_MODULE_CAPTURE_MODE_EVERY_FALLING_EDGE:
                CCP2_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_FALLING_EDGE);break;
            case CCPx_MODULE_CAPTURE_MODE_EVERY_RISING_EDGE:
                CCP2_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_RISING_EDGE);break;
            case CCPx_MODULE_CAPTURE_MODE_EVERY_4TH_RISING_EDGE:
                CCP2_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_4TH_RISING_EDGE);break;
            case CCPx_MODULE_CAPTURE_MODE_EVERY_16TH_RISING_EDGE:
                CCP2_SET_MODE(CCPx_MODULE_CAPTURE_MODE_EVERY_16TH_RISING_EDGE);break;
            default:
                /*Do nothing*/;        
        }
    }
    else{
        /*Do nothing*/
    }
    
    /*CCPx timer configurations*/
    CCPx_Timer_Config(_CCPx);
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
static void CCPx_Compare_mode_config(CCPx_t *_CCPx){
    if(CCP1_SELECTED == _CCPx->CCPx_Instance){
        switch(_CCPx->CCPx_Variant){
            case CCPx_MODULE_COMPARE_MODE_TOGGLE_OUTPUT_ON_MATCH_SELECTED:
                CCP1_SET_MODE(CCPx_MODULE_COMPARE_MODE_TOGGLE_OUTPUT_ON_MATCH_SELECTED);break;
            case CCPx_MODULE_COMPARE_SET_PIN_LOW:
                CCP1_SET_MODE(CCPx_MODULE_COMPARE_SET_PIN_LOW);break;
            case CCPx_MODULE_COMPARE_SET_PIN_HIGH:
                CCP1_SET_MODE(CCPx_MODULE_COMPARE_SET_PIN_HIGH);break;
            case CCPx_MODULE_COMPARE_GEN_SW_INTERRUPT:
                CCP1_SET_MODE(CCPx_MODULE_COMPARE_GEN_SW_INTERRUPT);break;
            case CCPx_MODULE_COMPARE_TRIGGER_SPECIAL_EVENT:
                CCP1_SET_MODE(CCPx_MODULE_COMPARE_TRIGGER_SPECIAL_EVENT);break;
            default:
                /*Do nothing*/;        
        }
    }
    else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
        switch(_CCPx->CCPx_Variant){
            case CCPx_MODULE_COMPARE_MODE_TOGGLE_OUTPUT_ON_MATCH_SELECTED:
                CCP2_SET_MODE(CCPx_MODULE_COMPARE_MODE_TOGGLE_OUTPUT_ON_MATCH_SELECTED);break;
            case CCPx_MODULE_COMPARE_SET_PIN_LOW:
                CCP2_SET_MODE(CCPx_MODULE_COMPARE_SET_PIN_LOW);break;
            case CCPx_MODULE_COMPARE_SET_PIN_HIGH:
                CCP2_SET_MODE(CCPx_MODULE_COMPARE_SET_PIN_HIGH);break;
            case CCPx_MODULE_COMPARE_GEN_SW_INTERRUPT:
                CCP2_SET_MODE(CCPx_MODULE_COMPARE_GEN_SW_INTERRUPT);break;
            case CCPx_MODULE_COMPARE_TRIGGER_SPECIAL_EVENT:
                CCP2_SET_MODE(CCPx_MODULE_COMPARE_TRIGGER_SPECIAL_EVENT);break;
            default:
                /*Do nothing*/;        
        }
    }
    else{
        /*Do nothing*/
    }
    
    /*CCPx timer configurations*/
    CCPx_Timer_Config(_CCPx);
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
static void CCPx_PWM_mode_config(CCPx_t *_CCPx){
    
    PR2 = (uint8)( ((_XTAL_FREQ) / ((_CCPx->PWM_FREQ) * (4.0) * ( (_CCPx->CCPx_Timer2_Postscaler) * (_CCPx->CCPx_Timer2_Prescaler) ) ) ) - 1 );
    
    if(CCP1_SELECTED == _CCPx->CCPx_Instance){
        CCP1_SET_MODE(CCPx_MODULE_PWM_MODE_SELECTED);
    }
    else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
        CCP2_SET_MODE(CCPx_MODULE_PWM_MODE_SELECTED);
    }
    else{
        /*Do nothing*/
    }
}
#endif


static void CCPx_Timer_Config(CCPx_t *_CCPx){
    switch(_CCPx->CCPx_CAPTURE_COMPARE_TIMER){
        case CCP1_CCP2_TIMER1:
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;break;
        case CCP1_TIMER1_CCP2_TIMER3:
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;break;
        case CCP1_CCP2_TIMER3:
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 1;break;
        default:
            /*Do nothing*/;
    }
}


#if (INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) || (INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
static void CCPx_Interrupt_Configuration(CCPx_t *_CCPx){
    if(CCP1_SELECTED == _CCPx->CCPx_Instance){
        /* This routine disable the interrupt feature for CCP1 module */
        CCP1_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for CCP1 module */
        CCP1_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_CCPx->CCP1_Interrupt_Priority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for CCP1 module */
                CCP1_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for CCP1 module */
                CCP1_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure CCP1 Interrupt Handler*/
        CCP1_InterrptHandle = _CCPx->CCP1_InterruptHandler;
         /* This routine clears the interrupt flag for CCP1 module */
        CCP1_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure CCP1 Interrupt Handler*/
        CCP1_InterrptHandle = _CCPx->CCP1_InterruptHandler;
        /* This routine enable the interrupt feature for CCP1 module */
        CCP1_INTERRUPT_ENABLE();
#endif  
    }
    else if(CCP2_SELECTED == _CCPx->CCPx_Instance){
        /* This routine disable the interrupt feature for CCP2 module */
        CCP2_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for CCP2 module */
        CCP2_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_CCPx->CCP2_Interrupt_Priority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for CCP2 module */
                CCP2_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for CCP2 module */
                CCP2_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure CCP2 Interrupt Handler*/
        CCP2_InterrptHandle = _CCPx->CCP2_InterruptHandler;
        /* This routine enable the interrupt feature for CCP2 module */
        CCP2_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure CCP2 Interrupt Handler*/
        CCP2_InterrptHandle = _CCPx->CCP2_InterruptHandler;
        /* This routine enable the interrupt feature for CCP2 module */
        CCP2_INTERRUPT_ENABLE();
#endif  
    }
    else{
            /*Do nothing*/
        }
}
#endif


    
#if (INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) || (INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
void CCP1_ISR(void){
    /* This routine clears the interrupt flag for CCP1 module */
    CCP1_INTERRUPT_FLAG_CLEAR();

    if(CCP1_InterrptHandle) CCP1_InterrptHandle();
}

void CCP2_ISR(void){
    /* This routine clears the interrupt flag for CCP2 module */
    CCP2_INTERRUPT_FLAG_CLEAR();

    if(CCP2_InterrptHandle) CCP2_InterrptHandle();
}

#endif