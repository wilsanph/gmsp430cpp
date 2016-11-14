/*
 * MapGpio.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#ifndef MAPGPIO_HPP_
#define MAPGPIO_HPP_

#include "../common.hpp"

namespace MapGpio {

	struct GpioRegs
	{
		u8 PxIN;
		u8 reserved1;// PxIN-2 or PxOUT-1
		u8 PxOUT;
		u8 reserved2;// PxOUT-2 or PxDIR-1
		u8 PxDIR;
		u8 reserved3;// PxDIR-2 or PxREN-1
		u8 PxREN;
		u8 reserved4;// PxREN-2 or PxDS-1
		u8 PxDS;
		u8 reserved5;// PxDS-2 or PxSEL-1
		u8 PxSEL;
		u8 reserved6;// PxSEL-2
	};

	struct InterruptRegs
	{
		u8 PxIV;
		u8 reserved1;// PxIV-2
		u8 PxIES;
		u8 reserved2;// PxIES-2
		u8 PxIE;
		u8 reserved3;// PxIE-2
		u8 PxIFG;
		u8 reserved4;// PxIFG-2
	};



}


#endif /* MAPGPIO_HPP_ */
