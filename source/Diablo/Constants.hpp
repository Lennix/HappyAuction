#pragma once
#include <Core/Type/Enum.hpp>
#include <Diablo/Type/ComboBox.hpp>
#include <Diablo/Types.hpp>
#include <Diablo/Enums.hpp>

namespace Diablo
{
    //------------------------------------------------------------------------
    extern ULong                GAME_GLOBAL_DELAY;
    static const ULong          GAME_GLOBAL_DELAY_MAX = 60000; // ms
    static const ULong          GAME_SLEEP_SLICE = 500; // ms

    //------------------------------------------------------------------------
    extern ULong                GAME_NEXTPAGE_DELAY;
    static const ULong          GAME_NEXTPAGE_DELAY_MIN = 0;        // ms
    static const ULong          GAME_NEXTPAGE_DELAY_MAX = 60000;    // ms

    //------------------------------------------------------------------------
    extern Double               GAME_CURRENT_QUERIES_PER_HOUR;
    extern Double               GAME_MAX_QUERIES_PER_HOUR;
    static const ULong          GAME_MAX_QUERIES_PER_HOUR_MIN = 0;        // qph
    static const ULong          GAME_MAX_QUERIES_PER_HOUR_MAX = 10000;    // qph

    //------------------------------------------------------------------------
    extern const Char*          GAME_WINDOW_TITLE;
    extern const Char*          GAME_WINDOW_CLASS;
    static const ULong          GAME_COORDINATE_SPREAD = 2;
    static const ULong          GAME_LEVEL_MAX = 99;

    //------------------------------------------------------------------------
    static const ULong          ITEM_STAT_VALUE_MIN = 1;
    static const ULong          ITEM_STAT_VALUE_MAX = 99999;
    static const ULong          ITEM_STAT_VALUE_LIMIT = 4;
    static const ULong          ITEM_STAT_LIMIT = 16;
    static const ULong          ITEM_SOCKET_LIMIT = 3;
    static const ULong          ITEM_GEM_RANK_LIMIT = 14;
    extern const ULongArray     ITEM_GEM_LIFEONHIT;
    extern const ULongArray     ITEM_GEM_CRITICALHITDAMAGE;
    extern const ULongArray     ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE;
    extern const ULongArray     ITEM_GEM_PHYSICALDAMAGETOATTACKER;
    extern const Char*          ITEM_GEM_TYPE_STRINGS[];

    //------------------------------------------------------------------------
    extern const Enum           ENUM_RARITIES;

    //------------------------------------------------------------------------
    static const ULong          AH_INPUT_PSTAT_LIMIT = 3;
    extern const Coordinate     AH_INPUT_LEVEL_MIN;
    extern const Coordinate     AH_INPUT_LEVEL_MAX;
    extern const Coordinate     AH_INPUT_PSTAT_VALUE[AH_INPUT_PSTAT_LIMIT];
    extern const Coordinate     AH_INPUT_UNIQUE;
    extern const Coordinate     AH_INPUT_BID;
    extern const Coordinate     AH_INPUT_BUYOUT;
    static const ULong          AH_INPUT_BUYOUT_RANDOM_LIMIT = 4000;
    extern const ComboBox       AH_COMBO_CHARACTER;
    extern const ComboBox       AH_COMBO_PRIMARY;
    extern const ComboBox       AH_COMBO_SECONDARY;
    extern const ComboBox       AH_COMBO_RARITY;
    extern const ComboBox       AH_COMBO_PSTAT;
    extern const Coordinate     AH_COMBO_COORDS[];
    extern const Coordinate     AH_BUTTON_SEARCH;
    extern const Coordinate     AH_BUTTON_BID;
    extern const Coordinate     AH_BUTTON_BUYOUT;
    extern const Coordinate     AH_BUTTON_BUYOUT_CONFIRM;
    extern const Coordinate     AH_BUTTON_BUYOUT_CONFIRM_OK;
    extern const Coordinate     AH_LIST_BEGIN;
    extern const Coordinate     AH_LIST_ICON;
    extern const Coordinate     AH_LIST_NEXT_BUTTON;
    extern const Coordinate     AH_LIST_SORT_DPSARMOR;
    extern const Coordinate     AH_LIST_SORT_BUYOUT;
    static const ULong          AH_LIST_WAIT_ITERATIONS = 6000;
    static const ULong          AH_LIST_ROW_LIMIT = 11;
    static const ULong          AH_RELOGIN_LOGOUT_DELAY = 500;
    static const ULong          AH_RELOGIN_POSTLOGIN_DELAY = 1100;
    static const ULong          AH_RELOGIN_AUCTIONHOUSE_DELAY = 200;
    extern const Coordinate     AH_RELOGIN_ACCOUNT;
    extern const Coordinate     AH_RELOGIN_PASSWORD;
    extern const Coordinate     AH_RELOGIN_LOGIN;
    extern const Coordinate     AH_RELOGIN_AUCTIONHOUSE;
    static const ULong          AH_STASH_COLUMNS = 7;
    static const ULong          AH_STASH_ROWS = 10;
    static const ULong          AH_STASH_BAGS = 3;

    extern const Coordinate     COORDS[UI_COUNT];
    extern const ULong          COMBO_HEIGHT[COMBO_COUNT];
    static const ULong          COMBO_BOX_REZMAP_MIN = 600;
    static const ULong          COMBO_BOX_REZMAP_MAX = 1200;
    extern const Double         COMBO_SELECTOR_REZMAP[];
}
