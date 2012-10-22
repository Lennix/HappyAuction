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
        ULong       delay;

        StateLogin():
            delay(0)
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
        TextString          rarity;
        TextString          primary;
        TextString          secondary;
        Number              level_min;
        Number              level_max;
        Number              buyout;
        TextString          unique;
        Index               unique_row;
        StateFiltersStat    stat[AH_PSTAT_LIMIT];

        StateFilters():
            level_min(NUMBER(-1,0)),
            level_max(NUMBER(-1,0)),
            buyout(NUMBER(-1,0)),
            unique_row(0)
        {
            *character = 0;
            *primary = 0;
            *secondary = 0;
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
        Index       row;
        Index       column;
        Index       bag;

        StateStash(): row(0), column(1), bag(1) {}
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
