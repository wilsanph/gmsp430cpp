

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/drivers/Motor.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

uart::Uart uartMod( uart::instanceAddress::USCIA0 );
Gpio::Pin uart1rx( Gpio::port::PORT3, Gpio::pins::pin4 );
Gpio::Pin uart1tx( Gpio::port::PORT3, Gpio::pins::pin3 );

struct RobotInfo
{
	float v;
	float wl;
	float v1;
	float v2;
};

RobotInfo robotInfo;

Gpio::Pin pwmOut1( Gpio::port::PORT1, Gpio::pins::pin2 );
Gpio::Pin pwmOut2( Gpio::port::PORT1, Gpio::pins::pin3 );
Gpio::Pin motorDir1( Gpio::port::PORT1, Gpio::pins::pin4 );
Gpio::Pin motorDir2 ( Gpio::port::PORT1, Gpio::pins::pin5 );

Timer::Pwm pwmT0Ch1( Timer::instance::TIMERA0,
                     Timer::channel::CH_1 );
Timer::Pwm pwmT0Ch2( Timer::instance::TIMERA0,
                     Timer::channel::CH_2 );

motor::Motor motor1( motor::direction::CLOCKWISE );
motor::Motor motor2( motor::direction::COUNTER_CLOCKWISE );

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

    uartMod.enableInterrupt( uart::config::interruptMode::INTERRUPT_RX );

    motor1.init( &motorDir1,
                 &pwmOut1,
                 &pwmT0Ch1 );

    motor2.init( &motorDir2,
                 &pwmOut2,
                 &pwmT0Ch2 );

    interrupts::enableInterrupts();

    robotInfo.v1 = 0;
    robotInfo.v2 = 0;
    robotInfo.v = 0;
    robotInfo.wl = 0;

    while( 1 )
    {
        common::sw_delay();
        led.toggle();

        robotInfo.v1 = robotInfo.v + 0.5 * robotInfo.wl;
        robotInfo.v2 = robotInfo.v - 0.5 * robotInfo.wl;

        motor1.setSpeed( robotInfo.v1 );
        motor2.setSpeed( robotInfo.v2 );
    }
}


#pragma vector=VECTOR_USCI_A0
__interrupt void uartrx_isr()
{

	u8 rxByte = uartMod.read();

	if ( rxByte == 'w' )
	{
		robotInfo.v += 0.1;
	}
	else if ( rxByte == 's' )
	{
		robotInfo.v -= 0.1;
	}
	else if ( rxByte == 'a' )
	{
		robotInfo.wl += 0.1;
	}
	else if ( rxByte == 'd' )
	{
		robotInfo.wl -= 0.1;
	}

	// v and w are set via commands
	// v = ( v1 + v2 ) / 2
	// w = ( v1 - v2 ) / L
    robotInfo.v = ( robotInfo.v > 0.5 ? 0.5 : robotInfo.v );
    robotInfo.v = ( robotInfo.v < -0.5 ? -0.5 : robotInfo.v );

    robotInfo.wl = ( robotInfo.wl > 1 ? 1 : robotInfo.wl );
    robotInfo.wl = ( robotInfo.wl < -1 ? -1 : robotInfo.wl );
}


