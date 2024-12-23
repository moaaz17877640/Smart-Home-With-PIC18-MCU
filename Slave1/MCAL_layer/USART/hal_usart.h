/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "hal_usart_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupts.h"
/* ----------------- Macro Declarations -----------------*/
/*Transmit Enable*/
#define EUSART_ASYNCHRONOUS_TX_ENABLE_SELECTED     1
#define EUSART_ASYNCHRONOUS_TX_DISABLE_SELECTED    0
/*Transmit interrupt Enable*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE_SELECTED    1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE_SELECTED   0
/*Transmit TX9 Enable*/
#define EUSART_ASYNCHRONOUS_TX9_ENABLE_SELECTED             1
#define EUSART_ASYNCHRONOUS_TX9_DISABLE_SELECTED            0

/*Receive Enable*/
#define EUSART_ASYNCHRONOUS_RX_ENABLE_SELECTED              1
#define EUSART_ASYNCHRONOUS_RX_DISABLE_SELECTED             0
/*Receive interrupt Enable*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE_SELECTED    1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE_SELECTED   0
/*Receive TX9 Enable*/
#define EUSART_ASYNCHRONOUS_RX9_ENABLE_SELECTED             1
#define EUSART_ASYNCHRONOUS_RX9_DISABLE_SELECTED            0
/* ----------------- Macro Functions Declarations -----------------*/
/*Serial Port Enable/Disable*/ 
#define EUSART_MODULE_ON()                            (RCSTAbits.SPEN = 1)
#define EUSART_MODULE_OFF()                           (RCSTAbits.SPEN = 0)
/*EUSART Mode Select*/ 
#define EUSART_SYNCHRONOUS_MODE()                     (TXSTAbits.SYNC = 1)
#define EUSART_ASYNCHRONOUS_MODE()                    (TXSTAbits.SYNC = 0)
/*16-Bit Baud Rate Register Enable*/
#define EUSART_16BIT_BAUDRATE()                       (BAUDCONbits.BRG16 = 1)
#define EUSART_8BIT_BAUDRATE()                        (BAUDCONbits.BRG16 = 0)
/*High Baud Rate Select*/
#define EUSART_ASYNCHRONOUS_HIGH_SPEED()              (TXSTAbits.BRGH = 1)
#define EUSART_ASYNCHRONOUS_LOW_SPEED()               (TXSTAbits.BRGH = 0)

/*Transmit Enable*/
#define EUSART_ASYNCHRONOUS_TX_ENABLE()               (TXSTAbits.TXEN = 1)
#define EUSART_ASYNCHRONOUS_TX_DISABLE()              (TXSTAbits.TXEN = 0)
/*Transmit interrupt Enable*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE()     (PIE1bits.TXIE = 1)
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE()    (PIE1bits.TXIE = 1)
/*Transmit TX9 Enable*/
#define EUSART_ASYNCHRONOUS_TX9_ENABLE()              (TXSTAbits.TX9 = 1)
#define EUSART_ASYNCHRONOUS_TX9_DISABLE()             (TXSTAbits.TX9 = 0)

/*Receive Enable*/
#define EUSART_ASYNCHRONOUS_RX_ENABLE()               (RCSTAbits.CREN = 1)
#define EUSART_ASYNCHRONOUS_RX_DISABLE()              (RCSTAbits.CREN = 0)
/*Receive interrupt Enable*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE()     (PIE1bits.RCIE = 1)
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE()    (PIE1bits.RCIE = 1)
/*Receive TX9 Enable*/
#define EUSART_ASYNCHRONOUS_RX9_ENABLE()              (RCSTAbits.RX9 = 1)
#define EUSART_ASYNCHRONOUS_RX9_DISABLE()             (RCSTAbits.RX9 = 0)
/* EUSART Framing Error */
#define EUSART_ASYNCHRONOUS_Framing_Error_Read()      (RCSTAbits.FERR)
/* EUSART Overrun Error */
#define EUSART_ASYNCHRONOUS_OVERRUN_Error_Read()      (RCSTAbits.OERR)
/* ----------------- Data Type Declarations -----------------*/
typedef enum {
    EUSART_BAUDRAT_ASYN_8BIT_HIGH_SPEED = 0,
    EUSART_BAUDRAT_ASYN_8BIT_LOW_SPEED,        
    EUSART_BAUDRAT_ASYN_16BIT_HIGH_SPEED,
    EUSART_BAUDRAT_ASYN_16BIT_LOW_SPEED,
    EUSART_BAUDRAT_SYN_8BIT,
    EUSART_BAUDRAT_SYN_16BIT
}ESUART_BAUDRAT_CONFIG_t;

typedef struct {
    Interrupt_Priority_Config  EUSART_TX_Interrupt_Priority;
    uint8 Transmit_Enable :1;
    uint8 Transmit_Interrupt_Enable :1;
    uint8 Transmit_TX9_Enable :1;
    uint8 Reserved :5;
}EUSART_TX_Config;

typedef struct {
    Interrupt_Priority_Config  EUSART_RX_Interrupt_Priority;
    uint8 Receive_Enable :1;
    uint8 Receive_Interrupt_Enable :1;
    uint8 Receive_RX9_Enable :1;
    uint8 Reserved :5;
}EUSART_RX_Config;

typedef struct {
    uint32 Baud_rate ;
    ESUART_BAUDRAT_CONFIG_t  BAUDRAT_CONFIG;
    EUSART_TX_Config         TX_Config;
    EUSART_RX_Config         RX_Config;
    void (*EUSART_TX_InterruptHandler)(void);
    void (*EUSART_RX_InterruptHandler)(void);
    void (*EUSART_FramingErrorInterruptHandler)(void);
    void (*EUSART_OverrunErrorInterruptHandler)(void);
}EUSART_Config_t;
/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType   EUSART_ASYNC_Init               (const EUSART_Config_t *_EUSART);
STD_ReturnType   EUSART_ASYNC_Deinit             (const EUSART_Config_t *_EUSART);

STD_ReturnType   EUSART_ASYNC_ReadByteBlocking   (uint8 *_Byte);
STD_ReturnType   EUSART_ASYNC_ReadByteNonBlocking   (uint8 *_Byte);
STD_ReturnType   EUSART_ASYNC_Restart            (void);

STD_ReturnType   EUSART_ASYNC_WriteByteBlocking  (uint8 _Byte);
STD_ReturnType   EUSART_ASYNC_WriteStringBlocking(uint8 *_Byte, uint16 str_len);
STD_ReturnType   EUSART_ASYNC_WriteByteNonBlocking  (uint8 _Byte);
STD_ReturnType   EUSART_ASYNC_WriteStringNonBlocking(uint8 *_Byte, uint16 str_len);



#endif	/* HAL_USART_H */

