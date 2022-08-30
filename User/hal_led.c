/********************************************************
* @file       hal_led.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_led.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ --------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Led_Init(PORT_TypeDef port, PIN_TypeDef pin )
{
    PORT_Init(port, pin, OUTPUT);
}

void Hal_Led_On(PORT_TypeDef port, PIN_TypeDef pin )
{
    PORT_SetBit(port, pin);
}

void Hal_Led_Off(PORT_TypeDef port, PIN_TypeDef pin )
{
    PORT_ClrBit(port, pin);
}

uint8_t Hal_Led_Get_State(PORT_TypeDef port, PIN_TypeDef pin )
{
    if(PORT_GetBit(port, pin))
    {
        return LED_ON;
    }
    else
    {
        return LED_OFF;
    }
}

void Hal_Led_Uv_On(void )
{
    PORT_SetBit(PORT1, PIN2);
}

void Hal_Led_Uv_Off(void )
{
    PORT_ClrBit(PORT1, PIN2);
}
