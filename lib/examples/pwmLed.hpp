

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Timer.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );
Gpio::Pin pwmOut( Gpio::port::PORT1, Gpio::pins::pin2 );

Timer::Pwm pwmT0Ch1( Timer::instance::TIMERA0,
                     Timer::channel::CH_1 );


float duty = 0.0f;

int main()
{
    dog.init( watchdog::config::clockSource::SMCLK,
              watchdog::config::mode::WATCHDOG_MODE,
              watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );

    pwmOut.setMode( Gpio::config::mode::alternate );
    pwmOut.setAlternateMode( Gpio::config::alternateMode::ALT_MODE_2 );

    pwmT0Ch1.stop();
    // 1Mhz clock, and we want 10 khz frequency
    // so 1000 / 10 -> 100
    pwmT0Ch1.config( 100,
                     duty,
    		 		 Timer::config::clockMainDivider::DIV_1,
    				 Timer::config::clockSubDivider::DIV_1,
					 Timer::config::clockSource::SMCLK );

    while( 1 )
    {
        common::sw_delay();
        led.toggle();
        pwmT0Ch1.setDuty( duty );
        if ( duty > 1 )
        {
        	duty = 0;
        }
        else
        {
        	duty += 0.01;
        }
    }
}
