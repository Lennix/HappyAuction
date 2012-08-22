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

        StateLogin() { name[0]=0; password[0]=0; }
    };

    /**/
    struct StateFiltersStat
    {
        Id      id;
        Number  value;

        StateFiltersStat(): id(INVALID_ID), value(NUMBER(-1,0)) {}
    };

    /**/
    struct StateFilters
    {
        Id                  character;
        Id                  type;
        Id                  rarity;
        Number              level_min;
        Number              level_max;
        Number              buyout;
        TextString          unique;
        StateFiltersStat    stat[AH_INPUT_PSTAT_LIMIT];

        StateFilters(): character(INVALID_ID), type(INVALID_ID), rarity(INVALID_ID), level_min(NUMBER(-1,0)), level_max(NUMBER(-1,0)), buyout(NUMBER(-1,0)) { unique[0]=0; }
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
