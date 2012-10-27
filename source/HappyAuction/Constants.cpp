#pragma once
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Enums.hpp>

namespace HappyAuction
{
    //------------------------------------------------------------------------
    const Char* APPLICATION_NAME =              "HappyAuction";
    const Char* APPLICATION_LOCALE_PATH =       "Locale/%s.txt";

    //------------------------------------------------------------------------
    const Char* EXCEPTION_SYSTEM =              "System Fail\n\n"
                                                "Possible Causes:\n"
                                                "- HappyAuction already running\n";
    const Char* EXCEPTION_APPLICATION =         "Application Fail\n\n"
                                                "Possible Causes:\n"
                                                "- No hotkeys were assigned\n";
    const Char* EXCEPTION_HOTKEY_TAKEN =        "HotKey (%s) is taken. Reassign in %s.";
    const Char* EXCEPTION_HOTKEY_PARSE =        "HotKey (%s) is invalid. Recheck %s.";
    const Char* EXCEPTION_SCRIPT =              "Script Fail\n\n"
                                                "Possible Causes:\n"
                                                "- Diablo 3 not running\n"
                                                "- Diablo 3 minimized\n"
                                                "- Not at auction house\n"
                                                "- Not latest HappyAuction\n";
    const Char* EXCEPTION_LUA =                 "LUA Fail:\n%s";
    const Char* EXCEPTION_LOCALE_FILE =         "Locale File (%s) missing or invalid";
    const Char* EXCEPTION_LOCALE_NOTSUPPORTED = "Function (%s) no supported for current locale (%s)";
    const Char* EXCEPTION_OBSOLETED =           "Obsoleted Function:\n%s\n\n"
                                                "See README for latest version";

    //------------------------------------------------------------------------
    const Char* SCRIPT_LOG_PATH =   "User%u.log";
    const Char* SCRIPT_MAIN_PATH =  "Lua/Main.lua";
    const Char* SCRIPT_FUNCTIONS[SCRIPT_COUNT] =
    {
        // auction/search
        "haBid",
        "haBuyout",
        "haFilterBuyout",
        "haFilterChar",
        "haFilterLevel",
        "haFilterPrimary",
        "haFilterRarity",
        "haFilterSecondary",
        "haFilterStat",
        "haFilterStatClear",
        "haFilterType",
        "haFilterUnique",
        "haListAt",
        "haListIterate",
        "haListSelect",
        "haSearch",
        "haSortBuyout",
        "haSortDpsArmor",
        "haSortTimeLeft",

        // auction/sell
        "haSell",
        "haSellCancel",
        "haSellIterate",
        "haStashAt",
        "haStashIterate",
        "haStashSelect",

        // auction/completed
        "haSendToStash",

        // item
        "haItem",
        "haItemStat",

        // other
        "haGetAccount",
        "haGetGold",
        "haGetInstance",
        "haLogout",
        "haSetGlobalDelay",
        "haSetLogin",
        "haSetLoginDelay",

        // utilities
        "haAlert",
        "haBeep",
        "haLog",
        "haPrompt",
        "haSleep",
        "haUpTime",

        // deprecated
        "haListNext",
        "haStashNext",
        "haReLogin",
        "haActionBid",
        "haActionBuyout",
        "haActionSearch",
        "haActionSortDpsArmor",
        "haActionSortBuyout",
        "haListItem",
        "haListItemStat",
        "haListItemSocket",
        "haStashSell",
        "haActionReLogin",
        "haSettingsListDelay",

        "haTest",
    };


    //------------------------------------------------------------------------
    const Char* SETTINGS_PATH = "Settings.cfg";
    static Settings::Item _settings[SETTINGS_COUNT] =
    {
        { "HotKey1", "C.F12" },
        { "HotKey2" },
        { "HotKey3" },
        { "HotKey4" },
        { "HotKey5" },
        { "HotKey6" },
        { "HotKey7" },
        { "HotKey8" },
        { "HotKey9" },
        { "HotKey10" },
        { "HotKey11" },
        { "HotKey12" },
        { "HotKey13" },
        { "HotKey14" },
        { "HotKey15" },
        { "HotKey16" },
        { "PauseKey1", "PAUSE" },
        { "PauseKey2" },
        { "PauseKey3" },
        { "PauseKey4" },
        { "PauseKey5" },
        { "PauseKey6" },
        { "PauseKey7" },
        { "PauseKey8" },
        { "PauseKey9" },
        { "PauseKey10" },
        { "PauseKey11" },
        { "PauseKey12" },
        { "PauseKey13" },
        { "PauseKey14" },
        { "PauseKey15" },
        { "PauseKey16" },
    };
    Settings::ItemCollection SETTINGS_ITEMS(_settings, ACOUNT(_settings));
}
