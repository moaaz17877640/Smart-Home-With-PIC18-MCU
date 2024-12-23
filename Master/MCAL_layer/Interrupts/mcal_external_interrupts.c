/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */
#include "mcal_external_interrupts.h"

static STD_ReturnType Interrupt_INTx_Enable        (const External_INTx_t *INTx);
static STD_ReturnType Interrupt_INTx_Disable       (const External_INTx_t *INTx);
static STD_ReturnType Interrupt_INTx_Pin_Init      (const External_INTx_t *INTx);
static STD_ReturnType Interrupt_INTx_Edge_Init     (const External_INTx_t *INTx);
static STD_ReturnType Interrupt_INTx_Priority_Init (const External_INTx_t *INTx);
static STD_ReturnType Interrupt_INTx_Clear_Flag    (const External_INTx_t *INTx);


static STD_ReturnType Interrupt_INTx_Set_Handler    (const External_INTx_t *INTx);

static STD_ReturnType Interrupt_INT0_Set_Handler    (void (*INT0_Handler)(void));
static STD_ReturnType Interrupt_INT1_Set_Handler    (void (*INT1_Handler)(void));
static STD_ReturnType Interrupt_INT2_Set_Handler    (void (*INT2_Handler)(void));

static InterruptHandler Interrupt_INT0_Handler = NULL;
static InterruptHandler Interrupt_INT1_Handler = NULL;
static InterruptHandler Interrupt_INT2_Handler = NULL;


static STD_ReturnType Interrupt_RBx_Enable         (const External_RBx_t *RBx);
static STD_ReturnType Interrupt_RBx_Disable        (const External_RBx_t *RBx);
static STD_ReturnType Interrupt_RBx_Pin_Init       (const External_RBx_t *RBx);
static STD_ReturnType Interrupt_RBx_Priority_Init  (const External_RBx_t *RBx);
static STD_ReturnType Interrupt_RBx_Clear_Flag     (const External_RBx_t *RBx);

static InterruptHandler Interrupt_RB4_Handler_HIGH = NULL;
static InterruptHandler Interrupt_RB4_Handler_LOW = NULL;
static InterruptHandler Interrupt_RB5_Handler_HIGH = NULL;
static InterruptHandler Interrupt_RB5_Handler_LOW = NULL;
static InterruptHandler Interrupt_RB6_Handler_HIGH = NULL;
static InterruptHandler Interrupt_RB6_Handler_LOW = NULL;
static InterruptHandler Interrupt_RB7_Handler_HIGH = NULL;
static InterruptHandler Interrupt_RB7_Handler_LOW = NULL;

static STD_ReturnType Interrupt_RBx_Set_Handler    (const External_RBx_t *RBx);

static STD_ReturnType Interrupt_RB4_Set_Handler_HIGH    (void (*RB4_Handler_HIGH)(void));
static STD_ReturnType Interrupt_RB4_Set_Handler_LOW     (void (*RB4_Handler_LOW)(void));
static STD_ReturnType Interrupt_RB5_Set_Handler_HIGH    (void (*RB5_Handler_HIGH)(void));
static STD_ReturnType Interrupt_RB5_Set_Handler_LOW     (void (*RB5_Handler_LOW)(void));
static STD_ReturnType Interrupt_RB6_Set_Handler_HIGH    (void (*RB6_Handler_HIGH)(void));
static STD_ReturnType Interrupt_RB6_Set_Handler_LOW     (void (*RB6_Handler_LOW)(void));
static STD_ReturnType Interrupt_RB7_Set_Handler_HIGH    (void (*RB7_Handler_HIGH)(void));
static STD_ReturnType Interrupt_RB7_Set_Handler_LOW     (void (*RB7_Handler_LOW)(void));





STD_ReturnType Interrupt_INTx_Init (const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine disable the interrupt feature for external INTx*/
        ret  = Interrupt_INTx_Disable       (INTx);
        /* This routine clears the interrupt flag for external INTx */
        ret |= Interrupt_INTx_Clear_Flag    (INTx);
        /* This routine initiate MCU pin for external INTx*/
        ret |= Interrupt_INTx_Pin_Init      (INTx);
        /* This routine set the edge detect of INTx*/
        ret |= Interrupt_INTx_Edge_Init     (INTx);
        /* This routine set the priority of INTx*/
        ret |= Interrupt_INTx_Priority_Init (INTx);
        /* Configure callback function*/
        ret |= Interrupt_INTx_Set_Handler    (INTx);
        /* This routine enable the interrupt feature for external INTx*/
        ret |= Interrupt_INTx_Enable        (INTx);
        
    }
    return ret;
}


STD_ReturnType Interrupt_INTx_Deinit (const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine disable the interrupt feature for external INTx*/
        ret  = Interrupt_INTx_Disable       (INTx);
        
        ret = E_OK;
    }
    return ret;
    
}


STD_ReturnType Interrupt_RBx_Init (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine disable the interrupt feature for external RBx*/
        ret  = Interrupt_RBx_Disable        (RBx);
        /* This routine clears the interrupt flag for external RBx */
        ret |= Interrupt_RBx_Clear_Flag     (RBx);
        /* This routine initiate MCU pin for external RBx*/
        ret |= Interrupt_RBx_Pin_Init       (RBx);
        /* This routine set the priority of RBx*/
        ret |= Interrupt_RBx_Priority_Init  (RBx);
        /* Configure callback functions*/
        ret |= Interrupt_RBx_Set_Handler    (RBx);
        /* This routine enable the interrupt feature for external RBx*/
        ret |= Interrupt_RBx_Enable         (RBx);
        
        ret = E_OK;
    }
    return ret;
}


STD_ReturnType Interrupt_RBx_Deinit (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine disable the interrupt feature for external RBx*/
        ret  = Interrupt_RBx_Disable        (RBx);
        
        ret = E_OK;
    }
    return ret;
}





static STD_ReturnType Interrupt_INTx_Pin_Init(const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(INTx->Interrupt_Pin));
    }
    return ret;
}

static STD_ReturnType Interrupt_INTx_Edge_Init(const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        switch(INTx->Interrupt_Source){
            case EXTERNAL_INTERRUPT_INT0: 
                if(INTERRUPT_FAILLING_EDGE == INTx->Interrupt_Edge){INT0_INTERRUPT_FAILLING_EDGE();}
                else if(INTERRUPT_RAISING_EDGE == INTx->Interrupt_Edge){INT0_INTERRUPT_RAISING_EDGE();}
                else {/*Do nothing*/}
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT1:
                if(INTERRUPT_FAILLING_EDGE == INTx->Interrupt_Edge){INT1_INTERRUPT_FAILLING_EDGE();}
                else if(INTERRUPT_RAISING_EDGE == INTx->Interrupt_Edge){INT1_INTERRUPT_RAISING_EDGE();}
                else {/*Do nothing*/}
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT2:
                if(INTERRUPT_FAILLING_EDGE == INTx->Interrupt_Edge){INT2_INTERRUPT_FAILLING_EDGE();}
                else if(INTERRUPT_RAISING_EDGE == INTx->Interrupt_Edge){INT2_INTERRUPT_RAISING_EDGE();}
                else {/*Do nothing*/}
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;  
        }
    }
    return ret;
}



static STD_ReturnType Interrupt_INTx_Clear_Flag(const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        switch(INTx->Interrupt_Source){
            case EXTERNAL_INTERRUPT_INT0:              
                /* Clears the interrupt flag for the external interrupt, INT0 */
                INT0_INTERRUPT_FLAG_CLEAR();
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT1:                
                /* Clears the interrupt flag for the external interrupt, INT1 */
                INT1_INTERRUPT_FLAG_CLEAR();
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT2:
                /* Clears the interrupt flag for the external interrupt, INT2 */
                INT2_INTERRUPT_FLAG_CLEAR();
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;  
        }
    }
    return ret;
}



static STD_ReturnType Interrupt_INTx_Priority_Init(const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        switch(INTx->Interrupt_Source){
            case EXTERNAL_INTERRUPT_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* This routine will enable high priority global interrupts*/
                INTERRUPT_Global_High_Priority_Enable();
#else
                /* This routine will enable global interrupts*/
                INTERRUPT_GlobalEnable();
                /* This routine will enable peripheral interrupts*/
                INTERRUPT_PeripheralEnable();
#endif
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT1:
                ret = E_OK;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* This routine will enable priority levels on interrupts*/
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == INTx->Interrupt_Priority){
                    /* This routine enable the interrupt low priority for external INT1 */
                    INT1_INTERRUPT_LOW_PRIORITY_ENABLE();
                    /* This routine will enable low priority global interrupts*/
                    INTERRUPT_Global_LOW_Priority_Enable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == INTx->Interrupt_Priority){
                    /* This routine enable the interrupt high priority for external INT1 */
                    INT1_INTERRUPT_HIGH_PRIORITY_ENABLE();
                    /* This routine will enable high priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();
                }
                else {/*Do nothing*/}
#else
                /* This routine will enable global interrupts*/
                INTERRUPT_GlobalEnable();
                /* This routine will enable peripheral interrupts*/
                INTERRUPT_PeripheralEnable();
#endif
                break;
            case EXTERNAL_INTERRUPT_INT2:
                ret = E_OK;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* This routine will enable priority levels on interrupts*/
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == INTx->Interrupt_Priority){
                    /* This routine enable the interrupt low priority for external INT2 */
                    INT2_INTERRUPT_LOW_PRIORITY_ENABLE();
                    /* This routine will enable low priority global interrupts*/
                    INTERRUPT_Global_LOW_Priority_Enable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == INTx->Interrupt_Priority){
                    /* This routine enable the interrupt high priority for external INT2 */
                    INT2_INTERRUPT_HIGH_PRIORITY_ENABLE();
                    /* This routine will enable high priority global interrupts*/
                    INTERRUPT_Global_High_Priority_Enable();
                }
                else {/*Do nothing*/}
#else
                /* This routine will enable global interrupts*/
                INTERRUPT_GlobalEnable();
                /* This routine will enable peripheral interrupts*/
                INTERRUPT_PeripheralEnable();
#endif
                break;
            default:
                ret = E_NOT_OK;  
        }
    }
    return ret;
}


static STD_ReturnType Interrupt_INTx_Enable(const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        switch(INTx->Interrupt_Source){
            case EXTERNAL_INTERRUPT_INT0:
                /* This routine enable the interrupt feature for external INT0 */
                INT0_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT1:
                /* This routine enable the interrupt feature for external INT1 */
                INT1_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT2:
                /* This routine enable the interrupt feature for external INT2 */
                INT2_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;  
        }
    }
    return ret;
}

static STD_ReturnType Interrupt_INTx_Disable(const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        switch(INTx->Interrupt_Source){
            case EXTERNAL_INTERRUPT_INT0:
                /* Disable the INT0 external interrupt */
                INT0_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT1:
                /* Disable the INT1 external interrupt */
                INT1_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            case EXTERNAL_INTERRUPT_INT2:
                /* Disable the INT2 external interrupt */
                INT2_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;  
        }
    }
    return ret;
}

static STD_ReturnType Interrupt_INTx_Set_Handler    (const External_INTx_t *INTx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INTx){
        ret = E_NOT_OK;
    }
    else{
        switch(INTx->Interrupt_Source){
            case EXTERNAL_INTERRUPT_INT0:
                /* Set Default Interrupt Handler for INT0 External Interrupt : Application ISR */
                ret = Interrupt_INT0_Set_Handler(INTx->EXT_InterruptHandler);
                break;
            case EXTERNAL_INTERRUPT_INT1:
                /* Set Default Interrupt Handler for INT1 External Interrupt : Application ISR */
                ret = Interrupt_INT1_Set_Handler(INTx->EXT_InterruptHandler);
                break;
            case EXTERNAL_INTERRUPT_INT2:
                /* Set Default Interrupt Handler for INT2 External Interrupt : Application ISR */
                ret = Interrupt_INT2_Set_Handler(INTx->EXT_InterruptHandler);
                break;
            default:
                ret = E_NOT_OK;  
        }
    }
    return ret;
}

static STD_ReturnType Interrupt_INT0_Set_Handler    (void (*INT0_Handler)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INT0_Handler){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_INT0_Handler = INT0_Handler;
        ret = E_OK;
        }
    return ret;
}

static STD_ReturnType Interrupt_INT1_Set_Handler    (void (*INT1_Handler)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INT1_Handler){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_INT1_Handler = INT1_Handler;
        ret = E_OK;
        }
    return ret;
}

static STD_ReturnType Interrupt_INT2_Set_Handler    (void (*INT2_Handler)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == INT2_Handler){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_INT2_Handler = INT2_Handler;
        ret = E_OK;
        }
    return ret;
}


void INT0_ISR(void){
    /* This routine clears the interrupt flag for external INT0 */
    INT0_INTERRUPT_FLAG_CLEAR();
    
    if(Interrupt_INT0_Handler)
        Interrupt_INT0_Handler();
    else{/*Do nothing*/}      
}

void INT1_ISR(void){
    /* This routine clears the interrupt flag for external INT0 */
    INT1_INTERRUPT_FLAG_CLEAR();
    
    if(Interrupt_INT1_Handler)
        Interrupt_INT1_Handler();
    else{/*Do nothing*/}      
}

void INT2_ISR(void){
    /* This routine clears the interrupt flag for external INT0 */
    INT2_INTERRUPT_FLAG_CLEAR();
    
    if(Interrupt_INT2_Handler)
        Interrupt_INT2_Handler();
    else{/*Do nothing*/}      
}

static STD_ReturnType Interrupt_RBx_Pin_Init       (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(RBx->Interrupt_Pin));
    }
    return ret;
}

static STD_ReturnType Interrupt_RBx_Priority_Init  (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* This routine will enable priority levels on interrupts*/
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == RBx->Interrupt_Priority){
            /* This routine enable the interrupt high priority for external RBx */
            RBx_INTERRUPT_HIGH_PRIORITY_ENABLE();
            /* This routine will enable high priority global interrupts*/
            INTERRUPT_Global_High_Priority_Enable();
        }
        else if(INTERRUPT_LOW_PRIORITY == RBx->Interrupt_Priority){
            /* This routine enable the interrupt low priority for external RBx */
            RBx_INTERRUPT_LOW_PRIORITY_ENABLE();
            /* This routine will enable low priority global interrupts*/
            INTERRUPT_Global_LOW_Priority_Enable();
        }
        else{
            /* Do nothing*/
        }
#else
        /* This routine will enable global interrupts*/
        INTERRUPT_GlobalEnable();
        /* This routine will enable peripheral interrupts*/
        INTERRUPT_PeripheralEnable();   
#endif
        ret = E_OK;
        
    }
    return ret;
}

static STD_ReturnType Interrupt_RBx_Enable         (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine enable the interrupt feature for external RBx */
        RBx_INTERRUPT_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}


static STD_ReturnType Interrupt_RBx_Disable        (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine disable the interrupt feature for external RBx */
        RBx_INTERRUPT_DISABLE();
        
        ret = E_OK;
    }
    return ret;
}

static STD_ReturnType Interrupt_RBx_Clear_Flag     (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        /* This routine clears the interrupt flag for external RBx */
        RBx_INTERRUPT_FLAG_CLEAR();
        
        ret = E_OK;
    }
    return ret;
}


static STD_ReturnType Interrupt_RBx_Set_Handler    (const External_RBx_t *RBx){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RBx){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        switch(RBx->Interrupt_Pin.pin){
            case pin4:
                Interrupt_RB4_Set_Handler_HIGH    (RBx->Interrupt_Handle_HIGH);
                Interrupt_RB4_Set_Handler_LOW     (RBx->Interrupt_Handle_LOW);break;
            case pin5:
                Interrupt_RB5_Set_Handler_HIGH    (RBx->Interrupt_Handle_HIGH);
                Interrupt_RB5_Set_Handler_LOW     (RBx->Interrupt_Handle_LOW);break;
            case pin6:
                Interrupt_RB6_Set_Handler_HIGH    (RBx->Interrupt_Handle_HIGH);
                Interrupt_RB6_Set_Handler_LOW     (RBx->Interrupt_Handle_LOW);break;
            case pin7:
                Interrupt_RB7_Set_Handler_HIGH    (RBx->Interrupt_Handle_HIGH);
                Interrupt_RB7_Set_Handler_LOW     (RBx->Interrupt_Handle_LOW);break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}

static STD_ReturnType Interrupt_RB4_Set_Handler_HIGH    (void (*RB4_Handler_HIGH)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB4_Handler_HIGH){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB4_Handler_HIGH = RB4_Handler_HIGH;
        ret = E_OK;
    }
    return ret;
}


static STD_ReturnType Interrupt_RB4_Set_Handler_LOW    (void (*RB4_Handler_LOW)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB4_Handler_LOW){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB4_Handler_LOW = RB4_Handler_LOW;
        ret = E_OK;
    }
    return ret;
}


static STD_ReturnType Interrupt_RB5_Set_Handler_HIGH    (void (*RB5_Handler_HIGH)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB5_Handler_HIGH){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB5_Handler_HIGH = RB5_Handler_HIGH;
        ret = E_OK;
    }
    return ret;
}

static STD_ReturnType Interrupt_RB5_Set_Handler_LOW     (void (*RB5_Handler_LOW)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB5_Handler_LOW){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB5_Handler_LOW = RB5_Handler_LOW;
        ret = E_OK;
    }
    return ret;
}

static STD_ReturnType Interrupt_RB6_Set_Handler_HIGH    (void (*RB6_Handler_HIGH)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB6_Handler_HIGH){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB6_Handler_HIGH = RB6_Handler_HIGH;
        ret = E_OK;
    }
    return ret;
}


static STD_ReturnType Interrupt_RB6_Set_Handler_LOW     (void (*RB6_Handler_LOW)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB6_Handler_LOW){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB6_Handler_LOW = RB6_Handler_LOW;
        ret = E_OK;
    }
    return ret;
}

static STD_ReturnType Interrupt_RB7_Set_Handler_HIGH    (void (*RB7_Handler_HIGH)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB7_Handler_HIGH){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB7_Handler_HIGH = RB7_Handler_HIGH;
        ret = E_OK;
    }
    return ret;
}
static STD_ReturnType Interrupt_RB7_Set_Handler_LOW     (void (*RB7_Handler_LOW)(void)){
    STD_ReturnType ret = E_NOT_OK;
    if(NULL == RB7_Handler_LOW){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RB7_Handler_LOW = RB7_Handler_LOW;
        ret = E_OK;
    }
    return ret;
}

void RB4_ISR(uint8 RB4_Source){
    /* This routine clears the interrupt flag for external RBx */
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(0 == RB4_Source){
        if(Interrupt_RB4_Handler_HIGH) Interrupt_RB4_Handler_HIGH();
        else {/*Do nothing*/}
    }
    else if(1 == RB4_Source){
        if(Interrupt_RB4_Handler_LOW) Interrupt_RB4_Handler_LOW();
        else {/*Do nothing*/}
    }
    else {/*Do nothing*/}
           
}

void RB5_ISR(uint8 RB5_Source){
    /* This routine clears the interrupt flag for external RBx */
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(0 == RB5_Source){
        if(Interrupt_RB5_Handler_HIGH) Interrupt_RB5_Handler_HIGH();
        else {/*Do nothing*/}
    }
    else if(1 == RB5_Source){
        if(Interrupt_RB5_Handler_LOW) Interrupt_RB5_Handler_LOW();
        else {/*Do nothing*/}
    }
    else {/*Do nothing*/}
           
}

void RB6_ISR(uint8 RB6_Source){
    /* This routine clears the interrupt flag for external RBx */
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(0 == RB6_Source){
        if(Interrupt_RB6_Handler_HIGH) Interrupt_RB6_Handler_HIGH();
        else {/*Do nothing*/}
    }
    else if(1 == RB6_Source){
        if(Interrupt_RB6_Handler_LOW) Interrupt_RB6_Handler_LOW();
        else {/*Do nothing*/}
    }
    else {/*Do nothing*/}
           
}

void RB7_ISR(uint8 RB7_Source){
    /* This routine clears the interrupt flag for external RBx */
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(0 == RB7_Source){
        if(Interrupt_RB7_Handler_HIGH) Interrupt_RB7_Handler_HIGH();
        else {/*Do nothing*/}
    }
    else if(1 == RB7_Source){
        if(Interrupt_RB7_Handler_LOW) Interrupt_RB7_Handler_LOW();
        else {/*Do nothing*/}
    }
    else {/*Do nothing*/}
           
}