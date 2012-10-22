#pragma once
#include <Core/Support/Settings.hpp>
#include <Core/System/System.hpp>
#include <Diablo/Constants.hpp>

namespace Diablo
{
    /**/
    class Locale
    {
    private:
        Settings    _settings;
        TextString  _locale;
        Bool        _is_default;

    public:
        /**/
        Locale():
            _settings(LOCALE_ITEMS)
        {
            // get locale
            if(!System::GetRegistryString(_locale, sizeof(_locale), LOCALE_REGISTRY_PATH, LOCALE_REGISTRY_KEY))
                Tools::StrNCpy(_locale, LOCALE_DEFAULT1, sizeof(TextString));

            // is default
            _is_default = strcmp(_locale, LOCALE_DEFAULT1) == 0 || strcmp(_locale, LOCALE_DEFAULT2) == 0;
        }

        /**/
        inline const Char* GetLocale()
        {
            return _locale;
        }

        /**/
        inline Bool IsDefault() const
        {
            return _is_default;
        }

        /**/
        Bool Load( const Char* path )
        {
            const Settings::ItemCollection& items = _settings.GetItems();

            // load locale settings
            if(!_settings.Load(path, true))
                return false;

            // for each local setting
            for( Settings::ItemIterator i = items.Begin(); i != items.End(); ++i )
            {
                Id id = i->custom2;

                // require all values
                if(*i->value == 0)
                    return false;

                // update string tables
                switch(i->custom1)
                {
                case LOCALE_GEMSTAT:
                    ITEM_GEM_STAT_IDS.ReplaceName(id, i->value);
                    break;
                }
            }

            return true;
        }

        /**/
        static Locale& GetInstance()
        {
            static Locale locale;
            return locale;
        }
    };
}
