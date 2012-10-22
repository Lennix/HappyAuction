#pragma once
#include <Diablo/Constants.hpp>
#include <Diablo/Enums.hpp>

namespace Diablo
{
    // private
    //------------------------------------------------------------------------
    #define FIXED_REZ_X 2560
    #define FIXED_REZ_Y 1600

    #define F2R_Y(y)    ((Double)(y) / (Double)FIXED_REZ_Y)
    #define F2R_X(x)    F2R_Y(x)
    #define F2R_XR(x)   F2R_Y(FIXED_REZ_X - (x))
    #define F2R_XC(x)   ((Double)((x) - (FIXED_REZ_X / 2)) / (Double)FIXED_REZ_Y)

    //------------------------------------------------------------------------
    static const ULong _C_ALL =     ~0;
    static const ULong _C_BARB =    BIT(FILTER_CHAR_BARBARIAN);
    static const ULong _C_DH =      BIT(FILTER_CHAR_DEMONHUNTER);
    static const ULong _C_MONK =    BIT(FILTER_CHAR_MONK);
    static const ULong _C_WD =      BIT(FILTER_CHAR_WITCHDOCTOR);
    static const ULong _C_WIZ =     BIT(FILTER_CHAR_WIZARD);

    //------------------------------------------------------------------------
    static IdEnum::Item _char_ids[] =
    {
        { "Barbarian",      FILTER_CHAR_BARBARIAN },
        { "Demon Hunter",   FILTER_CHAR_DEMONHUNTER },
        { "Monk",           FILTER_CHAR_MONK },
        { "Witch Doctor",   FILTER_CHAR_WITCHDOCTOR },
        { "Wizard",         FILTER_CHAR_WIZARD },
    };

    static IdEnum::Item _primary_ids[] =
    {
        { "1-Hand",             FILTER_PRI_1H },
        { "2-Hand",             FILTER_PRI_2H },
        { "Off-Hand",           FILTER_PRI_OH },
        { "Armor",              FILTER_PRI_ARMOR },
        { "Follower Special",   FILTER_PRI_FOLLOWER },
    };

    static ComboSecDepEnum::Item _combo_secondary_deps[] =
    {
        // 1-Hand
        { "All 1-Hand Item Types",      { FILTER_PRI_1H, _C_ALL } },
        { "Axe",                        { FILTER_PRI_1H, _C_ALL } },
        { "Ceremonial Knife",           { FILTER_PRI_1H, _C_WD } },
        { "Hand Crossbow",              { FILTER_PRI_1H, _C_DH } },
        { "Dagger",                     { FILTER_PRI_1H, _C_ALL } },
        { "Fist Weapon",                { FILTER_PRI_1H, _C_MONK } },
        { "Mace",                       { FILTER_PRI_1H, _C_ALL } },
        { "Mighty Weapon",              { FILTER_PRI_1H, _C_BARB } },
        { "Spear",                      { FILTER_PRI_1H, _C_ALL } },
        { "Sword",                      { FILTER_PRI_1H, _C_ALL } },
        { "Wand",                       { FILTER_PRI_1H, _C_WIZ } },

        // 2-Hand
        { "All 2-Hand Item Types",      { FILTER_PRI_2H, _C_ALL } },
        { "Two-Handed Axe",             { FILTER_PRI_2H, _C_BARB|_C_MONK|_C_WD|_C_WIZ } },
        { "Bow",                        { FILTER_PRI_2H, _C_DH|_C_WD|_C_WIZ } },
        { "Daibo",                      { FILTER_PRI_2H, _C_MONK } },
        { "Crossbow",                   { FILTER_PRI_2H, _C_DH|_C_WD|_C_WIZ } },
        { "Two-Handed Mace",            { FILTER_PRI_2H, _C_BARB|_C_MONK|_C_WD|_C_WIZ } },
        { "Two-Handed Mighty Weapon",   { FILTER_PRI_2H, _C_BARB } },
        { "Polearm",                    { FILTER_PRI_2H, _C_BARB|_C_MONK|_C_WD } },
        { "Staff",                      { FILTER_PRI_2H, _C_MONK|_C_WD|_C_WIZ } },
        { "Two-Handed Sword",           { FILTER_PRI_2H, _C_BARB|_C_MONK|_C_WD|_C_WIZ } },

        // Off-Hand
        { "All Off-Hand Item Types",    { FILTER_PRI_OH, _C_ALL } },
        { "Mojo",                       { FILTER_PRI_OH, _C_WD } },
        { "Source",                     { FILTER_PRI_OH, _C_WIZ } },
        { "Quiver",                     { FILTER_PRI_OH, _C_DH } },
        { "Shield",                     { FILTER_PRI_OH, _C_ALL } },

        // Armor
        { "All Armor Item Types",       { FILTER_PRI_ARMOR, _C_ALL } },
        { "Amulet",                     { FILTER_PRI_ARMOR, _C_ALL } },
        { "Belt",                       { FILTER_PRI_ARMOR, _C_ALL } },
        { "Boots",                      { FILTER_PRI_ARMOR, _C_ALL } },
        { "Bracers",                    { FILTER_PRI_ARMOR, _C_ALL } },
        { "Chest Armor",                { FILTER_PRI_ARMOR, _C_ALL } },
        { "Cloak",                      { FILTER_PRI_ARMOR, _C_DH } },
        { "Gloves",                     { FILTER_PRI_ARMOR, _C_ALL } },
        { "Helm",                       { FILTER_PRI_ARMOR, _C_ALL } },
        { "Pants",                      { FILTER_PRI_ARMOR, _C_ALL } },
        { "Mighty Belt",                { FILTER_PRI_ARMOR, _C_BARB } },
        { "Ring",                       { FILTER_PRI_ARMOR, _C_ALL } },
        { "Shoulders",                  { FILTER_PRI_ARMOR, _C_ALL } },
        { "Spirit Stone",               { FILTER_PRI_ARMOR, _C_MONK } },
        { "Voodoo Mask",                { FILTER_PRI_ARMOR, _C_WD } },
        { "Wizard Hat",                 { FILTER_PRI_ARMOR, _C_WIZ } },

        // Follower Special
        { "All Follower Special Item Types", { FILTER_PRI_FOLLOWER, _C_ALL } },
        { "Enchantress Focus",          { FILTER_PRI_FOLLOWER, _C_ALL } },
        { "Scoundrel Token",            { FILTER_PRI_FOLLOWER, _C_ALL } },
        { "Templar Relic",              { FILTER_PRI_FOLLOWER, _C_ALL } },
    };

    static IdEnum::Item _gem_stats[] =
    {
        // amethyst
        { "",   GEM_STAT_VITALITY },
        { "",   GEM_STAT_LIFEP },
        { "",   GEM_STAT_LIFEONHIT },

        // emerald
        { "",   GEM_STAT_DEXTERITY },
        { "",   GEM_STAT_GOLDFIND },
        { "",   GEM_STAT_CRITICALHITDAMAGE },

        // ruby
        { "",   GEM_STAT_STRENGTH },
        { "",   GEM_STAT_BONUSEXPERIENCE },
        { "",   GEM_STAT_AVERAGEDAMAGE },

        // topaz
        { "",   GEM_STAT_INTELLIGENCE },
        { "",   GEM_STAT_MAGICFIND },
        { "",   GEM_STAT_PHYSICALDAMAGETOATTACKER },
    };

    static IdEnum::Item _gem_types[] =
    {
        { "Empty",      GEM_TYPE_EMPTY },
        { "Amethyst",   GEM_TYPE_AMETHYST },
        { "Emerald",    GEM_TYPE_EMERALD },
        { "Ruby",       GEM_TYPE_RUBY },
        { "Topaz",      GEM_TYPE_TOPAZ },
    };

    static Settings::Item _locale_items[] =
    {
        { "GEM_STAT_VITALITY",                  "", LOCALE_GEMSTAT, GEM_STAT_VITALITY },
        { "GEM_STAT_LIFEP",                     "", LOCALE_GEMSTAT, GEM_STAT_LIFEP },
        { "GEM_STAT_LIFEONHIT",                 "", LOCALE_GEMSTAT, GEM_STAT_LIFEONHIT },
        { "GEM_STAT_DEXTERITY",                 "", LOCALE_GEMSTAT, GEM_STAT_DEXTERITY },
        { "GEM_STAT_GOLDFIND",                  "", LOCALE_GEMSTAT, GEM_STAT_GOLDFIND },
        { "GEM_STAT_CRITICALHITDAMAGE",         "", LOCALE_GEMSTAT, GEM_STAT_CRITICALHITDAMAGE },
        { "GEM_STAT_STRENGTH",                  "", LOCALE_GEMSTAT, GEM_STAT_STRENGTH },
        { "GEM_STAT_BONUSEXPERIENCE",           "", LOCALE_GEMSTAT, GEM_STAT_BONUSEXPERIENCE },
        { "GEM_STAT_AVERAGEDAMAGE",             "", LOCALE_GEMSTAT, GEM_STAT_AVERAGEDAMAGE },
        { "GEM_STAT_INTELLIGENCE",              "", LOCALE_GEMSTAT, GEM_STAT_INTELLIGENCE },
        { "GEM_STAT_MAGICFIND",                 "", LOCALE_GEMSTAT, GEM_STAT_MAGICFIND },
        { "GEM_STAT_PHYSICALDAMAGETOATTACKER",  "", LOCALE_GEMSTAT, GEM_STAT_PHYSICALDAMAGETOATTACKER },
    };

    //------------------------------------------------------------------------
    static const ULong _item_gem_lifeonhit[ITEM_GEM_RANK_LIMIT] =
    {
        2, 3, 6, 10, 15, 25, 35, 65, 105, 190, 300, 400, 500, 600
    };
    static const ULong _item_gem_criticalhitdamage[ITEM_GEM_RANK_LIMIT] =
    {
        10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100
    };
    static const ULong _item_gem_bonusminimumweapondamage[ITEM_GEM_RANK_LIMIT] =
    {
        2, 4, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };
    static const ULong _item_gem_physicaldamagetoattacker[ITEM_GEM_RANK_LIMIT] =
    {
        2, 3, 6, 10, 15, 30, 50, 100, 200, 350, 600, 900, 1250, 1800
    };


    // public
    //------------------------------------------------------------------------
    Settings::ItemCollection LOCALE_ITEMS(_locale_items, ACOUNT(_locale_items));
    const Char*             LOCALE_REGISTRY_PATH = "Software\\Blizzard Entertainment\\D3";
    const Char*             LOCALE_REGISTRY_KEY = "Locale";
    const Char*             LOCALE_DEFAULT1 = "enUS";
    const Char*             LOCALE_DEFAULT2 = "enGB";

    //------------------------------------------------------------------------
    const Char*             GAME_WINDOW_CLASS = "D3 Main Window Class";
    ULong                   GAME_GLOBAL_DELAY = 0;      // ms

    //------------------------------------------------------------------------
    const ULongArray        ITEM_GEM_LIFEONHIT(_item_gem_lifeonhit, ACOUNT(_item_gem_lifeonhit));
    const ULongArray        ITEM_GEM_CRITICALHITDAMAGE(_item_gem_criticalhitdamage, ACOUNT(_item_gem_criticalhitdamage));
    const ULongArray        ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE(_item_gem_bonusminimumweapondamage, ACOUNT(_item_gem_bonusminimumweapondamage));
    const ULongArray        ITEM_GEM_PHYSICALDAMAGETOATTACKER(_item_gem_physicaldamagetoattacker, ACOUNT(_item_gem_physicaldamagetoattacker));
    const IdEnum            ITEM_GEM_STAT_IDS(_gem_stats, ACOUNT(_gem_stats));
    const IdEnum            ITEM_GEM_TYPE_IDS(_gem_types, ACOUNT(_gem_types));

    //------------------------------------------------------------------------
    const IdEnum            AH_COMBO_CHAR_IDS(_char_ids, ACOUNT(_char_ids));
    const IdEnum            AH_COMBO_PRIMARY_IDS(_primary_ids, ACOUNT(_primary_ids));
    const ComboSecDepEnum   AH_COMBO_SECONDARY_DEPS(_combo_secondary_deps, ACOUNT(_combo_secondary_deps));

    //------------------------------------------------------------------------
    const Coordinate UI_COORDS[UI_COUNT] =
    {
        // UI_BUTTON_SEARCH
        Coordinate( F2R_XC(627),  F2R_Y(1245) ),
        // UI_BUTTON_BID
        Coordinate( F2R_XC(1646), F2R_Y(1300) ),
        // UI_BUTTON_BIDCONFIRM
        Coordinate( F2R_XC(1110), F2R_Y(1159) ),
        // UI_BUTTON_BUYOUT
        Coordinate( F2R_XC(2000), F2R_Y(1300) ),
        // UI_BUTTON_BUYOUTCONFIRM
        Coordinate( F2R_XC(1110), F2R_Y(1159) ),
        // UI_BUTTON_CREATEAUCTION
        Coordinate( F2R_XC(1278), F2R_Y(1299) ),
        // UI_BUTTON_SENDTOSTASH
        Coordinate( F2R_XC(629),  F2R_Y(664) ),
        // UI_BUTTON_LOGIN
        Coordinate( F2R_XC(1280), F2R_Y(1265) ),
        // UI_BUTTON_AUCTIONHOUSE
        Coordinate( F2R_X (345),  F2R_Y(949), Coordinate::LEFT ),
        // UI_BUTTON_OPTIONS
        Coordinate( F2R_XR(2345), F2R_Y(1500), Coordinate::RIGHT ),
        // UI_BUTTON_OPTIONSLOGOUT
        Coordinate( F2R_XC(1280),  F2R_Y(767) ),
        // UI_BUTTON_PROFILECLOSE
        Coordinate( F2R_XC(2196), F2R_Y(165) ),

        // UI_LBUTTON_PAGENEXT
        Coordinate( F2R_XC(1668), F2R_Y(1212) ),
        // UI_LBUTTON_SORTDPSARMOR
        Coordinate( F2R_XC(1662), F2R_Y(408) ),
        // UI_LBUTTON_SORTBUYOUT
        Coordinate( F2R_XC(1962), F2R_Y(408) ),
        // UI_LBUTTON_SORTTIMELEFT
        Coordinate( F2R_XC(2109), F2R_Y(408) ),
        // UI_LBUTTON_CLEARPSTAT0-5
        Coordinate( F2R_XC(799),  F2R_Y(880) ),
        Coordinate( F2R_XC(799),  F2R_Y(935) ),
        Coordinate( F2R_XC(799),  F2R_Y(991) ),
        Coordinate( F2R_XC(799),  F2R_Y(1048) ),
        Coordinate( F2R_XC(799),  F2R_Y(1104) ),
        Coordinate( F2R_XC(799),  F2R_Y(1160) ),

        // UI_TAB_SEARCH
        Coordinate( F2R_XC(791),  F2R_Y(240) ),
        // UI_TAB_SEARCH_EQUIPMENT
        Coordinate( F2R_XC(699),  F2R_Y(353) ),
        // UI_TAB_SELL
        Coordinate( F2R_XC(1122), F2R_Y(240) ),
        // UI_TAB_COMPLETED
        Coordinate( F2R_XC(1750), F2R_Y(240) ),
        // UI_TAB_STASHBAG1-3
        Coordinate( F2R_XC(1066), F2R_Y(482) ),
        Coordinate( F2R_XC(1066), F2R_Y(650) ),
        Coordinate( F2R_XC(1066), F2R_Y(808) ),

        // UI_CONTAINER_STASHBOXSIZE
        Coordinate( F2R_X(79.57), F2R_Y(82.3) ),
        // UI_CONTAINER_STASHBOX00
        Coordinate( F2R_XC(472),  F2R_Y(445) ),
        // UI_CONTAINER_LISTICON0
        Coordinate( F2R_XC(895),  F2R_Y(443) ),
        // UI_CONTAINER_LISTICONSIZE
        Coordinate( F2R_X(66.91), F2R_Y(66.91) ),
        // UI_CONTAINER_COMBOROWSIZE
        Coordinate( F2R_X(100),   F2R_Y(44.8) ),
        // UI_CONTAINER_UNIQUEROWSIZE
        Coordinate( F2R_X(100),   F2R_Y(51.4) ),

        // UI_INPUT_FILTERLEVELMIN
        Coordinate( F2R_XC(461),  F2R_Y(667) ),
        // UI_INPUT_FILTERLEVELMAX
        Coordinate( F2R_XC(570),  F2R_Y(667) ),
        // UI_INPUT_FILTERUNIQUE
        Coordinate( F2R_XC(622),  F2R_Y(736) ),
        // UI_INPUT_FILTERBUYOUT
        Coordinate( F2R_XC(622),  F2R_Y(785) ),
        // UI_INPUT_FILTERPSTAT0-5
        Coordinate( F2R_XC(739),  F2R_Y(880) ),
        Coordinate( F2R_XC(739),  F2R_Y(935) ),
        Coordinate( F2R_XC(739),  F2R_Y(991) ),
        Coordinate( F2R_XC(739),  F2R_Y(1048) ),
        Coordinate( F2R_XC(739),  F2R_Y(1104) ),
        Coordinate( F2R_XC(739),  F2R_Y(1160) ),
        // UI_INPUT_MAXBID
        Coordinate( F2R_XC(1466), F2R_Y(629) ),
        // UI_INPUT_SELLSTARTING
        Coordinate( F2R_XC(1278), F2R_Y(706) ),
        // UI_INPUT_SELLBUYOUT
        Coordinate( F2R_XC(1278), F2R_Y(826) ),
        // UI_INPUT_LOGINACCOUNT
        Coordinate( F2R_XC(1280), F2R_Y(880) ),
        // UI_INPUT_LOGINPASSWORD
        Coordinate( F2R_XC(1280), F2R_Y(1047) ),

        // UI_COMBO_RARITY
        Coordinate( F2R_XC(691),  F2R_Y(666) ),
        // UI_COMBO_CHARACTER
        Coordinate( F2R_XC(484),  F2R_Y(456) ),
        // UI_COMBO_PRIMARY
        Coordinate( F2R_XC(484),  F2R_Y(512) ),
        // UI_COMBO_SECONDARY
        Coordinate( F2R_XC(484),  F2R_Y(568) ),
        // UI_COMBO_PSTAT0-5
        Coordinate( F2R_XC(484),  F2R_Y(881) ),
        Coordinate( F2R_XC(484),  F2R_Y(937) ),
        Coordinate( F2R_XC(484),  F2R_Y(993) ),
        Coordinate( F2R_XC(484),  F2R_Y(1049) ),
        Coordinate( F2R_XC(484),  F2R_Y(1105) ),
        Coordinate( F2R_XC(484),  F2R_Y(1161) ),

        // UI_POPUP_ERROR
        Coordinate( F2R_XC(1280), F2R_Y(936) ),
        // UI_POPUP_OK
        Coordinate( F2R_XC(1280), F2R_Y(687) ),
        // UI_POPUP_UNIQUE
        Coordinate( F2R_XC(500),  F2R_Y(798) ),

        // UI_OTHER_GROUND
        Coordinate( F2R_XC(1280), F2R_Y(4) ),
    };
}
