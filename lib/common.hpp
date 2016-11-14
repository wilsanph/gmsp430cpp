/*
 * common.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define NULL 0

namespace common
{
	void sw_delay();
}

void common::sw_delay()
{
	volatile unsigned int i;
	for( i = 0; i < 10000; i++ );
}

#endif /* COMMON_HPP_ */
