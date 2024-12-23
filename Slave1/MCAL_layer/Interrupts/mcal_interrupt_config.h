/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_gen_cfg.h"
#include "../mcal_std_types.h"
#include "./../GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define INTERRUPT_ENABLE  1
#define INTERRUPT_DISABLE 0
#define INTERRUPT_OCCUR      1
#define INTERRUPT_NOT_OCCUR  0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0


/* ----------------- Macro Functions Declarations -----------------*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine will enable priority levels on interrupts*/
#define INTERRUPT_PriorityLevelsEnable()   (RCONbits.IPEN = 1)
/* This routine will disable priority levels on interrupts*/
#define INTERRUPT_PriorityLevelsDisable()   (RCONbits.IPEN = 0)

/* This routine will enable high priority global interrupts*/
#define INTERRUPT_Global_High_Priority_Enable()    (INTCONbits.GIEH = 1)
/* This routine will disable high priority global interrupts*/
#define INTERRUPT_Global_High_Priority_Disable()   (INTCONbits.GIEH = 0)
/* This routine will enable low priority global interrupts*/
#define INTERRUPT_Global_LOW_Priority_Enable()     (INTCONbits.GIEL = 1)
/* This routine will disable low priority global interrupts*/
#define INTERRUPT_Global_LOW_Priority_Disable()    (INTCONbits.GIEL = 0)
#else
/* This routine will enable global interrupts*/
#define INTERRUPT_GlobalEnable()   (INTCONbits.GIE = 1)
/* This routine will disable global interrupts*/
#define INTERRUPT_GlobalDisable()   (INTCONbits.GIE = 0)

/* This routine will enable peripheral interrupts*/
#define INTERRUPT_PeripheralEnable()   (INTCONbits.PEIE = 1)
/* This routine will enable peripheral interrupts*/
#define INTERRUPT_PeripheralDisable()   (INTCONbits.PEIE = 0)
#endif

/* ----------------- Data Type Declarations -----------------*/
typedef enum {
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY
}Interrupt_Priority_Config;

/* ----------------- Software Interfaces Declarations -----------------*/





#endif	/* MCAL_INTERRUPT_CONFIG_H */

