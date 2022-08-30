/********************************************************
* @file       hal_cms32l051.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_cms32l051.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ --------------------*/
#define INTP1_USB_DETECT                    (1 << 1)
#define INTP2_HALL_DETECT                   (1 << 2)
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Cms32l051_Gpio_Init(void )
{
    //p22, hall out, input
    //p21, key_en, output
    //p20, usb detect, input
    PORT_Init(PORT2, PIN2, INPUT);
    PORT_Init(PORT2, PIN1, OUTPUT);
    PORT_Init(PORT2, PIN0, INPUT);

    PORT_SetBit(PORT2, PIN1);
    
    //p12, led3, outpu6
    //p11, sda
    //p10, scl
    PORT_Init(PORT1, PIN2, OUTPUT);
    PORT_Init(PORT1, PIN1, OUTPUT);
    PORT_Init(PORT1, PIN0, INPUT);

}

void Cms32l051_Intp_Init(void )
{
    INTP_Init(INTP1_USB_DETECT, INTP_BOTH);
    INTP_Start(INTP1_USB_DETECT);

    INTP_Init(INTP2_HALL_DETECT, INTP_BOTH);
    INTP_Start(INTP2_HALL_DETECT);
}

void Cms32l051_Tim4_Channel0_Init(void )
{
    SystemCoreClockUpdate();
    //使能TM40外设时钟
    CGC->PER0 |= CGC_PER0_TM40EN_Msk; 
    //选择CKM0的时钟为Fclk 
    TM40->TPS0 = (TM40->TPS0 & ~TM40_TPS0_PRS00_Msk) | (0 << TM40_TPS0_PRS00_Pos);
    //选择CMK0 作为TM4通道0的时钟
    TM40->TMR00 = (TM40->TMR00 & ~TM40_TMR00_CKS_Msk) | (0 << TM40_TMR00_CKS_Pos); 
    //TM4 通道0只有软件触发开始有效
    TM40->TMR00 = (TM40->TMR00 & ~TM40_TMR00_STS_Msk) | (0 << TM40_TMR00_STS_Pos);
    //TM40通道0运行模式：间隔定时器
    TM40->TMR00 = (TM40->TMR00 & ~TM40_TMR00_MD_Msk) | (0 << TM40_TMR00_MD_Pos);

    TM40->TDR00 = (SystemCoreClock / 1000) - 1;

    INTC_ClearPendingIRQ(TM00_IRQn);
    NVIC_ClearPendingIRQ(TM00_IRQn);

    INTC_EnableIRQ(TM00_IRQn);

    TM40->TS0 |= TM40_TS0_TS00_Msk;
}

void Cms32l051_Adc_Init(void )
{
    ADC_Init();
}

