#pragma once
#include <HappyAuction/Core/Script.hpp>
#include <Core/System/Thread.hpp>
#include <Core/System/System.hpp>

namespace HappyAuction
{
    /**/
    class ScriptRunner:
        public Thread
    {
    private:
        Script  _script;
        Bool    _active;

    public:
        /**/
        ScriptRunner():
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
            _script.Start();
            _UpdateActiveStatus(false);
        }

        /**/
        void Stop()
        {
            _script.Stop();
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
