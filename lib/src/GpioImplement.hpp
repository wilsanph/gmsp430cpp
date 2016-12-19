/*
 * GpioImplement.hpp
 *
 *  Created on: Nov 29, 2014
 *      Author: wilsan
 */

#ifndef GPIOIMPLEMENT_HPP_
#define GPIOIMPLEMENT_HPP_

#include "../common.hpp"
#include "../memorymap/MapGpio.hpp"
#include "../include/Gpio.hpp"

#define GPIOMAP(x) ( reinterpret_cast<MapGpio::GpioRegs *>( x ) )

namespace Gpio
{

    Pin::Pin()
    {
        m_portID = port::PORT1;
        m_pinID = pins::pin0;
    }


    Pin::Pin( port::_port port, pins::_pins pinID )
    {
        m_portID = port;
        m_pinID = pinID;
    }

    void Pin::setMode( config::mode::_mode pinMode )
    {
        volatile u8 _reg = GPIOMAP( m_portID )->PxSEL;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxSEL = REG_PUT_BIT( _reg, m_pinID, pinMode );
    }

    void Pin::setIOMode( config::ioMode::_ioMode ioMode )
    {
        volatile u8 _reg = GPIOMAP( m_portID )->PxDIR;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxDIR = REG_PUT_BIT( _reg, m_pinID, ioMode );
    }

    void Pin::setAlternateMode( config::alternateMode::_alternateMode pinAlternateMode )
    {
        // Same as setting IO mode, it actually uses that bit to ...
        // select the alternate function to use from the 2 available options 
        volatile u8 _reg = GPIOMAP( m_portID )->PxDIR;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxDIR = REG_PUT_BIT( _reg, m_pinID, pinAlternateMode );
    }

    void Pin::setLow()
    {
        GPIOMAP( m_portID )->PxOUT &= MASK_CLEAR_BIT( m_pinID );
    }

    void Pin::setHigh()
    {
        GPIOMAP( m_portID )->PxOUT |= MASK_SET_BIT( m_pinID );
    }

    void Pin::setValue( u8 val )
    {
        volatile u8 _reg = GPIOMAP( m_portID )->PxOUT;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxOUT = REG_PUT_BIT( _reg, m_pinID, val );
    }

    void Pin::toggle()
    {
        GPIOMAP( m_portID )->PxOUT ^= MASK_SET_BIT( m_pinID );
    }

    bool Pin::isHigh()
    {
        return ( GPIOMAP( m_portID )->PxIN & MASK_SET_BIT( m_pinID ) ) == MASK_SET_BIT( m_pinID );
    }

    bool Pin::isLow()
    {
        return !this->isHigh();
    }

    void Pin::enableInterrupt()
    {
        GPIOMAP( m_portID )->PxIE |= MASK_SET_BIT( m_pinID );
    }

    void Pin::disableInterrupt()
    {
        GPIOMAP( m_portID )->PxIE &= MASK_CLEAR_BIT( m_pinID );
    }

    void Pin::clearInterruptFlag()
    {
        GPIOMAP( m_portID )->PxIFG &= MASK_CLEAR_BIT( m_pinID );
    }

    void Pin::selectInterruptEdge( config::interruptEdge::_interruptEdge pIntEdge )
    {
        volatile u8 _reg = GPIOMAP( m_portID )->PxIES;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxIES = REG_PUT_BIT( _reg, m_pinID, pIntEdge );
    }

    void Pin::selectOutputDriveStrength( config::driveStrength::_driveStrength pStrength )
    {
        volatile u8 _reg = GPIOMAP( m_portID )->PxDS;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxDS = REG_PUT_BIT( _reg, m_pinID, pStrength );
    }

    void Pin::selectInputPullResistor( config::pullResistor::_pullResistor pResistor )
    {
        GPIOMAP( m_portID )->PxREN |= MASK_SET_BIT( m_pinID );
        volatile u8 _reg = GPIOMAP( m_portID )->PxOUT;
        _reg = REG_CLEAR_BIT( _reg, m_pinID );
        GPIOMAP( m_portID )->PxOUT = REG_PUT_BIT( _reg, m_pinID, pResistor );
    }











    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::setMode( config::mode::_mode pinMode )
    {
        volatile u8 _reg = GPIOMAP( portID )->PxSEL;
        _reg = REG_CLEAR_BIT( _reg, pinID );
        GPIOMAP( portID )->PxSEL = REG_PUT_BIT( _reg, pinID, pinMode );
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::setIOMode( Gpio::config::ioMode::_ioMode ioMode )
    {
        volatile u8 _reg = GPIOMAP( portID )->PxDIR;
        _reg = REG_CLEAR_BIT( _reg, pinID );
        GPIOMAP( portID )->PxDIR = REG_PUT_BIT( _reg, pinID, ioMode );
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::setAlternateMode( config::alternateMode::_alternateMode pinAlternateMode )
    {
        // Same as setting IO mode, it actually uses that bit to ...
        // select the alternate function to use from the 2 available options 
        volatile u8 _reg = GPIOMAP( portID )->PxDIR;
        _reg = REG_CLEAR_BIT( _reg, pinID );
        GPIOMAP( portID )->PxDIR = REG_PUT_BIT( _reg, pinID, pinAlternateMode );
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::setLow()
    {
        GPIOMAP( portID )->PxOUT &= MASK_CLEAR_BIT( pinID );
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::setHigh()
    {
        GPIOMAP( portID )->PxOUT |= MASK_SET_BIT( pinID );
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::setValue( u8 val )
    {
        volatile u8 _reg = GPIOMAP( portID )->PxOUT;
        _reg = REG_CLEAR_BIT( _reg, pinID );
        GPIOMAP( portID )->PxOUT = REG_PUT_BIT( _reg, pinID, val );
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::toggle()
    {
        GPIOMAP( portID )->PxOUT ^= MASK_SET_BIT( pinID );
    }

    template<port::_port portID, pins::_pins pinID>
    bool TPin<portID,pinID>::isHigh()
    {
        return ( GPIOMAP( portID )->PxIN & MASK_SET_BIT( pinID ) ) == MASK_SET_BIT( pinID );
    }

    template<port::_port portID, pins::_pins pinID>
    bool TPin<portID,pinID>::isLow()
    {
        return !TPin<portID,pinID>::isHigh();
    }

    
    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::enableInterrupt()
    {
        // TODO
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::disableInterrupt()
    {
        // TODO
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::clearInterruptFlag()
    {
        // TODO
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::selectInterruptEdge( config::interruptEdge::_interruptEdge pIntEdge )
    {
        // TODO : Maybe just pass this to the enableInterrupt method
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::selectOutputDriveStrength( config::driveStrength::_driveStrength pStrength )
    {
        // TODO
    }

    template<port::_port portID, pins::_pins pinID>
    void TPin<portID,pinID>::selectInputPullResistor( config::pullResistor::_pullResistor pResistor )
    {
        // TODO
    }
}

#endif /* GPIOIMPLEMENT_HPP_ */
