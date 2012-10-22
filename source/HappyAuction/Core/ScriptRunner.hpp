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
        Index   _instance;

    public:
        /**/
        ScriptRunner( Index instance ):
            _script(instance),
            _active(false)
        {
        }

        /**/
        Script& GetScript()
        {
            return _script;
        }

        /**/
        Bool IsActive() const
        {
            return _active;
        }

        /**/
        void Run()
        {
            _OnStart();
            _script.Start();
            _OnStop();
        }

        /**/
        void Stop()
        {
            if(_active)
                _script.Stop();
            Thread::Wait();
        }

    private:
        /**/
        void _OnStart()
        {
            _active = true;
            System::SetStatus( System::GetStatus() + 1 );
        }

        /**/
        void _OnStop()
        {
            if(System::GetStatus() > 0)
                System::SetStatus( System::GetStatus() - 1 );

            _active = false;
        }
    };
}
