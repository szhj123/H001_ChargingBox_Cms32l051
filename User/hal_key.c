/********************************************************
* @file       drv_msg.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_key.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ --------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
hal_irq_handler_callback_t Hal_Key_Isr_Callback = NULL;
hal_irq_handler_callback_t Hal_Hall_Isr_Callback = NULL;

void Hal_Key_Init(void )
{
    Cms32l051_Gpio_Init();
    
    Cms32l051_Intp_Init();
}

void Hal_Key_En_Low(void )
{
    PORT_ClrBit(PORT2, PIN1);
}

void Hal_Key_En_High(void )
{
    PORT_SetBit(PORT2, PIN1);
}

uint8_t Hal_Key_Get_Tx_State(void )
{
    if(PORT_GetBit(PORT1, PIN1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t Hal_Key_Get_Hall_State(void )
{
    if(PORT_GetBit(PORT2, PIN2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Hal_Key_Reigst_Isr_Callback(hal_irq_handler_callback_t keyCallback, hal_irq_handler_callback_t hallCallback )
{
    Hal_Key_Isr_Callback = keyCallback;

    Hal_Hall_Isr_Callback = hallCallback;
}

void Hal_Key_Isr_Handler(void )
{
    if(Hal_Key_Isr_Callback != NULL)
    {
        Hal_Key_Isr_Callback();
    }
}

void Hal_Hall_Isr_Handler(void )
{
    if(Hal_Hall_Isr_Callback != NULL)
    {
        Hal_Hall_Isr_Callback();
    }
}

