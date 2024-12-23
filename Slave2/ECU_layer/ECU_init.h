/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef ECU_INIT_H
#define	ECU_INIT_H

/* includes */

#include "LED/ecu_led.h"
#include "Push_button/push_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/DC_Motor.h"
#include "Stepper_Motor/ecu_stepperMotor.h"
#include "Servo_Motor/ecu_servoMotor.h"
#include "Seven_Segment_Display/Seg.h"
#include "KeyPad/ecu_keyPad.h"
#include "LCD/LCD.h"
/* Macros declarations */


/* MACROS Functions declarations */


/* Data types declarations */

/* Functions declarations */
void LED_intialization(void);
void Push_Button_intialization(void);
void Relay_intialization(void);
void DC_Motor_intialization(void);
void Segment_intialization(void);
void KeyPad_intialization(void);
void LCD_intialization(void);




#endif	/* ECU_INIT_H */

