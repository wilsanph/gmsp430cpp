

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/include/Timer.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

Gpio::Pin sr_trigger( Gpio::port::PORT1, Gpio::pins::pin2 );
Gpio::Pin sr_echo( Gpio::port::PORT1, Gpio::pins::pin3 );

Timer::TimeEvent timerA0( Timer::instance::TIMERA0,
						  Timer::channel::CH_0 );

void takeDistance();
void beginTakeDistance();
u16 processDistance();

u16 g_distance = 0;

bool fun = false;

int main()
{
    dog.init( watchdog::config::clockSource::SMCLK,
              watchdog::config::mode::WATCHDOG_MODE,
              watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );

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

    if ( sr_echo.isLow() )
    {
    	g_distance = 0;
    }

    interrupts::enableInterrupts();

    while( 1 )
    {
        common::sw_delay();
        common::delay_us( 100 );
        led.toggle();

        beginTakeDistance();
    }
}

void beginTakeDistance()
{
	// send pulse
	sr_trigger.setHigh();
	common::delay_us( 10 );
	sr_trigger.setLow();

	sr_echo.enableInterrupt();
}

u16 processDistance()
{
	u16 _timer = timerA0.getTimerReg();

	return _timer;
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
