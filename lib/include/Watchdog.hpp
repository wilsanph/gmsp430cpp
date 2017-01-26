/*
 * Watchdog.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef WATCHDOG_HPP_
#define WATCHDOG_HPP_

namespace watchdog
{


	namespace config
	{
		namespace hold
		{
			enum _hold
			{
				DONT_HOLD = 0x0000,
				HOLD = 0x0080
			};
		}

		namespace password
		{
			enum _password
			{
				PASSWORD = 0x5a00
			};
		}

		namespace mode
		{
			enum _mode
			{
				WATCHDOG_MODE = 0x0000,
				INTERVAL_MODE =	0x0010
			};
		}

		namespace clockSource
		{
			enum _clockSource
			{
				SMCLK 	= 0x0000,
				ACLK	= 0x0020,
				VLOCLK	= 0x0040,
				X_CLK 	= 0x0060
			};
		}
	}

	class WatchdogTimer
	{
		public:

		WatchdogTimer();
		~WatchdogTimer();

		void init( config::hold::_hold pHold = config::hold::HOLD,
				   config::mode::_mode pMode = config::mode::WATCHDOG_MODE,
				   config::clockSource::_clockSource pClockSource  = config::clockSource::SMCLK );
		void hold();
	};

	namespace cf
	{
		void init( config::hold::_hold pHold = config::hold::HOLD,
				   config::mode::_mode pMode = config::mode::WATCHDOG_MODE,
				   config::clockSource::_clockSource pClockSource = config::clockSource::SMCLK );
		void hold();
	}
}

#include "../src/WatchdogImplement.hpp"

#endif /* WATCHDOG_HPP_ */
