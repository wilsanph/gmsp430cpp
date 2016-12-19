/*
 * MapWatchdog.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef MAPWATCHDOG_HPP_
#define MAPWATCHDOG_HPP_

#include "../common.hpp"

namespace MapWatchdog
{
	namespace address
	{
		enum _address
		{
			BASE_ADDRESS = 0x015c
		};
	}

	struct WatchdogRegs
	{
		u16 WDTCTL;
	};
}



#endif /* MAPWATCHDOG_HPP_ */
