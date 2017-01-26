
#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

int main()
{
    dog.init( watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );

    while( 1 )
    {
        common::sw_delay();
        led.toggle();
    }


}
