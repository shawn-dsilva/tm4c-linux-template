/*
* Copyright (c) 2018, Shawn D'silva <shawn.dsilva_97@protonmail.com>
* All rights reserved.
*
*  This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
*
* File:			startup.c
* Author:		Shawn D'silva <https://shawn-dsilva.github.io>.
* Version:		1.0.0.
* Description:	startup header for the TM4C Launchpad board,defines the vector table
    handlers and ISRS,also declares external variables
*/
#include <stdint.h>

// +-----------------------------------------------------------------------------------+
// +			        Type Definitions and Macros                                    +
// +-----------------------------------------------------------------------------------+

/*
 * Defines a macro DEFAULT that aliases the function prototype
 * to Default_Handler if the function is not defined
*/
#define DEFAULT __attribute__((weak, alias("Default_Handler")))

/* Defines a type for the ISR's in the vector table */
typedef void (*element_t)(void);

/* Defines a type for the vector table */
typedef union {
    element_t isr;   //all ISRs use this type
    void *stack_top; //pointer to top of the stack
} vector_table_t;

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
// +-----------------------------------------------------------------------------------+
// +			        Prototypes of Basic Exception Handlers                         +
// +-----------------------------------------------------------------------------------+

//Default Handler,does nothing
void Default_Handler(void);

//System Exception Handlers

void Reset_Handler(void);
DEFAULT void NMI_Handler(void);
DEFAULT void SVC_Handler(void);
DEFAULT void DebugMonitor_Handler(void);
DEFAULT void PendSV_Handler(void);
DEFAULT void SysTick_Handler(void);

//Fault Handlers

DEFAULT void HardFault_Handler(void);
DEFAULT void MemManageFault_Handler(void);
DEFAULT void BusFault_Handler(void);
DEFAULT void UsageFault_Handler(void);

// +-----------------------------------------------------------------------------------+
// +                Prototypes of Interrupt Service Routines                           +
// +-----------------------------------------------------------------------------------+
DEFAULT void GPIOPortA_ISR(void);
DEFAULT void GPIOPortB_ISR(void);
DEFAULT void GPIOPortC_ISR(void);
DEFAULT void GPIOPortD_ISR(void);
DEFAULT void GPIOPortE_ISR(void);
DEFAULT void UART0_ISR(void);
DEFAULT void UART1_ISR(void);
DEFAULT void SPI0_ISR(void);
DEFAULT void I2C0_ISR(void);
DEFAULT void PWM0Fault_ISR(void);
DEFAULT void PWM0Generator0_ISR(void);
DEFAULT void PWM0Generator1_ISR(void);
DEFAULT void PWM0Generator2_ISR(void);
DEFAULT void QEI0_ISR(void);
DEFAULT void ADC0Sequence0_ISR(void);
DEFAULT void ADC0Sequence1_ISR(void);
DEFAULT void ADC0Sequence2_ISR(void);
DEFAULT void ADC0Sequence3_ISR(void);
DEFAULT void WatchDogTimer_ISR(void);
DEFAULT void Timer0A_ISR(void);
DEFAULT void Timer0B_ISR(void);
DEFAULT void Timer1A_ISR(void);
DEFAULT void Timer1B_ISR(void);
DEFAULT void Timer2A_ISR(void);
DEFAULT void Timer2B_ISR(void);
DEFAULT void AnalogComparator0_ISR(void);
DEFAULT void AnalogComparator1_ISR(void);
DEFAULT void SystemCtrl_ISR(void);
DEFAULT void FlashCtrl_ISR(void);
DEFAULT void GPIOPortF_ISR(void);
DEFAULT void UART2_ISR(void);
DEFAULT void SPI1_ISR(void);
DEFAULT void Timer3A_ISR(void);
DEFAULT void Timer3B_ISR(void);
DEFAULT void I2C1_ISR(void);
DEFAULT void QEI1_ISR(void);
DEFAULT void CAN0_ISR(void);
DEFAULT void CAN1_ISR(void);
DEFAULT void Hibernation_ISR(void);
DEFAULT void USB0_ISR(void);
DEFAULT void PWM0Generator3_ISR(void);
DEFAULT void UDMASoftware_ISR(void);
DEFAULT void UDMAError_ISR(void);
DEFAULT void ADC1Sequence0_ISR(void);
DEFAULT void ADC1Sequence1_ISR(void);
DEFAULT void ADC1Sequence2_ISR(void);
DEFAULT void ADC1Sequence3_ISR(void);
DEFAULT void SPI2_ISR(void);
DEFAULT void SPI3_ISR(void);
DEFAULT void UART3_ISR(void);
DEFAULT void UART4_ISR(void);
DEFAULT void UART5_ISR(void);
DEFAULT void UART6_ISR(void);
DEFAULT void UART7_ISR(void);
DEFAULT void I2C2_ISR(void);
DEFAULT void I2C3_ISR(void);
DEFAULT void Timer4A_ISR(void);
DEFAULT void Timer4B_ISR(void);
DEFAULT void Timer5A_ISR(void);
DEFAULT void Timer5B_ISR(void);
DEFAULT void WideTimer0A_ISR(void);
DEFAULT void WideTimer0B_ISR(void);
DEFAULT void WideTimer1A_ISR(void);
DEFAULT void WideTimer1B_ISR(void);
DEFAULT void WideTimer2A_ISR(void);
DEFAULT void WideTimer2B_ISR(void);
DEFAULT void WideTimer3A_ISR(void);
DEFAULT void WideTimer3B_ISR(void);
DEFAULT void WideTimer4A_ISR(void);
DEFAULT void WideTimer4B_ISR(void);
DEFAULT void WideTimer5A_ISR(void);
DEFAULT void WideTimer5B_ISR(void);
DEFAULT void SystemException_ISR(void);
DEFAULT void PWM1Generator0_ISR(void);
DEFAULT void PWM1Generator1_ISR(void);
DEFAULT void PWM1Generator2_ISR(void);
DEFAULT void PWM1Generator3_ISR(void);
DEFAULT void PWM1Fault_ISR(void);

// +-----------------------------------------------------------------------------------+
// +					External Variables declaration					               +
// +-----------------------------------------------------------------------------------+

//main() of your program
extern int main(void);

//stack pointer
extern uint32_t _stack_ptr;
//.text/code,stored in Flash
extern uint32_t _etext;
//.data,copied into RAM on boot
extern uint32_t _data;
extern uint32_t _edata;
//.bss,unitialized variables
extern uint32_t _bss;
extern uint32_t _ebss;

/***************************************** END OF FILE *******************************************/
