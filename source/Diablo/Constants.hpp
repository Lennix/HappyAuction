#pragma once
#include <Diablo/Type/ComboBox.hpp>
#include <Diablo/Types.hpp>

namespace Diablo
{
    //------------------------------------------------------------------------
    extern ULong                GAME_ITEMREAD_DELAY;
    static const ULong          GAME_ITEMREAD_DELAY_MIN = 5;        // ms
    static const ULong          GAME_ITEMREAD_DELAY_MAX = 60000;    // ms

    //------------------------------------------------------------------------
    extern ULong                GAME_NEXTPAGE_DELAY;
    static const ULong          GAME_NEXTPAGE_DELAY_MIN = 0;        // ms
    static const ULong          GAME_NEXTPAGE_DELAY_MAX = 60000;    // ms

    //------------------------------------------------------------------------
    extern Double               GAME_QUERIES_PER_HOUR;

    //------------------------------------------------------------------------
    extern const Char*          GAME_WINDOW_TITLE;
    extern const Char*          GAME_WINDOW_CLASS;
    static const ULong          GAME_COORDINATE_SPREAD = 2;
    static const ULong          GAME_LEVEL_MIN = 1;
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
    static const ULong          AH_INPUT_PSTAT_LIMIT = 3;
    extern const Coordinate     AH_INPUT_LEVEL_MIN;
    extern const Coordinate     AH_INPUT_LEVEL_MAX;
    extern const Coordinate     AH_INPUT_PSTAT_VALUE[AH_INPUT_PSTAT_LIMIT];
    extern const Coordinate     AH_INPUT_UNIQUE;
    extern const Coordinate     AH_INPUT_BID;
    extern const Coordinate     AH_INPUT_BUYOUT;
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
    static const ULong          AH_LIST_WAIT_ITERATIONS = 200;
    static const ULong          AH_LIST_ROW_LIMIT = 11;
}
