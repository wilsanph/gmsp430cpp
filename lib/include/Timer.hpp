/*
 * Timer.hpp
 *
 *  Created on: Dec 5, 2016
 *      Author: gregor
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace Timer
{

    namespace instance
    {
        enum _instance
        {
            TIMERA0 = 0x0340,
            TIMERA1 = 0x0380,
            TIMERB0 = 0x03c0,   
            TIMERA2 = 0x0400
        };
    }

    namespace channel
    {
        enum _channel
        {
            CH_0,
            CH_1,
            CH_2,
            CH_3,
            CH_4,
            CH_5,
            CH_6
        };
    }

    namespace config
    {
    
        namespace clockSource
        {
            enum _clockSource
            {
                TAxCLK  = 0x0000,
                ACLK    = 0x0100,
                SMCLK   = 0x0200,
                INCLK   = 0x0300
            };
        }

        namespace clockMainDivider
        {
            enum _clockMainDivider
            {
                DIV_1   = 0x0000,
                DIV_2   = 0x0040,
                DIV_4   = 0x0080,
                DIV_8   = 0x00c0
            };
        }

        namespace clockSubDivider
        {
            enum _clockSubDivider
            {  
                DIV_1   = 0x00,
                DIV_2   = 0x01,
                DIV_3   = 0x02,
                DIV_4   = 0x03,
                DIV_5   = 0x04,
                DIV_6   = 0x05,
                DIV_7   = 0x06,
                DIV_8   = 0x07
            };
        }

        namespace countMode
        {
            enum _countMode
            {
                STOP_MODE       = 0x0000,
                UP_MODE         = 0x0010,
                CONTINUOUS_MODE = 0x0020,
                UP_DOWN_MODE    = 0x0030
            };
        }

        namespace captureMode
        {
            enum _captureMode
            {
                NO_CAPTURE              = 0x0000,
                CAPTURE_RISING_EDGE     = 0x4000,
                CAPTURE_FALLING_EDGE    = 0x8000,
                CAPTURE_BOTH_EDGES      = 0xc000
            };
        }

        namespace captureInput
        {
            enum _captureInput
            {
                CCIxA = 0x0000,
                CCIxB = 0x1000,
                GND   = 0x2000,
                VCC   = 0x3000
            };
        }

        namespace ccMode
        {
            enum _ccMode
            {
                COMPARE = 0x0000,
                CAPTURE = 0x0100               
            };
        }

        namespace outputMode
        {
            enum _outputMode
            {
                OUT_BIT         = 0x0000,
                SET             = 0x0020,
                TOGGLE_RESET    = 0x0040,
                SET_RESET       = 0x0060,
                TOGGLE          = 0x0080,
                RESET           = 0x00a0,
                TOGGLE_SET      = 0x00c0,
                RESET_SET       = 0x00e0
            };
        }
    }

    class TimeEvent
    {
        private:

        instance::_instance m_timer;

        channel::_channel m_channel;

        public:

        TimeEvent( instance::_instance timer,
                   channel::_channel channel );

        void stop();

        void config( u16 calcPeriod_ms,
                     config::clockMainDivider::_clockMainDivider pClockMainDivider,
                     config::clockSubDivider::_clockSubDivider pClockSubDivider,
                     config::clockSource::_clockSource pClockSource,
                     config::countMode::_countMode pCountMode );

        void restart();

        void enableInterrupt();

        bool isInterruptPending();

        u16 getTimerReg();
        void setTimerReg( u16 pTimerValue );
    };

    class Pwm
    {
        private :

        instance::_instance m_timer;
        channel::_channel m_channel;

        u16 m_period;
        u16 m_duty;

        public :

        Pwm( instance::_instance pTimer,
             channel::_channel pChannel );

        /**
        * @brief stops the whole timer and all channels
        */
        void stop();

        
        void config( u16 pCalcPeriod,
                     float pInitDuty,
                     config::clockMainDivider::_clockMainDivider pCalcMainDivider,
                     config::clockSubDivider::_clockSubDivider pCalcSubDivider,
                     config::clockSource::_clockSource pClockSource = config::clockSource::SMCLK );

        void setDuty( float pCalcDuty );
    };

}

#include "../src/TimerImplement.hpp"

#endif /* TIMER_HPP_ */
