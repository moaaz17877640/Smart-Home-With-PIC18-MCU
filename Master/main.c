/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
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

// Control buttons of clock system UI
#define KEY_LEFT '#'
#define KEY_RIGHT '='
#define KEY_ENTER '+'
#define KEY_START '-'

REALTIMECLOCK_DS1307_t  REALTIMECLOCK_DS1307;
STD_ReturnType ret;
unsigned char time_array[6] = {0, 0, 0, 0, 0, 0};  
uint8_t TemperatureSensor_TC74_Read_Value;
uint8_t LDR_Read_Value;
void Timer0_DefaultInterruptHandler(void);
void Dashboard(void);

// LCD configurations
LCD_Config_4Bit_Mode_t LCD_1 = {
  .DataPins[0].pin =  pin4,
  .DataPins[0].port =  portD,
  .DataPins[0].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[0].logic = GPIO_Pin_Logic_LOW,
  
  .DataPins[1].pin =  pin5,
  .DataPins[1].port =  portD,
  .DataPins[1].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[1].logic = GPIO_Pin_Logic_LOW,
  
  .DataPins[2].pin =  pin6,
  .DataPins[2].port =  portD,
  .DataPins[2].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[2].logic = GPIO_Pin_Logic_LOW,
  
  .DataPins[3].pin =  pin7,
  .DataPins[3].port =  portD,
  .DataPins[3].direction = GPIO_Pin_Direction_OUTPUT,
  .DataPins[3].logic = GPIO_Pin_Logic_LOW, 

  .LCD_E.pin =  pin0,
  .LCD_E.port =  portE,
  .LCD_E.direction = GPIO_Pin_Direction_OUTPUT,
  .LCD_E.logic = GPIO_Pin_Logic_LOW,
  
  
  .LCD_RS.pin =  pin3,
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
  .KeypadColoumnsConfig[0].pin = pin0,
  .KeypadColoumnsConfig[0].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[0].logic = GPIO_Pin_Logic_LOW,
  .KeypadColoumnsConfig[1].port = portD,
  .KeypadColoumnsConfig[1].pin = pin1,
  .KeypadColoumnsConfig[1].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[1].logic = GPIO_Pin_Logic_LOW,
  .KeypadColoumnsConfig[2].port = portD,
  .KeypadColoumnsConfig[2].pin = pin2,
  .KeypadColoumnsConfig[2].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[2].logic = GPIO_Pin_Logic_LOW,  
  .KeypadColoumnsConfig[3].port = portE,
  .KeypadColoumnsConfig[3].pin = pin1,
  .KeypadColoumnsConfig[3].direction = GPIO_Pin_Direction_INPUT,
  .KeypadColoumnsConfig[3].logic = GPIO_Pin_Logic_LOW
};
// Timer0 module configurations
Timer0_t timer0_1 = {
    .TIMER0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .Timer0_InterruptPriority = INTERRUPT_HIGH_PRIORITY,
    .Timer0_mode = TIMER0_TIMER_MODE,
    .Timer0_Prescaler_Value = TIMER0_PRESCALER_VALUE_DIV_16,
    .Timer0_preloadValue = 3036,
    .Timer0_prescalerConfig = TIMER0_PRESCALER_IS_ASSIGNED,
    .Timer0_registerSize = TIMER0_16BIT_TIMER_COUNTER,
    .Timer0_counterEdge = TIMER0_COUNTER_HIGH_TO_LOW_INC
};
// ADC module configurations
ADC_Config_t ADC_LDR = {
    .ADC_InterruptHandler = NULL,
    .Acquisition_Time = ADC_12_TAD,
    .Conversion_Clock = ADC_CONVERSTION_CLOCK_FOSC_DIV_4,
    .Channel = ADC_CHANNEL_AN0,
    .Voltage_Reference = DISABLE_VOLTAGE_REFERENCE,
    .Result_Format = ADC_RESULT_FORMAT_RIGHT
};
// Buzzer configurations
pinConfig_t Buzz =  {
    .port = portE,
    .pin = pin2,
    .direction = GPIO_Pin_Direction_OUTPUT,
    .logic = GPIO_Pin_Logic_LOW
};

// Display Clock value on LCD display
void update_display() {
    ret = ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_ON);
    ret = LCD_4Bits_Set_Curser(&LCD_1, ROW1,1);
    // Display time in HH:MM:SS format
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, time_array[0] + '0');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, time_array[1] + '0');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, ':');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, time_array[2] + '0');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, time_array[3] + '0');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, ':');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, time_array[4] + '0');
    ret = ECU_LCD_4Bit_Send_char_Data(&LCD_1, time_array[5] + '0');
    
    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1,ROW2,6, "Stop Watch");
    ret = LCD_4Bits_Set_Curser (&LCD_1, ROW1,9);
}

uint8 NumberPressed='\0';
uint8 nextBack= '\0', userInput = '\0',curserPos = 9 , seconds = 0, minutes = 0, hours = 0, exit_alarm = 0 ,exit_Clock = '\0';
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
	
	// Initialize hardware components
    ret = gpio_pin_initialize(&Buzz);
    ret = ECU_LCD_4Bit_Initialize(&LCD_1);
    ret = keyPad_Initialize(&keypad_1);
    ret = ADC_Init (&ADC_LDR);

    
    Dashboard();

    while (1)
    {
        
        
        NumberPressed = '\0';
		// Get the choice from user (Clock or Alarm)
        while(NumberPressed == '\0'){
			// Get user choice from keypad
            ret = keyPad_Read(&keypad_1, &NumberPressed);
            
			// Get temperature from temperature sensor(DS1307)
            TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
			// Send temperature to Slave 1 via I2C protocol
            I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
            __delay_ms(100);
            
			// Get light intensity from LDR sensor
            ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
			// Send light intensity to Slave 2 via I2c protocol
            I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
            __delay_ms(100);
             
			 // Check if Alarm counter reach to zero
            if(seconds == 0 && minutes == 0 && hours == 0){
				// De-initialize Timer0 if Alarm counter reach to zero
                ret = Timer0_Deinit (&timer0_1);
            }   
        }
        if( NumberPressed != '\0'){
			// Switch for clock system user input
            switch(NumberPressed){
				// if user clicks on clock choice
            case '1':
				// Clear LCD display
                ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_CLEAR);
                __delay_ms(10);
                // Get temperature from temperature sensor(DS1307)
                TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
				// Send temperature to Slave 1 via I2C protocol
                I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                __delay_ms(100);
                // Get light intensity from LDR sensor
                ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
				// Send light intensity to Slave 2 via I2c protocol
                I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                __delay_ms(100);
            
                exit_Clock = '\0';
				// Set Curser off in clock mode
                ret = ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_OFF);
                while(exit_Clock != '1'){
                    // Get temperature from temperature sensor(DS1307)
                    TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
					// Send temperature to Slave 1 via I2C protocol
                    I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                    __delay_ms(50);
                    // Get light intensity from LDR sensor
                    ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
					// Send light intensity to Slave 2 via I2c protocol
                    I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                    __delay_ms(50);
                    // Get exit_Clock value to exit clock mode 
                    ret = keyPad_Read(&keypad_1, &exit_Clock);
					 // Get clock and date data from RealTimeClock_DS1307 sensor
                    REALTIMECLOCK_DS1307 = REALTIMECLOCK_DS1307_Get_Data();
                    __delay_ms(50);
					// Print clock and date data on LCD display
                    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW2, 1,REALTIMECLOCK_DS1307_print_Data());
                    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW4, 1,"1: Back");
                }
				// check whether exit_Clock == 1 or not
                if(exit_Clock != '\0'){
					// if exit_Clock = 1 clear LCD display and show dashboard 
                    ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_CLEAR);
                    __delay_ms(10);
                    Dashboard();
                }
                
                break;
				// if user clicks on alarm choice
            case '2':
				// Clear LCD display
                ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_CLEAR);
                __delay_ms(10);
                exit_alarm = 1;
				// Show Alarm mode UI on LCD display
                update_display();
                ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW4, 1,"1: Back");
                while(exit_alarm != '1'){
                    // Get temperature from temperature sensor(DS1307)
                    TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
					// Send temperature to Slave 1 via I2C protocol
                    I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                    __delay_ms(100);
                    // Get light intensity from LDR sensor
                    ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
					// Send light intensity to Slave 2 via I2c protocol
                    I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                     __delay_ms(100);
            
                    while(nextBack == '\0'){
                        // Get temperature from temperature sensor(DS1307)
                        TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
						// Send temperature to Slave 1 via I2C protocol
                        I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                        __delay_ms(100);
						// Get light intensity from LDR sensor
                        ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
						// Send light intensity to Slave 2 via I2c protocol
                        I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                        __delay_ms(100);
                        // Check if Alarm counter reach to zero
                        if(seconds == 0 && minutes == 0 && hours == 0){
							// De-initialize Timer0 if Alarm counter reach to zero
                            ret = Timer0_Deinit (&timer0_1);
							// check whether exit_alarm == 12 or not
                            if(exit_alarm == 12)
							// Operate the buzzer
                            ret = gpio_pin_write_logic(&Buzz, GPIO_Pin_Logic_HIGH);
                        }   
						// Get value of Alarm curser 
                        ret = keyPad_Read(&keypad_1, &nextBack);
						// Get value of exit_alarm to exit when finishing
                        ret = keyPad_Read(&keypad_1, &exit_alarm);
                        __delay_ms(100);
						// check whether exit_alarm == 1 or not
                        if(exit_alarm == '1'){
							// Disabel the buzzer
                            ret = gpio_pin_write_logic(&Buzz, GPIO_Pin_Logic_LOW);
							// Clear LCD display
                            ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_CLEAR);
                            __delay_ms(10);
							// Set Curser off in Dashboard 
                            ret = ECU_LCD_4Bit_Send_Command(&LCD_1, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_OFF);
                            Dashboard();
                        }
                    }
                    while(nextBack != '\0'){
                        // Get temperature from temperature sensor(DS1307)
                        TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
						// Send temperature to Slave 1 via I2C protocol
                        I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                        __delay_ms(100);
                        // Get light intensity from LDR sensor
                        ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
						// Send light intensity to Slave 2 via I2c protocol
                        I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                        __delay_ms(100);
                        
                        if (nextBack == KEY_LEFT){
							// Move curser to left on LCD display
                            if (curserPos > 0) {
                                curserPos--;
                                if(curserPos == 3 || curserPos == 6){
                                    curserPos--;
                                }
                                ret = LCD_4Bits_Set_Curser (&LCD_1, ROW1,curserPos);
                                __delay_ms(200);
                                nextBack = '\0';
                        }
                        nextBack = '\0';
                        }
                        else if (nextBack == KEY_RIGHT){
							// Move curser to right on LCD display
                            if (curserPos < 8) {
                                curserPos++;
                                if(curserPos == 3 || curserPos == 6){
                                    curserPos++;
                                }
                                ret = LCD_4Bits_Set_Curser (&LCD_1, ROW1,curserPos);
                                __delay_ms(200);
                                nextBack = '\0';
                            }
                            nextBack = '\0';
                        }
                        else if(nextBack == KEY_ENTER){
                            __delay_ms(200);
                            while(userInput == '\0'){
                                // Get temperature from temperature sensor(DS1307)
                                TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
								// Send temperature to Slave 1 via I2C protocol
                                I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                               __delay_ms(100);
                               // Get light intensity from LDR sensor
                               ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
							   // Send light intensity to Slave 2 via I2c protocol
                                I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                                __delay_ms(100);
                                // Get the entered number from user
                                ret = keyPad_Read(&keypad_1, &userInput);
                            }
                            if (userInput >= '0' && userInput <= '9') {  // Validate that the input is a number
								// Check the curser position and show the updated number on it
                                if (curserPos == 1) {
                                    time_array[0] = userInput - '0';
                                    nextBack = '\0';
                                    userInput = '\0';
                                    update_display();
                                    __delay_ms(200);
                                } else if (curserPos == 2) {
                                    time_array[1] = userInput - '0';
                                    nextBack = '\0';
                                    userInput = '\0';
                                    update_display();
                                    __delay_ms(200);
                                } else if (curserPos == 4) {
                                    if(userInput > '5'){
                                        userInput  = '5';
                                    }
                                    time_array[2] = userInput - '0';
                                    nextBack = '\0';
                                    userInput = '\0';
                                    update_display();
                                    __delay_ms(200);
                                } else if (curserPos == 5) {
                                    time_array[3] = userInput - '0';
                                    nextBack = '\0';
                                    userInput = '\0';
                                    update_display();
                                    __delay_ms(200);
                                } else if (curserPos == 7) {
                                    if(userInput > '5'){
                                        userInput  = '5';
                                    }
                                    time_array[4] = userInput - '0';
                                    nextBack = '\0';
                                    userInput = '\0';
                                    update_display();
                                    __delay_ms(200);
                                } else if (curserPos == 8) {
                                    time_array[5] = userInput - '0';
                                    nextBack = '\0';
                                    userInput = '\0';
                                    update_display();
                                    __delay_ms(200);
                                }
                                else{
                                    /*Do nothing*/
                                }     
                            }
                            nextBack = '\0';
                            userInput = '\0';
							
							// Store Data to send it to Timer0 ISR
                            seconds = time_array[4]*10 + time_array[5];
                            minutes = time_array[2]*10 + time_array[3];
                            hours = time_array[0]*10 + time_array[1];
                            __delay_ms(200);

                        }
						// check whether start button is clicked or not
                        else if(nextBack == KEY_START){

							// Get temperature from temperature sensor(DS1307)
                            TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
							// Send temperature to Slave 1 via I2C protocol
                            I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
                            __delay_ms(100);
                            // Get light intensity from LDR sensor
                            ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
							// Send light intensity to Slave 2 via I2c protocol
                            I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
                             __delay_ms(100);   
                            // Timer0 initialize in case of Clicking on button start on keypad
                            ret = Timer0_Init (&timer0_1);
							// Set exit_alarm = 12 so buzzer can be operated when alarm counter reach to zero
                            exit_alarm = 12;
                            nextBack = '\0';
                        }
                        else{
                                nextBack = '\0';
                        }
                    }
                }
                
                break;
                default:/*Do nothing*/;
        }   }
    }
        
        
        
        // Add your application code
}


// Timer0 ISR 
void Timer0_DefaultInterruptHandler(void){
    if(seconds ==0){
        seconds = 60 ;
        if(minutes ==0){
            minutes = 60 ;
            hours--;
        }
        minutes--;
    }
    seconds--;
    time_array[4] = seconds /10;
    time_array[5] = seconds % 10;
    time_array[2] = minutes /10;
    time_array[3] = minutes % 10;
    time_array[0] = hours /10;
    time_array[1] = hours %10;
    // Show counter values after updating
    update_display(); 
}

// Clock system UI
void Dashboard(void){
    // Get temperature from temperature sensor(DS1307)
    TemperatureSensor_TC74_Read_Value = TemperatureSensor_TC74_Read_Temp(0x92);
	// Send temperature to Slave 1 via I2C protocol
    I2C_Write1ByteRegister(0x70, 0x00, TemperatureSensor_TC74_Read_Value);
    __delay_ms(100);
    // Get light intensity from LDR sensor
    ret = ADC_Get_Conversion_Result_Block (&ADC_LDR, ADC_CHANNEL_AN0, &LDR_Read_Value);
	// Send light intensity to Slave 2 via I2c protocol
    I2C_Write1ByteRegister(0x50, 0x00, LDR_Read_Value);
    __delay_ms(100);
            
    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW1, 1, "1: Clock");
    ret = ECU_LCD_4Bit_Send_String_Data_Postition(&LCD_1, ROW2, 1,"2: Alarm");
}