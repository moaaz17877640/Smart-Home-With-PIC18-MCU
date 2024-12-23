/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "hal_timer1.h"

#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*Timer1_InterruptHandler)(void) = NULL;
#endif

static uint16 timer1_preload = E_Zero_Init;

static inline void Timer1_Set_Resolution(const Timer1_t *_timer1);
static inline void Timer1_Set_Mode(const Timer1_t *_timer1);
static inline void Timer1_Interrupt_Configuration(const Timer1_t *_timer1);




STD_ReturnType Timer1_Init        (const Timer1_t *_timer1){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer1*/
        TIMER1_MODULE_OFF();
        /*Select timer1 resolution*/
        Timer1_Set_Resolution(_timer1);
        /*Select timer1 mode*/
        Timer1_Set_Mode(_timer1);
        /*Configure timer1 pre-scaler*/
        TIMER1_PRESCALER_CONFIG(_timer1->Timer1_Prescaler_Value);
        /*Configure pre-load value*/
        Timer1_Write_Value (_timer1, _timer1->Timer1_preloadValue);
        /*Store pre-load value*/
        timer1_preload = _timer1->Timer1_preloadValue;
        /*Enable timer1 Interrupt if needed*/
#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Timer1_Interrupt_Configuration(_timer1);
#endif
        /*Enable timer1*/
        TIMER1_MODULE_ON();

        ret = E_OK;
    }
    return ret;
}


STD_ReturnType Timer1_Deinit      (const Timer1_t *_timer1){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer1*/
        TIMER1_MODULE_OFF();
#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       TIMER1_INTERRUPT_DISABLE();
#endif

        ret = E_OK;
    }
    return ret;
    
}

STD_ReturnType Timer1_Write_Value (const Timer1_t *_timer1, uint16 _value){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{

        TMR1H = (uint8)(_value >> 8);
        TMR1L = (uint8)(_value);
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType Timer1_Read_Value  (const Timer1_t *_timer1, uint16 *_value){
    STD_ReturnType ret = E_NOT_OK;
    uint8 l_timer1l = E_Zero_Init, l_timer1h = E_Zero_Init;
    if(NULL == _timer1 || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        l_timer1l = TMR1L;
        l_timer1h = TMR1H;
        *_value = (uint16)(l_timer1l + (l_timer1h << 8));

        ret = E_OK;
    }
    return ret;
    
}

static inline void Timer1_Set_Resolution(const Timer1_t *_timer1){
    switch(_timer1->Timer1_registerSize){
        case TIMER1_8BIT_TIMER_COUNTER:   TIMER1_Set_8BIT_TIMER_COUNTER();break;
        case TIMER1_16BIT_TIMER_COUNTER:  TIMER1_Set_16BIT_TIMER_COUNTER();break;
        default: /*Do nothing*/;
    }
}


static inline void Timer1_Set_Mode(const Timer1_t *_timer1){
    switch(_timer1->Timer1_mode){
        case TIMER1_TIMER_MODE:   TIMER1_Set_TIMER_MODE();break;
        case TIMER1_COUNTER_MODE:
            TIMER1_Set_COUNTER_MODE();
            switch(_timer1->Timer1_OSC_Counter){
                case TIMER1_OSCILLATOR_ENABLE:
                    TIMER1_OSCILLATOR_SET_ENABLE();break;
                case TIMER1_OSCILLATOR_DISABLE:
                    TIMER1_OSCILLATOR_SET_DISABLE();break;
                default: /*Do nothing*/;
            };
            switch(_timer1->Timer1_Sync_Counter){
                case TIMER1_SYNC_COUNTER_MODE:
                    TIMER1_SYNC_COUNTER();break;
                case TIMER1_ASYNC_COUNTER_MODE:
                    TIMER1_ASYNC_COUNTER();break;
                default: /*Do nothing*/;
            }break;
        default: /*Do nothing*/;
    }
}



#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void Timer1_Interrupt_Configuration(const Timer1_t *_timer1){
        /* This routine disable the interrupt feature for Timer1 module */
        TIMER1_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for Timer1 module */
        TIMER1_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_timer1->Timer1_InterruptPriority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for Timer1 module */
                TIMER1_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for Timer1 module */
                TIMER1_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure Timer1 Interrupt Handler*/
        Timer1_InterruptHandler = _timer1->TIMER1_InterruptHandler;
        /* This routine enable the interrupt feature for Timer1 module */
        TIMER1_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure Timer1 Interrupt Handler*/
        Timer1_InterruptHandler = _timer1->TIMER1_InterruptHandler;
        /* This routine enable the interrupt feature for Timer1 module */
        TIMER1_INTERRUPT_ENABLE();
#endif  
}
#endif

#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void TMR1_ISR(void){
    /* This routine clears the interrupt flag for Timer1 module */
        TIMER1_INTERRUPT_FLAG_CLEAR();
        
        TMR1H = (uint8)(timer1_preload >> 8);
        TMR1L = (uint8)(timer1_preload);
        
        if(Timer1_InterruptHandler) Timer1_InterruptHandler();
}
#endif