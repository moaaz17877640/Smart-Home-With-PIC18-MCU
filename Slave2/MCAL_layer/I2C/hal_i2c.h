/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H


/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupts.h"
/* ----------------- Macro Declarations -----------------*/
/**
 * @note : 1 = Slew rate control disabled for Standard Speed mode (100 kHz) 
           0 = Slew rate control enabled for High-Speed mode (400 kHz)
 */
#define I2C_SLEW_RATE_CONTROL_DISABLED             1
#define I2C_SLEW_RATE_CONTROL_ENABLED              0
/**
 * @berief : SMBus Select
 */
#define I2C_ENABLE_SMBUS_SPECIFIC_INPUTS           1
#define I2C_DISABLE_SMBUS_SPECIFIC_INPUTS          0
/**
 * @berief : Master Synchronous Serial Port Enable 
 */
#define I2C_PORT_ENABLE_Selected                   1
#define I2C_PORT_DISABLE_Selected                  0
/**
 * @berief : SCK Release Control
 */
#define I2C_CLK_RELEASE                            1
#define I2C_CLK_STRETCH                            0
/**
 * @berief : Master Synchronous Serial Port Mode Select
 */
#define I2C_SLAVE_MODE_10BIT_START_STOP_INTERRUPT  0x0FU
#define I2C_SLAVE_MODE_7BIT_START_STOP_INTERRUPT   0x0EU
#define I2C_FIRMWARE_CONTROLLED_MASTER_MODE        0x0BU
#define I2C_MASTER_MODE                            0x08U
#define I2C_SLAVE_MODE_10BIT                       0x07U
#define I2C_SLAVE_MODE_7BIT                        0x06U
/**
 * @berief :  General Call Enable bit (Slave mode only)
 */
#define I2C_GENERAL_CALL_ENABLE                    1
#define I2C_GENERAL_CALL_DISABLE                   0
/**
 * @berief :  Acknowledge Status bit (Master Transmit mode only)
 */
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE            1
#define I2C_ACK_RECEIVED_FROM_SLAVE                0
/**
 * @berief :  Acknowledge Status bit (Master Transmit mode only)
 */
#define I2C_MASTER_SEND_NACK                       1          
#define I2C_MASTER_SEND_ACK                        0
/**
 * @berief :  Receive Enable bit (Master mode only)
 */
#define I2C_MASTER_RECEIVER_ENABLE                 1          
#define I2C_MASTER_RECEIVER_DISABLE                0
/**
 * @berief :  Start Condition indication
 */
#define I2C_START_BIT_DETECTED                     1          
#define I2C_START_BIT_NOT_DETECTED                 0
/**
 * @berief :  Stop Condition indication
 */
#define I2C_STOP_BIT_DETECTED                      1          
#define I2C_STOP_BIT_NOT_DETECTED                  0
/**
 * @berief :  Slave Mode Data/Address Indication
 */
#define I2C_LAST_RECEIVED_BYTE_DATA                1
#define I2C_LAST_RECEIVED_BYTE_ADDRESS             0
/**
 * @berief :  Slave Mode Data/Address Indication
 */
#define I2C_MSSP_MASTER_MODE_SELECTED              1
#define I2C_MSSP_SLAVE_MODE_SELECTED               0
/* ----------------- Macro Functions Declarations -----------------*/
#define I2C_SLEW_RATE_CONTROL(__CONFIG)         (SSPSTATbits.SMP = __CONFIG)
#define I2C_SMBUS_SELECT(__CONFIG)              (SSPSTATbits.CKE = __CONFIG)
#define I2C_SCK_STRETCH_CONTROL(__CONFIG)       (SSPCON1bits.CKP = __CONFIG)
#define I2C_MODE_VARIANT_SELECT(__CONFIG)       (SSPCON1bits.SSPM = __CONFIG)
#define I2C_CHECK_BUFFER_IF_FULL()              (SSPSTATbits.BF)
#define I2C_COLLISION_DETECT()                  (SSPCON1bits.WCOL)
#define I2C_WRITE_COLLISION_DETECT_RESET()      (SSPCON1bits.WCOL = 0)
#define I2C_RECEIVE_OVERFLOW_INDICATOR()        (SSPCON1bits.SSPOV)
#define I2C_RECEIVE_OVERFLOW_INDICATOR_RESET()  (SSPCON1bits.SSPOV = 0)
#define I2C_PORT_ENABLE()                       (SSPCON1bits.SSPEN = 1)
#define I2C_PORT_DISABLE()                      (SSPCON1bits.SSPEN = 0)
/**
 * @note : 1 = Indicates that the last byte received or transmitted was data
           0 = Indicates that the last byte received or transmitted was address
 */
#define I2C_DATA_ADDRESS()                      (SSPSTATbits.D_nA)
#define I2C_START_BIT_DETECT()                  (SSPSTATbits.S)
#define I2C_STOP_BIT_DETECT()                   (SSPSTATbits.P)
#define I2C_GENERATE_START_CONDITION()          (SSPCON2bits.SEN = 1)
#define I2C_GENERATE_START_CONDITION_STATE()    (SSPCON2bits.SEN)
#define I2C_GENERATE_STOP_CONDITION()           (SSPCON2bits.PEN = 1)
#define I2C_GENERATE_STOP_CONDITION_STATE()     (SSPCON2bits.PEN)
#define I2C_GENERATE_RSTART_CONDITION()         (SSPCON2bits.RSEN = 1)
#define I2C_GENERATE_RSTART_CONDITION_STATE()   (SSPCON2bits.RSEN)
/**
 * @note: In Slave mode:
            1 = Read
            0 = Write
   @note: In Master mode:
            1 = Transmit is in progress
            0 = Transmit is not in progress
 */
#define I2C_READ_WRITE_INFORMATION()            (SSPSTATbits.R_nW)
#define I2C_GENERAL_CALL(__CONFIG)              (SSPCON2bits.GCEN = __CONFIG)   
#define I2C_SLAVE_ACK_DETECT()                  (SSPCON2bits.ACKSTAT)
#define I2C_MASTER_SEND_ACK_NACK(__CONFIG)      (SSPCON2bits.ACKDT = __CONFIG)
#define I2C_MASTER_SEND_ACK_SEQ()               (SSPCON2bits.ACKEN = 1)
#define I2C_MASTER_SEND_ACK_SEQ_STATE()         (SSPCON2bits.ACKEN)
#define I2C_MASTER_RECEIVER_SELECT(__CONFIG)    (SSPCON2bits.RCEN = __CONFIG)
/* ----------------- Data Type Declarations -----------------*/


typedef struct{
#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void);
    void (*I2C_Report_Receive_OverFlow)(void);
    void (*I2C_DefaultInterruptHandler)(void);
    Interrupt_Priority_Config  I2C_Interrupt_Priority;
    Interrupt_Priority_Config I2C_BUS_COL_Interrupt_Priority;
#endif
    uint32 I2C_CLK;
    uint8  I2C_Mode_Variant;
    uint8  I2C_Slave_Address;
    uint8  I2C_Mode :1;
    uint8  I2C_Slew_Rate :1;
    uint8  I2C_SMBus_Control :1;
    uint8  I2C_General_Call :1;
    uint8  I2C_Master_Rec_Mode :1;
    uint8  I2C_Reserved :3;   
}I2C_Config_t;
/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType   I2C_Init                           (const I2C_Config_t *_I2C);
STD_ReturnType   I2C_Deinit                         (const I2C_Config_t *_I2C);

STD_ReturnType   I2C_Master_Send_Start              (const I2C_Config_t *_I2C);
STD_ReturnType   I2C_Master_Send_Stop               (const I2C_Config_t *_I2C);
STD_ReturnType   I2C_Master_Send_Repeated_Start     (const I2C_Config_t *_I2C);

STD_ReturnType   I2C_MasterReadData                 (const I2C_Config_t *_I2C, uint8 *_Data, uint8 _ACK);


STD_ReturnType   I2C_MasterWriteData                (const I2C_Config_t *_I2C, uint8 _Data, uint8 *_ACK);
STD_ReturnType   I2C_MasterWriteString              (const I2C_Config_t *_I2C, uint8 *_Data, uint16 str_len, uint8 *_ACK);

#endif	/* HAL_I2C_H */

