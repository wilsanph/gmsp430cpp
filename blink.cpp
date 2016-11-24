

#include <msp430.h>
#include "lib/include/Gpio.hpp"
#include "lib/interrupts.h"

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );
Gpio::Pin button( Gpio::port::PORT1, Gpio::pins::pin1 );
///void fun();

u8 edgesCount = 0;

int main()
{
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );
    
    button.setMode( Gpio::config::mode::gpio );
    button.setIOMode( Gpio::config::ioMode::input );
    button.enableInterrupt();
    button.selectInterruptEdge( Gpio::config::interruptEdge::FALLING );
    button.selectInputPullResistor( Gpio::config::pullResistor::PULLUP );
    button.clearInterruptFlag();

    interrupts::enableInterrupts();

    while( 1 )
    {
        /// common::sw_delay();
        /// led.toggle();
    }
}

#pragma vector=VECTOR_PORT1
__interrupt void port1_isr()
{
    button.clearInterruptFlag();
    led.toggle();
    edgesCount++;
}

///void fun()
///{
///
///
///}
