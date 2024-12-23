/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#ifndef MCAL_EXTERNAL_INTERRUPTS_H
#define	MCAL_EXTERNAL_INTERRUPTS_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#if EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for external INT0 */
#define INT0_INTERRUPT_ENABLE()     (INTCONbits.INT0IE = 1)
/* This routine disable the interrupt feature for external INT0 */
#define INT0_INTERRUPT_DISABLE()    (INTCONbits.INT0IE = 0)
/* This routine clears the interrupt flag for external INT0 */
#define INT0_INTERRUPT_FLAG_CLEAR()   (INTCONbits.INT0IF = 0)
/* This routine set the edge detect of INT0 to negative edge*/
#define INT0_INTERRUPT_FAILLING_EDGE()  (INTCON2bits.INTEDG0 = 0)
/* This routine set the edge detect of INT0 to positive edge*/
#define INT0_INTERRUPT_RAISING_EDGE()   (INTCON2bits.INTEDG0 = 1)

/* This routine enable the interrupt feature for external INT1 */
#define INT1_INTERRUPT_ENABLE()     (INTCON3bits.INT1IE = 1)
/* This routine disable the interrupt feature for external INT1 */
#define INT1_INTERRUPT_DISABLE()    (INTCON3bits.INT1IE = 0)
/* This routine clears the interrupt flag for external INT1 */
#define INT1_INTERRUPT_FLAG_CLEAR()   (INTCON3bits.INT1IF = 0)
/* This routine set the edge detect of INT1 to negative edge*/
#define INT1_INTERRUPT_FAILLING_EDGE()   (INTCON2bits.INTEDG1 = 0)
/* This routine set the edge detect of INT1 to positive edge*/
#define INT1_INTERRUPT_RAISING_EDGE()   (INTCON2bits.INTEDG1 = 1)


/* This routine enable the interrupt feature for external INT2 */
#define INT2_INTERRUPT_ENABLE()     (INTCON3bits.INT2IE = 1)
/* This routine disable the interrupt feature for external INT2 */
#define INT2_INTERRUPT_DISABLE()    (INTCON3bits.INT2IE = 0)
/* This routine clears the interrupt flag for external INT2 */
#define INT2_INTERRUPT_FLAG_CLEAR()   (INTCON3bits.INT2IF = 0)
/* This routine set the edge detect of INT2 to negative edge*/
#define INT2_INTERRUPT_FAILLING_EDGE()   (INTCON2bits.INTEDG2 = 0)
/* This routine set the edge detect of INT2 to positive edge*/
#define INT2_INTERRUPT_RAISING_EDGE()   (INTCON2bits.INTEDG2 = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for external INT1 */
#define INT1_INTERRUPT_HIGH_PRIORITY_ENABLE()  (INTCON3bits.INT1IP = 1)
/* This routine enable the interrupt low priority for external INT1 */
#define INT1_INTERRUPT_LOW_PRIORITY_ENABLE()   (INTCON3bits.INT1IP = 0)

/* This routine enable the interrupt high priority for external INT2 */
#define INT2_INTERRUPT_HIGH_PRIORITY_ENABLE()  (INTCON3bits.INT2IP = 1)
/* This routine enable the interrupt low priority for external INT2 */
#define INT2_INTERRUPT_LOW_PRIORITY_ENABLE()   (INTCON3bits.INT2IP = 0)
#endif
#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for external RBx */
#define RBx_INTERRUPT_ENABLE()     (INTCONbits.RBIE = 1)
/* This routine disable the interrupt feature for external RBx */
#define RBx_INTERRUPT_DISABLE()    (INTCONbits.RBIE = 0)
/* This routine clears the interrupt flag for external RBx */
#define RBx_INTERRUPT_FLAG_CLEAR()   (INTCONbits.RBIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for external RBx */
#define RBx_INTERRUPT_HIGH_PRIORITY_ENABLE()  (INTCON2bits.RBIP = 1)
/* This routine enable the interrupt low priority for external RBx */
#define RBx_INTERRUPT_LOW_PRIORITY_ENABLE()   (INTCON2bits.RBIP = 0)
#endif
#endif

/* ----------------- Data Type Declarations -----------------*/

typedef void (*InterruptHandler)(void);

typedef enum{
    INTERRUPT_FAILLING_EDGE = 0,
    INTERRUPT_RAISING_EDGE
}Interrupt_Edge_Config;

typedef enum{
    EXTERNAL_INTERRUPT_INT0 = 0,
    EXTERNAL_INTERRUPT_INT1,
    EXTERNAL_INTERRUPT_INT2
}Interrupt_Source_Config;


typedef struct{
    pinConfig_t                Interrupt_Pin;
    Interrupt_Edge_Config      Interrupt_Edge;
    Interrupt_Source_Config    Interrupt_Source;
    Interrupt_Priority_Config  Interrupt_Priority;
    void (* EXT_InterruptHandler)(void);
}External_INTx_t;

typedef struct{
    pinConfig_t                Interrupt_Pin;
    Interrupt_Priority_Config  Interrupt_Priority;
    InterruptHandler           Interrupt_Handle_HIGH;
    InterruptHandler           Interrupt_Handle_LOW;
}External_RBx_t;

/* ----------------- Software Interfaces Declarations -----------------*/
/**
 * 
 * @param INTx
 * @return 
 */
STD_ReturnType Interrupt_INTx_Init (const External_INTx_t *INTx);
/**
 * 
 * @param INTx
 * @return 
 */
STD_ReturnType Interrupt_INTx_Deinit (const External_INTx_t *INTx);
/**
 * 
 * @param RBx
 * @return 
 */
STD_ReturnType Interrupt_RBx_Init (const External_RBx_t *RBx);
/**
 * 
 * @param RBx
 * @return 
 */
STD_ReturnType Interrupt_RBx_Deinit (const External_RBx_t *RBx);

#endif	/* MCAL_EXTERNAL_INTERRUPTS_H */

