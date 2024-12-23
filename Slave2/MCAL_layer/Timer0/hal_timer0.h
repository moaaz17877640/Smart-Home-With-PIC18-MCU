/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* includes */
#include "./../mcal_std_types.h"
#include "./../GPIO/hal_gpio.h"
#include "./../Interrupts/mcal_internal_interrupts.h"


/* Macros declarations */

#define TIMER0_8BIT_TIMER_COUNTER              1
#define TIMER0_16BIT_TIMER_COUNTER             0

#define TIMER0_TIMER_MODE                      0
#define TIMER0_COUNTER_MODE                    1

#define TIMER0_COUNTER_HIGH_TO_LOW_INC         1
#define TIMER0_COUNTER_LOW_TO_HIGH_INC         0

#define TIMER0_PRESCALER_IS_ASSIGNED           0
#define TIMER0_PRESCALER_IS_NOT_ASSIGNED       1

/* MACROS Functions declarations */

/**
 *  @berief  Timer0 On/Off Control
 */
#define TIMER0_MODULE_OFF()                           (T0CONbits.TMR0ON = 0)
#define TIMER0_MODULE_ON()                            (T0CONbits.TMR0ON = 1)

/**
 *  @berief  Timer0 8-Bit/16-Bit Control
 */
#define TIMER0_Set_8BIT_TIMER_COUNTER()               (T0CONbits.T08BIT = 1)
#define TIMER0_Set_16BIT_TIMER_COUNTER()              (T0CONbits.T08BIT = 0)

/**
 *  @berief  Timer0 Clock Source Select
 */
#define TIMER0_Set_TIMER_MODE()                        (T0CONbits.T0CS = 0)
#define TIMER0_Set_COUNTER_MODE()                      (T0CONbits.T0CS = 1)

/**
 *  @berief  Timer0 Source Edge Select
 */
#define TIMER0_COUNTER_Set_HIGH_TO_LOW_INC()           (T0CONbits.T0SE = 1)
#define TIMER0_COUNTER_Set_LOW_TO_HIGH_INC()           (T0CONbits.T0SE = 0)

/**
 *  @berief  Timer0 Prescaler Assignment
 */
#define TIMER0_Set_PRESCALER_ASSIGNED()             (T0CONbits.PSA = 0)
#define TIMER0_Set_PRESCALER_NOT_ASSIGNED()         (T0CONbits.PSA = 1)

/* Data types declarations */


/**
 *  @berief  Timer0 Prescaler Select
 */
typedef enum {
    TIMER0_PRESCALER_VALUE_DIV_2 = 0,
    TIMER0_PRESCALER_VALUE_DIV_4,
    TIMER0_PRESCALER_VALUE_DIV_8,
    TIMER0_PRESCALER_VALUE_DIV_16,
    TIMER0_PRESCALER_VALUE_DIV_32,
    TIMER0_PRESCALER_VALUE_DIV_64,
    TIMER0_PRESCALER_VALUE_DIV_128,
    TIMER0_PRESCALER_VALUE_DIV_256
}Timer0_Prescaler_Value_t;

/**
 *  @berief  Timer0 Configuration
 */
typedef struct {
#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER0_InterruptHandler)(void);
    Interrupt_Priority_Config Timer0_InterruptPriority;
#endif
    Timer0_Prescaler_Value_t     Timer0_Prescaler_Value;
    uint16 Timer0_preloadValue;
    uint8 Timer0_registerSize    :1 ; 
    uint8 Timer0_mode            :1 ; 
    uint8 Timer0_counterEdge     :1 ; 
    uint8 Timer0_prescalerConfig :1 ;
    uint8 Timer0_Reserved        :4 ;   
}Timer0_t;


/* Functions declarations */

STD_ReturnType Timer0_Init        (const Timer0_t *_timer0);
STD_ReturnType Timer0_Deinit      (const Timer0_t *_timer0);
STD_ReturnType Timer0_Write_Value (const Timer0_t *_timer0, uint16 _value);
STD_ReturnType Timer0_Read_Value  (const Timer0_t *_timer0, uint16 *_value);


#endif	/* HAL_TIMER0_H */

