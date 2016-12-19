/*
 * AdcImplement.hpp
 *
 *  Created on: Dec 15, 2016
 *      Author: wilsan
 */

#ifndef ADCIMPLEMENT_HPP_
#define ADCIMPLEMENT_HPP_

#include "../memorymap/MapAdc.hpp"
#include "../include/Adc.hpp"

#define MAP_ADC reinterpret_cast<MapAdc::AdcRegs*>( MapAdc::address::BASE_ADDRESS )

namespace adc
{

	Adc::Adc()
	{
	}

	void Adc::config( config::channel::_channel pStartChannel,
					  config::channel::_channel pEndChannel,
					  config::conversionMode::_conversionMode pConversionMode,
					  config::clockSource::_clockSource pClockSource,
					  config::samplingPeriod::_samplingPeriod pSamplingPeriod,
					  config::multiSC::_multiSC pMultiSC )
	{
		// Disable the module to configure it
		MAP_ADC->CTL0 &= ( 0xffff - ( 1 << 1 ) );

		MAP_ADC->CTL0 = ( pSamplingPeriod << 8 ) | 
						( pSamplingPeriod << 12 ) |
						( pMultiSC );

		MAP_ADC->CTL1 = ( pStartChannel << 12 )|
						( pConversionMode )|
						( pClockSource << 3 ) |
						( 1 << 9 );

		MAP_ADC->MCTL[pEndChannel] |= ( 1 << 7 );
	}

	void Adc::configInputChannel( u8 indxChannel,
								  config::inputChannel::_inputChannel pInputChannel )
	{
		volatile u8 _reg = MAP_ADC->MCTL[indxChannel];
		_reg &= ( 0xf0 );
		MAP_ADC->MCTL[indxChannel] = _reg | pInputChannel;
	}

	bool Adc::isBusy()
	{
		volatile u16 _reg = MAP_ADC->CTL1;
		return ( _reg & 0x01 ) == 0x01;
	}

	void Adc::start()
	{
		MAP_ADC->CTL0 |= ( 1 << 4 ) | // turn on adc
						 ( 1 << 1 ); // Enable conversion
		MAP_ADC->CTL0 |= ( 1 ); // Activate the soft trigger
	}

	void Adc::stop()
	{
		MAP_ADC->CTL0 &= ( 0xffff - ( 1 << 1 ) );// disable conversion
		MAP_ADC->CTL0 &= ( 0xffff - ( 1 << 4 ) );// turn off adc
	}

	void Adc::readBuffer( u16* dataBuffer,
						  u8 sizeBuffer, 
						  u8 startIndx )
	{
		u8 q;
		u8 currentChannel;
		for ( q = 0; q < sizeBuffer; q++ )
		{
			currentChannel = ( startIndx + q ) % 16;
			*dataBuffer = MAP_ADC->MEM[currentChannel];
			dataBuffer++;
		}
		
	}

}


#endif /* ADCIMPLEMENT_HPP_ */
