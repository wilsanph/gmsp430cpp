

#pragma once

#include "../include/Gpio.hpp"
#include "../include/Timer.hpp"

#define TOTAL_SR04_SENSORS 2

namespace sensors
{


	class SR04
	{
		private:

		Timer::TimeEvent* m_timer;

		Gpio::Pin* m_trigger;
		Gpio::Pin* m_echo;


		public:

		SR04();
		~SR04();

		float distance;
		bool isBusy;

		void init( Timer::TimeEvent* pTimer,
				   Gpio::Pin* pTrigger,
				   Gpio::Pin* pEcho );

		void beginSample();
		void processDistance();
		void onInterrupt();

	};


	SR04::SR04()
	{
		this->distance = 0;
		m_timer = NULL;
		m_trigger = NULL;
		m_echo = NULL;
		isBusy = false;
	}

	SR04::~SR04()
	{
		m_timer = NULL;
		m_trigger = NULL;
		m_echo = NULL;
	}

	void SR04::init( Timer::TimeEvent* pTimer,
				  	 Gpio::Pin* pTrigger,
				     Gpio::Pin* pEcho )
	{
		m_timer = pTimer;
		m_trigger = pTrigger;
		m_echo = pEcho;

	    m_trigger->setMode( Gpio::config::mode::gpio );
	    m_trigger->setIOMode( Gpio::config::ioMode::output );
	    m_trigger->setLow();

	    m_echo->setMode( Gpio::config::mode::gpio );
	    m_echo->setIOMode( Gpio::config::ioMode::input );
	    m_echo->selectInputPullResistor( Gpio::config::pullResistor::PULLUP );
	    m_echo->selectInterruptEdge( Gpio::config::interruptEdge::RISING );
	    m_echo->clearInterruptFlag();

	    m_timer->stop();
	    m_timer->config( 10000,
	    		  		 Timer::config::clockMainDivider::DIV_1,
	    				 Timer::config::clockSubDivider::DIV_1,
						 Timer::config::clockSource::SMCLK,
						 Timer::config::countMode::UP_MODE );
	}

	void SR04::beginSample()
	{
		m_trigger->setHigh();
		common::delay_us( 5 );
		m_trigger->setLow();

		m_echo->enableInterrupt();
		isBusy = true;
	}

	void SR04::onInterrupt()
	{
		if ( m_echo->isHigh() )
		{
	    	m_echo->selectInterruptEdge( Gpio::config::interruptEdge::FALLING );
	        m_timer->stop();
	        m_timer->config( 10000,
	        				Timer::config::clockMainDivider::DIV_1,
	        				Timer::config::clockSubDivider::DIV_1,
	    					Timer::config::clockSource::SMCLK,
	    					Timer::config::countMode::UP_MODE );
	    	m_timer->restart();
		}
		else
		{
			m_echo->selectInterruptEdge( Gpio::config::interruptEdge::RISING );
			m_timer->stop();

			processDistance();
			m_echo->disableInterrupt();
			isBusy = false;
		}
		m_echo->clearInterruptFlag();
	}

	void SR04::processDistance()
	{
		this->distance = ( m_timer->getTimerReg() / 58.82f );
	}



	class SR04Manager
	{
		private:

		SR04* m_sensors[TOTAL_SR04_SENSORS];
		u8 m_currentIndx;
		u8 m_totalSensors;


		public:

		bool isBusy;

		SR04Manager()
		{
			m_currentIndx = 0;
			m_totalSensors = 0;
			isBusy = false;
		}

		~SR04Manager()
		{
			u8 q;
			for( q = 0; q < TOTAL_SR04_SENSORS; q++ )
			{
				m_sensors[q] = NULL;
			}
			m_currentIndx = 0;
			m_totalSensors = 0;
		}

		void attachSensor( SR04* pSensor )
		{
			m_sensors[m_totalSensors] = pSensor;
			m_totalSensors++;
		}

		void beginSample()
		{
			isBusy = true;
			m_currentIndx = 0;
			m_sensors[m_currentIndx]->beginSample();
		}

		void onInterrupt()
		{
			m_sensors[m_currentIndx]->onInterrupt();
			if ( !m_sensors[m_currentIndx]->isBusy )
			{
				m_currentIndx++;
				if ( m_currentIndx == m_totalSensors )
				{
					isBusy = false;
					m_currentIndx = 0;
				}
				else
				{
					m_sensors[m_currentIndx]->beginSample();
				}
			}
		}

		float getDistance( u8 pSensorIndx )
		{
			return m_sensors[pSensorIndx]->distance;
		}

		u8 totalSensors()
		{
			return m_totalSensors;
		}

	};

}
