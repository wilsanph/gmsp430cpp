/*
 * UartImplement.hpp
 *
 *  Created on: Dec 15, 2016
 *      Author: wilsan
 */

#ifndef UARTIMPLEMENT_HPP_
#define UARTIMPLEMENT_HPP_

#include "../memorymap/MapUart.hpp"
#include "../include/Uart.hpp"

#define MAP_UART( x ) reinterpret_cast<MapUart::UartRegs*>( x )

namespace uart
{


	Uart::Uart( instanceAddress::_instanceAddress pInstanceAddress )
	{
		m_baseAddress = pInstanceAddress;
	}

	void Uart::config( config::baudrate::_baudrate pBaudRate,
					   config::databits::_databits pDataBits,
					   config::parity::_parity pParity,
					   config::stopbits::_stopbits pStopBits,
					   config::msbfirst::_msbfirst pMSBfirst,
					   config::clockSource::_clockSource pClockSource,
					   config::timingMode::_timingMode pTimingMode )
	{
		// Put the modulee in reset state
		MAP_UART( m_baseAddress )->UCAxCTL1 |= 1;

		MAP_UART( m_baseAddress )->UCAxCTL1 |= ( pClockSource );

		MAP_UART( m_baseAddress )->UCAxCTL0 = ( pDataBits ) |
										( pStopBits ) |
										( pMSBfirst ) |
										( pParity == config::parity::NONE ?
											0x00 : 0x80 ) |
										( pParity >> 1 );

		if ( pTimingMode == config::timingMode::LOW_FREQUENCY )
		{
			volatile u8 baud_int  = 1048576 / pBaudRate;
			volatile u8 baud_frac = ( 1048576 - baud_int * pBaudRate ) * 8;
			baud_frac = baud_frac / pBaudRate + 1;

			// disable the oversampling
			MAP_UART( m_baseAddress )->UCAxMCTL &= 0xfe;

			MAP_UART( m_baseAddress )->UCAxMCTL |= ( baud_frac << 1 );
			MAP_UART( m_baseAddress )->UCAxBR0 = baud_int;
		}
		else
		{
			// not implemented yet
		}

		// Enable the moduleee
		MAP_UART( m_baseAddress )->UCAxCTL1 &= 0xfe;
	}

	void Uart::enableInterrupt( config::interruptMode::_interruptMode pInterrupt )
	{
		MAP_UART( m_baseAddress )->UCAxIE |= ( pInterrupt );
	}

	void Uart::disableInterrupt( config::interruptMode::_interruptMode pInterrupt )
	{
		MAP_UART( m_baseAddress )->UCAxIE &= ( 0xff - pInterrupt );
	}

	void Uart::write( u8 pData )
	{
		// Wait until the txbuf is empty
		while( ( MAP_UART( m_baseAddress )->UCAxIFG & 0x02 ) != 0x02 );

		MAP_UART( m_baseAddress )->UCAxTXBUF = pData;
	}

	u8 Uart::read()
	{
		return MAP_UART( m_baseAddress )->UCAxRXBUF;
	}

	void Uart::writeFloat( float value, u8 decimals )
	{

		if ( value < 0 )
		{
			write( '-' );
			value = -value;
		}

		// normalize the value according to the number of ...
		// decimals to be sent
		u8 q;
		for ( q = 0; q < decimals; q++ )
		{
			value = value * 10;
		}

		if ( value >= 1 )
		{
			// Get the number of digits
			i32 value_int = value;
			i32 currentVal = value_int;
			i32 maxPot10 = 1;
			u8 numOfDigits = 0;

			while( true )
			{
				numOfDigits++;
				if ( currentVal / 10 < 1 )
				{
					break;
				}
				currentVal = ( currentVal - ( currentVal % 10 ) ) / 10;
				maxPot10 *= 10;
			}

			if ( numOfDigits == decimals )
			{
				write( '0' );
				write( '.' );
			}

			for ( q = 0; q < numOfDigits; q++ )
			{
				u8 digit = value_int / maxPot10;
				write( '0' + digit );
				value_int = value_int - ( digit ) * maxPot10;
				maxPot10 = maxPot10 / 10;
				if ( q == numOfDigits - decimals - 1 )
				{
					write( '.' );
				}
			}
		}
		else
		{
			write( '0' );
			write( '.' );
			for( q = 0; q < decimals; q++ )
			{
				write( '0' );
			}
		}

	}
}


#endif /* UARTIMPLEMENT_HPP_ */
