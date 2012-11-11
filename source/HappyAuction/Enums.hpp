#pragma once
#include <HappyAuction/Root.hpp>
#include <HappyAuction/Constants.hpp>

namespace HappyAuction
{
    /**/
    enum
    {
        // auction/search
        SCRIPT_HABID,
        SCRIPT_HABUYOUT,
        SCRIPT_HAFILTERBUYOUT,
        SCRIPT_HAFILTERCHAR,
        SCRIPT_HAFILTERLEVEL,
        SCRIPT_HAFILTERPRIMARY,
        SCRIPT_HAFILTERRARITY,
        SCRIPT_HAFILTERSECONDARY,
        SCRIPT_HAFILTERSTAT,
        SCRIPT_HAFILTERSTATCLEAR,
        SCRIPT_HAFILTERTYPE,
        SCRIPT_HAFILTERUNIQUE,
        SCRIPT_HALISTAT,
        SCRIPT_HALISTITERATE,
        SCRIPT_HALISTSELECT,
        SCRIPT_HASEARCH,
        SCRIPT_HASORTBUYOUT,
        SCRIPT_HASORTDPSARMOR,
        SCRIPT_HASORTTIMELEFT,

        // auction/sell
        SCRIPT_HASELL,
        SCRIPT_HASELLCANCEL,
        SCRIPT_HASELLITERATE,
        SCRIPT_HASTASHAT,
        SCRIPT_HASTASHITERATE,
        SCRIPT_HASTASHSELECT,

        // auction/completed
        SCRIPT_HASENDTOSTASH,

        // item
        SCRIPT_HAITEM,
        SCRIPT_HAITEMSTAT,

        // etc
        SCRIPT_HAGETACCOUNT,
        SCRIPT_HAGETGOLD,
        SCRIPT_HAGETINSTANCE,
        SCRIPT_HALOGOUT,
        SCRIPT_HASETGLOBALDELAY,
        SCRIPT_HASETLOGIN,
        SCRIPT_HASETLOGINDELAY,

        // utilities
        SCRIPT_HAALERT,
        SCRIPT_HABEEP,
        SCRIPT_HALOG,
        SCRIPT_HAPROMPT,
        SCRIPT_HASLEEP,
        SCRIPT_HAUPTIME,

        // deprecated
        SCRIPT_HALISTNEXT,
        SCRIPT_HASTASHNEXT,
        SCRIPT_HARELOGIN,
        SCRIPT_HAACTIONBID,
        SCRIPT_HAACTIONBUYOUT,
        SCRIPT_HAACTIONSEARCH,
        SCRIPT_HAACTIONSORTDPSARMOR,
        SCRIPT_HAACTIONSORTBUYOUT,
        SCRIPT_HALISTITEM,
        SCRIPT_HALISTITEMSTAT,
        SCRIPT_HALISTITEMSOCKET,
        SCRIPT_HASTASHSELL,
        SCRIPT_HAACTIONRELOGIN,
        SCRIPT_HASETTINGSLISTDELAY,

        SCRIPT_HATEST,
        SCRIPT_COUNT,
    };

    /**/
    enum
    {
        SETTINGS_HOTKEY1,
        SETTINGS_HOTKEYLAST = (SETTINGS_HOTKEY1 + APPLICATION_APPLET_LIMIT - 1),
        SETTINGS_PAUSEKEY1,
        SETTINGS_PAUSELAST = (SETTINGS_PAUSEKEY1 + APPLICATION_APPLET_LIMIT - 1),
        SETTINGS_COUNT
    };
}
