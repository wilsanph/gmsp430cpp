/*
 * blink.hpp
 *
 *  Created on: Nov 29, 2014
 *      Author: wilsan
 */

#ifndef BLINK_HPP_
#define BLINK_HPP_

#include "../include/Gpio.hpp"

Gpio::Pin led( Gpio::baseAddresses::PORT1, Gpio::pins::pin0 );

int main()
{

	led.setMode( Gpio::config::mode::gpio );
	led.setIOMode( Gpio::config::ioMode::output );

	while( 1 )
	{
		common::sw_delay();
		led.toggle();
	}
}



#endif /* BLINK_HPP_ */
