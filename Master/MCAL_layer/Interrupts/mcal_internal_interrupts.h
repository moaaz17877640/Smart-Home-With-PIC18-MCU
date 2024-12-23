/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#ifndef MCAL_INTERNAL_INTERRUPTS_H
#define	MCAL_INTERNAL_INTERRUPTS_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for ADC module */
#define ADC_INTERRUPT_ENABLE()                 (PIE1bits.ADIE = 1)
/* This routine disable the interrupt feature for ADC module */
#define ADC_INTERRUPT_DISABLE()                (PIE1bits.ADIE = 0)
/* This routine clears the interrupt flag for ADC module */
#define ADC_INTERRUPT_FLAG_CLEAR()             (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for ADC module */
#define ADC_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR1bits.ADIP = 1)
/* This routine enable the interrupt low priority for ADC module */
#define ADC_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR1bits.ADIP = 0)
#endif
#endif

#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for TIMER0 module */
#define TIMER0_INTERRUPT_ENABLE()                 (INTCONbits.TMR0IE = 1)
/* This routine disable the interrupt feature for TIMER0 module */
#define TIMER0_INTERRUPT_DISABLE()                (INTCONbits.TMR0IE = 0)
/* This routine clears the interrupt flag for TIMER0 module */
#define TIMER0_INTERRUPT_FLAG_CLEAR()             (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for TIMER0 module */
#define TIMER0_INTERRUPT_HIGH_PRIORITY_ENABLE()  (INTCON2bits.TMR0IP = 1)
/* This routine enable the interrupt low priority for TIMER0 module */
#define TIMER0_INTERRUPT_LOW_PRIORITY_ENABLE()   (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for TIMER1 module */
#define TIMER1_INTERRUPT_ENABLE()                (PIE1bits.TMR1IE = 1)
/* This routine disable the interrupt feature for TIMER1 module */
#define TIMER1_INTERRUPT_DISABLE()               (PIE1bits.TMR1IE = 0)
/* This routine clears the interrupt flag for TIMER1 module */
#define TIMER1_INTERRUPT_FLAG_CLEAR()            (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for TIMER1 module */
#define TIMER1_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR1bits.TMR1IP = 1)
/* This routine enable the interrupt low priority for TIMER1 module */
#define TIMER1_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR1bits.TMR1IP = 0)
#endif
#endif

#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for TIMER2 module */
#define TIMER2_INTERRUPT_ENABLE()                 (PIE1bits.TMR2IE = 1)
/* This routine disable the interrupt feature for TIMER2 module */
#define TIMER2_INTERRUPT_DISABLE()                (PIE1bits.TMR2IE = 0)
/* This routine clears the interrupt flag for TIMER2 module */
#define TIMER2_INTERRUPT_FLAG_CLEAR()             (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for TIMER2 module */
#define TIMER2_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR1bits.TMR2IP = 1)
/* This routine enable the interrupt low priority for TIMER2 module */
#define TIMER2_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR1bits.TMR2IP = 0)
#endif
#endif

#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for TIMER3 module */
#define TIMER3_INTERRUPT_ENABLE()                 (PIE2bits.TMR3IE = 1)
/* This routine disable the interrupt feature for TIMER3 module */
#define TIMER3_INTERRUPT_DISABLE()                (PIE2bits.TMR3IE = 0)
/* This routine clears the interrupt flag for TIMER3 module */
#define TIMER3_INTERRUPT_FLAG_CLEAR()             (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for TIMER3 module */
#define TIMER3_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR2bits.TMR3IP = 1)
/* This routine enable the interrupt low priority for TIMER3 module */
#define TIMER3_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR2bits.TMR3IP = 0)
#endif
#endif

#if INTERRUPT_USART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for USART TX module */
#define USART_TX_INTERRUPT_ENABLE()                (PIE1bits.TXIE = 1)
/* This routine disable the interrupt feature for USART TX module */
#define USART_TX_INTERRUPT_DISABLE()               (PIE1bits.TXIE = 0)
/* This routine clears the interrupt flag for USART TX module */
#define USART_TX_INTERRUPT_FLAG_CLEAR()            (PIR1bits.TXIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for USART TX module */
#define USART_TX_INTERRUPT_HIGH_PRIORITY_ENABLE() (IPR1bits.TXIP = 1)
/* This routine enable the interrupt low priority for USART TX module */
#define USART_TX_INTERRUPT_LOW_PRIORITY_ENABLE()  (IPR1bits.TXIP = 0)
#endif
#endif

#if INTERRUPT_USART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for USART RX module */
#define USART_RX_INTERRUPT_ENABLE()                (PIE1bits.RCIE = 1)
/* This routine disable the interrupt feature for USART RX module */
#define USART_RX_INTERRUPT_DISABLE()               (PIE1bits.RCIE = 0)
/* This routine clears the interrupt flag for USART RX module */
#define USART_RX_INTERRUPT_FLAG_CLEAR()            (PIR1bits.RCIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for USART RX module */
#define USART_RX_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR1bits.RCIP = 1)
/* This routine enable the interrupt low priority for USART RX module */
#define USART_RX_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR1bits.RCIP = 0)
#endif
#endif

#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for MCCP I2C module */
#define MCCP_I2C_INTERRUPT_ENABLE()                        (PIE1bits.SSPIE = 1)
#define MCCP_I2C_BUS_COL_INTERRUPT_ENABLE()                (PIE2bits.BCLIE = 1)
/* This routine disable the interrupt feature for MCCP I2C module */
#define MCCP_I2C_INTERRUPT_DISABLE()                       (PIE1bits.SSPIE = 0)
#define MCCP_I2C_BUS_COL_INTERRUPT_DISABLE()               (PIE2bits.BCLIE = 0)
/* This routine clears the interrupt flag for MCCP I2C module */
#define MCCP_I2C_INTERRUPT_FLAG_CLEAR()                    (PIR1bits.SSPIF = 0)
#define MCCP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR()            (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for MCCP I2C module */
#define MCCP_I2C_INTERRUPT_HIGH_PRIORITY_ENABLE()         (IPR1bits.SSPIP = 1)
#define I2C_BUS_COL_INTERRUPT_HIGH_PRIORITY_ENABLE() (IPR2.BCLIP = 1)
/* This routine enable the interrupt low priority for MCCP I2C module */
#define MCCP_I2C_INTERRUPT_LOW_PRIORITY_ENABLE()          (IPR1bits.SSPIP = 0)
#define MCCP_I2C_BUS_COL_INTERRUPT_LOW_PRIORITY_ENABLE()  (IPR2bits.BCLIP = 0)
#endif
#endif

#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for MCCP SPI module */
#define MCCP_SPI_INTERRUPT_ENABLE()                 (PIE1bits.SSPIE = 1)
/* This routine disable the interrupt feature for MCCP SPI module */
#define MCCP_SPI_INTERRUPT_DISABLE()                (PIE1bits.SSPIE = 0)
/* This routine clears the interrupt flag for MCCP SPI module */
#define MCCP_SPI_INTERRUPT_FLAG_CLEAR()             (PIR1bits.SSPIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for MCCP SPI module */
#define MCCP_SPI_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR1bits.SSPIP = 1)
/* This routine enable the interrupt low priority for MCCP SPI module */
#define MCCP_SPI_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR2bits.BCLIP = 0)
#endif
#endif

#if INTERRUPT_CCP1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for CCP1 module */
#define CCP1_INTERRUPT_ENABLE()                 (PIE1bits.CCP1IE = 1)
/* This routine disable the interrupt feature for CCP1 module */
#define CCP1_INTERRUPT_DISABLE()                (PIE1bits.CCP1IE = 0)
/* This routine clears the interrupt flag for CCP1 module */
#define CCP1_INTERRUPT_FLAG_CLEAR()             (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for CCP1 module */
#define CCP1_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR1bits.CCP1IP = 1)
/* This routine enable the interrupt low priority for CCP1 module */
#define CCP1_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR1bits.CCP1IP = 0)
#endif
#endif

#if INTERRUPT_CCP2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt feature for CCP2 module */
#define CCP2_INTERRUPT_ENABLE()                 (PIE2bits.CCP2IE = 1)
/* This routine disable the interrupt feature for CCP2 module */
#define CCP2_INTERRUPT_DISABLE()                (PIE2bits.CCP2IE = 0)
/* This routine clears the interrupt flag for CCP2 module */
#define CCP2_INTERRUPT_FLAG_CLEAR()             (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine enable the interrupt high priority for CCP2 module */
#define CCP2_INTERRUPT_HIGH_PRIORITY_ENABLE()  (IPR2bits.CCP2IP = 1)
/* This routine enable the interrupt low priority for CCP2 module */
#define CCP2_INTERRUPT_LOW_PRIORITY_ENABLE()   (IPR2bits.CCP2IP = 0)
#endif
#endif
/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/




#endif	/* MCAL_INTERNAL_INTERRUPTS_H */

