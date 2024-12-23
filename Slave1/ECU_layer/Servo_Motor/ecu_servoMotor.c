/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#include "ecu_servoMotor.h"


static STD_ReturnType ret;
volatile static uint8 CCP1_flag;
volatile static uint16 PWM_Val;
static CCPx_t CCP1_obj;
static Timer1_t timer1_obj;
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
void CCP1_DefaultISR(void){
    CCP1_flag++;
    ret = Timer1_Write_Value(&timer1_obj, 0);
    if(1 == CCP1_flag){
        ret = CCPx_CompareMode_WriteData(&CCP1_obj, PWM_Val);
        CCP1_SET_MODE(CCPx_MODULE_COMPARE_SET_PIN_HIGH);
    }
    else if(2 == CCP1_flag){
        ret = CCPx_CompareMode_WriteData(&CCP1_obj, 20000 - PWM_Val);
        CCP1_SET_MODE(CCPx_MODULE_COMPARE_SET_PIN_LOW);
        CCP1_flag = 0; 
    }
    else{
        /*Do nothing*/
    }
    
}
#endif
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
STD_ReturnType Servo_Init (const Servo_Config_t *_Servo){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _Servo ){
        rt = E_NOT_OK;
    }
    else{
        CCP1_obj.CCPx_CAPTURE_COMPARE_TIMER = CCP1_CCP2_TIMER1_SELECTED;
        CCP1_obj.CCPx_Instance = _Servo->servoPin;
        CCP1_obj.CCPx_MODE = CCPx_CFG_COMPARE_MODE;
        if(CCP1_SELECTED == _Servo->servoPin){
            CCP1_obj.CCPx_PIN.port = portC;
            CCP1_obj.CCPx_PIN.pin =  pin2;
            CCP1_obj.CCPx_PIN.direction = GPIO_Pin_Direction_OUTPUT;
            CCP1_obj.CCPx_PIN.logic = GPIO_Pin_Logic_LOW;
        }
        else if(CCP2_SELECTED == _Servo->servoPin){
            CCP1_obj.CCPx_PIN.port = portC;
            CCP1_obj.CCPx_PIN.pin =  pin1;
            CCP1_obj.CCPx_PIN.direction = GPIO_Pin_Direction_OUTPUT;
            CCP1_obj.CCPx_PIN.logic = GPIO_Pin_Logic_LOW;
        }
        CCP1_obj.CCPx_Variant = CCPx_MODULE_COMPARE_SET_PIN_LOW;
        CCP1_obj.CCP1_InterruptHandler = CCP1_DefaultISR;
        
        timer1_obj.TIMER1_InterruptHandler = NULL;
        timer1_obj.Timer1_mode = TIMER1_TIMER_MODE;
        timer1_obj.Timer1_registerSize = TIMER1_16BIT_TIMER_COUNTER;
        timer1_obj.Timer1_Prescaler_Value = TIMER1_PRESCALE_VALUE_DIV_1;
        timer1_obj.Timer1_preloadValue = 0;
        
        rt = E_OK; 
    }
    return rt;
}
#endif
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
STD_ReturnType Servo_Set_Angle (const Servo_Config_t *_Servo, uint8 _Servo_Angle){
    STD_ReturnType rt = E_NOT_OK;
     if(NULL == _Servo ){
        rt = E_NOT_OK;
    }
    else{
         _Servo_Angle -= 34;
        PWM_Val = (uint16) (((_Servo_Angle * 1000.0) / 180) + 999);
        ret = CCPx_CompareMode_WriteData(&CCP1_obj, 20000 - PWM_Val);
        ret = CCPx_Init(&CCP1_obj);
        Timer1_Init(&timer1_obj);

        rt = E_OK;
    }
    return rt;
}
#endif