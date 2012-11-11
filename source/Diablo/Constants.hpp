#pragma once
#include <Core/Type/Enum.hpp>
#include <Core/Support/Settings.hpp>
#include <Diablo/Type/EnumObjects.hpp>
#include <Diablo/Types.hpp>
#include <Diablo/Enums.hpp>

namespace Diablo
{
    //------------------------------------------------------------------------
    extern Settings::ItemCollection LOCALE_ITEMS;
    extern const Char*              LOCALE_REGISTRY_PATH;
    extern const Char*              LOCALE_REGISTRY_KEY;
    extern const Char*              LOCALE_DEFAULT1;
    extern const Char*              LOCALE_DEFAULT2;

    //------------------------------------------------------------------------
    extern const Char*              GAME_WINDOW_CLASS;
    static const ULong              GAME_GLOBAL_DELAY_MAX =         60000;  // ms
    static const ULong              GAME_SLEEP_SLICE =              500;    // ms
    static const Number             GAME_LEVEL_MAX =                NUMBER(99, 0);
    static const ULong              GAME_LOGOUT_DELAY =             1000;
    static const ULong              GAME_LOGIN_LOOP_DELAY =         500;
    static const ULong              GAME_LOGIN_LOBBY_DELAY =        1400;
    static const ULong              GAME_MAIN_AUCTION_DELAY =       300;

    //------------------------------------------------------------------------
    static const ULong              TRAINER_UIOBJECT_LIMIT =        200;
    static const ULong              TRAINER_UISEARCH_DEPTH =        15;

    //------------------------------------------------------------------------
    static const ULong              ITEM_STAT_LIMIT =               14;
    static const Number             ITEM_STAT_VALUE_MAX =           NUMBER(99999, 0);
    static const ULong              ITEM_STAT_VALUE_LIMIT =         4;
    static const ULong              ITEM_SOCKET_LIMIT =             3;
    static const ULong              ITEM_GEM_RANK_LIMIT =           14;
    extern const ULongArray         ITEM_GEM_LIFEONHIT;
    extern const ULongArray         ITEM_GEM_CRITICALHITDAMAGE;
    extern const ULongArray         ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE;
    extern const ULongArray         ITEM_GEM_PHYSICALDAMAGETOATTACKER;
    extern const IdEnum             ITEM_GEM_STAT_IDS;
    extern const IdEnum             ITEM_GEM_TYPE_IDS;
    extern const IdEnum             ITEM_RARITY_COLORS;
    const extern IdEnum             ITEM_RARITY_STRINGS;

    //------------------------------------------------------------------------
    static const ULong              AH_PSTAT_LIMIT =                6;
    static const ULong              AH_BUYOUT_RANDOM_LIMIT =        4000;
    static const ULong              AH_ITEMHOVER_WAIT_ITERATIONS =  200;
    static const ULong              AH_NETWORK_WAIT_ITERATIONS =    6000;
    static const ULong              AH_BUTTON_WAIT_ITERATIONS =     40;
    static const ULong              AH_RESULTS_ROW_LIMIT =          11;
    static const ULong              AH_SELL_VISIBLE_LIMIT =         5;
    static const ULong              AH_SELL_ROW_LIMIT =             10;
    static const ULong              AH_UNIQUE_ROW_LIMIT =           5;
    static const ULong              AH_STASH_COLUMNS =              7;
    static const ULong              AH_STASH_ROWS =                 10;
    static const ULong              AH_STASH_BAGS =                 3;
    extern const IdEnum             AH_COMBO_CHAR_IDS;
    extern const IdEnum             AH_COMBO_PRIMARY_IDS;
    extern const ComboSecDepEnum    AH_COMBO_SECONDARY_DEPS;
    extern const Char*              AH_POPUP_SUCCESS_CREATEAUCTION;
    extern const Char*              AH_POPUP_SUCCESS_BUYOUT;
    extern const Char*              AH_POPUP_SUCCESS_BID;

    //------------------------------------------------------------------------
    static const ULong              UI_COORD_SPREAD =               2;
    extern const Coordinate         UI_COORDS[UI_COUNT];
    static const ULong              UI_COMBO_ROW_LIMIT =            TRAINER_UIOBJECT_LIMIT;
    static const ULong              UI_COMBO_REZMAP_MIN =           600;
    static const ULong              UI_COMBO_REZMAP_MAX =           1200;
}
