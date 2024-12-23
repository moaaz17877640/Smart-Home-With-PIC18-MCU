/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_timer2.h"

#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*Timer2_InterruptHandler)(void) = NULL;
#endif

static inline void Timer2_Interrupt_Configuration(const Timer2_t *_timer2);

static uint8 timer2_preload = E_Zero_Init;


STD_ReturnType Timer2_Init        (const Timer2_t *_timer2){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer2){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer2*/
        TIMER2_MODULE_OFF();
        /*Configure timer1 pre-scaler*/
        TIMER2_PRESCALER_CONFIG(_timer2->Timer2_Prescaler);
        /*Configure timer1 post-scaler*/
        TIMER2_POSTSCALER_CONFIG(_timer2->Timer2_Postscaler);
        /*Configure pre-load value*/
        Timer2_Write_Value (_timer2, _timer2->Timer2_preloadValue);
        /*Store pre-load value*/
        timer2_preload = _timer2->Timer2_preloadValue;
        /*Enable timer1 Interrupt if needed*/
#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Timer2_Interrupt_Configuration(_timer2);
#endif
        /*Enable timer1*/
        TIMER2_MODULE_ON();

        ret = E_OK;
    }
    return ret;
}

STD_ReturnType Timer2_Deinit      (const Timer2_t *_timer2){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer2){
        ret = E_NOT_OK;
    }
    else{
        /*Disable timer1*/
        TIMER2_MODULE_OFF();
#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
       TIMER2_INTERRUPT_DISABLE();
#endif

        ret = E_OK;
    }
    return ret;
}

STD_ReturnType Timer2_Write_Value (const Timer2_t *_timer2, uint8 _value){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer2){
        ret = E_NOT_OK;
    }
    else{

        TMR2 = (uint8)(_value);
        
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType Timer2_Read_Value  (const Timer2_t *_timer2, uint8 *_value){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _timer2 || NULL == _value){
        ret = E_NOT_OK;
    }
    else{

        *_value = (uint8)(TMR2);

        ret = E_OK;
    }
    return ret;
    
}

#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void Timer2_Interrupt_Configuration(const Timer2_t *_timer2){
    /* This routine disable the interrupt feature for Timer2 module */
        TIMER2_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for Timer2 module */
        TIMER2_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_timer2->Timer2_InterruptPriority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for Timer2 module */
                TIMER2_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for Timer2 module */
                TIMER2_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure Timer2 Interrupt Handler*/
        Timer2_InterruptHandler = _timer2->TIMER2_InterruptHandler;
        /* This routine enable the interrupt feature for Timer2 module */
        TIMER2_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure Timer2 Interrupt Handler*/
        Timer2_InterruptHandler = _timer2->TIMER2_InterruptHandler;
        /* This routine enable the interrupt feature for Timer2 module */
        TIMER2_INTERRUPT_ENABLE();
#endif  
}
#endif

#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void TMR2_ISR(void){
    /* This routine clears the interrupt flag for Timer2 module */
        TIMER2_INTERRUPT_FLAG_CLEAR();
        
        TMR2 = (uint8)(timer2_preload);
        
        if(Timer2_InterruptHandler) Timer2_InterruptHandler();
}
#endif