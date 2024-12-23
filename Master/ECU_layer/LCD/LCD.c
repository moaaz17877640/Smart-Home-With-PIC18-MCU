/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "LCD.h"

STD_ReturnType LCD_Send_4Bits               (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Data);
STD_ReturnType LCD_4Bits_Send_Enable_Signal (const LCD_Config_4Bit_Mode_t *_LCD);
STD_ReturnType LCD_4Bits_Set_Curser         (const LCD_Config_4Bit_Mode_t *_LCD, uint8 row, uint8 coloumn);
STD_ReturnType LCD_8Bits_Send_Enable_Signal (const LCD_Config_8Bit_Mode_t *_LCD);
STD_ReturnType LCD_8Bits_Set_Curser         (const LCD_Config_8Bit_Mode_t *_LCD, uint8 row, uint8 coloumn);


STD_ReturnType ECU_LCD_4Bit_Initialize (const LCD_Config_4Bit_Mode_t *_LCD){
    STD_ReturnType rt = E_NOT_OK;
    uint8 LCD_Counter = E_Zero_Init;
    if(NULL == _LCD ){
       rt = E_NOT_OK;
    }
    else{
        rt = gpio_pin_initialize(&(_LCD->LCD_E));
        rt = gpio_pin_initialize(&(_LCD->LCD_RS));
        for(LCD_Counter = E_Zero_Init; LCD_Counter<4 ; LCD_Counter++){
           rt = gpio_pin_initialize(&(_LCD->DataPins[LCD_Counter]));
        }
        __delay_ms(15);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_8BIT_MODE_2_LINES);
        __delay_ms(4.1);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_8BIT_MODE_2_LINES);
        __delay_us(100);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_8BIT_MODE_2_LINES);

        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_CLEAR);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_RETURN_HOME);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_OFF);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_4BIT_MODE_2_LINES);
        rt = ECU_LCD_4Bit_Send_Command(_LCD,_LCD_DDRAM_START);
    }
    
    return rt;
}

STD_ReturnType ECU_LCD_4Bit_Send_Command (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Command){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _LCD){
       rt = E_NOT_OK;
    }
    else{

        rt = gpio_pin_write_logic(&(_LCD->LCD_RS), GPIO_Pin_Logic_LOW);

        rt = LCD_Send_4Bits(_LCD, _Command >> 4);

        rt = LCD_4Bits_Send_Enable_Signal(_LCD);

        rt = LCD_Send_4Bits(_LCD, _Command);

        rt = LCD_4Bits_Send_Enable_Signal(_LCD);
    }
    
    return rt;
}


STD_ReturnType ECU_LCD_4Bit_Send_char_Data (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Data){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
        rt = gpio_pin_write_logic(&(_LCD->LCD_RS), GPIO_Pin_Logic_HIGH);

        rt = LCD_Send_4Bits(_LCD, _Data >> 4);

        rt = LCD_4Bits_Send_Enable_Signal(_LCD);

        rt = LCD_Send_4Bits(_LCD, _Data);
   
        rt = LCD_4Bits_Send_Enable_Signal(_LCD);
    }
    
    return rt;
}


STD_ReturnType ECU_LCD_4Bit_Send_char_Data_Position     (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 _Data){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
        rt = LCD_4Bits_Set_Curser(_LCD, _Row, _Coloumn);
        rt = ECU_LCD_4Bit_Send_char_Data (_LCD, _Data);
    }
    
    return rt; 
}


STD_ReturnType ECU_LCD_4Bit_Send_String_Data            (const LCD_Config_4Bit_Mode_t *_LCD, uint8 *_Str){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
         while(*_Str){
             rt = ECU_LCD_4Bit_Send_char_Data (_LCD, *_Str++);
         }
         
    }
    
    return rt; 
}


STD_ReturnType ECU_LCD_4Bit_Send_String_Data_Postition  (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 *_Str){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
        LCD_4Bits_Set_Curser(_LCD, _Row, _Coloumn);
        while(*_Str){
             rt = ECU_LCD_4Bit_Send_char_Data (_LCD, *_Str++);
         }
         
    }
    
    return rt; 
}



STD_ReturnType ECU_LCD_4Bit_Send_Custom_Char            (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn,
                                                          const uint8 _Char[], uint8 mem_pos){
    STD_ReturnType rt = E_NOT_OK;
    uint8 LCD_Counter = E_Zero_Init;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
         rt = ECU_LCD_4Bit_Send_Command(_LCD , (_LCD_CGRAM_START+(mem_pos*8)));
         for(LCD_Counter=0 ; LCD_Counter<8 ; ++LCD_Counter){
             rt = ECU_LCD_4Bit_Send_char_Data(_LCD, _Char[LCD_Counter]);
         }
         rt  = ECU_LCD_4Bit_Send_char_Data_Position(_LCD, _Row, _Coloumn, mem_pos);
    }
    
    return rt;
}




STD_ReturnType ECU_LCD_8Bit_Initialize(const LCD_Config_8Bit_Mode_t *_LCD){
    STD_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = E_Zero_Init;
    if(NULL == _LCD){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_initialize(&(_LCD->LCD_RS));
        ret = gpio_pin_initialize(&(_LCD->LCD_E));
        for(l_data_pins_counter=E_Zero_Init; l_data_pins_counter<8; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(_LCD->DataPins[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_8BIT_MODE_2_LINES);
        __delay_ms(5);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_8BIT_MODE_2_LINES);
        __delay_us(150);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_8BIT_MODE_2_LINES);
        
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_CLEAR);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_RETURN_HOME);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSER_OFF);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, _LCD_8BIT_MODE_2_LINES);
        ret = ECU_LCD_8Bit_Send_Command(_LCD, 0x80);
    }
    return ret;
}


STD_ReturnType ECU_LCD_8Bit_Send_Command (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Command){
      STD_ReturnType rt = E_NOT_OK;
      uint8 LCD_Counter = E_Zero_Init;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
         rt = gpio_pin_write_logic(&(_LCD->LCD_RS), GPIO_Pin_Logic_LOW);
         for(LCD_Counter = E_Zero_Init; LCD_Counter<8 ; LCD_Counter++){
             rt = gpio_pin_write_logic(&(_LCD->DataPins[LCD_Counter]),((_Command>>LCD_Counter)&((uint8)0x01)));
         }
         rt = LCD_8Bits_Send_Enable_Signal (_LCD);
    }
    
    return rt;
}


STD_ReturnType ECU_LCD_8Bit_Send_char_Data              (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Data){
    STD_ReturnType rt = E_NOT_OK;
    uint8 LCD_Counter = E_Zero_Init;
    if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
         rt = gpio_pin_write_logic(&(_LCD->LCD_RS), GPIO_Pin_Logic_HIGH);
         for(LCD_Counter = E_Zero_Init; LCD_Counter<8 ; LCD_Counter++){
             rt = gpio_pin_write_logic(&(_LCD->DataPins[LCD_Counter]),((_Data>>LCD_Counter)&((uint8)0x01)));
         }
         rt = LCD_8Bits_Send_Enable_Signal (_LCD);
    }
    
    return rt;
}


STD_ReturnType ECU_LCD_8Bit_Send_char_Data_Position     (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 _Data){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
        LCD_8Bits_Set_Curser(_LCD, _Row, _Coloumn);
        ECU_LCD_8Bit_Send_char_Data (_LCD, _Data);
    }
    
    return rt; 
}


STD_ReturnType ECU_LCD_8Bit_Send_String_Data            (const LCD_Config_8Bit_Mode_t *_LCD, uint8 *_Str){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
         while(*_Str){
             ECU_LCD_8Bit_Send_char_Data (_LCD, *_Str++);
         }
         
    }
    
    return rt;
}


STD_ReturnType ECU_LCD_8Bit_Send_String_Data_Postition  (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn, uint8 *_Str){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
        LCD_8Bits_Set_Curser(_LCD, _Row, _Coloumn);
        ECU_LCD_8Bit_Send_String_Data(_LCD, _Str);
         
    }
    
    return rt; 
}



STD_ReturnType ECU_LCD_8Bit_Send_Custom_Char            (const LCD_Config_8Bit_Mode_t *_LCD, uint8 _Row, uint8 _Coloumn,
                                                          const uint8 _Char[], uint8 mem_pos){
    STD_ReturnType rt = E_NOT_OK;
    uint8 LCD_Counter = E_Zero_Init;
     if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
         rt = ECU_LCD_8Bit_Send_Command(_LCD , (_LCD_CGRAM_START+(mem_pos*8)));
         for(LCD_Counter=E_Zero_Init ; LCD_Counter<8 ; ++LCD_Counter){
             rt = ECU_LCD_8Bit_Send_char_Data(_LCD, _Char[LCD_Counter]);
         }
         rt  = ECU_LCD_8Bit_Send_char_Data_Position(_LCD, _Row, _Coloumn, mem_pos);
    }
    
    return rt;
}      



STD_ReturnType Convert_uint8_to_string (uint8 _Value, uint8 *_String){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _String){
        rt = E_NOT_OK;
    }
    else{
        memset((char*)_String , '\0', 4);
        sprintf(_String , "%i" , _Value);
    }
    return rt;
}


STD_ReturnType Convert_uint132_to_string(uint32 _Value, uint8 *_String){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _String){
        rt = E_NOT_OK;
    }
    else{
        memset((char*)_String , '\0', 11);
        sprintf(_String , "%i" , _Value);
    }
    return rt;
}


STD_ReturnType Convert_uint16_to_string(uint16 _Value, uint8 *_String){
   STD_ReturnType rt = E_NOT_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
     if(NULL == _String){
        rt = E_NOT_OK;
    }
    else{
        memset(_String, ' ', 5);
        _String[5] = '\0';
        sprintf((char *)Temp_String, "%i", _Value);
        while(Temp_String[DataCounter] != '\0'){
            _String[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return rt;
}



STD_ReturnType LCD_Send_4Bits (const LCD_Config_4Bit_Mode_t *_LCD, uint8 _Data){
     STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD ){
        rt = E_NOT_OK;
    }
    else{
        rt = gpio_pin_write_logic(&(_LCD->DataPins[0]), (_Data >> 0) & (uint8)0x01);
        rt = gpio_pin_write_logic(&(_LCD->DataPins[1]), (_Data >> 1) & (uint8)0x01);
        rt = gpio_pin_write_logic(&(_LCD->DataPins[2]), (_Data >> 2) & (uint8)0x01);
        rt = gpio_pin_write_logic(&(_LCD->DataPins[3]), (_Data >> 3) & (uint8)0x01);
    }
     return rt;
}


STD_ReturnType LCD_4Bits_Send_Enable_Signal (const LCD_Config_4Bit_Mode_t *_LCD){
     STD_ReturnType rt = E_NOT_OK;
     if(NULL == _LCD ){
        rt = E_NOT_OK;
    }
    else{
        rt = gpio_pin_write_logic(&(_LCD->LCD_E), GPIO_Pin_Logic_HIGH);
        __delay_us(5);
        rt = gpio_pin_write_logic(&(_LCD->LCD_E), GPIO_Pin_Logic_LOW);;
    }
     return rt;
}

STD_ReturnType LCD_8Bits_Send_Enable_Signal (const LCD_Config_8Bit_Mode_t *_LCD){
    STD_ReturnType rt = E_NOT_OK;
    if(NULL == _LCD){
        rt = E_NOT_OK;
    }
    else{
        rt = gpio_pin_write_logic(&(_LCD->LCD_E),GPIO_Pin_Logic_HIGH);
        __delay_us(5);
        rt = gpio_pin_write_logic(&(_LCD->LCD_E),GPIO_Pin_Logic_LOW);
    }
    
    return rt;
}

STD_ReturnType LCD_4Bits_Set_Curser (const LCD_Config_4Bit_Mode_t *_LCD, uint8 row, uint8 coloumn){
     STD_ReturnType rt = E_NOT_OK;
     coloumn-- ;
     if(NULL == _LCD ){
        rt = E_NOT_OK;
    }
    else{
         switch(row){
             case ROW1:
                 rt = ECU_LCD_4Bit_Send_Command(_LCD , (0x80 + coloumn ));break;
             case ROW2:
                 rt = ECU_LCD_4Bit_Send_Command(_LCD , (0xc0 + coloumn ));break;
             case ROW3:
                 rt = ECU_LCD_4Bit_Send_Command(_LCD , (0x94 + coloumn ));break;  
             case ROW4:
                 rt = ECU_LCD_4Bit_Send_Command(_LCD , (0xd4 + coloumn ));break;    
         }
    }
     return rt;
}

STD_ReturnType LCD_8Bits_Set_Curser (const LCD_Config_8Bit_Mode_t *_LCD, uint8 row, uint8 coloumn){
    STD_ReturnType rt = E_NOT_OK;
     coloumn-- ;
     if(NULL == _LCD ){
        rt = E_NOT_OK;
    }
    else{
         switch(row){
             case ROW1:
                 rt = ECU_LCD_8Bit_Send_Command(_LCD , (0x80 + coloumn ));break;
             case ROW2:
                 rt = ECU_LCD_8Bit_Send_Command(_LCD , (0xc0 + coloumn ));break;
             case ROW3:
                 rt = ECU_LCD_8Bit_Send_Command(_LCD , (0x94 + coloumn ));break;  
             case ROW4:
                 rt = ECU_LCD_8Bit_Send_Command(_LCD , (0xd4 + coloumn ));break;    
         }
    }
     return rt;
}

