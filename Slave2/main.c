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

volatile uint8 LDR_Get_Data;
STD_ReturnType ret;


// LCD display configurations
LCD_Config_4Bit_Mode_t LCD_1 = {
  .DataPins[0].pin =  pin6,
  .DataPins[0].port =  portD,
  .DataPins[0].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[0].logic = GPIO_Pin_Logic_LOW,
  
  .DataPins[1].pin =  pin7,
  .DataPins[1].port =  portD,
  .DataPins[1].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[1].logic = GPIO_Pin_Logic_LOW,
  
  .DataPins[2].pin =  pin0,
  .DataPins[2].port =  portE,
  .DataPins[2].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[2].logic = GPIO_Pin_Logic_LOW,
  
  .DataPins[3].pin =  pin1,
  .DataPins[3].port =  portE,
  .DataPins[3].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[3].logic = GPIO_Pin_Logic_LOW, 

  .LCD_E.pin =  pin5,
  .LCD_E.port =  portD,
  .LCD_E.direction = GPIO_Pin_Direction_OUTPUT,
  .LCD_E.logic = GPIO_Pin_Logic_LOW,
  
  
  .LCD_RS.pin =  pin4,
  .LCD_RS.port =  portD,
  .LCD_RS.direction = GPIO_Pin_Direction_OUTPUT,
  .LCD_RS.logic = GPIO_Pin_Logic_LOW,
};
// Keypad configurations
KeyPad_t keypad_1 = {
  .KeypadRowsConfig[0].port = portC,
  .KeypadRowsConfig[0].pin = pin0,
  .KeypadRowsConfig[0].direction = GPIO_Pin_Direction_OUTPUT,
  .KeypadRowsConfig[0].logic = GPIO_Pin_Logic_LOW,
  .KeypadRowsConfig[1].port = portC,
  .KeypadRowsConfig[1].pin = pin1,
  .KeypadRowsConfig[1].direction = GPIO_Pin_Direction_OUTPUT,
  .KeypadRowsConfig[1].logic = GPIO_Pin_Logic_LOW,
  .KeypadRowsConfig[2].port = portC,
  .KeypadRowsConfig[2].pin = pin2,
  .KeypadRowsConfig[2].direction = GPIO_Pin_Direction_OUTPUT,
  .KeypadRowsConfig[2].logic = GPIO_Pin_Logic_LOW,
  .KeypadRowsConfig[3].port = portC,
  .KeypadRowsConfig[3].pin = pin5,
  .KeypadRowsConfig[3].direction = GPIO_Pin_Direction_OUTPUT,
  .KeypadRowsConfig[3].logic = GPIO_Pin_Logic_LOW,
  
  .KeypadColoumnsConfig[0].port = portD,
  .KeypadColoumnsConfig[0].pin = pin1,
  .KeypadColoumnsConfig[0].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[0].logic = GPIO_Pin_Logic_LOW,
  .KeypadColoumnsConfig[1].port = portD,
  .KeypadColoumnsConfig[1].pin = pin2,
  .KeypadColoumnsConfig[1].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[1].logic = GPIO_Pin_Logic_LOW,
  .KeypadColoumnsConfig[2].port = portD,
  .KeypadColoumnsConfig[2].pin = pin3,
  .KeypadColoumnsConfig[2].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[2].logic = GPIO_Pin_Logic_LOW,  
};
// Gate DC motor configurations
DC_Motor_t Dc_Motor_Gate = {
  .dc_motor_pin[0].port = portC,
  .dc_motor_pin[0].pin = pin6,
  .dc_motor_pin[0].direction = GPIO_Pin_Direction_OUTPUT,
  .dc_motor_pin[0].logic = GPIO_Pin_Logic_LOW,
          
  .dc_motor_pin[1].port = portC,
  .dc_motor_pin[1].pin = pin7,
  .dc_motor_pin[1].direction = GPIO_Pin_Direction_OUTPUT,
  .dc_motor_pin[1].logic = GPIO_Pin_Logic_LOW  
};
// LEDs configurations
LED_Config_t RED_LED  = {.port_name = portB, .pin_name = pin7, .led_logic = GPIO_Pin_Logic_LOW};
LED_Config_t GREEN_LED = {.port_name = portE, .pin_name = pin2, .led_logic = GPIO_Pin_Logic_LOW};

// I2C ISR
void I2C_DefaultInterruptHandler(void){
	// Get illumination intensity from master
    LDR_Get_Data = SSPBUF;
}
// Indoor lamp configurations
pinConfig_t InDoor_E = {
  .port = portD,
  .pin = pin0,
  .direction = GPIO_Pin_Direction_OUTPUT,
  .logic = GPIO_Pin_Logic_LOW
};

// Wrong password handling
void WrongPassword(void){
    ret = LED_turnON(&RED_LED);
    ret = LED_turnOFF(&GREEN_LED);
    ret = ECU_DC_Motor_stop(&Dc_Motor_Gate);
    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW1, 3, "Wrong password!!!");
    __delay_ms(500);
    while(1){
        ret = ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_CLEAR);
    }
}

uint8 NumberPressed='\0',LCD_curser=0,currentPassword[7],correctPassword[7]= {'1','3','9','5','4','4','7'},iter;
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
    //INTERRUPT_PeripheralInterruptDisable();
    
    // I2C module initialize
    I2C_Open();
    I2C_SlaveSetReadIntHandler(I2C_DefaultInterruptHandler);
    
	// Hardware components initialization
    ret = ECU_LCD_4Bit_Initialize(&LCD_1);
    ret = keyPad_Initialize(&keypad_1);
    ret = ECU_DC_Motor_initialize(&Dc_Motor_Gate);
    ret = LED_init(&RED_LED);
    ret = LED_init(&GREEN_LED);
    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW1, 3, "Enter the password");
    // GPIO module initialize
    ret = gpio_pin_initialize(&InDoor_E);

    while (1)
    {
        NumberPressed = '\0';
		// polling to read character from keypad entered by the user
        while(NumberPressed == '\0'){
			// Get the entered character on keypad
            ret = keyPad_Read(&keypad_1, &NumberPressed);
            
			// Check if LDR value get from master is more than or equal to 130
            if(130 <= LDR_Get_Data){
				// Turn off Indoor illumination
                ret = gpio_pin_write_logic(&InDoor_E, GPIO_Pin_Logic_LOW);
            }
			// Check if LDR value get from master is less than 130
            else if(130 > LDR_Get_Data){
				// Turn on Indoor illumination
                ret = gpio_pin_write_logic(&InDoor_E, GPIO_Pin_Logic_HIGH);
            }
            else{/*Do nothing*/}
        }
        while(NumberPressed !='\0'){
			
            // Check if LDR value get from master is more than or equal to 130
            if(130 <= LDR_Get_Data){
				// Turn off Indoor illumination
                ret = gpio_pin_write_logic(&InDoor_E, GPIO_Pin_Logic_LOW);
            }
			// Check if LDR value get from master is less than 130
            else if(130 > LDR_Get_Data){
				// Turn on Indoor illumination
                ret = gpio_pin_write_logic(&InDoor_E, GPIO_Pin_Logic_HIGH);
            }
            else{/*Do nothing*/}
            __delay_ms(550);
			// Store number character gotten by user on array 
            currentPassword[LCD_curser] = NumberPressed;
			// Show * on LCD display with each character entered by user
            ret = ECU_LCD_4Bit_Send_char_Data_Position(&LCD_1, ROW2, LCD_curser+2, '*');
			// Increase LCD curser
            LCD_curser++;
            __delay_ms(250);
            NumberPressed = '\0';
        }
		// Check if character no. gotten by user is equal to 7 (end of password)
        if(7 == LCD_curser){
			// Clear LCD
            ret = ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_CLEAR);
            __delay_ms(10);
			// Iterate on password characters array to verify password
            for(iter = 0 ;iter < LCD_curser ; iter++){
				// check if any character entered by user isn't identical to any correct password character
                if(currentPassword[iter] != correctPassword[iter]){
					// go to wrong password handler
                    WrongPassword();
                }
            }
            // if password entered by user is correct 
			// Turn off red LED
            ret = LED_turnOFF(&RED_LED);
			// Turn on green LED
            ret = LED_turnON(&GREEN_LED);
			// Operate DC motor to open the gate 
            ret = ECU_DC_Motor_move_right(&Dc_Motor_Gate);
            __delay_ms(1500);
			// Disable  DC motor after opening the gate
            ret = ECU_DC_Motor_stop(&Dc_Motor_Gate);
        }
        
       
        // Add your application code
    }
}
/**
 End of File
*/