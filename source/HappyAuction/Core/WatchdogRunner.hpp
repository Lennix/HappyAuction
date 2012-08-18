#pragma once
#include <Core/System/Thread.hpp>
#include <Core/System/System.hpp>

namespace HappyAuction
{
    /**/
    class WatchdogRunner:
        public Thread
    {
    private:
        Bool    _active;

    public:
        /**/
        WatchdogRunner():
            _active(false)
        {
        }

        /**/
        Bool IsActive() const
        {
            return _active;
        }

        /**/
        void Run()
        {
            _UpdateActiveStatus(true);
            // mach krassen shit
            _UpdateActiveStatus(false);
        }

        /**/
        void Stop()
        {
            // hör auf mit krassem shit
            Thread::Wait();
            _UpdateActiveStatus(false);
        }

    private:
        /**/
        void _UpdateActiveStatus( Bool active )
        {
            System::SetStatus(active ? System::STATUS_ACTIVE : System::STATUS_IDLE);
            _active = active;
        }
    };
}
