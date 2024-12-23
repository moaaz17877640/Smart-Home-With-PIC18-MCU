/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* includes */
#include "./../mcal_std_types.h"
#include "./../GPIO/hal_gpio.h"
#include "./../Interrupts/mcal_internal_interrupts.h"


/* Macros declarations */

/* MACROS Functions declarations */

/**
 *  @berief  Timer2 On/Off Control
 */
#define TIMER2_MODULE_OFF()                             (T2CONbits.TMR2ON = 0)
#define TIMER2_MODULE_ON()                              (T2CONbits.TMR2ON = 1)

/**
 *  @berief  Timer2 Prescaler Assignment
 */
#define TIMER2_PRESCALER_CONFIG(__CONFIG__)             (T2CONbits.T2CKPS = __CONFIG__)

/**
 *  @berief  Timer2 Postscaler Assignment
 */
#define TIMER2_POSTSCALER_CONFIG(__CONFIG__)            (T2CONbits.T2OUTPS = __CONFIG__)



/* Data types declarations */

/**
 *  @berief  Timer2 Input Clock Post-scaler
 */
typedef enum {
    TIMER2_POSTSCALER_VALUE_1 = 0,
    TIMER2_POSTSCALER_VALUE_2,
    TIMER2_POSTSCALER_VALUE_3,
    TIMER2_POSTSCALER_VALUE_4,
    TIMER2_POSTSCALER_VALUE_5,
    TIMER2_POSTSCALER_VALUE_6,
    TIMER2_POSTSCALER_VALUE_7,
    TIMER2_POSTSCALER_VALUE_8,
    TIMER2_POSTSCALER_VALUE_9,
    TIMER2_POSTSCALER_VALUE_10,
    TIMER2_POSTSCALER_VALUE_11,
    TIMER2_POSTSCALER_VALUE_12,
    TIMER2_POSTSCALER_VALUE_13,
    TIMER2_POSTSCALER_VALUE_14,
    TIMER2_POSTSCALER_VALUE_15,
    TIMER2_POSTSCALER_VALUE_16
}Timer2_Postscaler_t;

/**
 *  @berief  Timer2 Input Clock Pre-scaler
 */
typedef enum {
    TIMER2_PRESCALER_VALUE_1 = 0,
    TIMER2_PRESCALER_VALUE_4,
    TIMER2_PRESCALER_VALUE_16,
}Timer2_Prescaler_t;


/**
 *  @berief  Timer2 Configurations
 */
typedef struct {
#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER2_InterruptHandler)(void);
    Interrupt_Priority_Config Timer2_InterruptPriority;
#endif
    uint16 Timer2_preloadValue;
    Timer2_Postscaler_t   Timer2_Postscaler;
    Timer2_Prescaler_t     Timer2_Prescaler;
}Timer2_t;


/* Functions declarations */

STD_ReturnType Timer2_Init        (const Timer2_t *_timer2);
STD_ReturnType Timer2_Deinit      (const Timer2_t *_timer2);
STD_ReturnType Timer2_Write_Value (const Timer2_t *_timer2, uint8 _value);
STD_ReturnType Timer2_Read_Value  (const Timer2_t *_timer2, uint8 *_value);

#endif	/* HAL_TIMER2_H */

