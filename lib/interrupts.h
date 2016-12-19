
#pragma once

#ifndef INTERRUPTS_HPP_
#define INTERRUPTS_HPP_

#define PISR (void (*)(void))


#define VECTOR_RTC              ( 41 * 1u )
#define VECTOR_PORT2            ( 42 * 1u )
#define VECTOR_TIMERA2_GROUP    ( 43 * 1u )
#define VECTOR_TIMERA2_SINGLE   ( 44 * 1u )
#define VECTOR_USCI_B1          ( 45 * 1u )
#define VECTOR_USCI_A1          ( 46 * 1u )
#define VECTOR_PORT1            ( 47 * 1u )
#define VECTOR_TIMERA1_GROUP    ( 48 * 1u )
#define VECTOR_TIMERA1_SINGLE   ( 49 * 1u )
#define VECTOR_DMA              ( 50 * 1u )
#define VECTOR_USB_UBM          ( 51 * 1u )
#define VECTOR_TIMERA0_GROUP    ( 52 * 1u )
#define VECTOR_TIMERA0_SINGLE   ( 53 * 1u )
#define VECTOR_ADC12            ( 54 * 1u )
#define VECTOR_USCI_B0          ( 55 * 1u )
#define VECTOR_USCI_A0          ( 56 * 1u )
#define VECTOR_WDT              ( 57 * 1u )
#define VECTOR_TIMER0_B1        ( 58 * 1u )
#define VECTOR_TIMER0_B0        ( 59 * 1u )
#define VECTOR_COMP_B           ( 60 * 1u )
#define VECTOR_UNMI             ( 61 * 1u )
#define VECTOR_SYSNMI           ( 62 * 1u )
#define VECTOR_RESET            ( 63 * 1u )


namespace interrupts
{

    void enableInterrupts();

}




void interrupts::enableInterrupts()
{
    asm(" NOP");
    asm(" EINT");
    asm(" NOP");
}

#endif
