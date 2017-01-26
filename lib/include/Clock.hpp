/*
 * Clock.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

namespace clock
{

	namespace config
	{
		namespace clockSource
		{
			enum _clockSource
			{
				XT1CLK 		= 0x00,
				VLOCLK 		= 0x01,
				REFOCLK 	= 0x02,
				DCOCLK		= 0x03,
				DCOCLKDIV	= 0x04,
				XT2CLK 		= 0x05
			};
		}

		namespace clockSignal
		{
			enum _clockSignal
			{
				MCLK  = 0,
				SMCLK = 1,
				ACLK  = 2
			};
		}

		namespace clockDivider
		{
			enum _clockDivider
			{
				DIV_1  = 0x00,
				DIV_2  = 0x01,
				DIV_4  = 0x02,
				DIV_8  = 0x03,
				DIV_16 = 0x04,
				DIV_32 = 0x05
			};
		}

		namespace fllRefSource
		{
			enum _fllRefSource
			{
				XT1CLK 		= 0x00,
				REFOCLK 	= 0x02,
				XT2CLK 		= 0x05
			};
		}

		namespace fllRefDivider
		{
			enum _fllRefDivider
			{
				DIV_1  = 0x00,
				DIV_2  = 0x01,
				DIV_4  = 0x02,
				DIV_8  = 0x03,
				DIV_12 = 0x04,
				DIV_16 = 0x05
			};
		}

		namespace freqRange
		{
			enum _freqRange
			{
				RANGE_0,
				RANGE_1,
				RANGE_2,
				RANGE_3,
				RANGE_4,
				RANGE_5,
				RANGE_6,
				RANGE_7
			};
		}
	}

	class Clock
	{
		public:

		Clock();
		static u32 MasterClockHz;
		static u32 SecondaryMasterClockHz;
		static u32 AuxiliaryClockHz;

		void initClockSignal( config::clockSignal::_clockSignal pClockSignal,
							  config::clockSource::_clockSource pClockSource,
							  config::clockDivider::_clockDivider pClockDivider );

		void initFLL( u16 fllD,
					  u16 fllN,
					  config::freqRange::_freqRange pFreqRange,
					  config::fllRefSource::_fllRefSource pFllRefSource,
					  config::fllRefDivider::_fllRefDivider pFllRefDivider );

		void turnOnXT1();
		void turnOnXT2();
	};

}

#include "../src/ClockImplement.hpp"

#endif /* CLOCK_HPP_ */
