#pragma once
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/ScriptRunner.hpp>
#include <HappyAuction/Core/AuthRunner.hpp>
#include <HappyAuction/Resource/resource.h>
#include <Core/System/System.hpp>

namespace HappyAuction
{
    /**/
    class Application
    {
    private:
        AuthRunner _auth;

    public:
        /**/
        void Run()
        {
            // init application
            if(!_InitApplication())
                throw EXCEPTION_FATAL;

            if(!_auth.CheckAuth())
                throw EXCEPTION_FATAL;

            // run system
            if(!_RunSystem())
                throw EXCEPTION_FATAL;

            // stop bot
            _auth.Stop();
        }

        /**/
        void ToggleBot()
        {
            if(_auth.IsActive())
                _auth.Stop();
            else
                _auth.Start();
        }

    private:
        /**/
        Bool _InitApplication()
        {
            return System::SetHotKey(MOD_CONTROL, VK_F12, _OnHotKey, this);
        }

        /**/
        Bool _RunSystem()
        {
            // init system
            System::SetStatusIcon(System::STATUS_IDLE, IDI_ICON_IDLE);
            System::SetStatusIcon(System::STATUS_ACTIVE, IDI_ICON_ACTIVE);

            // init system
            return System::Run(APPLICATION_NAME);
        }

        /**/
        static void _OnHotKey( void* custom )
        {
            Application& app = *reinterpret_cast<Application*>(custom);
            app.ToggleBot();
        }
    };
}
