/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef LCD_H
#define	LCD_H

/* includes */
#include "LCD_cfg.h"
#include "./../../MCAL_layer/GPIO/hal_gpio.h"

/* Macros declarations */
#define _LCD_CLEAR                                0x01
#define _LCD_RETURN_HOME                          0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF             0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON              0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF             0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON              0x07

#define _LCD_DISPLAY_OFF                          0x08

#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSER_ON    0x0F
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_ON   0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSER_OFF   0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_OFF  0x0C

#define _LCD_MOVE_CURSER_OFF_RIGHT_SHIFT          0x17
#define _LCD_MOVE_CURSER_OFF_LEFT_SHIFT           0x13
#define _LCD_MOVE_CURSER_ON_LEFT_SHIFT            0x1B
#define _LCD_MOVE_CURSER_ON_RIGHT_SHIFT           0x1F

#define _LCD_8BIT_MODE_2_LINES                    0x38
#define _LCD_4BIT_MODE_2_LINES                    0x28

#define _LCD_CGRAM_START                          0x40
#define _LCD_DDRAM_START                          0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* MACROS Functions declarations */


/* Data types declarations */
typedef struct{
    pinConfig_t LCD_RS;
    pinConfig_t LCD_E;
    pinConfig_t DataPins[4];
}LCD_Config_4Bit_Mode_t;

typedef struct{
    pinConfig_t LCD_RS;
    pinConfig_t LCD_E;
    pinConfig_t DataPins[8];
}LCD_Config_8Bit_Mode_t;


/* Functions declarations */
STD_ReturnType ECU_LCD_4Bit_Initialize                  (const LCD_Config_4Bit_Mode_t *_LCD);
STD_ReturnType ECU_LCD_4Bit_Send_Command                (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Command);
STD_ReturnType LCD_4Bits_Set_Curser                     (const LCD_Config_4Bit_Mode_t *_LCD, uint8 row, uint8 coloumn);
STD_ReturnType ECU_LCD_4Bit_Send_char_Data              (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Data);
STD_ReturnType ECU_LCD_4Bit_Send_char_Data_Position     (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 _Data);
STD_ReturnType ECU_LCD_4Bit_Send_String_Data            (const LCD_Config_4Bit_Mode_t *_LCD, uint8 *_Str);
STD_ReturnType ECU_LCD_4Bit_Send_String_Data_Postition  (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 *_Str);
STD_ReturnType ECU_LCD_4Bit_Send_Custom_Char            (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn,
                                                          const uint8 _Char[], uint8 mem_pos);

STD_ReturnType ECU_LCD_8Bit_Initialize                  (const LCD_Config_8Bit_Mode_t *_LCD);
STD_ReturnType ECU_LCD_8Bit_Send_Command                (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Command);
STD_ReturnType ECU_LCD_8Bit_Send_char_Data              (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Data);
STD_ReturnType ECU_LCD_8Bit_Send_char_Data_Position     (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 _Data);
STD_ReturnType ECU_LCD_8Bit_Send_String_Data            (const LCD_Config_8Bit_Mode_t *_LCD, uint8 *_Str);
STD_ReturnType ECU_LCD_8Bit_Send_String_Data_Postition  (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 *_Str);
STD_ReturnType ECU_LCD_8Bit_Send_Custom_Char            (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn,
                                                          const uint8 _Char[], uint8 mem_pos);      

STD_ReturnType Convert_uint8_to_string (uint8 _Value,  uint8 *_String);
STD_ReturnType Convert_uint16_to_string(uint16 _Value, uint8 *_String);
STD_ReturnType Convert_uint32_to_string(uint32 _Value, uint8 *_String);

 

#endif	/* LCD_H */

