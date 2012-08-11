#pragma once
#include <HappyAuction/Constants.hpp>

namespace HappyAuction
{
    //------------------------------------------------------------------------
    const Char* APPLICATION_NAME =      "HappyAuction";

    //------------------------------------------------------------------------
    const Char* EXCEPTION_FATAL =       "Fatal Fail\n\n"
                                        "Possible Causes:\n"
                                        "- HappyAuction already running\n"
                                        "- Something else hogging CTRL-F12 hotkey\n";
    const Char* EXCEPTION_INITIALIZE =  "Open Fail\n\n"
                                        "Possible Causes:\n"
                                        "- Diablo 3 not running\n"
                                        "- Diablo 3 minimized\n"
                                        "- Not at auction house\n"
                                        "- Not latest HappyAuction\n";
    const Char* EXCEPTION_SCRIPT =      "LUA Error:\n%s";
    

    //------------------------------------------------------------------------
    const Char* SCRIPT_PATH =           "Lua/Main.lua";
    const Char* SCRIPT_STRINGS[SCRIPT_COUNT] =
    {
        "haFilterType",
        "haFilterLevel",
        "haFilterRarity",
        "haFilterStat",
        "haFilterBuyout",
        "haFilterUnique",

        "haActionBid",
        "haActionBuyout",
        "haActionSearch",
        "haActionSortDpsArmor",
        "haActionSortBuyout",
        "haActionReLogin",

        "haListSelect",
        "haListNext",
        "haListItem",//DEPRECATED
        "haListItemStat",//DEPRECATED
        "haListItemSocket",//DEPRECATED

        "haStashSell",
        "haStashNext",

        "haItem",
        "haItemStat",

        "haLog",
        "haBeep",
        "haSleep",
        "haAlert",

        "haSettingsListDelay",//DEPRECATED
        "haSetGlobalDelay",

        "haTest",
    };
}
