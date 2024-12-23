/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupts.h"
/* ----------------- Macro Declarations -----------------*/
/**
 * @berief : Sample mode configure
 */
#define SPI_SAMPLE_AT_END_OF_OUTPUT_TIME           1
#define SPI_SAMPLE_AT_MIDDLE_OF_OUTPUT_TIME        0
/**
 * @berief : Transmit mode configure
 */
#define SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE           1
#define SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE           0
/**
 * @berief : Clock Polarity Select
 */
#define SPI_IDLE_STATE_FOR_CLOCK_IS_A_HIGH_LEVEL   1
#define SPI_IDLE_STATE_FOR_CLOCK_IS_A_LOW_LEVEL    0
/**
 * @berief : SPI Mode Select
 */
#define SPI_MASTER_MODE_SELECTED                   1
#define SPI_SLAVE_MODE_SELECTED                    0
/**
 * @berief : SPI Interrupt Enable/Disable
 */
#define SPI_INTERRUPT_ENABLE                       1
#define SPI_INTERRUPT_DISABLE                      0
/* ----------------- Macro Functions Declarations -----------------*/
#define SPI_SAMPLE_MODE_SELECT(__CONFIG)        (SSPSTATbits.SMP = __CONFIG)
#define SPI_CLOCK_PHASE_SELECT(__CONFIG)        (SSPSTATbits.CKE = __CONFIG)
#define SPI_CLOCK_POLARITY_SELECT(__CONFIG)     (SSPCON1bits.CKP = __CONFIG)
#define SPI_MODE_VARIANT_SELECT(__CONFIG)       (SSPCON1bits.SSPM = __CONFIG)
#define SPI_CHECK_BUFFER_IF_FULL()              (SSPSTATbits.BF)
#define SPI_WRITE_COLLISION_DETECT()            (SSPCON1bits.WCOL)
#define SPI_WRITE_COLLISION_DETECT_RESET()      (SSPCON1bits.WCOL = 0)
#define SPI_RECEIVE_OVERFLOW_INDICATOR()        (SSPCON1bits.SSPOV)
#define SPI_RECEIVE_OVERFLOW_INDICATOR_RESET()  (SSPCON1bits.SSPOV = 0)
#define SPI_PORT_ENABLE()                       (SSPCON1bits.SSPEN = 1)
#define SPI_PORT_DISABLE()                      (SSPCON1bits.SSPEN = 0)
/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    SPI_MASTER_MODE_CLOCK_FOSC_DIV_4 = 0,
    SPI_MASTER_MODE_CLOCK_FOSC_DIV_16,
    SPI_MASTER_MODE_CLOCK_FOSC_DIV_64,
    SPI_MASTER_MODE_CLOCK_TMR_DIV_2,
    SPI_SLAVE_MODE_CLOCK_SCK_SS_ENABLED,
    SPI_SLAVE_MODE_CLOCK_SCK_SS_DISABLED,      
}SPI_Mode_Variant_t;



typedef struct{
#if INTERRUPT_MCCP_SPI_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*SPI_InterruptHandler)(void);
    Interrupt_Priority_Config  SPI_Interrupt_Priority;
#endif
    uint8 SPI_Mode :1;
    uint8 SPI_Interrupt_Enable :1;
    SPI_Mode_Variant_t  SPI_Mode_Variant;
    uint8 SPI_Sample_mode      :1;
    uint8 SPI_Clock_Phase      :1;
    uint8 SPI_Clock_Polarity   :1;
    uint8 Reserved :3;
}SPI_Config_t;
/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType   SPI_Init                  (const SPI_Config_t *_SPI);
STD_ReturnType   SPI_Deinit                (const SPI_Config_t *_SPI);

STD_ReturnType   SPI_ReadByteBlocking      (uint8 *_Byte);
STD_ReturnType   SPI_ReadByteNonBlocking   (uint8 *_Byte);

STD_ReturnType   SPI_WriteByteBlocking     (uint8 _Byte);
STD_ReturnType   SPI_WriteStringBlocking   (uint8 *_Byte, uint16 str_len);
STD_ReturnType   SPI_WriteByteNonBlocking  (uint8 _Byte);
STD_ReturnType   SPI_WriteStringNonBlocking(uint8 *_Byte, uint16 str_len);
#endif	/* HAL_SPI_H */

