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

#define GPIOMAP(x) ( reinterpret_cast<MapGpio::GpioRegs *>( x ) )

namespace Gpio
{

	Gpio::Pin::Pin()
	{
		this->m_portID = Gpio::port::PORT1;
		this->m_pinID = Gpio::pins::pin0;
	}


	Gpio::Pin::Pin( Gpio::port::_port port, Gpio::pins::_pins pinID )
	{
		this->m_portID = port;
		this->m_pinID = pinID;
	}

	void Gpio::Pin::setMode( Gpio::config::mode::_mode pinMode )
	{
        volatile u8 _reg = GPIOMAP( m_portID )->PxSEL;
	    _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxSEL = REG_PUT_BIT( _reg, m_pinID, pinMode );
	}

	void Gpio::Pin::setIOMode( Gpio::config::ioMode::_ioMode ioMode )
	{
        volatile u8 _reg = GPIOMAP( m_portID )->PxDIR;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxDIR = REG_PUT_BIT( _reg, m_pinID, ioMode );
	}

	void Gpio::Pin::setLow()
	{
        GPIOMAP( m_portID )->PxOUT &= MASK_CLEAR_BIT( m_pinID );
	}

	void Gpio::Pin::setHigh()
	{
        GPIOMAP( m_portID )->PxOUT |= MASK_SET_BIT( m_pinID );
	}

	void Gpio::Pin::setValue( u8 val )
	{
        volatile u8 _reg = GPIOMAP( m_portID )->PxOUT;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxOUT = REG_PUT_BIT( _reg, m_pinID, val );
	}

	void Gpio::Pin::toggle()
	{
        GPIOMAP( m_portID )->PxOUT ^= MASK_SET_BIT( m_pinID );
	}

	bool Gpio::Pin::isHigh()
	{
		return ( GPIOMAP( m_portID )->PxIN & MASK_SET_BIT( m_pinID ) ) == MASK_SET_BIT( m_pinID );
	}

	bool Gpio::Pin::isLow()
	{
		return !this->isHigh();
	}
}

#endif /* GPIOIMPLEMENT_HPP_ */
