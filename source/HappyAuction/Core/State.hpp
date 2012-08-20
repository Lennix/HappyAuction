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
        Long    value;

        StateFiltersStat(): id(INVALID_ID), value(-1) {}
    };

    /**/
    struct StateFilters
    {
        Id                  character;
        Id                  type;
        Id                  rarity;
        Long                level_min;
        Long                level_max;
        Long                buyout;
        TextString          unique;
        StateFiltersStat    stat[AH_INPUT_PSTAT_LIMIT];

        StateFilters(): character(INVALID_ID), type(INVALID_ID), rarity(INVALID_ID), level_min(-1), level_max(-1), buyout(-1) { unique[0]=0; }
    };

    /**/
    struct StateSearch
    {
        Bool        active;
        Index       row;
        Index       page;
        ULong       sort_buyout;
        ULong       sort_dpsarmor;

        StateSearch():
            active(false),
            row(0),
            page(0),
            sort_buyout(0),
            sort_dpsarmor(0)
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
