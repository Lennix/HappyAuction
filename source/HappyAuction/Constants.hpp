#pragma once
#include <Core/Support/Settings.hpp>
#include <HappyAuction/Root.hpp>

namespace HappyAuction
{
    //------------------------------------------------------------------------
    extern const Char*  APPLICATION_NAME;
    static const ULong  APPLICATION_APPLET_LIMIT = 16;
    extern const Char*  APPLICATION_LOCALE_PATH;

    //------------------------------------------------------------------------
    extern const Char*  EXCEPTION_SYSTEM;
    extern const Char*  EXCEPTION_APPLICATION;
    extern const Char*  EXCEPTION_HOTKEY_TAKEN;
    extern const Char*  EXCEPTION_HOTKEY_PARSE;
    extern const Char*  EXCEPTION_SCRIPT;
    extern const Char*  EXCEPTION_LUA;
    extern const Char*  EXCEPTION_LOCALE_FILE;
    extern const Char*  EXCEPTION_LOCALE_NOTSUPPORTED;
    extern const Char*  EXCEPTION_OBSOLETED;

    //------------------------------------------------------------------------
    static const ULong  SCRIPT_PAUSE_SLICE = 100; // ms
    extern const Char*  SCRIPT_LOG_PATH;
    extern const Char*  SCRIPT_MAIN_PATH;
    extern const Char*  SCRIPT_FUNCTIONS[];

    //------------------------------------------------------------------------
    extern const Char*              SETTINGS_PATH;
    extern Settings::ItemCollection SETTINGS_ITEMS;
}
