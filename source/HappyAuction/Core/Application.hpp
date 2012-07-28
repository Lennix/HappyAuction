#pragma once
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/ScriptRunner.hpp>
#include <HappyAuction/Resource/resource.h>
#include <Core/System/System.hpp>

namespace HappyAuction
{
    /**/
    class Application
    {
    private:
        ScriptRunner _runner;

    public:
        /**/
        void Run()
        {
            // init system
            if(!_InitSystem())
                throw EXCEPTION_FATAL;

            // init application
            if(!_InitApplication())
                throw EXCEPTION_FATAL;

            // run system
            if(!System::Run())
                throw EXCEPTION_FATAL;

            // stop bot
            _runner.Stop();
        }

        /**/
        void ToggleBot()
        {
            if(_runner.IsActive())
                _runner.Stop();
            else
                _runner.Start();
        }

    private:
        /**/
        Bool _InitApplication()
        {
            return System::SetHotKey(MOD_CONTROL, VK_F12, _OnHotKey, this);
        }

        /**/
        Bool _InitSystem()
        {
            // init system
            System::SetStatusIcon(System::STATUS_IDLE, IDI_ICON_IDLE);
            System::SetStatusIcon(System::STATUS_ACTIVE, IDI_ICON_ACTIVE);

            // init system
            return System::Initialize(APPLICATION_NAME);
        }

        /**/
        static void _OnHotKey( void* custom )
        {
            Application& app = *reinterpret_cast<Application*>(custom);
            app.ToggleBot();
        }
    };
}
