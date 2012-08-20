#pragma once
#include <HappyAuction/Root.hpp>

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
        SCRIPT_HAFILTERRARITY,
        SCRIPT_HAFILTERSTAT,
        SCRIPT_HAFILTERSTATCLEAR,
        SCRIPT_HAFILTERTYPE,
        SCRIPT_HAFILTERUNIQUE,
        SCRIPT_HALISTNEXT,
        SCRIPT_HALISTSELECT,
        SCRIPT_HASEARCH,
        SCRIPT_HASORTBUYOUT,
        SCRIPT_HASORTDPSARMOR,

        // auction/sell
        SCRIPT_HASELL,
        SCRIPT_HASTASHNEXT,
        SCRIPT_HASTASHSELECT,

        // auction/completed
        SCRIPT_HASENDTOSTASH,

        // item
        SCRIPT_HAITEM,
        SCRIPT_HAITEMSTAT,

        // settings
        SCRIPT_HASETGLOBALDELAY,
        SCRIPT_HASETLOGIN,

        // utilities
        SCRIPT_HAALERT,
        SCRIPT_HABEEP,
        SCRIPT_HALOG,
        SCRIPT_HASLEEP,
        SCRIPT_HAUPTIME,

        // deprecated
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

        // happy auction advanced:
        SCRIPT_HAPARSETIME,
        SCRIPT_HAGETGOLD,
        SCRIPT_HASETTINGSNEXTDELAY,
        SCRIPT_HASETTINGSQUERIESPERHOUR,

        SCRIPT_COUNT,
    };
}
 