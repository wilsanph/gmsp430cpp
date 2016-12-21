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
}


#endif /* UARTIMPLEMENT_HPP_ */
