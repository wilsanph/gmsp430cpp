/*
 * Adc.hpp
 *
 *  Created on: Dec 13, 2014
 *      Author: wilsan
 */

#ifndef ADC_HPP_
#define ADC_HPP_

namespace adc
{


	namespace config
	{
		namespace conversionMode
		{
			enum _conversionMode
			{
				SINGLE_CHANNEL_SINGLE_CONVERSION = 0x0,
				SEQUENCE_OF_CHANNELS = 0x2,
				REPEAT_SINGLE_CHANNEL = 0x4,
				REPEAT_SEQUENCE_OF_CHANNELS = 0x6
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
				CH_6,
				CH_7,
				CH_8,
				CH_9,
				CH_10,
				CH_11,
				CH_12,
				CH_13,
				CH_14,
				CH_15
			};
		}

		namespace inputChannel
		{
			enum _inputChannel
			{
				A0 = 0x0,
				A1 = 0x1,
				A2 = 0x2,
				A3 = 0x3,
				A4 = 0x4,
				A5 = 0x5,
				A6 = 0x6,
				A7 = 0x7,
				A13 = 0xd,
				A14 = 0xe,
				A15 = 0xf
			};
		}

		namespace clockSource
		{
			enum _clockSource
			{
				ADC12OSC,
				ACLK,
				MCLK,
				SMCLK
			};
		}

		namespace samplingPeriod 
		{
			enum _samplingPeriod
			{
				CYCLES_4,
				CYCLES_8,
				CYCLES_16,
				CYCLES_32,
				CYCLES_64,
				CYCLES_96,
				CYCLES_128,
				CYCLES_192,
				CYCLES_256,
				CYCLES_384,
				CYCLES_512,
				CYCLES_768,
				CYCLES_1024
			};
		}

		namespace multiSC
		{
			enum _multiSC
			{
				USE 	 = 0x0080,
				DONT_USE = 0x0000
			};
		}


	}

	class Adc
	{
		public:

		Adc();

		void config( config::channel::_channel pStartChannel,
					 config::channel::_channel pEndChannel,
					 config::conversionMode::_conversionMode pConversionMode,
					 config::clockSource::_clockSource pClockSource,
					 config::samplingPeriod::_samplingPeriod pSamplingPeriod,
					 config::multiSC::_multiSC pMultiSC );

		void configInputChannel( u8 indxChannel,
								 config::inputChannel::_inputChannel pInputChannel );

		bool isBusy();

		void start();

		void stop();

		void readBuffer( u16* dataBuffer, u8 sizeBuffer, u8 startIndx );
	};

}

#include "../src/AdcImplement.hpp"

#endif /* ADC_HPP_ */
