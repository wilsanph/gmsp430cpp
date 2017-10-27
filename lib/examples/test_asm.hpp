
#include "lib/include/Watchdog.hpp"
#include "lib/include/Gpio.hpp"
#include <string>

watchdog::WatchdogTimer dog;

Gpio::Pin led( Gpio::port::PORT1, Gpio::pins::pin0 );

u32 fun = 0;

struct FunType
{
	u32 runPt;
	u32 next;
};

FunType foo;

void funFunct()
{
	fun++;
}

class FunOS
{
	public :

		static void start( u32 num )
		{
			fun += num;
		}

	private :
		u32 m_bar;
};

FunOS toc;

extern "C"
{
	///extern void asm_init();
}

int main()
{
    dog.init( watchdog::config::hold::HOLD );

    led.setMode( Gpio::config::mode::gpio );
    led.setIOMode( Gpio::config::ioMode::output );

    ///asm_init();

    while( 1 )
    {
        common::sw_delay();
        led.toggle();
        fun = fun + 3;
        asm(" NOP");
        asm(" NOP");

        asm(" add.w  #0x0005,&fun");
        asm(" add.w  #0x0005,&fun");
        asm(" add.w  #0x0005,&fun");

        foo.runPt = 1;
        foo.next = 1;
        foo.runPt = foo.runPt + 3;
        foo.next = foo.next + 3;

        asm(" NOP");
        asm(" NOP");

        funFunct();

        std::string funStr( "some text" );
        FunOS::start( fun );

        ///asm(" .ref funFunct");
        ///asm(" calla #funFunct");
    }


}
