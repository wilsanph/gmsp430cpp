/*
 * TimerImplement.hpp
 *
 *  Created on: Nov 30, 2014
 *      Author: wilsan
 */

#ifndef TIMERIMPLEMENT_HPP_
#define TIMERIMPLEMENT_HPP_

#include "../common.hpp"
#include "../memorymap/MapTimer.hpp"
#include "../include/Timer.hpp"

namespace Timer
{
	Timer::Timer::Timer()
	{
		this->m_timerID 	= Timer::instance::TIMERA0;
		this->m_subtimerID	= Timer::subtimer::SUBTIMER0;
	}

	Timer::Timer::Timer( Timer::instance::_instance timerID,
						 Timer::subtimer::_subtimer subtimerID )
	{
		this->m_timerID 	= timerID;
		this->m_subtimerID	= subtimerID;
	}

	void Timer::Timer::config( u16 period_ms, 
					 		   Timer::mode::_mode tMode, 
					 		   Timer::divider::_divider tDivider,
					 		   Timer::interrupt::_interrupt tInterrupt,
					 		   Timer::clockSource::_clockSource tClockSource )
	{
		// Clear the previous config
		
	}
}



#endif /* TIMERIMPLEMENT_HPP_ */
