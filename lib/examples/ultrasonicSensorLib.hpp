

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/include/Timer.hpp"
#include "lib/drivers/SR04.hpp"
#include "lib/interrupts.h"
#include <vector>


watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

Gpio::Pin sr_trigger( Gpio::port::PORT1, Gpio::pins::pin2 );
Gpio::Pin sr_echo( Gpio::port::PORT1, Gpio::pins::pin3 );

uart::Uart uartMod( uart::instanceAddress::USCIA1 );
Gpio::Pin uart1rx( Gpio::port::PORT4, Gpio::pins::pin4 );
Gpio::Pin uart1tx( Gpio::port::PORT4, Gpio::pins::pin5 );

Timer::TimeEvent timerA0( Timer::instance::TIMERA0,
						  Timer::channel::CH_0 );

sensors::SR04 uSensor1;

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

    uSensor1.init( &timerA0, &sr_trigger, &sr_echo );

    interrupts::enableInterrupts();

    while( 1 )
    {
        common::sw_delay();
        led.toggle();

        uSensor1.beginSample();

        uartMod.write( 'f' );
        uartMod.write( ':' );
        uartMod.write( ' ' );
        uartMod.writeFloat( uSensor1.distance, 2 );
        uartMod.write( 10 );
        uartMod.write( 13 );
    }
}

#pragma vector=VECTOR_PORT1
__interrupt void port1_isr()
{
    uSensor1.onInterrupt();
}
