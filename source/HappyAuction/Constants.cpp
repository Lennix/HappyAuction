#pragma once
#include <HappyAuction/Constants.hpp>

namespace HappyAuction
{
    //------------------------------------------------------------------------
    const Char* APPLICATION_NAME =          "HappyAuction";

    //------------------------------------------------------------------------
    const Char* EXCEPTION_FATAL =           "Fatal Fail\n\n"
                                            "Possible Causes:\n"
                                            "- HappyAuction already running\n"
                                            "- Something else hogging CTRL-F12 hotkey\n";
    const Char* EXCEPTION_INITIALIZE =      "Open Fail\n\n"
                                            "Possible Causes:\n"
                                            "- Diablo 3 not running\n"
                                            "- Diablo 3 minimized\n"
                                            "- Not at auction house\n"
                                            "- Not latest HappyAuction\n";
    const Char* EXCEPTION_SCRIPT =          "LUA Error:\n%s";
    const Char* EXCEPTION_SCRIPT_FILTER =   "haFilter Operation Failed:\n\n";
    const Char* EXCEPTION_OBSOLETED =       "Obsoleted Function:\n%s\n\n"
                                            "See README for latest version";


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

        // settings
        "haSetGlobalDelay",
        "haSetLogin",

        // utilities
        "haAlert",
        "haBeep",
        "haLog",
        "haSleep",
        "haUpTime",

        // deprecated
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

        // happy auction advanced:
        "haParseTime",
        "haGetGold",
        "haSettingsNextDelay",
        "haSettingsQueriesPerHour",
    };
}
