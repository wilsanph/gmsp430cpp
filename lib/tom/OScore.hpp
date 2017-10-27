
#include "../Common.hpp"


#pragma once



namespace osCore
{

    namespace taskState
    {
        enum _taskState
        {
            READY   = 0,
            RUNNING = 1
        };
    }

    struct PCB
    {
        u32 *runPt;
        u32 *next;
        taskState::_taskState state;
    };


    class OS
    {

    public :

        static void start();

        static void suspend();

        static void schedule();


    private :

    }


}



void osCore::OS::start( osCore::PCB* initTask )
{
    


}

void osCore::OS::suspend()
{


}

