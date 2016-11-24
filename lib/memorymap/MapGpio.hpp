/*
 * MapGpio.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#ifndef MAPGPIO_HPP_
#define MAPGPIO_HPP_

#include "../common.hpp"

namespace MapGpio
{

	struct GpioRegs
	{
		u8 PxIN;//0x00
		u8 reserved1;// PxIN-2 or PxOUT-1 //0x01
		u8 PxOUT;//0x02
		u8 reserved2;// PxOUT-2 or PxDIR-1//0x03
		u8 PxDIR;//0x04
		u8 reserved3;// PxDIR-2 or PxREN-1//0x05
		u8 PxREN;//0x06
		u8 reserved4;// PxREN-2 or PxDS-1//0x07
		u8 PxDS;//0x08
		u8 reserved5;// PxDS-2 or PxSEL-1//0x09
		u8 PxSEL;//0x0a
		u8 reserved6;// PxSEL-2//0x0b
		u8 reserved7[12];//[0x0c-0x17]
		u8 PxIES;//0x18
		u8 reserved8;// PxIES-2 or PxIE-1 //0x19
		u8 PxIE;//0x1a
		u8 reserved9;// PxIE-2 or PxIFG //0x1b
		u8 PxIFG;//0x1c
		u8 reserved10;// PxIFG-2 // 0x1d
	};

}


#endif /* MAPGPIO_HPP_ */
