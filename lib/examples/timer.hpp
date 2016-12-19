

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Timer.hpp"
#include "lib/interrupts.h"

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );
Gpio::Pin button( Gpio::port::PORT1, Gpio::pins::pin1 );
///void fun();

Timer::TimeEvent timerA0( Timer::instance::TIMERA0,
						  Timer::channel::CH_0 );

watchdog::WatchdogTimer dog;

u32 ticksCount = 0;

int main()
{
    dog.init( watchdog::config::clockSource::SMCLK,
              watchdog::config::mode::WATCHDOG_MODE,
              watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );
    
    timerA0.stop();
    timerA0.config( 1000,
    				Timer::config::clockMainDivider::DIV_1,
    				Timer::config::clockSubDivider::DIV_1,
					Timer::config::clockSource::SMCLK,
					Timer::config::countMode::UP_MODE );
    timerA0.enableInterrupt();
    timerA0.restart();

    interrupts::enableInterrupts();

    while( 1 )
    {
        /// common::sw_delay();
        /// led.toggle();
    }
}

#pragma vector=VECTOR_TIMERA0_SINGLE
__interrupt void timerA0_single_isr()
{
	ticksCount++;
	if ( ticksCount >= 1000 )
	{
		ticksCount = 0;
		led.toggle();
	}
}

///void fun()
///{
///
///
///}
