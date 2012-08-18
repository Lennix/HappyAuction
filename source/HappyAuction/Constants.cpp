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
        // auction/search
        "haBid",
        "haBuyout",
        "haFilterBuyout",
        "haFilterChar",
        "haFilterLevel",
        "haFilterRarity",
        "haFilterStat",
        "haFilterStatClear",
        "haFilterType",
        "haFilterUnique",
        "haListNext",
        "haListSelect",
        "haSearch",
        "haSortBuyout",
        "haSortDpsArmor",

        // auction/sell
        "haSell",
        "haStashNext",
        "haStashSelect",

        // auction/completed
        "haSendToStash",

        // item
        "haItem",
        "haItemStat",

        // etc
        "haReLogin",

        // settings
        "haSetGlobalDelay",

        // utilities
        "haAlert",
        "haBeep",
        "haLog",
        "haSleep",
        "haUpTime",

        "haActionBid",//DEPRECATED
        "haActionBuyout",//DEPRECATED
        "haActionSearch",//DEPRECATED
        "haActionSortDpsArmor",//DEPRECATED
        "haActionSortBuyout",//DEPRECATED
        "haListItem",//DEPRECATED
        "haListItemStat",//DEPRECATED
        "haListItemSocket",//DEPRECATED
        "haStashSell",//DEPRECATED
        "haActionReLogin",//DEPRECATED
        "haSettingsListDelay",//DEPRECATED

        "haTest",

        // happy auction advanced:
        "haParseTime",
        "haGetGold",
        "haSettingsNextDelay",
        "haSettingsQueriesPerHour",
    };
}
