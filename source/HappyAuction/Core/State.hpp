#pragma once
#include <HappyAuction/Root.hpp>
#include <Diablo/Constants.hpp>
#include <Diablo/Type/Item.hpp>

namespace HappyAuction
{
    /**/
    struct StateLogin
    {
        TextString  name;
        TextString  password;

        StateLogin()
        {
            *name = 0;
            *password = 0;
        }
    };

    /**/
    struct StateFiltersStat
    {
        TextString  name;
        Number      value;

        StateFiltersStat():
            value(NUMBER(-1,0))
        {
            *name = 0;
        }
    };

    /**/
    struct StateFilters
    {
        TextString          character;
        TextString          type;
        TextString          rarity;
        Number              level_min;
        Number              level_max;
        Number              buyout;
        TextString          unique;
        StateFiltersStat    stat[AH_PSTAT_LIMIT];

        StateFilters():
            level_min(NUMBER(-1,0)),
            level_max(NUMBER(-1,0)),
            buyout(NUMBER(-1,0))
        {
            *character = 0;
            *type = 0;
            *rarity = 0;
            *unique = 0;
        }
    };

    /**/
    struct StateSearch
    {
        Bool        active;
        Index       row;
        Index       page;
        Id          sort_id;
        ULong       sort_count;

        StateSearch():
            active(false),
            row(0),
            page(0),
            sort_id(INVALID_ID),
            sort_count(0)
        {}
    };

    /**/
    struct StateStash
    {
        Index       column;
        Index       row;
        Index       bag;

        StateStash(): column(0), row(0), bag(0) {}
    };

    /**/
    struct State
    {
        StateLogin      login;
        StateFilters    filters;
        StateSearch     search;
        StateStash      stash;
        Item            item;
    };
}
