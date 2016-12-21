/*
 * MapUart.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#ifndef MAPUART_HPP_
#define MAPUART_HPP_

#include "../common.hpp"

namespace MapUart
{

	struct UartRegs
	{
		u8 UCAxCTL1;// 	0x00
		u8 UCAxCTL0;// 	0x01
		u8 rsvd1[4];// 	0x02,0x03,0x04,0x05
		u8 UCAxBR0;// 	0x06
		u8 UCAxBR1;// 	0x07
		u8 UCAxMCTL;// 	0x08
		u8 rsvd2[1];// 	0x09
		u8 UCAxSTAT;//	0x0a
		u8 rsvd3[1];// 	0x0b
		u8 UCAxRXBUF;// 0x0c
		u8 rsvd4[1];//	0x0d
		u8 UCAxTXBUF;// 0x0e
		u8 rsvd5[1];// 	0x0f
		u8 UCAxABCTL;// 0x10
		u8 rsvd6[1];// 	0x11
		u8 UCAxIRTCTL;//0x12
		u8 UCAxIRRCTL;//0x13
		u8 rsvd7[8];//  0x14-0x1b
		u8 UCAxIE;//  	0x1c
		u8 UCAxIFG;//  	0x1d
		u16 UCAxIV;//   0x1e
	};

}


#endif /* MAPUART_HPP_ */
