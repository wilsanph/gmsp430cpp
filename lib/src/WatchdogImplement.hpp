/*
 * WatchdogImplement.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef WATCHDOGIMPLEMENT_HPP_
#define WATCHDOGIMPLEMENT_HPP_

#include "../memorymap/MapWatchdog.hpp"
#include "../include/Watchdog.hpp"

namespace watchdog
{

	WatchdogTimer::WatchdogTimer()
	{
	}

	WatchdogTimer::~WatchdogTimer()
	{
	}

	void WatchdogTimer::init( config::hold::_hold pHold,
							  config::mode::_mode pMode,
							  config::clockSource::_clockSource pClockSource )
	{
		reinterpret_cast<MapWatchdog::WatchdogRegs*>
				( MapWatchdog::address::BASE_ADDRESS )->WDTCTL = config::password::PASSWORD |
																 pMode | pClockSource | pHold;
	}

	void WatchdogTimer::hold()
	{
		volatile u16 _reg = reinterpret_cast<MapWatchdog::WatchdogRegs*>
									( MapWatchdog::address::BASE_ADDRESS )->WDTCTL & ( 0x00ff );
		reinterpret_cast<MapWatchdog::WatchdogRegs*>
					( MapWatchdog::address::BASE_ADDRESS )->WDTCTL = config::password::PASSWORD |
																	 _reg | config::hold::HOLD;
	}	

	void cf::init( config::hold::_hold pHold,
				   config::mode::_mode pMode,
				   config::clockSource::_clockSource pClockSource )
	{
		reinterpret_cast<MapWatchdog::WatchdogRegs*>
				( MapWatchdog::address::BASE_ADDRESS )->WDTCTL = config::password::PASSWORD |
																 pMode | pClockSource | pHold;
	}

	void cf::hold()
	{
		volatile u16 _reg = reinterpret_cast<MapWatchdog::WatchdogRegs*>
									( MapWatchdog::address::BASE_ADDRESS )->WDTCTL & ( 0x00ff );
		reinterpret_cast<MapWatchdog::WatchdogRegs*>
					( MapWatchdog::address::BASE_ADDRESS )->WDTCTL = config::password::PASSWORD |
																	 _reg | config::hold::HOLD;
	}
}


#endif /* WATCHDOGIMPLEMENT_HPP_ */
