/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "hal_i2c.h"

#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*I2C_DefaultInterruptHandler)(void) = NULL;
static void(*I2C_Report_Receive_OverFlow)(void) = NULL;
static void(*I2C_Report_Write_Collision)(void) = NULL;
static STD_ReturnType I2C_Interrupt_Config        (const I2C_Config_t *_I2C);
#endif

static void I2C_GPIO_CFG                 (void);
static void I2C_Master_Mode_Configuration(const I2C_Config_t *_I2C);
static void I2C_Slave_Mode_Configuration (const I2C_Config_t *_I2C);


STD_ReturnType   I2C_Init                           (const I2C_Config_t *_I2C){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
       /*I2C Disable*/
        I2C_PORT_DISABLE();
        /*Pins configurations*/
        I2C_GPIO_CFG();
       /*I2C Select mode*/
        if(I2C_MSSP_MASTER_MODE_SELECTED == _I2C->I2C_Mode){
            /* I2C Master Mode Clock Configurations */
            I2C_Master_Mode_Configuration(_I2C);
        }
        else if(I2C_MSSP_SLAVE_MODE_SELECTED == _I2C->I2C_Mode){
            /* I2C Slave Mode General Call Configurations */
            if(I2C_GENERAL_CALL_ENABLE == _I2C->I2C_General_Call){
                I2C_GENERAL_CALL(I2C_GENERAL_CALL_ENABLE);
            }
            else if(I2C_GENERAL_CALL_DISABLE == _I2C->I2C_General_Call){
                I2C_GENERAL_CALL(I2C_GENERAL_CALL_DISABLE);
            }
            else{/*Do nothing*/}
                /* Clear the Write Collision Detect */
                I2C_WRITE_COLLISION_DETECT_RESET();
                /* Clear the Receive Overflow Indicator */
                I2C_RECEIVE_OVERFLOW_INDICATOR_RESET();
                /* Release the clock */
                I2C_SCK_STRETCH_CONTROL(I2C_CLK_RELEASE);
                /* Assign the I2C Slave Address */
                SSPADD = _I2C->I2C_Slave_Address;
                /* I2C Slave Mode Configurations */
                I2C_Slave_Mode_Configuration(_I2C);
        }
        else{/*Do nothing*/}
        /* MSSP I2C Slew Rate Control */
        if(I2C_SLEW_RATE_CONTROL_DISABLED == _I2C->I2C_Slew_Rate){
            I2C_SLEW_RATE_CONTROL(I2C_SLEW_RATE_CONTROL_DISABLED);
        }
        else if(I2C_SLEW_RATE_CONTROL_ENABLED == _I2C->I2C_Slew_Rate){
            I2C_SLEW_RATE_CONTROL(I2C_SLEW_RATE_CONTROL_ENABLED);
        }
        else{/*Do nothing*/}
        /* MSSP I2C SMBus Control*/
        if(I2C_ENABLE_SMBUS_SPECIFIC_INPUTS == _I2C->I2C_SMBus_Control){
            I2C_SMBUS_SELECT(I2C_ENABLE_SMBUS_SPECIFIC_INPUTS);
        }
        else if(I2C_DISABLE_SMBUS_SPECIFIC_INPUTS == _I2C->I2C_SMBus_Control){
            I2C_SMBUS_SELECT(I2C_DISABLE_SMBUS_SPECIFIC_INPUTS);
        }
        else{/*Do nothing*/}
        /*Configure SPI interrupt*/
#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = I2C_Interrupt_Config(_I2C);
#endif
        /*I2C Enable*/
        I2C_PORT_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}
STD_ReturnType   I2C_Deinit                         (const I2C_Config_t *_I2C){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
       /*I2C Disable*/
        I2C_PORT_DISABLE();
#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine disable the interrupt feature for MCCP I2C module */
        MCCP_I2C_INTERRUPT_DISABLE();
        MCCP_I2C_BUS_COL_INTERRUPT_DISABLE();
#endif
        
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   I2C_Master_Send_Start              (const I2C_Config_t *_I2C){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
        /* Initiates Start condition on SDA and SCL pins */
        I2C_GENERATE_START_CONDITION();  /* Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware. */
        /* Wait for the completion of the Start condition */
        while(I2C_GENERATE_START_CONDITION_STATE());
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        MCCP_I2C_INTERRUPT_FLAG_CLEAR();
        /* Report The Start Condition Detection */
        if(I2C_START_BIT_DETECTED == I2C_START_BIT_DETECT()){
            ret = E_OK;    /* Indicates that a Start bit has been detected last */
        }
        else{
            ret = E_NOT_OK;  /* Start bit was not detected last */
        }
    }
    return ret;
}
STD_ReturnType   I2C_Master_Send_Stop               (const I2C_Config_t *_I2C){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
        /* Initiates Stop condition on SDA and SCL pins */
        I2C_GENERATE_STOP_CONDITION();  /* Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware */
        /* Wait for the completion of the Stop condition */
        while(I2C_GENERATE_STOP_CONDITION_STATE());
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        MCCP_I2C_INTERRUPT_FLAG_CLEAR();
        /* Report The Stop Condition Detection */
        if(I2C_STOP_BIT_DETECTED == I2C_STOP_BIT_DETECT()){
            ret = E_OK;   /* Indicates that a Stop bit has been detected last */
        }
        else{
            ret = E_NOT_OK;  /* Stop bit was not detected last */
        }
        
    }
    return ret;
}
STD_ReturnType   I2C_Master_Send_Repeated_Start     (const I2C_Config_t *_I2C){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
        /* Initiates Repeated Start condition on SDA and SCL pins */
        I2C_GENERATE_RSTART_CONDITION(); /* Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
        /* Wait for the completion of the Repeated Start condition */
        while(I2C_GENERATE_RSTART_CONDITION_STATE());
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        MCCP_I2C_INTERRUPT_FLAG_CLEAR();
        
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType   I2C_MasterReadData               (const I2C_Config_t *_I2C, uint8 *_Data, uint8 _ACK){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
        /* Master Mode Receive Enable */
       I2C_MASTER_RECEIVER_SELECT(I2C_MASTER_RECEIVER_ENABLE);
       /* Wait for buffer full flag : A complete byte received */
       while(!(I2C_CHECK_BUFFER_IF_FULL()));
       /* Copy The data registers to buffer variable */
       *_Data = SSPBUF;
       /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        MCCP_I2C_INTERRUPT_FLAG_CLEAR();
        /* Send ACK or NACK after read */
        if(I2C_MASTER_SEND_ACK == _ACK){
            I2C_MASTER_SEND_ACK_NACK(I2C_MASTER_SEND_ACK); /* Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            I2C_MASTER_SEND_ACK_SEQ();
            while(I2C_MASTER_SEND_ACK_SEQ_STATE());  /* Automatically cleared by hardware */
        }
        else if(I2C_MASTER_SEND_NACK == _ACK){
            I2C_MASTER_SEND_ACK_NACK(I2C_MASTER_SEND_NACK); /* Not Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            I2C_MASTER_SEND_ACK_SEQ();
            while(I2C_MASTER_SEND_ACK_SEQ_STATE()); /* Automatically cleared by hardware */
        }
        else{/*Do nothing*/}
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType   I2C_MasterWriteData        (const I2C_Config_t *_I2C, uint8 _Data, uint8 *_ACK){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
        /* Write Data to the Data register */
        SSPBUF = _Data;
        /* Wait The transmission to be completed */
        while(I2C_CHECK_BUFFER_IF_FULL());
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        MCCP_I2C_INTERRUPT_FLAG_CLEAR();
        /* Report the acknowledge received from the slave */
        if(I2C_ACK_RECEIVED_FROM_SLAVE == I2C_SLAVE_ACK_DETECT()){
            *_ACK = I2C_ACK_RECEIVED_FROM_SLAVE; /* Acknowledge was received from slave */
        }
        else{
            *_ACK = I2C_ACK_NOT_RECEIVED_FROM_SLAVE; /* Acknowledge was not received from slave */
        }

        ret = E_OK;
    }
    return ret;
}


STD_ReturnType   I2C_MasterWriteString        (const I2C_Config_t *_I2C, uint8 *_Data, uint16 str_len, uint8 *_ACK){
    STD_ReturnType ret = E_NOT_OK;
    uint16 l_Counter_Characters = E_Zero_Init; 
    if(NULL == _I2C){
            ret = E_NOT_OK;
        }
    else{
        for(l_Counter_Characters = E_Zero_Init;l_Counter_Characters<str_len;l_Counter_Characters++){
            ret = I2C_MasterWriteDataBlocking(_I2C, _Data[l_Counter_Characters], _ACK);
            __delay_us(100);
        }
        
        ret = E_OK;
        
    }
    return ret;
}



static void I2C_GPIO_CFG(void){
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}
static void I2C_Master_Mode_Configuration(const I2C_Config_t *_I2C){
    I2C_MODE_VARIANT_SELECT(_I2C->I2C_Mode_Variant);
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / _I2C->I2C_CLK) - 1);
}
static void I2C_Slave_Mode_Configuration (const I2C_Config_t *_I2C){
    I2C_MODE_VARIANT_SELECT(_I2C->I2C_Mode_Variant);
}

#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType I2C_Interrupt_Config        (const I2C_Config_t *_I2C){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == _I2C){
        ret = E_NOT_OK;
    }
    else{
        /* This routine disable the interrupt feature for I2C module */
        MCCP_I2C_INTERRUPT_DISABLE();
        MCCP_I2C_BUS_COL_INTERRUPT_DISABLE();
        /* This routine disable the flag the interrupt feature for I2C module*/
        MCCP_I2C_INTERRUPT_FLAG_CLEAR();
        MCCP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        switch(_I2C->I2C_Interrupt_Priority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for I2C module  */
                MCCP_I2C_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for I2C module  */
                MCCP_I2C_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        switch(_I2C->I2C_BUS_COL_Interrupt_Priority){
            case INTERRUPT_LOW_PRIORITY: 
                /* This routine enable the interrupt low priority for I2C module  */
                MCCP_I2C_BUS_COL_INTERRUPT_LOW_PRIORITY_ENABLE();
                /* This routine will enable low priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
                INTERRUPT_Global_LOW_Priority_Enable();break;
            case INTERRUPT_HIGH_PRIORITY:
                /* This routine enable the interrupt high priority for I2C module  */
                I2C_BUS_COL_INTERRUPT_HIGH_PRIORITY_ENABLE();
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();break;
            default: /*Do nothing*/;
        }
        /*Configure I2C module Interrupt Handler*/
        I2C_DefaultInterruptHandler = _I2C->I2C_DefaultInterruptHandler;
        I2C_Report_Receive_OverFlow = _I2C->I2C_Report_Receive_OverFlow;
        I2C_Report_Write_Collision = _I2C->I2C_Report_Write_Collision;
        /* This routine enable the interrupt feature for I2C module  */
        MCCP_I2C_INTERRUPT_ENABLE();
        MCCP_I2C_BUS_COL_INTERRUPT_ENABLE();
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();
        /*Configure I2C module Interrupt Handler*/
        I2C_DefaultInterruptHandler = _I2C->I2C_DefaultInterruptHandler;
        I2C_Report_Receive_OverFlow = _I2C->I2C_Report_Receive_OverFlow;
        I2C_Report_Write_Collision = _I2C->I2C_Report_Write_Collision;
        /* This routine enable the interrupt feature for I2C module  */
        MCCP_I2C_INTERRUPT_ENABLE();
        MCCP_I2C_BUS_COL_INTERRUPT_ENABLE();
#endif  
        ret = E_OK;
    }

    return ret;
}
#endif

#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void MSSP_I2C_ISR(void){
    MCCP_I2C_INTERRUPT_FLAG_CLEAR();
    if(I2C_DefaultInterruptHandler) I2C_DefaultInterruptHandler();
}
#endif

#if INTERRUPT_MCCP_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void MSSP_I2C_BC_ISR(void){
    MCCP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR();
    if(I2C_Report_Write_Collision) I2C_Report_Write_Collision();
}
#endif