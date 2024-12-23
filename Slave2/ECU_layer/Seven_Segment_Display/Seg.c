
#include "Seg.h"

STD_ReturnType ECU_Segment_initialize(const Segment_Config_t *_Segment){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _Segment ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(_Segment->Segment_pins[SEGMENT_PIN1]));
        gpio_pin_initialize(&(_Segment->Segment_pins[SEGMENT_PIN2]));
        gpio_pin_initialize(&(_Segment->Segment_pins[SEGMENT_PIN3]));
        gpio_pin_initialize(&(_Segment->Segment_pins[SEGMENT_PIN4]));
         

        rt = E_OK;
      
    }
    return rt;
}



STD_ReturnType ECU_Segment_write(const Segment_Config_t *_Segment, uint8 Segment_write){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _Segment ){
        rt = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic   (&(_Segment->Segment_pins[SEGMENT_PIN1]), (Segment_write) & 0x01 );
        gpio_pin_write_logic   (&(_Segment->Segment_pins[SEGMENT_PIN2]), (Segment_write>>1) & 0x01 );
        gpio_pin_write_logic   (&(_Segment->Segment_pins[SEGMENT_PIN3]), (Segment_write>>2) & 0x01 );
        gpio_pin_write_logic   (&(_Segment->Segment_pins[SEGMENT_PIN4]), (Segment_write>>3) & 0x01 );
         

        rt = E_OK;
      
    }
    return rt;
}