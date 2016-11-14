/*
 * MapTimer.hpp
 *
 *  Created on: Nov 30, 2014
 *      Author: wilsan
 */

#ifndef MAPTIMER_HPP_
#define MAPTIMER_HPP_

#include "../common.hpp"

namespace MapTimer
{

	struct TimerARegs
	{
		u16 TAxCTL;
		u16 TAxCCTL0;
		u16 TAxCCTL1;
		u16 TAxCCTL2;
		u16 TAxCCTL3;
		u16 TAxCCTL4;
		u16 reserved1;
		u16 reserved2;
		u16 TAxR;
		u16 TAxCCR0;
		u16 TAxCCR1;
		u16 TAxCCR2;
		u16 TAxCCR3;
		u16 TAxCCR4;
		u16 reserved3;
		u16 reserved4;
		u16 TAxEX0;
		u16 TAxIV;
	};

	struct TimerBRegs
	{
		u16 TBxCTL;
		u16 TBxCCTL0;
		u16 TBxCCTL1;
		u16 TBxCCTL2;
		u16 TBxCCTL3;
		u16 TBxCCTL4;
		u16 TBxCCTL5;
		u16 TBxCCTL6;
		u16 TBxR;
		u16 TBxCCR0;
		u16 TBxCCR1;
		u16 TBxCCR2;
		u16 TBxCCR3;
		u16 TBxCCR4;
		u16 TBxCCR5;
		u16 TBxCCR6;
		u16 TBxEX0;
		u16 TBxIV;
	};

}



#endif /* MAPTIMER_HPP_ */
