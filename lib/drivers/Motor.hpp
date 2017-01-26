

#pragma once

#include "../include/Gpio.hpp"
#include "../include/Timer.hpp"



namespace motor
{

	namespace direction 
	{
		enum _direction
		{
			CLOCKWISE,
			COUNTER_CLOCKWISE
		};
	}

	class Motor
	{
		private:

		Gpio::Pin* m_pinDir;
		Gpio::Pin* m_pwmOutPin;
		Timer::Pwm* m_pwm;

		float m_duty;
		direction::_direction m_direction;
		direction::_direction m_initialDirection;

		public:

		Motor( direction::_direction pInitialDirection)
		{
			m_direction = m_initialDirection = pInitialDirection;
			m_pinDir = NULL;
			m_pwm = NULL;
			m_pwmOutPin = NULL;
			m_duty = 0;
		}

		~Motor()
		{
			m_pwm = NULL;
			m_pinDir = NULL;
			m_pwmOutPin = NULL;
		}

		void init( Gpio::Pin* pPinDir,
				   Gpio::Pin* pPwmOutPin,
				   Timer::Pwm* pPwm )
		{
			m_pinDir = pPinDir;
			m_pwm = pPwm;
			m_pwmOutPin = pPwmOutPin;

			m_pinDir->setMode( Gpio::config::mode::gpio );
			m_pinDir->setIOMode( Gpio::config::ioMode::output );

			m_pwmOutPin->setMode( Gpio::config::mode::alternate );
			m_pwmOutPin->setAlternateMode( Gpio::config::alternateMode::ALT_MODE_2 );

			m_pwm->stop();
		    // 1Mhz clock, and we want 10 KHz frequency
		    // so 1000000 / 100 -> 10000
		   	m_pwm->config( 100, // -> just a 1% resolution
		   				   0,
		   				   Timer::config::clockMainDivider::DIV_1,
		   				   Timer::config::clockSubDivider::DIV_1,
		   				   Timer::config::clockSource::SMCLK );

		   	if ( m_direction == direction::COUNTER_CLOCKWISE )
		   	{
		   		m_pinDir->setLow();
		   	}
		   	else
		   	{
		   		m_pinDir->setHigh();
		   	}

		}

		void setSpeed( float pCalcDuty )
		{
			pCalcDuty = ( pCalcDuty < -1 ? -1 : pCalcDuty );
			pCalcDuty = ( pCalcDuty > 1 ? 1 : pCalcDuty );

			if ( pCalcDuty == m_duty )
			{
				return;
			}

			m_duty = pCalcDuty;
			m_pwm->setDuty( m_duty < 0 ? -m_duty : m_duty );
			if ( m_duty > 0 )
			{
				setDirection( m_initialDirection );
			}
			else
			{
				setDirection( m_initialDirection == direction::COUNTER_CLOCKWISE ?
									direction::CLOCKWISE : direction::COUNTER_CLOCKWISE );
			}
		}

		void setDirection( direction::_direction pDirection )
		{
			if ( m_direction == pDirection )
			{
				return;
			}

			m_direction = pDirection;
			if ( m_direction == direction::COUNTER_CLOCKWISE )
			{
				m_pinDir->setLow();
			}
			else
			{
				m_pinDir->setHigh();
			}
		}

	};

}


