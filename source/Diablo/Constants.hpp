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
    extern const Char*          GAME_WINDOW_TITLE;
    extern const Char*          GAME_WINDOW_CLASS;
    static const ULong          GAME_COORDINATE_SPREAD = 2;
    static const Number         GAME_LEVEL_MAX = NUMBER(99, 0);

    //------------------------------------------------------------------------
    static const Number         ITEM_STAT_VALUE_MIN = NUMBER(0,     1);
    static const Number         ITEM_STAT_VALUE_MAX = NUMBER(99999, 0);
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
    static const ULong          AH_INPUT_PSTAT_LIMIT = 6;
    static const ULong          AH_INPUT_BUYOUT_RANDOM_LIMIT = 4000;
    extern const ComboBox       AH_COMBO_CHARACTER;
    extern const ComboBox       AH_COMBO_PRIMARY;
    extern const ComboBox       AH_COMBO_SECONDARY;
    extern const ComboBox       AH_COMBO_RARITY;
    extern const ComboBox       AH_COMBO_PSTAT;
    extern const ComboBox*      AH_COMBO_MAP[];
    static const ULong          AH_LIST_WAIT_ITERATIONS = 6000;
    static const ULong          AH_LIST_ROW_LIMIT = 11;
    static const ULong          AH_RELOGIN_LOGOUT_DELAY = 500;
    static const ULong          AH_RELOGIN_POSTLOGIN_DELAY = 1500;
    static const ULong          AH_RELOGIN_AUCTIONHOUSE_DELAY = 200;
    static const ULong          AH_STASH_COLUMNS = 7;
    static const ULong          AH_STASH_ROWS = 10;
    static const ULong          AH_STASH_BAGS = 3;

    extern const Coordinate     COORDS[UI_COUNT];
    extern const ULong          COMBO_DROP_COUNT[COMBO_COUNT];
    static const ULong          COMBO_BOX_REZMAP_MIN = 600;
    static const ULong          COMBO_BOX_REZMAP_MAX = 1200;
    extern const Double         COMBO_SELECTOR_REZMAP[];
}
