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
	struct WatchdogRegs
	{
		u8 reserved1[12];
		u16 WDTCTL;// 0x0c
	};
}



#endif /* MAPWATCHDOG_HPP_ */
