/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_timer3.h"

#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*Timer3_InterruptHandler)(void) = NULL;
#endif

static uint16 timer3_preload = E_Zero_Init;

static inline void Timer3_Set_Resolution(const Timer3_t *_timer3);
static inline void Timer3_Set_Mode(const Timer3_t *_timer3);
static inline void Timer3_Interrupt_Configuration(const Timer3_t *_timer3);


STD_ReturnType Timer3_Init        (const Timer3_t *_timer3){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer3*/
        TIMER3_MODULE_OFF();
        /*Select timer1 resolution*/
        Timer3_Set_Resolution(_timer3);
        /*Select timer3 mode*/
        Timer3_Set_Mode(_timer3);
        /*Configure timer3 pre-scaler*/
        TIMER3_PRESCALER_CONFIG(_timer3->Timer3_Prescaler_Value);
        /*Configure pre-load value*/
        Timer3_Write_Value (_timer3, _timer3->Timer3_preloadValue);
        /*Store pre-load value*/
        timer3_preload = _timer3->Timer3_preloadValue;
        /*Enable timer3 Interrupt if needed*/
#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Timer3_Interrupt_Configuration(_timer3);
#endif
        /*Enable timer3*/
        TIMER3_MODULE_ON();

        ret = E_OK;
    }
    return ret;
}

STD_ReturnType Timer3_Deinit      (const Timer3_t *_timer3){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer3*/
        TIMER3_MODULE_OFF();
#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       TIMER3_INTERRUPT_DISABLE();
#endif

        ret = E_OK;
    }
    return ret;
    
}

STD_ReturnType Timer3_Write_Value (const Timer3_t *_timer3, uint16 _value){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{

        TMR3H = (uint8)(_value >> 8);
        TMR3L = (uint8)(_value);
        
        ret = E_OK;
    }
    return ret;
    
}

STD_ReturnType Timer3_Read_Value  (const Timer3_t *_timer3, uint16 *_value){
    STD_ReturnType ret = E_NOT_OK;
    uint8 l_timer3l = E_Zero_Init, l_timer3h = E_Zero_Init;
    if(NULL == _timer3 || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        l_timer3l = TMR3L;
        l_timer3h = TMR3H;
        *_value = (uint16)(l_timer3l + (l_timer3h << 8));

        ret = E_OK;
    }
    return ret;
    
}

static inline void Timer3_Set_Resolution(const Timer3_t *_timer3){
    switch(_timer3->Timer3_registerSize){
        case TIMER3_8BIT_TIMER_COUNTER:   TIMER3_Set_8BIT_TIMER_COUNTER();break;
        case TIMER3_16BIT_TIMER_COUNTER:  TIMER3_Set_16BIT_TIMER_COUNTER();break;
        default: /*Do nothing*/;
    }
}


static inline void Timer3_Set_Mode(const Timer3_t *_timer3){
    switch(_timer3->Timer3_mode){
        case TIMER3_TIMER_MODE:   TIMER3_Set_TIMER_MODE();break;
        case TIMER3_COUNTER_MODE:
            TIMER3_Set_COUNTER_MODE();
            switch(_timer3->Timer3_Sync_Counter){
                case TIMER3_SYNC_COUNTER_MODE:
                    TIMER3_SYNC_COUNTER();break;
                case TIMER3_ASYNC_COUNTER_MODE:
                    TIMER3_ASYNC_COUNTER();break;
                default: /*Do nothing*/;
            }break;
        default: /*Do nothing*/;
    }
}



#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void Timer3_Interrupt_Configuration(const Timer3_t *_timer3){
        /* This routine disable the interrupt feature for Timer3 module */
        TIMER3_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for Timer3 module */
        TIMER3_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_timer3->Timer3_InterruptPriority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for Timer3 module */
                TIMER3_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for Timer3 module */
                TIMER3_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure Timer3 Interrupt Handler*/
        Timer3_InterruptHandler = _timer3->TIMER3_InterruptHandler;
        /* This routine enable the interrupt feature for Timer3 module */
        TIMER3_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure Timer3 Interrupt Handler*/
        Timer3_InterruptHandler = _timer3->TIMER3_InterruptHandler;
        /* This routine enable the interrupt feature for Timer3 module */
        TIMER3_INTERRUPT_ENABLE();
#endif  
}
#endif

#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void TMR3_ISR(void){
    /* This routine clears the interrupt flag for Timer3 module */
        TIMER3_INTERRUPT_FLAG_CLEAR();
        
        TMR3H = (uint8)(timer3_preload >> 8);
        TMR3L = (uint8)(timer3_preload);
        
        if(Timer3_InterruptHandler) Timer3_InterruptHandler();
}
#endif
