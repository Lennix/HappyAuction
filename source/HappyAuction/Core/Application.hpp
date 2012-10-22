#pragma once
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/ScriptRunner.hpp>
#include <HappyAuction/Resource/resource.h>
#include <Diablo/Core/Locale.hpp>
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
            _settings(SETTINGS_ITEMS)
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
        Bool _AppLoadLocale()
        {
            TextString  path;
            Locale&     locale = Locale::GetInstance();

            // load locale
            sprintf(path, APPLICATION_LOCALE_PATH, Locale::GetInstance().GetLocale());
            if(!Locale::GetInstance().Load(path))
            {
                System::Message(false, EXCEPTION_LOCALE_FILE, path);
                return false;
            }

            return true;
        }

        /**/
        Bool _AppLoadHotKeys()
        {
            // read hotkeys and add applets
            for( Index i = 0; i < APPLICATION_APPLET_LIMIT; i++ )
            {
                Index           hotkey_index = i + SETTINGS_HOTKEY1;
                const Char*     hotkey_string = _settings[hotkey_index];
                System::Keys    hotkey;

                // stop at first empty hotkey
                if(*hotkey_string == 0)
                    break;

                // parse hotkey
                if(!System::ParseHotKey( hotkey, hotkey_string))
                {
                    System::Message(false, EXCEPTION_HOTKEY_PARSE, hotkey_string, SETTINGS_PATH);
                    return false;
                }

                // set hotkey
                if(!System::AddHotKey(hotkey_index, hotkey, _OnHotKey, reinterpret_cast<void*>(i)))
                {
                    System::Message(false, EXCEPTION_HOTKEY_TAKEN, hotkey_string, SETTINGS_PATH);
                    return false;
                }

                // add applet
                Applet& applet = _applets.Push();
                applet.runner = new ScriptRunner(i);
                applet.active = true;
            }

            // success if any applets created
            return _applets.GetCount() > 0;
        }

        /**/
        Bool _AppLoadPauseKeys()
        {
            for( Index i = 0; i < _applets.GetCount(); i++ )
            {
                Index           pausekey_index = i + SETTINGS_PAUSEKEY1;
                const Char*     pausekey_string = _settings[pausekey_index];
                System::Keys    pausekey;

                // pausekey is optional
                if(*pausekey_string != 0)
                {
                    // parse pausekey
                    if(!System::ParseHotKey( pausekey, pausekey_string ))
                    {
                        System::Message(false, EXCEPTION_HOTKEY_PARSE, pausekey_string, SETTINGS_PATH);
                        return false;
                    }

                    // set pausekey
                    if(!System::AddHotKey(pausekey_index, pausekey, _OnPauseKey, reinterpret_cast<void*>(i)))
                    {
                        System::Message(false, EXCEPTION_HOTKEY_TAKEN, pausekey_string, SETTINGS_PATH);
                        return false;
                    }
                }
            }

            return true;
        }

        /**/
        Bool _AppInitialize()
        {
            // load settings
            _settings.Load(SETTINGS_PATH);
            
            // load locale
            if(!_AppLoadLocale())
                return false;

            // load hotkeys
            if(!_AppLoadHotKeys())
                return false;

            // load pause keys
            if(!_AppLoadPauseKeys())
                return false;

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
        void _ToggleRunning( Index index )
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
        void _TogglePaused( Index index )
        {
            assert(_applets[index].active);
            ScriptRunner&   runner = *_applets[index].runner;

            // toggle pause script
            if(runner.IsActive())
                runner.GetScript().Pause(!runner.GetScript().IsPaused());
        }

        /**/
        static void _OnHotKey( void* custom )
        {
            Application::GetInstance()._ToggleRunning(reinterpret_cast<Index>(custom));
        }

        /**/
        static void _OnPauseKey( void* custom )
        {
            Application::GetInstance()._TogglePaused(reinterpret_cast<Index>(custom));
        }
    };
}
