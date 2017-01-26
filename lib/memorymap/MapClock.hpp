/*
 * MapClock.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#ifndef MAPCLOCK_HPP_
#define MAPCLOCK_HPP_

#include "../common.hpp"

namespace MapClock
{

	namespace address
	{
		enum _address
		{
			BASE_ADDRESS = 0x0160
		};
	}

	struct ClockRegs
	{
		u16 UCSCTL0;
		u16 UCSCTL1;
		u16 UCSCTL2;
		u16 UCSCTL3;
		u16 UCSCTL4;
		u16 UCSCTL5;
		u16 UCSCTL6;
		u16 UCSCTL7;
		u16 UCSCTL8;
		u16 UCSCTL9;
	};

}


#endif /* MAPCLOCK_HPP_ */
