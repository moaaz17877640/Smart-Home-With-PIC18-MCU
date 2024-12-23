/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/* includes */
#include "hal_ccp_cfg.h"
#include "../mcal_std_types.h"
#include "./../Interrupts/mcal_internal_interrupts.h"
#include "./../GPIO/hal_gpio.h"


/* Macros declarations */

/* CCPx Module Mode Select */
#define CCPx_MODULE_DISABLE_SELECTED                              (uint8)0x00
#define CCPx_MODULE_COMPARE_MODE_TOGGLE_OUTPUT_ON_MATCH_SELECTED  (uint8)0x02
#define CCPx_MODULE_CAPTURE_MODE_EVERY_FALLING_EDGE               (uint8)0x04
#define CCPx_MODULE_CAPTURE_MODE_EVERY_RISING_EDGE                (uint8)0x05
#define CCPx_MODULE_CAPTURE_MODE_EVERY_4TH_RISING_EDGE            (uint8)0x06
#define CCPx_MODULE_CAPTURE_MODE_EVERY_16TH_RISING_EDGE           (uint8)0x07
#define CCPx_MODULE_COMPARE_SET_PIN_LOW                           (uint8)0x08
#define CCPx_MODULE_COMPARE_SET_PIN_HIGH                          (uint8)0x09
#define CCPx_MODULE_COMPARE_GEN_SW_INTERRUPT                      (uint8)0x0A
#define CCPx_MODULE_COMPARE_TRIGGER_SPECIAL_EVENT                 (uint8)0x0B
#define CCPx_MODULE_PWM_MODE_SELECTED                             (uint8)0x0C

/* CCPx Capture Mode State  */
#define CCPx_COMPARE_NOT_READY                                    0x00
#define CCPx_COMPARE_READY                                        0x01

/* CCPx Compare Mode State  */
#define CCPx_CAPTURE_NOT_READY                                    0x00
#define CCPx_CAPTURE_READY                                        0x01

/* Timer3 and Timer1 to CCPx Enable */
#define CCP1_CCP2_TIMER1                                          0x00
#define CCP1_TIMER1_CCP2_TIMER3                                   0x01
#define CCP1_CCP2_TIMER3                                          0x02

/* MACROS Functions declarations */

/* CCPx Module Mode Select */
#define CCP1_SET_MODE(__CONFIG)                                  (CCP1CONbits.CCP1M = __CONFIG)
#define CCP2_SET_MODE(__CONFIG)                                  (CCP2CONbits.CCP2M = __CONFIG)


/* Data types declarations */

/**
 *  @berief  Timer2 Input Clock Post-scaler for CCP module
 */
typedef enum {
    CCPx_TIMER2_POSTSCALER_VALUE_1 = 1,
    CCPx_TIMER2_POSTSCALER_VALUE_2,
    CCPx_TIMER2_POSTSCALER_VALUE_3,
    CCPx_TIMER2_POSTSCALER_VALUE_4,
    CCPx_TIMER2_POSTSCALER_VALUE_5,
    CCPx_TIMER2_POSTSCALER_VALUE_6,
    CCPx_TIMER2_POSTSCALER_VALUE_7,
    CCPx_TIMER2_POSTSCALER_VALUE_8,
    CCPx_TIMER2_POSTSCALER_VALUE_9,
    CCPx_TIMER2_POSTSCALER_VALUE_10,
    CCPx_TIMER2_POSTSCALER_VALUE_11,
    CCPx_TIMER2_POSTSCALER_VALUE_12,
    CCPx_TIMER2_POSTSCALER_VALUE_13,
    CCPx_TIMER2_POSTSCALER_VALUE_14,
    CCPx_TIMER2_POSTSCALER_VALUE_15,
    CCPx_TIMER2_POSTSCALER_VALUE_16
}CCPx_Timer2_Postscaler_t;

/**
 *  @berief  Timer2 Input Clock Pre-scaler for CCP module
 */
typedef enum {
    CCPx_TIMER2_PRESCALER_VALUE_1 = 1,
    CCPx_TIMER2_PRESCALER_VALUE_4,
    CCPx_TIMER2_PRESCALER_VALUE_16,
}CCPx_Timer2_Prescaler_t;

/*
  @Summary      Define the values to select the CCPx Main mode
*/
typedef enum {
    CCPx_CFG_CAPTURE_MODE = 0, /* Select CCPx Capture Mode */
    CCPx_CFG_COMPARE_MODE,     /* Select CCPx Compare Mode */
    CCPx_CFG_PWM_MODE          /* Select CCPx PWM Mode */
}CCPx_MODE_t;


typedef enum {
    CCP1_SELECTED = 0, 
    CCP2_SELECTED,     
}CCPx_Instance_T;

typedef enum {
    CCP1_CCP2_TIMER1_SELECTED = 0, 
    CCP1_TIMER1_CCP2_TIMER3_SELECTED,     
    CCP1_CCP2_TIMER3_SELECTED        
}CCPx_CAPTURE_COMPARE_TIMER_T;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
*/
typedef union {
    struct {
        uint8 CCPR_LOW;  /* CCPR1 low register */
        uint8 CCPR_HIGH; /* CCPR1 high register */
    };
    struct {
        uint16 CCPR_16BIT;  /* Read CCPR1 as a 16 Bit value */
    };
}CCPx_reg_t;

/*
  @Summary      CCP Module configurations
  @Description  This data type used to describe the module initialization configuration
*/
typedef struct {
    CCPx_Instance_T  CCPx_Instance;  /* CCP main mode */
    CCPx_MODE_t      CCPx_MODE;      /* CCP selected mode variant */
    uint8            CCPx_Variant;   /* CCP Pin I/O configurations */
    pinConfig_t      CCPx_PIN;
    CCPx_CAPTURE_COMPARE_TIMER_T   CCPx_CAPTURE_COMPARE_TIMER;
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
    uint32 PWM_FREQ;  /* CCP PWM mode frequency */
    CCPx_Timer2_Postscaler_t  CCPx_Timer2_Postscaler;
    CCPx_Timer2_Prescaler_t   CCPx_Timer2_Prescaler;
#endif
    
#if (INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*CCP1_InterruptHandler)(void);
    Interrupt_Priority_Config  CCP1_Interrupt_Priority;
#endif
    
#if (INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*CCP2_InterruptHandler)(void);
    Interrupt_Priority_Config  CCP2_Interrupt_Priority;
#endif 
}CCPx_t;

/* Functions declarations */

STD_ReturnType CCPx_Init    (CCPx_t *_CCPx);
STD_ReturnType CCPx_Deinit  (CCPx_t *_CCPx);

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE_SELECTED)
STD_ReturnType CCPx_CaptureMode_IsData_Ready  (const CCPx_t *_CCPx, uint8 *isData_ready);
STD_ReturnType CCPx_CaptureMode_GetData       (const CCPx_t *_CCPx, uint16 *_Data);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
STD_ReturnType CCPx_CompareMode_IsComplete      (const CCPx_t *_CCPx, uint8 *IsComplete);
STD_ReturnType CCPx_CompareMode_WriteData       (const CCPx_t *_CCPx, uint16 _Data);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
STD_ReturnType CCPx_PWM_Mode_setDutyCycle       (const CCPx_t *_CCPx, uint8 _Duty);
STD_ReturnType CCPx_PWM_Mode_Start       (const CCPx_t *_CCPx);
STD_ReturnType CCPx_PWM_Mode_Stop       (const CCPx_t *_CCPx);
#endif

#endif	/* HAL_CCP_H */

