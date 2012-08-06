#pragma once
#include <HappyAuction/Constants.hpp>

namespace HappyAuction
{
    //------------------------------------------------------------------------
    const Char* APPLICATION_NAME =      "HappyAuction";

    //------------------------------------------------------------------------
    const Char* EXCEPTION_FATAL =       "Fatal Fail!";
    const Char* EXCEPTION_INITIALIZE =  "Open Fail\n\nPossible Causes:\n"
                                        "- Diablo 3 not running\n"
                                        "- Diablo 3 minimized\n"
                                        "- Not at AuctionHouse/Search/Equipment\n"
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
        "haListItem",
        "haListItemStat",
        "haListItemSocket",

        "haLog",
        "haBeep",
        "haSleep",
        "haAlert",

        "haSettingsListDelay",//DEPRECATED
        "haSetGlobalDelay",
    };
}
