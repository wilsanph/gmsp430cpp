

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Timer.hpp"
#include "lib/include/Adc.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );
Gpio::Pin pwmOut( Gpio::port::PORT1, Gpio::pins::pin2 );
Gpio::Pin adcIn( Gpio::port::PORT6, Gpio::pins::pin0 );


Timer::Pwm pwmT0Ch1( Timer::instance::TIMERA0,
                     Timer::channel::CH_1 );

adc::Adc adcMod;

float duty = 0.03f;

u16 adcBuff[1] = { 0 };

int main()
{
    dog.init( watchdog::config::clockSource::SMCLK,
              watchdog::config::mode::WATCHDOG_MODE,
              watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );
    
    pwmOut.setMode( Gpio::config::mode::alternate );
    pwmOut.setAlternateMode( Gpio::config::alternateMode::ALT_MODE_2 );

    adcIn.setMode( Gpio::config::mode::alternate );

    adcMod.config( adc::config::channel::CH_0,
    			   adc::config::channel::CH_0,
				   adc::config::conversionMode::SINGLE_CHANNEL_SINGLE_CONVERSION,
				   adc::config::clockSource::SMCLK,
				   adc::config::samplingPeriod::CYCLES_16,
				   adc::config::multiSC::USE );
    adcMod.configInputChannel( 0, adc::config::inputChannel::A0 );

    pwmT0Ch1.stop();
    // 1Mhz clock, and we want 50 hz frequency
    // so 1000000 / 20000 -> 50
    // range:
    // for 20ms -> 20000
    // for 2ms	-> 2000 ... +90° -> 10%
    // for 1ms	-> 1000 ... -90° -> 5%
    pwmT0Ch1.config( 20000,
                     duty,
    		 		 Timer::config::clockMainDivider::DIV_1,
    				 Timer::config::clockSubDivider::DIV_1,
					 Timer::config::clockSource::SMCLK );

    while( 1 )
    {
        common::sw_delay();
        led.toggle();
        adcMod.start();
        while( adcMod.isBusy() );
        adcMod.readBuffer( adcBuff, 1, 0 );
        adcMod.stop();
        pwmT0Ch1.setDuty( 0.03 + 0.09 * ( adcBuff[0] / 4095.0f) );
    }
}
