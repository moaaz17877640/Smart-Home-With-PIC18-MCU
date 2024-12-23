/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K20
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "application.h"

/*
                         Main application
 */


volatile uint8_t TemperatureSensor_GetValue;
STD_ReturnType ret;
Button_status_t outDoor_Status;

// First Seven segment display configurations  
Segment_Config_t SevenSeG = {
  .Segment_pins[0].port = portD,
  .Segment_pins[0].pin = pin0,
  .Segment_pins[0].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[0].logic = GPIO_Pin_Logic_LOW,
  .Segment_pins[1].port = portD,
  .Segment_pins[1].pin = pin1,
  .Segment_pins[1].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[1].logic = GPIO_Pin_Logic_LOW,
  .Segment_pins[2].port = portD,
  .Segment_pins[2].pin = pin2,
  .Segment_pins[2].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[2].logic = GPIO_Pin_Logic_LOW,
  .Segment_pins[3].port = portD,
  .Segment_pins[3].pin = pin3,
  .Segment_pins[3].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[3].logic = GPIO_Pin_Logic_LOW,
  .Segment_type = SEGMENT_COMMON_ANODE
};
// Second Seven segment display configurations  
Segment_Config_t SevenSeG_2 = {
  .Segment_pins[0].port = portC,
  .Segment_pins[0].pin = pin6,
  .Segment_pins[0].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[0].logic = GPIO_Pin_Logic_LOW,
  .Segment_pins[1].port = portC,
  .Segment_pins[1].pin = pin7,
  .Segment_pins[1].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[1].logic = GPIO_Pin_Logic_LOW,
  .Segment_pins[2].port = portE,
  .Segment_pins[2].pin = pin0,
  .Segment_pins[2].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[2].logic = GPIO_Pin_Logic_LOW,
  .Segment_pins[3].port = portE,
  .Segment_pins[3].pin = pin1,
  .Segment_pins[3].direction = GPIO_Pin_Direction_OUTPUT,
  .Segment_pins[3].logic = GPIO_Pin_Logic_LOW,
  .Segment_type = SEGMENT_COMMON_ANODE
};
// Heater Dc motor configurations
DC_Motor_t Heater = {
  .dc_motor_pin[0].port = portC,
  .dc_motor_pin[0].pin = pin0,
  .dc_motor_pin[0].direction = GPIO_Pin_Direction_OUTPUT,
  .dc_motor_pin[0].logic = GPIO_Pin_Logic_LOW,
          
  .dc_motor_pin[1].port = portC,
  .dc_motor_pin[1].pin = pin1,
  .dc_motor_pin[1].direction = GPIO_Pin_Direction_OUTPUT,
  .dc_motor_pin[1].logic = GPIO_Pin_Logic_LOW  
};
// Cooler Dc motor configurations
DC_Motor_t Cooler = {
  .dc_motor_pin[0].port = portC,
  .dc_motor_pin[0].pin = pin2,
  .dc_motor_pin[0].direction = GPIO_Pin_Direction_OUTPUT,
  .dc_motor_pin[0].logic = GPIO_Pin_Logic_LOW,
          
  .dc_motor_pin[1].port = portC,
  .dc_motor_pin[1].pin = pin5,
  .dc_motor_pin[1].direction = GPIO_Pin_Direction_OUTPUT,
  .dc_motor_pin[1].logic = GPIO_Pin_Logic_LOW  
};
// First Seven segment display enable bit configurations  
pinConfig_t SSD_E1 = {
  .port = portD,
  .pin = pin4,
  .direction = GPIO_Pin_Direction_OUTPUT,
  .logic = GPIO_Pin_Logic_LOW
};
// Second Seven segment display enable bit configurations  
pinConfig_t SSD_E2 = {
  .port = portD,
  .pin = pin5,
  .direction = GPIO_Pin_Direction_OUTPUT,
  .logic = GPIO_Pin_Logic_LOW
};
// Outdoor lamp configurations  
pinConfig_t OutDoor_lamp = {
  .port = portB,
  .pin = pin6,
  .direction = GPIO_Pin_Direction_OUTPUT,
  .logic = GPIO_Pin_Logic_LOW
};
// OutDoor illumination button configurations  
Button_Config_t  OutDoor_E = {
  .btn.port = portB,  
  .btn.pin = pin7,
  .btn.direction = GPIO_Pin_Direction_INPUT,
  .btn.logic = GPIO_Pin_Logic_LOW,
  .btn_connection = BUTTON_ACTIVE_HIGH,
  .btn_status = BUTTON_RELEASED
};
        
        
// LEDs configurations        
LED_Config_t RED_LED  = {.port_name = portD, .pin_name = pin6, .led_logic = GPIO_Pin_Logic_LOW };
LED_Config_t BLUE_LED = {.port_name = portD, .pin_name = pin7, .led_logic = GPIO_Pin_Logic_LOW };

// I2C ISR
void I2C_DefaultInterruptHandler(void){
	// Read temperatue sent by master
    TemperatureSensor_GetValue = SSPBUF;
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
//    INTERRUPT_PeripheralInterruptDisable();
    
	// I2C module Initialize
    I2C_Open();
    I2C_SlaveSetReadIntHandler(I2C_DefaultInterruptHandler);
    // Hardware components Initialize
    ret = gpio_pin_initialize(&SSD_E1);
    ret = gpio_pin_initialize(&SSD_E2);
    ret = gpio_pin_initialize(&OutDoor_lamp);
    ret = LED_init(&RED_LED);
    ret = LED_init(&BLUE_LED);
    ret = ECU_DC_Motor_initialize (&Heater);
    ret = ECU_DC_Motor_initialize (&Cooler);
    ret = ECU_Segment_initialize(&SevenSeG);
    ret = ECU_Segment_initialize(&SevenSeG_2);
    ret = ECU_Button_Intalize (&OutDoor_E);
    
    // GPIO module Initialize
    ret = gpio_pin_write_logic(&SSD_E1,GPIO_Pin_Logic_HIGH);
    ret = gpio_pin_write_logic(&SSD_E2,GPIO_Pin_Logic_HIGH);
     

    while (1)
    { 
        // Show temperature on the two Seven segment displays   
        ret = ECU_Segment_write(&SevenSeG,(uint8)(TemperatureSensor_GetValue/10));
        ret = ECU_Segment_write(&SevenSeG_2,(uint8)(TemperatureSensor_GetValue % 10));

         // check if temperature is less than 20 Celsius 
        if(20 > TemperatureSensor_GetValue){
			// operate Heater
            ret = ECU_DC_Motor_move_right(&Heater);
			// Disable Cooler
            ret = ECU_DC_Motor_stop(&Cooler);
			// Turn on red LED
            ret = LED_turnON (&RED_LED);
			// Turn off blue LED
            ret = LED_turnOFF (&BLUE_LED);
        }
		// check if temperature is between 20 and 30 Celsius
        else if(20 <= TemperatureSensor_GetValue && 30 > TemperatureSensor_GetValue){
			// Disable Heater
            ret = ECU_DC_Motor_stop(&Heater);
			// Disable Cooler
            ret = ECU_DC_Motor_stop(&Cooler);
			// Turn off red LED
            ret = LED_turnOFF (&RED_LED);
			// Turn off blue LED
            ret = LED_turnOFF (&BLUE_LED);
        }
		// check if temperature is more than or equal to 30 Celsius 
        else if(30 <= TemperatureSensor_GetValue){
			// Disable Heater
            ret = ECU_DC_Motor_stop(&Heater);
			// operate Cooler
            ret = ECU_DC_Motor_move_right(&Cooler);
			// Turn off red LED
            ret = LED_turnOFF (&RED_LED);
			// Turn on blue LED
            ret = LED_turnON (&BLUE_LED);
        }
        else{/*Do Nothing*/}
        
        // Read outdoor illumination button status
        ret = ECU_Button_Read(&OutDoor_E,  &outDoor_Status);
		// Check whether outdoor illumination button is pressed or released
        if(BUTTON_PRESSED == outDoor_Status){
			// Enable outdoor illumination
            gpio_pin_write_logic(&OutDoor_lamp,GPIO_Pin_Logic_HIGH);
        }
        else if(BUTTON_RELEASED == outDoor_Status){
			// Disbale outdoor illumination
            gpio_pin_write_logic(&OutDoor_lamp,GPIO_Pin_Logic_LOW);
        }
        else{/*Do nothing*/}

        // Add your application code
    }
}


