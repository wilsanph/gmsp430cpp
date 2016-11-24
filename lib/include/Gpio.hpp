/*
 * Gpio.hpp
 *
 *  Created on: 17/11/2014
 *      Author: USER01
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#include "../common.hpp"
#include "../memorymap/MapGpio.hpp"

namespace Gpio
{

    namespace port
    {
        enum _port
	{
	    PORT1 = 0x0200,
	    PORT2 = 0x0201,
	    PORT3 = 0x0220,
	    PORT4 = 0x0221,
	    PORT5 = 0x0240,
	    PORT6 = 0x0241,
	    PORT7 = 0x0260,
	    PORT8 = 0x0261
	};
    }

    namespace pins
    {
	enum _pins
	{
	    pin0 = 0,
	    pin1 = 1,
	    pin2 = 2,
	    pin3 = 3,
	    pin4 = 4,
	    pin5 = 5,
	    pin6 = 6,
	    pin7 = 7
	};
    }

    namespace config
    {
        namespace mode
        {
            enum _mode
            {
                gpio = 0,
                alternate = 1
            };
        }

        namespace ioMode
        {
            enum _ioMode
            {
                input = 0,
                output = 1
            };
        }
                
        namespace pullResistor
        {
            enum _pullResistor
            {
                PULLDOWN = 0,
                PULLUP = 1
            };
        }

        namespace driveStrength
        {
            enum _driveStrength
            {
                REDUCED = 0,
                FULL = 1
            };
        }

        namespace interruptEdge
        {
            enum _interruptEdge
            {
                RISING = 0,
                FALLING = 1
            };
        }
    }

    /**
     * @brief Pin class: Handles a single pin
     *
     */
    class Pin
    {

        private:
        /** @property port to whom this pin is related to*/
        port::_port m_portID;
        /** @property index of the pin related to the port it belongs to*/
        pins::_pins m_pinID;

        public:
        /** @constructor 
        *   @brief creates a default pin
        */
        Pin();

        /** @constructor 
         *  @param port
         *  @param pinID
         *  @brief creates a pin related to port <port> and pin <pinID>
         */
        Pin( port::_port port, pins::_pins pinID );

        void setMode( config::mode::_mode pinMode );
        void setIOMode( config::ioMode::_ioMode pinIOMode );
        void setLow();
        void setHigh();
        void setValue( u8 val );
        void toggle();
        bool isHigh();
        bool isLow();

        void enableInterrupt();
        void disableInterrupt();
        void clearInterruptFlag();
        void selectInterruptEdge( config::interruptEdge::_interruptEdge pIntEdge );

        void selectOutputDriveStrength( config::driveStrength::_driveStrength pStrength );
        void selectInputPullResistor( config::pullResistor::_pullResistor pResistor );
    };
        
    template <port::_port portID,pins::_pins pinID>
    class TPin
    {
        
        static void setMode( config::mode::_mode pinMode );
        static void setIOMode( config::ioMode::_ioMode pinIOMode );
        static void setLow();
        static void setHigh();
        static void setValue( u8 val );
        static void toggle();
        static bool isHigh();
        static bool isLow();
        
        static void enableInterrupt();
        static void disableInterrupt();
        static void clearInterruptFlag();
        static void selectInterruptEdge( config::interruptEdge::_interruptEdge pIntEdge );

        static void selectOutputDriveStrength( config::driveStrength::_driveStrength pStrength );
        static void selectInputPullResistor( config::pullResistor::_pullResistor pResistor );
    };

}

#include "../src/GpioImplement.hpp"



#endif /* GPIO_HPP_ */
