/*
 * MapAdc.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#ifndef MAPADC_HPP_
#define MAPADC_HPP_

#include "../common.hpp"

namespace MapAdc
{

	namespace address
	{
		enum _address
		{
			BASE_ADDRESS = 0x0700
		};
	}

	struct AdcRegs
	{
		u16 CTL0;
		u16 CTL1;
		u16 CTL2;
		u16 rsvd[2];
		u16 IFG;
		u16 IE;
		u16 IV;
		u8 MCTL[16];
		u16 MEM[16];
	};

}


#endif /* MAPADC_HPP_ */
