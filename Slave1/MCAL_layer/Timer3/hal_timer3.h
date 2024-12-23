/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* includes */
#include "./../mcal_std_types.h"
#include "./../GPIO/hal_gpio.h"
#include "./../Interrupts/mcal_internal_interrupts.h"

/* Macros declarations */

/* 16-Bit Read/Write Mode Enable */
#define TIMER3_8BIT_TIMER_COUNTER              0
#define TIMER3_16BIT_TIMER_COUNTER             1
/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE                      0
#define TIMER3_COUNTER_MODE                    1
/* Timer3 Input Clock Pre-scaler */
#define TIMER3_PRESCALE_VALUE_DIV_1            0
#define TIMER3_PRESCALE_VALUE_DIV_2            1
#define TIMER3_PRESCALE_VALUE_DIV_4            2
#define TIMER3_PRESCALE_VALUE_DIV_8            3
/* Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE      1
#define TIMER3_SYNC_COUNTER_MODE       0


/* MACROS Functions declarations */

/**
 *  @berief  Timer3 On/Off Control
 */
#define TIMER3_MODULE_OFF()                           (T3CONbits.TMR3ON = 0)
#define TIMER3_MODULE_ON()                            (T3CONbits.TMR3ON = 1)

/**
 *  @berief  Timer3 8-Bit/16-Bit Control
 */
#define TIMER3_Set_8BIT_TIMER_COUNTER()               (T3CONbits.RD16 = 0)
#define TIMER3_Set_16BIT_TIMER_COUNTER()              (T3CONbits.RD16 = 1)

/**
 *  @berief  Timer3 Clock Source Select
 */
#define TIMER3_Set_TIMER_MODE()                        (T3CONbits.TMR3CS = 0)
#define TIMER3_Set_COUNTER_MODE()                      (T3CONbits.TMR3CS = 1)

/**
 *  @berief  Timer3 Pre-scaler Assignment
 */
#define TIMER3_PRESCALER_CONFIG(__CONFIG__)            (T3CONbits.T3CKPS = __CONFIG__)

/**
 *  @berief  Timer3 External Clock Input Synchronization Select
 */
#define TIMER3_SYNC_COUNTER()                          (T3CONbits.T3SYNC = 0)
#define TIMER3_ASYNC_COUNTER()                         (T3CONbits.T3SYNC = 1)

/* Data types declarations */



/**
 *  @berief  Timer1 Configuration
 */
typedef struct {
#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER3_InterruptHandler)(void);
    Interrupt_Priority_Config Timer3_InterruptPriority;
#endif
    uint16 Timer3_preloadValue;
    uint8 Timer3_Prescaler_Value :2;
    uint8 Timer3_registerSize    :1 ; 
    uint8 Timer3_mode            :1 ; 
    uint8 Timer3_Sync_Counter    :1 ; 
    uint8 Timer3_Reserved        :3 ;   
}Timer3_t;


/* Functions declarations */

STD_ReturnType Timer3_Init        (const Timer3_t *_timer3);
STD_ReturnType Timer3_Deinit      (const Timer3_t *_timer3);
STD_ReturnType Timer3_Write_Value (const Timer3_t *_timer3, uint16 _value);
STD_ReturnType Timer3_Read_Value  (const Timer3_t *_timer3, uint16 *_value);


#endif	/* HAL_TIMER3_H */

