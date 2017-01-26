

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/include/Timer.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

Gpio::Pin sr_trigger( Gpio::port::PORT1, Gpio::pins::pin2 );
Gpio::Pin sr_echo( Gpio::port::PORT1, Gpio::pins::pin3 );

uart::Uart uartMod( uart::instanceAddress::USCIA1 );
Gpio::Pin uart1rx( Gpio::port::PORT4, Gpio::pins::pin4 );
Gpio::Pin uart1tx( Gpio::port::PORT4, Gpio::pins::pin5 );

Timer::TimeEvent timerA0( Timer::instance::TIMERA0,
						  Timer::channel::CH_0 );

void beginTakeDistance();
float processDistance();

float g_distance = 0;

bool fun = false;

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

    sr_trigger.setMode( Gpio::config::mode::gpio );
    sr_trigger.setIOMode( Gpio::config::ioMode::output );
    sr_trigger.setLow();

    sr_echo.setMode( Gpio::config::mode::gpio );
    sr_echo.setIOMode( Gpio::config::ioMode::input );
    sr_echo.selectInputPullResistor( Gpio::config::pullResistor::PULLUP );
    sr_echo.selectInterruptEdge( Gpio::config::interruptEdge::RISING );
    sr_echo.clearInterruptFlag();

    timerA0.stop();
    timerA0.config( 10000,
    				Timer::config::clockMainDivider::DIV_1,
    				Timer::config::clockSubDivider::DIV_1,
					Timer::config::clockSource::SMCLK,
					Timer::config::countMode::UP_MODE );

    interrupts::enableInterrupts();

    while( 1 )
    {
        common::sw_delay();
        led.toggle();

        beginTakeDistance();

        uartMod.write( 'f' );
        uartMod.write( ':' );
        uartMod.write( ' ' );
        uartMod.writeFloat( g_distance, 2 );
        uartMod.write( 10 );
        uartMod.write( 13 );
    }
}

void beginTakeDistance()
{
	// send pulse
	sr_trigger.setHigh();
	common::delay_us( 5 );
	sr_trigger.setLow();

	sr_echo.enableInterrupt();
}

float processDistance()
{
	u16 _timer = timerA0.getTimerReg();
	// The clock is currently running at 1Mhz, so ...
	// the total time in seconds is _timer * ( 1 / 1000000 )
	///float dTime = _timer / 1000000.0f;
	// The distance traveled in time dTime is 34000cm/s * dTime
	// and that is 2 * distance measured
	///float _distance = 34000.0f * dTime / 2.0f;
	// Simplified calculation
	float _distance = _timer / 58.82f;

	return _distance;
}

#pragma vector=VECTOR_PORT1
__interrupt void port1_isr()
{
    if( sr_echo.isHigh() )
    {
    	sr_echo.selectInterruptEdge( Gpio::config::interruptEdge::FALLING );
        timerA0.stop();
        timerA0.config( 10000,
        				Timer::config::clockMainDivider::DIV_1,
        				Timer::config::clockSubDivider::DIV_1,
    					Timer::config::clockSource::SMCLK,
    					Timer::config::countMode::UP_MODE );
    	timerA0.restart();

    	fun = true;
    }
    else
    {
    	sr_echo.selectInterruptEdge( Gpio::config::interruptEdge::RISING );
        timerA0.stop();

        g_distance = processDistance();

        sr_echo.disableInterrupt();

        fun = false;
    }
    sr_echo.clearInterruptFlag();
}
