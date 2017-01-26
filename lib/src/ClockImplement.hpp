/*
 * ClockImplement.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: wilsan
 */

#ifndef CLOCKIMPLEMENT_HPP_
#define CLOCKIMPLEMENT_HPP_

#include "../memorymap/MapClock.hpp"
#include "../include/Clock.hpp"

#define MAP_CLOCK reinterpret_cast<MapClock::ClockRegs*>( MapClock::address::BASE_ADDRESS )

namespace clock
{

	Clock::Clock()
	{
	}

	u32 Clock::MasterClockHz 			= 10000000;
	u32 Clock::SecondaryMasterClockHz	= 10000000;
	u32 Clock::AuxiliaryClockHz 		= 10000000;

	void Clock::initClockSignal( config::clockSignal::_clockSignal pClockSignal,
							  	 config::clockSource::_clockSource pClockSource,
							  	 config::clockDivider::_clockDivider pClockDivider )
	{
		volatile u16 reg = MAP_CLOCK->UCSCTL4;
		reg &= ( 0xffff - ( 0x7 << ( pClockSignal * 4 ) ) );
		reg |= ( pClockSource << ( pClockSignal * 4 ) );
		MAP_CLOCK->UCSCTL4 = reg;

		volatile u16 reg = MAP_CLOCK->UCSCTL5;
		reg &= ( 0xffff - ( 0x7 << ( pClockSignal * 4 ) ) );
		reg |= ( pClockDivider << ( pClockSignal * 4 ) );
		MAP_CLOCK->UCSCTL5 = reg;
	}

	void Clock::initFLL( u16 fllD,
						 u16 fllN,
						 config::freqRange::_freqRange pFreqRange,
						 config::fllRefSource::_fllRefSource pFllRefSource,
						 config::fllRefDivider::_fllRefDivider pFllRefDivider )
	{
		// disable fll
		asm( " bis.w #SCG0,SR" );

		// configure *************************************************
		// Select the range of frequency the DCO is going to use
		MAP_CLOCK->UCSCTL1 = ( freqRange << 4 );
		// Set the multipliers for the fll
		MAP_CLOCK->UCSCTL2 = ( fllD << 12 ) | fllN;
		// Set the fll source and divider
		MAP_CLOCK->UCSCTL3 = ( pFllRefSource << 4 ) | pFllRefDivider;
		// ***********************************************************

		// reenable fll
		asm( " bic.w #SCG0,SR" );

		// wait till the fll does it sweetness
		while( ( MAP_CLOCK->UCSCTL7 & 0x1 ) != 0 );
	}

	void Clock::turnOnXT1()
	{
		MAP_CLOCK->UCSCTL6 &= ( 0xffff - ( 1 << 0 ) );
	}

	void Clock::turnOnXT2()
	{
		MAP_CLOCK->UCSCTL6 &= ( 0xffff - ( 1 << 8 ) );
	}

}


#endif /* CLOCKIMPLEMENT_HPP_ */
