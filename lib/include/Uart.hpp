/*
 * Uart.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef UART_HPP_
#define UART_HPP_

namespace uart
{

	namespace instanceAddress
	{
		enum _instanceAddress
		{
			USCIA0 = 0x05c0,
			USCIA1 = 0x0600
		};
	}

	namespace config
	{

		namespace clockSource
		{
			enum _clockSource
			{
				UCAxCLK = 0x00,
				ACLK = 0x40,
				SMCLK = 0x80
			};
		}

		namespace databits
		{
			enum _databits
			{
				BITS_8 = 0x00,
				BITS_7 = 0x10
			};
		}

		namespace parity
		{
			enum _parity
			{
				NONE = 0x00,
				EVEN = 0x01,
				ODD  = 0x80
			};
		}

		namespace baudrate
		{	
			enum _baudrate
			{
				BAUDRATE_9600 = 9600,
				BAUDRATE_19200 = 19200,
				BAUDRATE_38400 = 38400,
				BAUDRATE_57600 = 57600,
				BAUDRATE_115200 = 115200 
			};
		}

		namespace stopbits
		{
			enum _stopbits
			{
				STOPBITS_1 = 0x00,
				STOPBITS_2 = 0x08
			};
		}

		namespace msbfirst
		{
			enum _msbfirst
			{
				LSB_FIRST = 0x00,
				MSB_FIRST = 0x20
			};
		}

		namespace timingMode
		{
			enum _timingMode
			{
				LOW_FREQUENCY,
				OVERSAMPLING
			};
		}

	}

	class Uart
	{
		private :

		instanceAddress::_instanceAddress m_baseAddress;

		public :

		Uart( instanceAddress::_instanceAddress pInstanceAddress );

		void config( config::baudrate::_baudrate pBaudRate,
					 config::databits::_databits pDataBits,
					 config::parity::_parity pParity,
					 config::stopbits::_stopbits pStopBits,
					 config::msbfirst::_msbfirst pMSBfirst,
					 config::clockSource::_clockSource pClockSource,
					 config::timingMode::_timingMode pTimingMode );

		void write( u8 pData );

		u8 read();
	};

}

#include "../src/UartImplement.hpp"

#endif /* UART_HPP_ */
