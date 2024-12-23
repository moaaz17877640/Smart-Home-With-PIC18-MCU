/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "hal_timer0.h"

#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*Timer0_InterruptHandler)(void) = NULL;
#endif

static uint16 timer0_preload = E_Zero_Init;

static inline void Timer0_Set_Resolution(const Timer0_t *_timer0);
static inline void Timer0_Set_Mode(const Timer0_t *_timer0);
static inline void Timer0_Prescaler_Config(const Timer0_t *_timer0);
static inline void Timer0_Interrupt_Configuration(const Timer0_t *_timer0);



STD_ReturnType Timer0_Init        (const Timer0_t *_timer0){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer0*/
        TIMER0_MODULE_OFF();
        /*Select timer0 resolution*/
        Timer0_Set_Resolution(_timer0);
        /*Select timer0 mode*/
        Timer0_Set_Mode(_timer0);
        /*Configure timer0 prescaler*/
        Timer0_Prescaler_Config(_timer0);
        /*Configure preload value*/
        Timer0_Write_Value (_timer0, _timer0->Timer0_preloadValue);
        /*Store preload value*/
        timer0_preload = _timer0->Timer0_preloadValue;
        /*Enable timer0 Interrupt if needed*/
#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Timer0_Interrupt_Configuration(_timer0);
#endif
        /*Enable timer0*/
        TIMER0_MODULE_ON();

        ret = E_OK;
    }
    return ret;
}


STD_ReturnType Timer0_Deinit      (const Timer0_t *_timer0){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer0*/
        TIMER0_MODULE_OFF();
#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       TIMER0_INTERRUPT_DISABLE();
#endif

        ret = E_OK;
    }
    return ret;
    
}

STD_ReturnType Timer0_Write_Value (const Timer0_t *_timer0, uint16 _value){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        if(TIMER0_8BIT_TIMER_COUNTER == _timer0->Timer0_registerSize){
            TMR0L = (uint8)(_value);
        }
        else if(TIMER0_16BIT_TIMER_COUNTER == _timer0->Timer0_registerSize){
            TMR0H = (uint8)(_value >> 8);
            TMR0L = (uint8)(_value);
        }
        else{
            /*Do nothing*/
        }
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType Timer0_Read_Value  (const Timer0_t *_timer0, uint16 *_value){
    STD_ReturnType ret = E_NOT_OK;
    uint8 l_timer0l = E_Zero_Init, l_timer0h = E_Zero_Init;
    if(NULL == _timer0 || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        if(TIMER0_8BIT_TIMER_COUNTER == _timer0->Timer0_registerSize){
            l_timer0l = TMR0L;
            *_value = (uint8)l_timer0l;
        }
        else if(TIMER0_16BIT_TIMER_COUNTER == _timer0->Timer0_registerSize){
            l_timer0l = TMR0L;
            l_timer0h = TMR0H;
            *_value = (uint16)(l_timer0l + (l_timer0h << 8));
        }
        else{
            /*Do nothing*/
        }
        
        
        ret = E_OK;
    }
    return ret;
    
}

static inline void Timer0_Set_Resolution(const Timer0_t *_timer0){
    switch(_timer0->Timer0_registerSize){
        case TIMER0_8BIT_TIMER_COUNTER:   TIMER0_Set_8BIT_TIMER_COUNTER();break;
        case TIMER0_16BIT_TIMER_COUNTER:  TIMER0_Set_16BIT_TIMER_COUNTER();break;
        default: /*Do nothing*/;
    }
}


static inline void Timer0_Set_Mode(const Timer0_t *_timer0){
    switch(_timer0->Timer0_mode){
        case TIMER0_TIMER_MODE:   TIMER0_Set_TIMER_MODE();break;
        case TIMER0_COUNTER_MODE:
            TIMER0_Set_COUNTER_MODE();
            switch(_timer0->Timer0_counterEdge){
                case TIMER0_COUNTER_HIGH_TO_LOW_INC:
                    TIMER0_COUNTER_Set_HIGH_TO_LOW_INC();break;
                case TIMER0_COUNTER_LOW_TO_HIGH_INC:
                    TIMER0_COUNTER_Set_LOW_TO_HIGH_INC();break;
                default: /*Do nothing*/;
            }break;
        default: /*Do nothing*/;
    }
}

static inline void Timer0_Prescaler_Config(const Timer0_t *_timer0){

    switch(_timer0->Timer0_prescalerConfig){
        case TIMER0_PRESCALER_IS_ASSIGNED:   
            TIMER0_Set_PRESCALER_ASSIGNED();
            T0CONbits.T0PS = _timer0->Timer0_Prescaler_Value;
            break;
        case TIMER0_PRESCALER_IS_NOT_ASSIGNED: TIMER0_Set_PRESCALER_NOT_ASSIGNED();break;
        default: /*Do nothing*/;
    }

}


#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void Timer0_Interrupt_Configuration(const Timer0_t *_timer0){
        /* This routine disable the interrupt feature for Timer0 module */
        TIMER0_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for Timer0 module */
        TIMER0_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_timer0->Timer0_InterruptPriority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for Timer0 module */
                TIMER0_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for Timer0 module */
                TIMER0_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure Timer0 Interrupt Handler*/
        Timer0_InterruptHandler = _timer0->TIMER0_InterruptHandler;
        /* This routine enable the interrupt feature for Timer0 module */
        TIMER0_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure Timer0 Interrupt Handler*/
        Timer0_InterruptHandler = _timer0->TIMER0_InterruptHandler;
        /* This routine enable the interrupt feature for Timer0 module */
        TIMER0_INTERRUPT_ENABLE();
#endif  
}
#endif

#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void TMR0_ISR(void){
    /* This routine clears the interrupt flag for Timer0 module */
        TIMER0_INTERRUPT_FLAG_CLEAR();
        
        TMR0H = (timer0_preload) >> 8;
        TMR0L = (uint8)(timer0_preload);
        
        if(Timer0_InterruptHandler) Timer0_InterruptHandler();
}
#endif