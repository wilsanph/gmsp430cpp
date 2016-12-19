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

    struct CTLRegFields
    {
        u16 reserved1:6;
        u16 TASSEL:2;
        u16 ID:2;
        u16 MC:2;
        u16 reserved2:1;
        u16 TACLR:1;
        u16 TAIE:1;
        u16 TAIFG:1;
    };
    
    union CTLReg
    {
        u16 reg;
        CTLRegFields fields;
    };
    
    struct CCTLRegFields
    {
        u16 CM:2;
        u16 CCIS:2;
        u16 SCS:1;
        u16 SCCI:1;
        u16 reserved1:1;
        u16 CAP:1;
        u16 OUTMOD:3;
        u16 CCIE:1;
        u16 CCI:1;
        u16 OUT:1;
        u16 COV:1;
        u16 CCIFG:1;
    };
   
    union CCTLReg
    {
        u16 reg;
        CTLRegFields fields;
    };

    struct TimerRegs
    {
        u16 TxyCTL;
        u16 TxyCCTL0;
        u16 TxyCCTL1;
        u16 TxyCCTL2;
        u16 TxyCCTL3;
        u16 TxyCCTL4;
        u16 TxyCCTL5;
        u16 TxyCCTL6;
        u16 TxyR;
        u16 TxyCCR0;
        u16 TxyCCR1;
        u16 TxyCCR2;
        u16 TxyCCR3;
        u16 TxyCCR4;
        u16 TxyCCR5;
        u16 TxyCCR6;
        u16 TxyEX0;
        u16 reserved1[6];//[0x22-0x2d]
        u16 TxyIV;
    };

}



#endif /* MAPTIMER_HPP_ */
