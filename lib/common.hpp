/*
 * common.hpp
 *
 *  Created on: 18/11/2014
 *      Author: USER01
 */

#pragma once

#ifndef COMMON_HPP_
#define COMMON_HPP_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char i8;
typedef signed short i16;
typedef int i32;

#define NULL 0

#define MASK_SET_BIT(bit) ( 1 << bit )
#define MASK_CLEAR_BIT(bit) ( 0xff - ( 1 << bit ) )
#define REG_CLEAR_BIT(reg,bit) ( 0xff - ( 1 << bit ) ) & reg
#define REG_SET_BIT(reg,bit) ( 1 << bit ) | reg
#define REG_PUT_BIT(reg,bit,value) ( value << bit ) | reg

namespace common
{
	void delay10us();

	void sw_delay();
	extern "C"
	{
		extern void delay_us( u16 us );
		extern void delay_ms( u16 ms );
	}
}

void common::delay10us()
{
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}

void common::sw_delay()
{
	volatile unsigned int i;
	for( i = 0; i < 10000; i++ );
}

#endif /* COMMON_HPP_ */
