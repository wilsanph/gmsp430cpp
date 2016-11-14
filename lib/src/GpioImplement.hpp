/*
 * GpioImplement.hpp
 *
 *  Created on: Nov 29, 2014
 *      Author: wilsan
 */

#ifndef GPIOIMPLEMENT_HPP_
#define GPIOIMPLEMENT_HPP_

#include "../common.hpp"
#include "../memorymap/MapGpio.hpp"
#include "../include/Gpio.hpp"

namespace Gpio
{

	Gpio::Pin::Pin()
	{
		this->portID = Gpio::port::PORT1;
		this->pinID = Gpio::pins::pin0;
	}


	Gpio::Pin::Pin( Gpio::port::_port port, Gpio::pins::_pins pinID )
	{
		this->portID = port;
		this->pinID = pinID;
	}

	/**
	 * TODO: Can be optimized by using a bitwise XOR and changing the ...
	 * ... config values to their oposite in their definition
	 */

	void Gpio::Pin::setMode( Gpio::config::mode::_mode pinMode )
	{
		// Do a single write to this register by creating a temp variable ...
		// to store the result value of the operation
		volatile u8 unchangedPart = reinterpret_cast<MapGpio::GpioRegs *>
								( this->portID )->PxSEL;
		unchangedPart &= ( 0xff - ( 1 << pinID ) );
		// Put the 'pinMode' value in that bit
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->portID )->PxSEL = unchangedPart + ( pinMode << this->pinID );
	}

	void Gpio::Pin::setIOMode( Gpio::config::ioMode::_ioMode ioMode )
	{
		// Do a single write to this register by creating a temp variable ...
		// to store the result value of the operation
		volatile u8 unchangedPart = reinterpret_cast<MapGpio::GpioRegs *>
								( this->portID )->PxDIR;
		unchangedPart &= ( 0xff - ( 1 << pinID ) );
		// Put the 'ioMode' value in that bit
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->portID )->PxDIR = unchangedPart + ( ioMode << this->pinID );
	}

	void Gpio::Pin::setLow()
	{
		// Put a '0' in the desired bit
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->portID )->PxOUT &= ( 0xff - ( 1 << this->pinID ) );
	}

	void Gpio::Pin::setHigh()
	{
		// Put a '1' in the desired bit
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->portID )->PxOUT |= ( 1 << this->pinID );
	}

	void Gpio::Pin::setValue( u8 val )
	{
		// Do a single write to this register by creating a temp variable ...
		// to store the result value of the operation
		volatile u8 unchangedPart = reinterpret_cast<MapGpio::GpioRegs *>
								( this->portID )->PxOUT;
		unchangedPart &= ( 0xff - ( 1 << pinID ) );
		// Put the 'val' value in that bit
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->portID )->PxOUT = unchangedPart + ( val << this->pinID );
	}

	void Gpio::Pin::toggle()
	{
		// Toggle using the Bitwise XOR operator
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->portID )->PxOUT ^= ( 1 << this->pinID );
	}

	bool Gpio::Pin::isHigh()
	{
		return ( reinterpret_cast<MapGpio::GpioRegs *>( this->portID )->PxIN &
					( 1 << this->pinID ) ) == ( 1 << this->pinID );
	}

	bool Gpio::Pin::isLow()
	{
		return !this->isHigh();
	}
}

#endif /* GPIOIMPLEMENT_HPP_ */
