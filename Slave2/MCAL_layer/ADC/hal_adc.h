/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupts.h"
#include "hal_adc_cfg.h"

/* Macros declarations */

/**
 *  @berief Analog-To-Digital port configuration
 *  @note When ADC_AN4_ANALOG_FUNCTIONALITY is onfigured, this means 
 *        AN4, AN3, AN2, AN1, and AN0 are analog functionality
 */
#define ADC_ANO_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F



#define ADC_CONVERSION_COMPLETED  0x01U
#define ADC_CONVERSION_INPROGRESS 0x01U

/* MACROS Functions declarations */

/**
 *   @berief Get the status of Analog-To-Digital conversion
 */
#define ADC_CONVERSION_STATUS()   (ADCON0bits.GO_nDONE)

/**
 *  @berief Start Analog-To-Digital conversion
 */
#define ADC_CONVERSION_START()    (ADCON0bits.GODONE = 1)

/**
 *   @berief Analog-To-Digital control
 *   @note ADC_CONVERSION_ENABLE():  Enable Analog-To-Digital
 *         ADC_CONVERSION_DISABLE(): Disable Analog-To-Digital
 */
#define ADC_CONVERSION_ENABLE()    (ADCON0bits.ADON = 1)
#define ADC_CONVERSION_DISABLE()   (ADCON0bits.ADON = 0)

/**
 *   @berief Analog-To-Digital voltage reference configuration
 *   @note ADC_ENABLE_VOLTAGE_REFERENCE(): Voltage reference is VREFF- and VREFF+
 *         ADC_DISABLE_VOLTAGE_REFERENCE(): Voltage reference is VSS and VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()  do{ ADCON1bits.VCFG0 = 1;\
                                            ADCON1bits.VCFG1 = 1;\
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE()  do{ ADCON1bits.VCFG0 = 0;\
                                            ADCON1bits.VCFG1 = 0;\
                                        }while(0)

/**
 *   @berief Analog-To-Digital port configuration control
 *   @note   Example: ADC_ANALOG_DIGITAL_PORT_COFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *           When ADC_AN4_ANALOG_FUNCTIONALITY is onfigured, this means 
 *           AN4, AN3, AN2, AN1, and AN0 are analog functionality
 *   @ref    Analog-To-Digital port configuration
 */
#define ADC_ANALOG_DIGITAL_PORT_COFIG(__CONFIG)  (ADCON1bits.PCFG = __CONFIG)

/**
 *   @berief A/D Result configuration
 *   @note ADC_RESULT_RIGHT_FORMAT(): A/D Result right format
 *         ADC_RESULT_LEFT_FORMAT(): A/D Result left format
 */
#define ADC_RESULT_RIGHT_FORMAT()     (ADCON2bits.ADFM = 1) 
#define ADC_RESULT_LEFT_FORMAT()      (ADCON2bits.ADFM = 0) 

/* Data types declarations */

/**
 *   @berief A/D Channel selection 
 */
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12         
}ADC_Channel_t;

/**
 *   @berief A/D Acquisition Time Selection
 *   @note Acquisition time(Sampling time) is the time required for the ADC 
 *         to capture the input voltage during sampling 
 *   @note  Acquisition time of a Successive Approximation Register (SAR) ADC is the amount of time 
 *          required to charge the holding capacitor (CHOLD) on the front end of an ADC
 */
typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD       
}ADC_Acquisition_Time_t;

/**
 * @brief  A/D Conversion Clock Select
 * @note   If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) 
 *         is added before the A/D clock starts.
 * @note   This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum {
    ADC_CONVERSTION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_64,
}ADC_Conversion_CLK_t;

/**
 *   @berief A/D Voltage Reference selection 
 *   @note ADC_ENABLE_VOLTAGE_REFERENCE(): Voltage reference is VREFF- and VREFF+
 *         ADC_DISABLE_VOLTAGE_REFERENCE(): Voltage reference is VSS and VDD
 */
typedef enum {
    DISABLE_VOLTAGE_REFERENCE = 0,
    ENABLE_VOLTAGE_REFERENCE        
}ADC_Voltage_Reference_t;

/**
 *   @berief A/D Result_Format selection
 * 
 */
typedef enum {
    ADC_RESULT_FORMAT_LEFT = 0,
    ADC_RESULT_FORMAT_RIGHT        
}ADC_Result_Format_t;

/**
 *   @berief A/D Configuration
 */
typedef struct {
#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
    Interrupt_Priority_Config  Interrupt_Priority;
#endif
    ADC_Channel_t           Channel;
    ADC_Acquisition_Time_t  Acquisition_Time;
    ADC_Conversion_CLK_t    Conversion_Clock;
    ADC_Voltage_Reference_t Voltage_Reference;
    ADC_Result_Format_t     Result_Format;  
}ADC_Config_t;    

/**
 *   @berief A/D result data type
 */
typedef uint16 ADC_Result_t;


/* Functions declarations */

/**
 * 
 * @param _ADC_config
 * @return 
 */
STD_ReturnType ADC_Init (const ADC_Config_t *_ADC_config);

/**
 * 
 * @param _ADC_config
 * @return 
 */
STD_ReturnType ADC_Deinit (const ADC_Config_t *_ADC_config);

/**
 * 
 * @param _ADC_config
 * @param _ADC_Channel
 * @return 
 */
STD_ReturnType ADC_Select_Channel (const ADC_Config_t *_ADC_config, ADC_Channel_t _ADC_Channel);

/**
 * 
 * @param _ADC_config
 * @return 
 */
STD_ReturnType ADC_Start_Conversion (const ADC_Config_t *_ADC_config);

/**
 * 
 * @param _ADC_config
 * @param _Conversion_status
 * @return 
 */
STD_ReturnType ADC_Is_Conversion_Done (const ADC_Config_t *_ADC_config, uint8 *_Conversion_status);

/**
 * 
 * @param _ADC_config
 * @param _ADC_Result
 * @return 
 */
STD_ReturnType ADC_Conversion_Result (const ADC_Config_t *_ADC_config, ADC_Result_t *_ADC_Result);

/**
 * 
 * @param _ADC_config
 * @param _ADC_Channel
 * @param _ADC_Result
 * @return 
 */
STD_ReturnType ADC_Get_Conversion_Result_Block (const ADC_Config_t *_ADC_config, ADC_Channel_t _ADC_Channel,
                                                                                ADC_Result_t *_ADC_Result);

/**
 * 
 * @param _ADC_config
 * @param _ADC_Channel
 * @return 
 */
STD_ReturnType ADC_Start_Interrupt (const ADC_Config_t *_ADC_config, ADC_Channel_t _ADC_Channel);




#endif	/* HAL_ADC_H */

