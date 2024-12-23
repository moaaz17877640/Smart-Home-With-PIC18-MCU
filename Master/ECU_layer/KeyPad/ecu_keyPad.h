/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H


/* includes */
#include "ecu_keyPad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Macros declarations */
#define  ECU_KEYPAD_ROWS     4
#define  ECU_KEYPAD_COLOUMNS 4


/* MACROS Functions declarations */


/* Data types declarations */
typedef struct{
    pinConfig_t KeypadRowsConfig[ECU_KEYPAD_ROWS];
    pinConfig_t KeypadColoumnsConfig[ECU_KEYPAD_COLOUMNS];
}KeyPad_t;

/* Functions declarations */
STD_ReturnType keyPad_Initialize(const KeyPad_t *keypad);
STD_ReturnType keyPad_Read(const KeyPad_t *keypad, uint8 *keypad_value);


#endif	/* ECU_KEYPAD_H */

