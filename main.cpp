

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

uart::Uart uartMod( uart::instanceAddress::USCIA1 );

int main()
{
    dog.init( watchdog::config::clockSource::SMCLK,
              watchdog::config::mode::WATCHDOG_MODE,
              watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );

    uartMod.config( uart::config::baudrate::BAUDRATE_115200,
    			    uart::config::databits::BITS_8,
				    uart::config::parity::NONE,
				    uart::config::stopbits::STOPBITS_1,
				    uart::config::msbfirst::LSB_FIRST,
				    uart::config::clockSource::SMCLK,
				    uart::config::timingMode::LOW_FREQUENCY );


    while( 1 )
    {
        common::sw_delay();
        led.toggle();
        uartMod.write( 'a' );
    }
}
