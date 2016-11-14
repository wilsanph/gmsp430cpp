/*
 * Gpio.hpp
 *
 *  Created on: 17/11/2014
 *      Author: USER01
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#include "../common.hpp"
#include "../memorymap/MapGpio.hpp"

namespace Gpio
{

	namespace port
	{
		enum _port
		{
			PORT1 = 0x0200,
			PORT2 = 0x0201,
			PORT3 = 0x0220,
			PORT4 = 0x0221,
			PORT5 = 0x0240,
			PORT6 = 0x0241,
			PORT7 = 0x0260,
			PORT8 = 0x0261
		};
	}

	namespace pins
	{
		enum _pins
		{
			pin0 = 0,
			pin1 = 1,
			pin2 = 2,
			pin3 = 3,
			pin4 = 4,
			pin5 = 5,
			pin6 = 6,
			pin7 = 7
		};
	}

	namespace config
	{
		namespace mode
		{
			enum _mode
			{
				gpio = 0,
				alternate = 1
			};
		}

		namespace ioMode
		{
			enum _ioMode
			{
				input = 0,
				output = 1
			};
		}

	}

	/**
	 * @brief
	 *
	 */
	class Pin
	{

	private:
		port::_port portID;
		pins::_pins pinID;

	public:
		Pin();
		Pin( port::_port port, pins::_pins pinID );
		void setMode( config::mode::_mode pinMode );
		void setIOMode( config::ioMode::_ioMode pinIOMode );
		void setLow();
		void setHigh();
		void setValue( u8 val );
		void toggle();
		bool isHigh();
		bool isLow();

	};

}

#include "../src/GpioImplement.hpp"



#endif /* GPIO_HPP_ */
