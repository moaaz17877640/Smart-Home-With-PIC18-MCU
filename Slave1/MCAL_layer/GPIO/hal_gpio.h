/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* includes */
#include "../mcal_std_types.h"
#include "Config.h"
#include <time.h>




/* Macros declarations */
#define Bit_mask   (uint8)1

#define maximumNumberOfPorts    5
#define maximumNumberOfPins     8


#define GPIO_Port_Pin_Configuration   config_Enable
#define GPIO_Port_Configuration       config_Enable

#define GPIO_Port_Mask   0xff

#define _XTAL_FREQ 8000000UL

/* MACROS Functions declarations */

#define HWREG8(_x)    (*(volatile uint8*)(_x))

#define setBit(Reg,Bit_position)     (Reg |= (Bit_mask<<Bit_position))
#define clearBit(Reg,Bit_position)   (Reg &= ~(Bit_mask<<Bit_position))
#define toggleBit(Reg,Bit_position)  (Reg ^= (Bit_mask<<Bit_position))
#define readBit(Reg,Bit_position)    ((Reg >> Bit_position) & Bit_mask)


/* Data types declarations */
typedef enum{
    GPIO_Pin_Logic_LOW=0,
    GPIO_Pin_Logic_HIGH
}logic_t;

typedef enum{
    GPIO_Pin_Direction_OUTPUT=0,
    GPIO_Pin_Direction_INPUT
}direction_t;

typedef enum{
    pin0=0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7
}pinIndex_t;

typedef enum{
    portA=0,
    portB,
    portC,
    portD,
    portE        
}portIndex_t;

typedef struct{
    uint8 port       : 3;
    uint8 pin        : 3;
    uint8 direction  : 1;
    uint8 logic      : 1;    
}pinConfig_t;

/* Functions declarations */

STD_ReturnType gpio_pin_direction_initialize (const pinConfig_t* pinConfig );
STD_ReturnType gpio_pin_get_direction_status (const pinConfig_t* pinConfig, direction_t* getDirection );

STD_ReturnType gpio_pin_write_logic   (const pinConfig_t* pinConfig, logic_t logic );
STD_ReturnType gpio_pin_read_logic    (const pinConfig_t* pinConfig, logic_t* logic );
STD_ReturnType gpio_pin_toggle_logic  (const pinConfig_t* pinConfig);
STD_ReturnType gpio_pin_initialize    (const pinConfig_t* pinConfig);

STD_ReturnType gpio_port_direction_initialize   (portIndex_t port, uint8  direction  );
STD_ReturnType gpio_port_get_direction_status   (portIndex_t port, uint8* direction  );
STD_ReturnType gpio_port_write_logic            (portIndex_t port, uint8 logic );
STD_ReturnType gpio_port_read_logic             (portIndex_t port, uint8* logic );
STD_ReturnType gpio_port_toggle_logic           (portIndex_t port);

#endif	/* HAL_GPIO_H */

