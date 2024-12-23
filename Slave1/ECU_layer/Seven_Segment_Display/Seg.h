/* 
 * File:   7Seg.h
 * Author: hp
 *
 * Created on 22 February 2024, 20:49
 */

#ifndef SEG_H
#define	SEG_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "Seg_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define SEGMENT_PIN1  0
#define SEGMENT_PIN2  1
#define SEGMENT_PIN3  2
#define SEGMENT_PIN4  3


/* ----------------- Macro Functions Declarations -----------------*/



/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    SEGMENT_COMMON_ANODE=0,
    SEGMENT_COMMON_CATHODE        
}Segment_type_t;

typedef struct{
    pinConfig_t Segment_pins[4];
    Segment_type_t Segment_type;
}Segment_Config_t;


/* ----------------- Software Interfaces Declarations -----------------*/
STD_ReturnType ECU_Segment_initialize(const Segment_Config_t *_Segment);
STD_ReturnType ECU_Segment_write(const Segment_Config_t *_Segment, uint8 Segment_write);

#endif	/* SEG_H */

