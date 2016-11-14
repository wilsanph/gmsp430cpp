/*
 * Timer.hpp
 *
 *  Created on: Nov 30, 2014
 *      Author: wilsan
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace Timer
{

	namespace instance
	{
		enum _instance
		{
			TIMERA0 = 0x0340,
			TIMERA1 = 0x0380,
			TIMERA2 = 0x0400
		};
	}

	namespace subtimer
	{
		enum _subtimer 
		{
			SUBTIMER0 = 0,
			SUBTIMER1 = 1,
			SUBTIMER2 = 2,
			SUBTIMER3 = 3,
			SUBTIMER4 = 4,
			SUBTIMER5 = 5,
			SUBTIMER6 = 6,
			SUBTIMER7 = 7
		};
	}

	namespace config
	{
		namespace mode
		{
			enum _mode 
			{
				stop = 0,
				countUp = 16,
				countContinuous = 32,
				countUpAndDown = 48
			}; 
		}

		namespace clockSource
		{
			enum _clockSource
			{
				ACLK = 0x100,
				SMCLK = 0x200,
				INCLK = 0x300
			};
		}

		namespace divider
		{
			enum _divider
			{
				div_1 = 0,
				div_2 = 0x040,
				div_3 = 0x080,
				div_4 = 0x0c0
			};
		}

		namespace interrupt
		{
			enum _interrupt 
			{  
				disabled = 0x0,
				enabled = 0x2
			};
		}
	}

	class Timer
	{
	private:
		instance::_instance m_timerID;
		subtimer::_subtimer m_subtimerID;
		void enableClock( clockSource::_clockSource tClockSource );

	public:		
		Timer();
		Timer( instance::_instance timerID, 
			   subtimer::_subtimer subtimerID );
		void config( u16 period_ms, 
					 mode::_mode tMode, 
					 divider::_divider tDivider,
					 interrupt::_interrupt tInterrupt,
					 clockSource::_clockSource tClockSource );
	};

}

#include "../src/TimerImplement.hpp"

#endif /* TIMER_HPP_ */
