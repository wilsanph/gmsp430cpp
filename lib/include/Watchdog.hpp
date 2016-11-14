/*
 * Watchdog.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef WATCHDOG_HPP_
#define WATCHDOG_HPP_

namespace Watchdog
{

	enum _password
	{
		password = 0x5a00
	};

	namespace config
	{
		namespace holdWatchdog
		{
			enum _holdWatchdog
			{

			};
		}
	}

	class WatchdogTimer
	{
	private:

	public:

		void init();
	};

}



#endif /* WATCHDOG_HPP_ */
