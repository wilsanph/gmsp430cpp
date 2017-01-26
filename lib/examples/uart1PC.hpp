

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

uart::Uart uartMod( uart::instanceAddress::USCIA1 );
Gpio::Pin uart1rx( Gpio::port::PORT4, Gpio::pins::pin4 );
Gpio::Pin uart1tx( Gpio::port::PORT4, Gpio::pins::pin5 );

int main()
{
    dog.init( watchdog::config::clockSource::SMCLK,
              watchdog::config::mode::WATCHDOG_MODE,
              watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );

    uart1rx.setMode( Gpio::config::mode::alternate );
    uart1tx.setMode( Gpio::config::mode::alternate );

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
        uartMod.write( 'f' );
        uartMod.write( ':' );
        uartMod.write( ' ' );
        uartMod.writeFloat( 123.5, 2 );
        uartMod.write( 10 );
        uartMod.write( 13 );
    }
}




