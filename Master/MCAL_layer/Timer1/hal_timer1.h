/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* includes */
#include "./../mcal_std_types.h"
#include "./../GPIO/hal_gpio.h"
#include "./../Interrupts/mcal_internal_interrupts.h"


/* Macros declarations */

/* 16-Bit Read/Write Mode Enable */
#define TIMER1_8BIT_TIMER_COUNTER              0
#define TIMER1_16BIT_TIMER_COUNTER             1
/* Timer1 Clock Source (Timer or Counter) */
#define TIMER1_TIMER_MODE                      0
#define TIMER1_COUNTER_MODE                    1
/* Timer1 Input Clock Pre-scaler */
#define TIMER1_PRESCALE_VALUE_DIV_1            0
#define TIMER1_PRESCALE_VALUE_DIV_2            1
#define TIMER1_PRESCALE_VALUE_DIV_4            2
#define TIMER1_PRESCALE_VALUE_DIV_8            3
/* Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE      1
#define TIMER1_SYNC_COUNTER_MODE       0
/* Timer1 Oscillator */
#define TIMER1_OSCILLATOR_ENABLE       1
#define TIMER1_OSCILLATOR_DISABLE      0



/* MACROS Functions declarations */

/**
 *  @berief  Timer1 On/Off Control
 */
#define TIMER1_MODULE_OFF()                           (T1CONbits.TMR1ON = 0)
#define TIMER1_MODULE_ON()                            (T1CONbits.TMR1ON = 1)

/**
 *  @berief  Timer1 8-Bit/16-Bit Control
 */
#define TIMER1_Set_8BIT_TIMER_COUNTER()               (T1CONbits.RD16 = 0)
#define TIMER1_Set_16BIT_TIMER_COUNTER()              (T1CONbits.RD16 = 1)

/**
 *  @berief  Timer1 Clock Source Select
 */
#define TIMER1_Set_TIMER_MODE()                        (T1CONbits.TMR1CS = 0)
#define TIMER1_Set_COUNTER_MODE()                      (T1CONbits.TMR1CS = 1)

/**
 *  @berief  Timer1 Prescaler Assignment
 */
#define TIMER1_PRESCALER_CONFIG(__CONFIG__)            (T1CONbits.T1CKPS = __CONFIG__)

/**
 *  @berief  Timer1 Oscillator Enable
 */
#define TIMER1_OSCILLATOR_SET_ENABLE()                     (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_SET_DISABLE()                    (T1CONbits.T1OSCEN = 0)

/**
 *  @berief  Timer1 External Clock Input Synchronization Select
 */
#define TIMER1_SYNC_COUNTER()                          (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNC_COUNTER()                         (T1CONbits.T1SYNC = 1)

/**
 *  @berief  Timer1 System Clock Status
 *  @note 1 = Device clock is derived from Timer1 oscillator
          0 = Device clock is derived from another source
 */
#define TIMER1_CLOCK_STATUS()                          (T1CONbits.T1RUN)

/* Data types declarations */



/**
 *  @berief  Timer1 Configuration
 */
typedef struct {
#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER1_InterruptHandler)(void);
    Interrupt_Priority_Config Timer1_InterruptPriority;
#endif
    uint16 Timer1_preloadValue;
    uint8 Timer1_Prescaler_Value :2;
    uint8 Timer1_registerSize    :1 ; 
    uint8 Timer1_mode            :1 ; 
    uint8 Timer1_Sync_Counter    :1 ; 
    uint8 Timer1_OSC_Counter     :1 ;
    uint8 Timer1_Reserved        :2 ;   
}Timer1_t;


/* Functions declarations */

STD_ReturnType Timer1_Init        (const Timer1_t *_timer1);
STD_ReturnType Timer1_Deinit      (const Timer1_t *_timer1);
STD_ReturnType Timer1_Write_Value (const Timer1_t *_timer1, uint16 _value);
STD_ReturnType Timer1_Read_Value  (const Timer1_t *_timer1, uint16 *_value);

#endif	/* HAL_TIMER1_H */

