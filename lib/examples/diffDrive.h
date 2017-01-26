

#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include "lib/include/Uart.hpp"
#include "lib/drivers/Motor.hpp"
#include "lib/interrupts.h"

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

uart::Uart uartMod( uart::instanceAddress::USCIA1 );
Gpio::Pin uart1rx( Gpio::port::PORT4, Gpio::pins::pin4 );
Gpio::Pin uart1tx( Gpio::port::PORT4, Gpio::pins::pin5 );


struct MotorInfo
{
	float speed;
	u8 direction;
};

MotorInfo motor1Info;
MotorInfo motor2Info;

Gpio::Pin pwmOut1( Gpio::port::PORT1, Gpio::pins::pin2 );
Gpio::Pin pwmOut2( Gpio::port::PORT1, Gpio::pins::pin3 );
Gpio::Pin motorDir1( Gpio::port::PORT1, Gpio::pins::pin4 );
Gpio::Pin motorDir2 ( Gpio::port::PORT1, Gpio::pins::pin5 );

Timer::Pwm pwmT0Ch1( Timer::instance::TIMERA0,
                     Timer::channel::CH_1 );
Timer::Pwm pwmT0Ch2( Timer::instance::TIMERA0,
                     Timer::channel::CH_2 );

motor::Motor motor1;
motor::Motor motor2;

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

    motor1Info.speed = 0;
    motor2Info.speed = 0;


    while( 1 )
    {
        common::sw_delay();
        led.toggle();

        motor1.setSpeed( motor1Info.speed );
        motor2.setSpeed( motor2Info.speed );
    }
}


#pragma vector=VECTOR_USCI_A1
__interrupt void uartrx_isr()
{

	u8 rxByte = uartMod.read();

	if ( rxByte == 'w' )
	{
		motor1Info.speed += 0.1;
		motor2Info.speed += 0.1;
	}
	else if ( rxByte == 's' )
	{
		motor1Info.speed -= 0.1;
		motor2Info.speed -= 0.1;
	}

}


