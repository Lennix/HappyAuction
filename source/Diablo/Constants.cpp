#pragma once
#include <Diablo/Constants.hpp>
#include <Diablo/Enums.hpp>

namespace Diablo
{
    //------------------------------------------------------------------------
    static const ULong _C_ALL =         ~0;
    static const ULong _C_BARB =        BIT(FILTER_CHAR_BARBARIAN);
    static const ULong _C_DH =          BIT(FILTER_CHAR_DEMONHUNTER);
    static const ULong _C_MONK =        BIT(FILTER_CHAR_MONK);
    static const ULong _C_WD =          BIT(FILTER_CHAR_WITCHDOCTOR);
    static const ULong _C_WIZ =         BIT(FILTER_CHAR_WIZARD);

    static const UHuge _ALL =           ~0;
    static const UHuge _1H_ALL =        B64(FILTER_SEC_1H_ALL), _1H_AXE = B64(FILTER_SEC_1H_AXE), _1H_CEREMONIALKNIFE = B64(FILTER_SEC_1H_CEREMONIALKNIFE), _1H_HANDCROSSBOW = B64(FILTER_SEC_1H_HANDCROSSBOW), _1H_DAGGER = B64(FILTER_SEC_1H_DAGGER), _1H_FISTWEAPON = B64(FILTER_SEC_1H_FISTWEAPON), _1H_MACE = B64(FILTER_SEC_1H_MACE), _1H_MIGHTYWEAPON = B64(FILTER_SEC_1H_MIGHTYWEAPON), _1H_SPEAR = B64(FILTER_SEC_1H_SPEAR), _1H_SWORD = B64(FILTER_SEC_1H_SWORD), _1H_WAND = B64(FILTER_SEC_1H_WAND);
    static const UHuge _2H_ALL =        B64(FILTER_SEC_2H_ALL), _2H_AXE = B64(FILTER_SEC_2H_AXE), _2H_BOW = B64(FILTER_SEC_2H_BOW), _2H_DAIBO = B64(FILTER_SEC_2H_DAIBO), _2H_CROSSBOW = B64(FILTER_SEC_2H_CROSSBOW), _2H_MACE = B64(FILTER_SEC_2H_MACE), _2H_MIGHTYWEAPON = B64(FILTER_SEC_2H_MIGHTYWEAPON), _2H_POLEARM = B64(FILTER_SEC_2H_POLEARM), _2H_STAFF = B64(FILTER_SEC_2H_STAFF), _2H_SWORD = B64(FILTER_SEC_2H_SWORD);
    static const UHuge _OH_ALL =        B64(FILTER_SEC_OH_ALL), _OH_MOJO = B64(FILTER_SEC_OH_MOJO), _OH_SOURCE = B64(FILTER_SEC_OH_SOURCE), _OH_QUIVER = B64(FILTER_SEC_OH_QUIVER), _OH_SHIELD = B64(FILTER_SEC_OH_SHIELD);
    static const UHuge _ARMOR_ALL =     B64(FILTER_SEC_ARMOR_ALL), _ARMOR_AMULET = B64(FILTER_SEC_ARMOR_AMULET), _ARMOR_BELT = B64(FILTER_SEC_ARMOR_BELT), _ARMOR_BOOTS = B64(FILTER_SEC_ARMOR_BOOTS), _ARMOR_BRACERS = B64(FILTER_SEC_ARMOR_BRACERS), _ARMOR_CHESTARMOR = B64(FILTER_SEC_ARMOR_CHESTARMOR), _ARMOR_CLOAK = B64(FILTER_SEC_ARMOR_CLOAK), _ARMOR_GLOVES = B64(FILTER_SEC_ARMOR_GLOVES), _ARMOR_HELM = B64(FILTER_SEC_ARMOR_HELM), _ARMOR_PANTS = B64(FILTER_SEC_ARMOR_PANTS), _ARMOR_MIGHTYBELT = B64(FILTER_SEC_ARMOR_MIGHTYBELT), _ARMOR_RING = B64(FILTER_SEC_ARMOR_RING), _ARMOR_SHOULDERS = B64(FILTER_SEC_ARMOR_SHOULDERS), _ARMOR_SPIRITSTONE = B64(FILTER_SEC_ARMOR_SPIRITSTONE), _ARMOR_VOODOOMASK = B64(FILTER_SEC_ARMOR_VOODOOMASK), _ARMOR_WIZARDHAT = B64(FILTER_SEC_ARMOR_WIZARDHAT);
    static const UHuge _FOLLOWER_ALL =  B64(FILTER_SEC_FOLLOWER_ALL), _FOLLOWER_ENCHANTRESS = B64(FILTER_SEC_FOLLOWER_ENCHANTRESS), _FOLLOWER_SCOUNDREL = B64(FILTER_SEC_FOLLOWER_SCOUNDREL), _FOLLOWER_TEMPLAR = B64(FILTER_SEC_FOLLOWER_TEMPLAR);
    static const UHuge _1H =            _1H_ALL | _1H_AXE | _1H_CEREMONIALKNIFE | _1H_HANDCROSSBOW | _1H_DAGGER | _1H_FISTWEAPON | _1H_MACE | _1H_MIGHTYWEAPON | _1H_SPEAR | _1H_SWORD | _1H_WAND;
    static const UHuge _2H =            _2H_ALL | _2H_AXE | _2H_BOW | _2H_DAIBO | _2H_CROSSBOW | _2H_MACE | _2H_MIGHTYWEAPON | _2H_POLEARM | _2H_STAFF | _2H_SWORD;
    static const UHuge _OH =            _OH_ALL | _OH_MOJO | _OH_SOURCE | _OH_QUIVER | _OH_SHIELD;
    static const UHuge _ARMOR =         _ARMOR_ALL | _ARMOR_AMULET | _ARMOR_BELT | _ARMOR_BOOTS | _ARMOR_BRACERS | _ARMOR_CHESTARMOR | _ARMOR_CLOAK | _ARMOR_GLOVES | _ARMOR_HELM | _ARMOR_PANTS | _ARMOR_MIGHTYBELT | _ARMOR_RING | _ARMOR_SHOULDERS | _ARMOR_SPIRITSTONE | _ARMOR_VOODOOMASK | _ARMOR_WIZARDHAT;
    static const UHuge _FOLLOWER =      _FOLLOWER_ALL | _FOLLOWER_ENCHANTRESS | _FOLLOWER_SCOUNDREL | _FOLLOWER_TEMPLAR;

    //------------------------------------------------------------------------
    const ComboOption _options_character[] =
    {
        { "Default",        { 0 }, _ALL },
        { "Barbarian",      { 0 }, _ALL },
        { "Demon Hunter",   { 0 }, _ALL },
        { "Monk",           { 0 }, _ALL },
        { "Witch Doctor",   { 0 }, _ALL },
        { "Wizard",         { 0 }, _ALL },
    };

    const ComboOption _options_primary[] =
    {
        { "1-Hand",             { 0 }, _ALL },
        { "2-Hand",             { 0 }, _ALL },
        { "Off-Hand",           { 0 }, _ALL },
        { "Armor",              { 0 }, _ALL },
        { "Follower Special",   { 0 }, _ALL },
    };

    const ComboOption _options_secondary[] =
    {
        // 1-Hand
        { "All 1-Hand Item Types",      { 0 }, B64(FILTER_PRI_1H), _C_ALL },
        { "Axe",                        { 0 }, B64(FILTER_PRI_1H), _C_ALL },
        { "Ceremonial Knife",           { 0 }, B64(FILTER_PRI_1H), _C_WD },
        { "Hand Crossbow",              { 0 }, B64(FILTER_PRI_1H), _C_DH },
        { "Dagger",                     { 0 }, B64(FILTER_PRI_1H), _C_ALL },
        { "Fist Weapon",                { 0 }, B64(FILTER_PRI_1H), _C_MONK },
        { "Mace",                       { 0 }, B64(FILTER_PRI_1H), _C_ALL },
        { "Mighty Weapon",              { 0 }, B64(FILTER_PRI_1H), _C_BARB },
        { "Spear",                      { 0 }, B64(FILTER_PRI_1H), _C_ALL },
        { "Sword",                      { 0 }, B64(FILTER_PRI_1H), _C_ALL },
        { "Wand",                       { 0 }, B64(FILTER_PRI_1H), _C_WIZ },

        // 2-Hand
        { "All 2-Hand Item Types",      { 0 }, B64(FILTER_PRI_2H), _C_ALL },
        { "Two-Handed Axe",             { 0 }, B64(FILTER_PRI_2H), _C_BARB|_C_MONK|_C_WD|_C_WIZ },
        { "Bow",                        { 0 }, B64(FILTER_PRI_2H), _C_DH|_C_WD|_C_WIZ },
        { "Daibo",                      { 0 }, B64(FILTER_PRI_2H), _C_MONK },
        { "Crossbow",                   { 0 }, B64(FILTER_PRI_2H), _C_DH|_C_WD|_C_WIZ },
        { "Two-Handed Mace",            { 0 }, B64(FILTER_PRI_2H), _C_BARB|_C_MONK|_C_WD|_C_WIZ },
        { "Two-Handed Mighty Weapon",   { 0 }, B64(FILTER_PRI_2H), _C_BARB },
        { "Polearm",                    { 0 }, B64(FILTER_PRI_2H), _C_BARB|_C_MONK|_C_WD },
        { "Staff",                      { 0 }, B64(FILTER_PRI_2H), _C_MONK|_C_WD|_C_WIZ },
        { "Two-Handed Sword",           { 0 }, B64(FILTER_PRI_2H), _C_BARB|_C_MONK|_C_WD|_C_WIZ },

        // Off-Hand
        { "All Off-Hand Item Types",    { 0 }, B64(FILTER_PRI_OH), _C_ALL },
        { "Mojo",                       { 0 }, B64(FILTER_PRI_OH), _C_WD },
        { "Source",                     { 0 }, B64(FILTER_PRI_OH), _C_WIZ },
        { "Quiver",                     { 0 }, B64(FILTER_PRI_OH), _C_DH },
        { "Shield",                     { 0 }, B64(FILTER_PRI_OH), _C_ALL },

        // Armor
        { "All Armor Item Types",       { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Amulet",                     { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Belt",                       { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Boots",                      { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Bracers",                    { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Chest Armor",                { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Cloak",                      { 0 }, B64(FILTER_PRI_ARMOR), _C_DH },
        { "Gloves",                     { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Helm",                       { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Pants",                      { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Mighty Belt",                { 0 }, B64(FILTER_PRI_ARMOR), _C_BARB },
        { "Ring",                       { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Shoulders",                  { 0 }, B64(FILTER_PRI_ARMOR), _C_ALL },
        { "Spirit Stone",               { 0 }, B64(FILTER_PRI_ARMOR), _C_MONK },
        { "Voodoo Mask",                { 0 }, B64(FILTER_PRI_ARMOR), _C_WD },
        { "Wizard Hat",                 { 0 }, B64(FILTER_PRI_ARMOR), _C_WIZ },

        // Follower Special
        { "All Follower Special Item Types", { 0 }, B64(FILTER_PRI_FOLLOWER), _C_ALL },
        { "Enchantress Focus",          { 0 }, B64(FILTER_PRI_FOLLOWER), _C_ALL },
        { "Scoundrel Token",            { 0 }, B64(FILTER_PRI_FOLLOWER), _C_ALL },
        { "Templar Relic",              { 0 }, B64(FILTER_PRI_FOLLOWER), _C_ALL },
    };

    const ComboOption _options_rarity[] =
    {
        { "All",        { 0 }, _ALL },
        { "Inferior",   { 0 }, _ALL },
        { "Normal",     { 0 }, _ALL },
        { "Superior",   { 0 }, _ALL },
        { "Magic",      { 0 }, _ALL },
        { "Rare",       { 0 }, _ALL },
        { "Legendary",  { 0 }, _ALL },
    };

    const ComboOption _options_pstats[] =
    {
        { "None",                               { 0 },                                                                  _ALL },

        // damage
        { "Damage",                             { 0 },                                                                  (_1H) | (_2H) | (_ARMOR) | (_OH) | (_FOLLOWER) },
        { "All Resistance",                     { "+%u Resistance to All Elements" },                                   (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Arcane Resistance",                  { "+%u Arcane Resistance" },                                            (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Armor",                              { "+%u Armor" },                                                        (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER_ALL|_FOLLOWER_TEMPLAR) },
        { "Attack Speed %",                     { "Increases Attack Speed by %u%%",
                                                  "Attack Speed Increased by %u%%" },                                   (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_GLOVES|_ARMOR_RING)},
        { "Bleed Chance",                       { "%u%% chance to inflict Bleed for %u-%u damage over %u seconds." },   (_1H) | (_2H) | (_OH) },
        { "Block %",                            { "+%u%% Chance to Block" },                                            (_ARMOR_ALL) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER_ALL|_FOLLOWER_TEMPLAR) },
        { "Bonus Minimum Arcane Damage",        { "+%u-%u Arcane Damage" },                                             (_1H) | (_2H) },
        { "Bonus Minimum Cold Damage",          { "+%u-%u Cold Damage" },                                               (_1H) | (_2H) },
        { "Bonus Minimum Fire Damage",          { "+%u-%u Fire Damage" },                                               (_1H) | (_2H) },
        { "Bonus Minimum Holy Damage",          { "+%u-%u Holy Damage" },                                               (_1H) | (_2H) },
        { "Bonus Minimum Lightning Damage",     { "+%u-%u Lightning Damage" },                                          (_1H) | (_2H) },
        { "Bonus Minimum Poison Damage",        { "+%u-%u Poison Damage" },                                             (_1H) | (_2H) },
        { "Bonus Minimum Weapon Damage",        { "+%u Minimum Damage" },                                               (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_RING) },
        { "Bonus vs Elites",                    { "Increases Damage Against Elites by %u%%" },                          (_1H) | (_2H_ALL|_2H_AXE|_2H_BOW|_2H_DAIBO|_2H_CROSSBOW|_2H_MACE|_2H_MIGHTYWEAPON|_2H_STAFF|_2H_SWORD) | (_OH) },
        { "Cold Resistance",                    { "+%u Cold Resistance" },                                              (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Critical Hit Chance",                { "Critical Hit Chance Increased by %u%%" },                            (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_BRACERS|_ARMOR_GLOVES|_ARMOR_HELM|_ARMOR_RING|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH) },
        { "Critical Hit Damage",                { "Critical Hit Damage Increased by %u%%" },                            (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_GLOVES|_ARMOR_RING) | (_FOLLOWER) },
        { "Fire Resistance",                    { "+%u Fire Resistance" },                                              (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Lightning Resistance",               { "+%u Lightning Resistance" },                                         (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Min Bleed Damage",                   { "%u%% chance to inflict Bleed for %u-%u damage over %u seconds." },   (_1H) | (_2H) | (_OH) },
        { "Physical Damage to Attacker",        { "Melee attackers take %u damage per hit" },                           (_ARMOR) | (_OH) },
        { "Physical Resistance",                { "+%u Physical Resistance" },                                          (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Poison Resistance",                  { "+%u Poison Resistance" },                                            (_ARMOR) | (_OH_ALL|_OH_SHIELD) | (_FOLLOWER) },
        { "Reduced Damage from Elites",         { "Reduces damage from elites by %u%%" },                               (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) | (_OH_ALL|_OH_SHIELD) },
        { "Reduced Damage from Melee Attacks",  { "Reduces damage from melee attacks by %u%%" },                        (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_BRACERS|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) | (_OH_ALL|_OH_SHIELD) },
        { "Reduced Damage from Ranged Attacks", { "Reduces damage from ranged attacks by %u%%" },                       (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_BRACERS|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) | (_OH_ALL|_OH_SHIELD) },
        { "Weapon Damage %",                    { "+%u%% Damage" },                                                     (_1H) | (_2H) },

        // crowd control
        { "Crowd Control",                      { 0 },                                                                  (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_BELT|_ARMOR_BOOTS|_ARMOR_BRACERS|_ARMOR_GLOVES|_ARMOR_HELM|_ARMOR_PANTS|_ARMOR_MIGHTYBELT|_ARMOR_RING|_ARMOR_SHOULDERS|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH) },
        { "Chance to Blind on Hit",             { "%u%% Chance to Blind on Hit" },                                      (_1H) | (_2H) | (_OH) },
        { "Chance to Chill on Hit",             { "%u%% Chance to Chill on Hit" },                                      (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_SHOULDERS) | (_OH) },
        { "Chance to Fear on Hit",              { "%u%% Chance to Fear on Hit" },                                       (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH) },
        { "Chance to Freeze on Hit",            { "%u%% Chance to Freeze on Hit" },                                     (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) | (_OH) },
        { "Chance to Immobilize on Hit",        { "%u%% Chance to Immobilize on Hit" },                                 (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_BOOTS) | (_OH) },
        { "Chance to Knockback on Hit",         { "%u%% Chance to Knockback on Hit" },                                  (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_BRACERS) | (_OH) },
        { "Chance to Slow on Hit",              { "%u%% Chance to Slow on Hit" },                                       (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_PANTS) | (_OH) },
        { "Chance to Stun on Hit",              { "%u%% Chance to Stun on Hit" },                                       (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_GLOVES) | (_OH) },
        { "Crowd Control Reduction",            { "Reduces duration of control impairing effects by %u" },              (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_HELM|_ARMOR_RING|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH_ALL|_OH_SHIELD) },

        // life
        { "Life",                               { 0 },                                                                  (_1H) | (_2H) | (_ARMOR) | (_OH) | (_FOLLOWER)},
        { "Extra Health from Globes",           { "Health Globes Grant +%u Life." },                                    (_ARMOR) | (_OH) },
        { "Life %",                             { "+%u%% Life" },                                                       (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_BELT|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_HELM|_ARMOR_MIGHTYBELT|_ARMOR_RING|_ARMOR_SHOULDERS|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH) },
        { "Life Regeneration",                  { "Regenerates %u Life per Second" },                                   (_ARMOR) | (_OH) | (_FOLLOWER) },
        { "Life Steal",                         { "%u%% of Damage Dealt Is Converted to Life" },                        (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Life after Kill",                    { "+%u Life after Each Kill" },                                         (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_RING) | (_FOLLOWER) },
        { "Life on Hit",                        { "Each Hit Adds +%u Life" },                                           (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_RING) | (_FOLLOWER) },
        { "Life Per Spirit Spent",              { "Gain %u Life per Spirit Spent" },                                    (_1H_ALL|_1H_FISTWEAPON) | (_2H_ALL|_2H_DAIBO) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },

        // resource
        { "Resource",                           { 0 },                                                                  (_1H_ALL|_1H_CEREMONIALKNIFE|_1H_HANDCROSSBOW|_1H_FISTWEAPON|_1H_MIGHTYWEAPON|_1H_WAND) |
                                                                                                                        (_2H_ALL|_2H_DAIBO|_2H_MIGHTYWEAPON) |
                                                                                                                        (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_HELM|_ARMOR_MIGHTYBELT|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) |
                                                                                                                        (_OH_ALL|_OH_MOJO|_OH_SOURCE|_OH_QUIVER) },
        { "Arcane Power on Crit",               { "Critical Hits grant %u Arcane Power" },                              (_1H_ALL|_1H_WAND) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) | (_OH_ALL|_OH_SOURCE) },
        { "Hatred Regeneration",                { "Increases Hatred Regeneration by %u per Second" },                   (_1H_ALL|_1H_HANDCROSSBOW) | (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) | (_OH_ALL|_OH_QUIVER) },
        { "Mana Regeneration",                  { "Increases Mana Regeneration by %u per Second" },                     (_1H_ALL|_1H_CEREMONIALKNIFE) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_VOODOOMASK) | (_OH_ALL|_OH_MOJO) },
        { "Max Arcane Power",                   { "+%u Maximum Arcane Power" },                                         (_1H_ALL|_1H_WAND) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) | (_OH_ALL|_OH_SOURCE) },
        { "Max Discipline",                     { "+%u Maximum Discipline" },                                           (_1H_ALL|_1H_HANDCROSSBOW) | (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) | (_OH_ALL|_OH_QUIVER) },
        { "Max Fury",                           { "+%u Maximum Fury" },                                                 (_1H_ALL|_1H_MIGHTYWEAPON) | (_2H_ALL|_2H_MIGHTYWEAPON) | (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Max Mana",                           { "+%u Maximum Mana" },                                                 (_1H_ALL|_1H_CEREMONIALKNIFE) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_VOODOOMASK) | (_OH_ALL|_OH_MOJO) },
        { "Spirit Regeneration",                { "Increases Spirit Regeneration by %u per Second" },                   (_1H_ALL|_1H_FISTWEAPON) | (_2H_ALL|_2H_DAIBO) | (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },

        // attributes
        { "Attributes",                         { 0 },                                                                  _ALL },
        { "Dexterity",                          { "+%u Dexterity" },                                                    _ALL },
        { "Experience",                         { "Monster kills grant +%u experience." },                              _ALL },
        { "Intelligence",                       { "+%u Intelligence" },                                                 _ALL },
        { "Strength",                           { "+%u Strength" },                                                     _ALL },
        { "Vitality",                           { "+%u Vitality" },                                                     _ALL },

        // skills
        { "Skills",                             { 0 },                                                                          (_1H_ALL|_1H_CEREMONIALKNIFE|_1H_DAGGER|_1H_SPEAR|_1H_SWORD|_1H_WAND) |
                                                                                                                                (_2H_ALL|_2H_AXE|_2H_BOW|_2H_DAIBO|_2H_CROSSBOW|_2H_MACE|_2H_MIGHTYWEAPON|_2H_POLEARM|_2H_STAFF|_2H_SWORD) |
                                                                                                                                (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_HELM|_ARMOR_MIGHTYBELT|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) |
                                                                                                                                (_OH) },
        { "Barbarian Skill Bonus: Bash",                    { "Increases Bash Damage by %u%%" },                                (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Barbarian Skill Bonus: Cleave",                  { "Increases Cleave Damage by %u%%" },                              (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Barbarian Skill Bonus: Frenzy",                  { "Increases Frenzy Damage by %u%%" },                              (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Barbarian Skill Bonus: Hammer of the Ancients",  { "Reduces resource cost of Hammer of the Ancients by %u Fury." },  (_2H_ALL|_2H_AXE|_2H_MACE|_2H_MIGHTYWEAPON|_2H_POLEARM|_2H_SWORD) | (_OH_ALL|_OH_SHIELD) },
        { "Barbarian Skill Bonus: Overpower",               { "Increases Critical Hit Chance of Overpower by %u%%" },           (_2H_ALL|_2H_AXE|_2H_MACE|_2H_MIGHTYWEAPON|_2H_POLEARM|_2H_SWORD) | (_OH_ALL|_OH_SHIELD) },
        { "Barbarian Skill Bonus: Rend",                    { "Reduces resource cost of Rend by %u Fury." },                    (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Barbarian Skill Bonus: Revenge",                 { "Increases Critical Hit Chance of Revenge by %u%%" },             (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Barbarian Skill Bonus: Seismic Slam",            { "Increases Critical Hit Chance of Seismic Slam by %u%%" },        (_2H_ALL|_2H_AXE|_2H_MACE|_2H_MIGHTYWEAPON|_2H_POLEARM|_2H_SWORD) | (_OH_ALL|_OH_SHIELD) },
        { "Barbarian Skill Bonus: Weapon Throw",            { "Reduces resource cost of Weapon Throw by %u Fury." },            (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_MIGHTYBELT) },
        { "Barbarian Skill Bonus: Whirlwind",               { "Increases Critical Hit Chance of Whirlwind by %u%%" },           (_2H_ALL|_2H_AXE|_2H_MACE|_2H_MIGHTYWEAPON|_2H_POLEARM|_2H_SWORD) | (_OH_ALL|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Bola Shot",            { "Increases Bola Shot Damage by %u%%" },                           (_OH_ALL|_OH_QUIVER|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Chakram",              { "Reduces resource cost of Chakram by %u Hatred." },               (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) },
        { "Demon Hunter Skill Bonus: Elemental Arrow",      { "Increases Elemental Arrow Damage by %u%%" },                     (_OH_ALL|_OH_QUIVER|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Entangling Shot",      { "Increases Entangling Shot Damage by %u%%" },                     (_OH_ALL|_OH_QUIVER|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Evasive Fire",         { "Increases Evasive Fire Damage by %u%%" },                        (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) },
        { "Demon Hunter Skill Bonus: Grenades",             { "Increases Grenades Damage by %u%%" },                            (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) },
        { "Demon Hunter Skill Bonus: Hungering Arrow",      { "Increases Hungering Arrow Damage by %u%%" },                     (_OH_ALL|_OH_QUIVER|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Impale",               { "Reduces resource cost of Impale by %u Hatred." },                (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) },
        { "Demon Hunter Skill Bonus: Multishot",            { "Increases Critical Hit Chance of Multishot by %u%%" },           (_OH_ALL|_OH_QUIVER|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Rapid Fire",           { "Increases Critical Hit Chance of Rapid Fire by %u%%" },          (_OH_ALL|_OH_QUIVER|_OH_SHIELD) },
        { "Demon Hunter Skill Bonus: Spike Trap",           { "Increases Spike Trap Damage by %u%%" },                          (_ARMOR_ALL|_ARMOR_CHESTARMOR|_ARMOR_CLOAK) },
        { "Demon Hunter Skill Bonus: Strafe",               { "Increases Critical Hit Chance of Strafe by %u%%" },              0 },
        { "Monk Skill Bonus: Crippling Wave",               { "Increases Crippling Wave Damage by %u%%" },                      (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Monk Skill Bonus: Cyclone Strike",               { "Reduces resource cost of Cyclone Strike by %u Spirit." },        (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Monk Skill Bonus: Deadly Reach",                 { "Increases Deadly Reach Damage by %u%%" },                        (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Monk Skill Bonus: Exploding Palm",               { "Increases Exploding Palm Damage by %u%%" },                      (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Monk Skill Bonus: Fists of Thunder",             { "Increases Fists of Thunder Damage by %u%%" },                    (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Monk Skill Bonus: Lashing Tail Kick",            { "Reduces resource cost of Lashing Tail Kick by %u Spirit." },     (_2H_ALL|_2H_DAIBO|_2H_POLEARM|_2H_STAFF) },
        { "Monk Skill Bonus: Sweeping Wind",                { "Increases Sweeping Wind Damage by %u%%" },                       (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Monk Skill Bonus: Tempest Rush",                 { "Increases Critical Hit Chance of Tempest Rush by %u%%" },        (_2H_ALL|_2H_DAIBO|_2H_POLEARM|_2H_STAFF) },
        { "Monk Skill Bonus: Wave of Light",                { "Increases Critical Hit Chance of Wave of Light by %u%%" },       (_2H_ALL|_2H_DAIBO|_2H_POLEARM|_2H_STAFF) },
        { "Monk Skill Bonus: Way of the Hundred Fists",     { "Increases Way of the Hundred Fists Damage by %u%%" },            (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_SPIRITSTONE) },
        { "Witch Doctor Skill Bonus: Acid Cloud",           { "Increases Critical Hit Chance of Acid Cloud by %u%%" },          (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_VOODOOMASK) },
        { "Witch Doctor Skill Bonus: Firebats",             { "Reduces resource cost of Firebats by %u Mana." },                (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_VOODOOMASK) },
        { "Witch Doctor Skill Bonus: Firebomb",             { "Reduces resource cost of Firebomb by %u Mana." },                (_1H_ALL|_1H_CEREMONIALKNIFE|_1H_DAGGER|_1H_SPEAR) | (_2H_ALL|_2H_BOW|_2H_CROSSBOW) },
        { "Witch Doctor Skill Bonus: Haunt",                { "Increases Haunt Damage by %u%%" },                               (_1H_ALL|_1H_CEREMONIALKNIFE|_1H_DAGGER|_1H_SPEAR) | (_2H_ALL|_2H_BOW|_2H_CROSSBOW) },
        { "Witch Doctor Skill Bonus: Locust Swarm",         { "Increases Locust Swarm Damage by %u%%" },                        (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_VOODOOMASK) },
        { "Witch Doctor Skill Bonus: Plague of Toads",      { "Increases Plague of Toads Damage by %u%%" },                     (_1H_ALL|_1H_CEREMONIALKNIFE|_1H_DAGGER|_1H_SPEAR) | (_2H_ALL|_2H_BOW|_2H_CROSSBOW) },
        { "Witch Doctor Skill Bonus: Poison Darts",         { "Increases Poison Dart Damage by %u%%" },                         (_2H_ALL|_2H_BOW|_2H_CROSSBOW) | (_OH_ALL|_OH_MOJO|_OH_SHIELD) },
        { "Witch Doctor Skill Bonus: Spirit Barrage",       { "Increases Spirit Barrage Damage by %u%%" },                      (_2H_ALL|_2H_BOW|_2H_CROSSBOW) | (_OH_ALL|_OH_MOJO|_OH_SHIELD) },
        { "Witch Doctor Skill Bonus: Summon Zombie Dogs",   { "Reduces cooldown of Summon Zombie Dogs by %u seconds." },        (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_VOODOOMASK) },
        { "Witch Doctor Skill Bonus: Wall of Zombies",      { "Reduces cooldown of Wall of Zombies by %u seconds." },           (_2H_ALL|_2H_BOW|_2H_CROSSBOW) | (_OH_ALL|_OH_MOJO|_OH_SHIELD) },
        { "Witch Doctor Skill Bonus: Zombie Charger",       { "Reduces resource cost of Zombie Charger by %u Spirit." },        (_2H_ALL|_2H_BOW|_2H_CROSSBOW) | (_OH_ALL|_OH_MOJO|_OH_SHIELD) },
        { "Wizard Skill Bonus: Arcane Orb",                 { "Increases Critical Hit Chance of Arcane Orb by %u%%" },          (_OH_ALL|_OH_SOURCE|_OH_SHIELD) },
        { "Wizard Skill Bonus: Arcane Torrent",             { "Reduces resource cost of Arcane Torrent by %u Arcane Power." },  (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) },
        { "Wizard Skill Bonus: Blizzard",                   { "Increases Duration of Blizzard by %u Seconds" },                 (_OH_ALL|_OH_SOURCE|_OH_SHIELD) },
        { "Wizard Skill Bonus: Disintegrate",               { "Reduces resource cost of Disintegrate by %u Arcane Power." },    (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) },
        { "Wizard Skill Bonus: Electrocute",                { "Increases Electrocute Damage by %u%%" },                         (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) },
        { "Wizard Skill Bonus: Energy Twister",             { "Increases Critical Hit Chance of Energy Twister by %u%%" },      (_1H_ALL|_1H_DAGGER|_1H_SPEAR|_1H_SWORD|_1H_WAND) | (_2H_ALL|_2H_STAFF) },
        { "Wizard Skill Bonus: Explosive Blast",            { "Increases Critical Hit Chance of Explosive Blast by %u%%" },     (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) },
        { "Wizard Skill Bonus: Hydra",                      { "Reduces resource cost of Hydra by %u Arcane Power." },           (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) },
        { "Wizard Skill Bonus: Magic Missile",              { "Increases Magic Missile Damage by %u%%" },                       (_1H_ALL|_1H_DAGGER|_1H_SPEAR|_1H_SWORD|_1H_WAND) | (_2H_ALL|_2H_STAFF) },
        { "Wizard Skill Bonus: Meteor",                     { "Reduces resource cost of Meteor by %u Arcane Power." },          (_OH_ALL|_OH_SOURCE|_OH_SHIELD) },
        { "Wizard Skill Bonus: Ray of Frost",               { "Increases Critical Hit Chance of Ray of Frost by %u%%" },        (_ARMOR_ALL|_ARMOR_HELM|_ARMOR_WIZARDHAT) },
        { "Wizard Skill Bonus: Shock Pulse",                { "Increases Shock Pulse Damage by %u%%" },                         (_OH_ALL|_OH_SOURCE|_OH_SHIELD) },
        { "Wizard Skill Bonus: Spectral Blade",             { "Increases Spectral Blade Damage by %u%%" },                      (_OH_ALL|_OH_SOURCE|_OH_SHIELD) },

        // properties
        { "Properties",                         { 0 },                                                      (_1H) | (_2H) | (_ARMOR) | (_OH) },
        { "Gold Find",                          { "+%u%% Extra Gold from Monsters" },                       (_ARMOR) | (_OH) },
        { "Has Sockets",                        { 0 },                                                      (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_AMULET|_ARMOR_BELT|_ARMOR_BRACERS|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_HELM|_ARMOR_PANTS|_ARMOR_MIGHTYBELT|_ARMOR_RING|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH) },
        { "Indestructible",                     { "Ignores Durability Loss" },                              (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_BOOTS|_ARMOR_BRACERS|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_GLOVES|_ARMOR_HELM|_ARMOR_PANTS|_ARMOR_MIGHTYBELT|_ARMOR_SHOULDERS|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) | (_OH) },
        { "Magic Find",                         { "%u%% Better Chance of Finding Magical Items" },          (_ARMOR) | (_OH) },
        { "Movement Speed",                     { "+%u%% Movement Speed" },                                 (_ARMOR_ALL|_ARMOR_BOOTS) },
        { "Pickup Radius",                      { "Increases Gold and Health Pickup by %u Yards." },        (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_BOOTS|_ARMOR_BRACERS|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_GLOVES|_ARMOR_HELM|_ARMOR_PANTS|_ARMOR_MIGHTYBELT|_ARMOR_SHOULDERS|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) },
        { "Reduced Level Requirement",          { "Level Requirement Reduced by %u" },                      (_1H) | (_2H) | (_ARMOR_ALL|_ARMOR_BELT|_ARMOR_BOOTS|_ARMOR_BRACERS|_ARMOR_CHESTARMOR|_ARMOR_CLOAK|_ARMOR_GLOVES|_ARMOR_HELM|_ARMOR_PANTS|_ARMOR_MIGHTYBELT|_ARMOR_SHOULDERS|_ARMOR_SPIRITSTONE|_ARMOR_VOODOOMASK|_ARMOR_WIZARDHAT) },

        // other
        { "Bonus Damage",                       { "+%u-%u Damage" } },
        { "Bonus Maximum Weapon Damage",        { "+%u Maximum Damage" } },
        { "Arcane Damage %",                    { "Adds %u%% to Arcane Damage" } },
        { "Cold Damage %",                      { "Adds %u%% to Cold Damage" } },
        { "Fire Damage %",                      { "Adds %u%% to Fire Damage" } },
        { "Lightning Damage %",                 { "Adds %u%% to Lightning Damage" } },
        { "Poison Damage %",                    { "Adds %u%% to Poison Damage" } },
        { "Weapon Damage %",                    { "Adds %u%% to Weapon Damage" } },

        // gem
        { "Empty Socket" },
        { "Bonus Experience",                   { "Increases Bonus Experience by %u%%" } },
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
    extern ULong        GAME_ITEMREAD_DELAY = 50; // ms

    extern ULong        GAME_NEXTPAGE_DELAY = 50; // ms

    const Char*         GAME_WINDOW_TITLE = "Diablo III";
    const Char*         GAME_WINDOW_CLASS = "D3 Main Window Class";

    const ULongArray    ITEM_GEM_LIFEONHIT(_item_gem_lifeonhit, ACOUNT(_item_gem_lifeonhit));
    const ULongArray    ITEM_GEM_CRITICALHITDAMAGE(_item_gem_criticalhitdamage, ACOUNT(_item_gem_criticalhitdamage));
    const ULongArray    ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE(_item_gem_bonusminimumweapondamage, ACOUNT(_item_gem_bonusminimumweapondamage));
    const ULongArray    ITEM_GEM_PHYSICALDAMAGETOATTACKER(_item_gem_physicaldamagetoattacker, ACOUNT(_item_gem_physicaldamagetoattacker));
    const Char*         ITEM_GEM_TYPE_STRINGS[] =
    {
        "Amethyst",
        "Emerald",
        "Ruby",
        "Topaz",
    };


    const Coordinate AH_INPUT_LEVEL_MIN =   { -0.5025, 0.471875, };
    const Coordinate AH_INPUT_LEVEL_MAX =   { -0.434375, 0.471875 };
    const Coordinate AH_INPUT_PSTAT_VALUE[AH_INPUT_PSTAT_LIMIT] =
    {
        { -0.315625, 0.553125 },
        { -0.315625, 0.588125 },
        { -0.315625, 0.62375 }
    };
    const Coordinate AH_INPUT_UNIQUE =      { -0.44875, 0.70375 };
    const Coordinate AH_INPUT_BID =         { 0.114375, 0.43125 };
    const Coordinate AH_INPUT_BUYOUT =      { -0.32875, 0.70375 };

    const ComboBox AH_COMBO_CHARACTER       ( _options_character,   ACOUNT(_options_character) );
    const ComboBox AH_COMBO_PRIMARY         ( _options_primary,     ACOUNT(_options_primary) );
    const ComboBox AH_COMBO_SECONDARY       ( _options_secondary,   ACOUNT(_options_secondary) );
    const ComboBox AH_COMBO_RARITY          ( _options_rarity,      ACOUNT(_options_rarity) );
    const ComboBox AH_COMBO_PSTAT           ( _options_pstats,      ACOUNT(_options_pstats) );

    const Coordinate AH_COMBO_COORDS[] = // indexed by AuctionTrainer::COMBO_*
    {
        { -0.354375, 0.4725 },

        { -0.419375, 0.28375 },
        { -0.419375, 0.35625 },
        { -0.419375, 0.395625 },

        { -0.4375, 0.55375 },
        { -0.4375, 0.58875 },
        { -0.4375, 0.62375 }
    };

    const Coordinate AH_BUTTON_SEARCH =             { -0.4075,  0.77625 };
    const Coordinate AH_BUTTON_BID =                { 0.229375, 0.813125 };
    const Coordinate AH_BUTTON_BUYOUT =             { 0.4475,   0.813125 };
    const Coordinate AH_BUTTON_BUYOUT_CONFIRM =     { -0.10375, 0.66625 };
    const Coordinate AH_BUTTON_BUYOUT_CONFIRM_OK =  { 0,        0.4275 };

    const Coordinate AH_LIST_BEGIN =                { -0.24125, 0.27625 };
    const Coordinate AH_LIST_ICON =                 { 0.04125,  0.04181875 };
    const Coordinate AH_LIST_NEXT_BUTTON =          { 0.243125, 0.7575 };

    const Coordinate AH_LIST_SORT_DPSARMOR =        { 0.234375, 0.25625 };
    const Coordinate AH_LIST_SORT_BUYOUT =          { 0.42625,  0.25625 };
}
