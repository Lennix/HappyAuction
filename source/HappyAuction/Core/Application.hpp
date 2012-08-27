#pragma once
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/ScriptRunner.hpp>
#include <HappyAuction/Resource/resource.h>
#include <Core/System/System.hpp>
#include <Core/Support/Settings.hpp>

namespace HappyAuction
{
    /**/
    class Application
    {
    private:
        struct Applet
        {
            Bool            active;
            ULong           modifier;
            ULong           key;
            ScriptRunner*   runner;
        };

        typedef FixedArray<Applet, APPLICATION_APPLET_LIMIT>    AppletCollection;
        typedef AppletCollection::Iterator                      AppletIterator;

    private:
        AppletCollection    _applets;
        Settings            _settings;

    private:
        /* singleton */
        Application():
            _settings(SETTINGS_PATH, SETTINGS_ITEMS)
        {
            _applets.MemoryZero();
        }

    public:
        /**/
        void Run()
        {
            // initialize system
            if(_SystemInitialize())
            {
                // initialize application
                if(_AppInitialize())
                {
                    // run system
                    if(!System::Run())
                        System::Message(false, EXCEPTION_SYSTEM);

                    // finalize application
                    _AppFinalize();
                }

                // finalize system
                _SystemFinalize();
            }
            else
                System::Message(false, EXCEPTION_SYSTEM);
        }

        /**/
        static Application& GetInstance()
        {
            static Application application;
            return application;
        }

    private:
        /**/
        Bool _AppInitialize()
        {
            Index i;

            for( i = SETTINGS_HOTKEY1; i <= SETTINGS_HOTKEYLAST; i++ )
            {
                const Char* hotkey_string = _settings[i];
                Bits        modifiers;
                Id          key;

                // stop at first empty hotkey
                if(*hotkey_string == 0)
                    break;

                // parse hotkey
                if(!System::ParseHotKey( modifiers, key, hotkey_string))
                {
                    System::Message(false, EXCEPTION_HOTKEY_PARSE, hotkey_string, SETTINGS_PATH);
                    return false;
                }

                // add applet
                if(!_AddApplet(modifiers, key))
                {
                    System::Message(false, EXCEPTION_HOTKEY_TAKEN, hotkey_string, SETTINGS_PATH);
                    return false;
                }
            }

            // fail if nothing assigned
            if(i == SETTINGS_HOTKEY1)
            {
                System::Message(false, EXCEPTION_APPLICATION);
                return false;
            }

            return true;
        }

        void _AppFinalize()
        {
            // delete applets
            for( AppletIterator i = _applets.Begin(); i != _applets.End(); ++i )
            {
                Applet& applet = *i;

                if(applet.active)
                {
                    // stop runner
                    applet.runner->Stop();

                    // delete
                    delete applet.runner;

                    // remove hotkey
                    System::RemoveHotKey(_applets.IndexOf(i));
                }
            }
        }

        /**/
        Bool _SystemInitialize()
        {
            // init icons
            for( Index i = 0; i < _applets.GetLimit(); i++ )
            {
                Id icon_id = Tools::Min<Id>(IDI_ICON_IDLE + i, IDI_ICON_STATUS4P);
                System::SetStatusIcon(i, icon_id);
            }

            // init system
            return System::Initialize(APPLICATION_NAME);
        }

        /**/
        void _SystemFinalize()
        {
            // finalize system
            System::Finalize();
        }

        /**/
        Bool _AddApplet( ULong hk_modifier, ULong hk_key )
        {
            Index index = _applets.GetCount();

            // limit check
            if(index >= _applets.GetLimit())
                return false;

            // set hotkey
            if(!System::AddHotKey(index, hk_modifier, hk_key, _OnHotKey, reinterpret_cast<void*>(index)))
                return false;

            // add applet
            Applet& applet = _applets.Push();

            // initialize
            applet.runner = new ScriptRunner(index);
            applet.modifier = hk_modifier;
            applet.key = hk_key;
            applet.active = true;

            return true;
        }

        /**/
        void _ToggleBot( Index index )
        {
            assert(_applets[index].active);
            ScriptRunner& runner = *_applets[index].runner;

            // toggle start/stop runner
            if(runner.IsActive())
                runner.Stop();
            else
                runner.Start();
        }

        /**/
        static void _OnHotKey( void* custom )
        {
            Application::GetInstance()._ToggleBot(reinterpret_cast<Index>(custom));
        }
    };
}
