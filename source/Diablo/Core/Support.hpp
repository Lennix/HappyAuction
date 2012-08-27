#pragma once
#include <Core/System/System.hpp>
#include <Diablo/Root.hpp>
#include <Diablo/Constants.hpp>
#include <Diablo/Types.hpp>
#include <Diablo/Type/Item.hpp>

namespace Diablo
{
    /**/
    class Support
    {
    public:
        /**/
        static Bool GetGemInfo( GemTypeId& type, ULong& rank, const Item::Stat& stat )
        {
            type = GEM_TYPE_EMPTY;
            rank = 0;

            if(stat.values.GetCount() > 0)
            {
                ULong       value = static_cast<ULong>(NUMBER_WHOLE(stat.values[0]));
                GemStatId   stat_id;

                // parse gem stat
                if(!ITEM_GEM_STAT_IDS.FindObject(reinterpret_cast<Id&>(stat_id), stat.text, true))
                    return false;

                // get type from stat id
                switch(stat_id)
                {
                // amethyst
                case GEM_STAT_VITALITY:
                case GEM_STAT_LIFEP:
                case GEM_STAT_LIFEONHIT:
                    type = GEM_TYPE_AMETHYST;
                    break;

                // emerald
                case GEM_STAT_DEXTERITY:
                case GEM_STAT_GOLDFIND:
                case GEM_STAT_CRITICALHITDAMAGE:
                    type = GEM_TYPE_EMERALD;
                    break;

                // ruby
                case GEM_STAT_STRENGTH:
                case GEM_STAT_BONUSEXPERIENCE:
                case GEM_STAT_AVERAGEDAMAGE:
                    type = GEM_TYPE_RUBY;
                    break;

                // topaz
                case GEM_STAT_INTELLIGENCE:
                case GEM_STAT_MAGICFIND:
                case GEM_STAT_PHYSICALDAMAGETOATTACKER:
                    type = GEM_TYPE_TOPAZ;
                    break;

                default:
                    return false;
                }

                // get rank from stat value
                switch(stat_id)
                {
                case GEM_STAT_VITALITY:
                case GEM_STAT_DEXTERITY:
                case GEM_STAT_STRENGTH:
                case GEM_STAT_INTELLIGENCE:
                    rank = ((value - 6) / 4 + 1);
                    break;
                
                case GEM_STAT_GOLDFIND:
                case GEM_STAT_MAGICFIND:
                case GEM_STAT_BONUSEXPERIENCE:
                    rank = ((value - 5) / 2 + 1);
                    break;

                case GEM_STAT_LIFEP:
                    rank = (value - 4);
                    break;

                case GEM_STAT_LIFEONHIT:
                    rank = ITEM_GEM_LIFEONHIT.IndexOf(ITEM_GEM_LIFEONHIT.FlatSearch(value)) + 1;
                    break;

                case GEM_STAT_CRITICALHITDAMAGE:
                    rank = ITEM_GEM_CRITICALHITDAMAGE.IndexOf(ITEM_GEM_CRITICALHITDAMAGE.FlatSearch(value)) + 1;
                    break;

                case GEM_STAT_AVERAGEDAMAGE:
                    rank = ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE.IndexOf(ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE.FlatSearch(value)) + 1;
                    break;

                case GEM_STAT_PHYSICALDAMAGETOATTACKER:
                    rank = ITEM_GEM_PHYSICALDAMAGETOATTACKER.IndexOf(ITEM_GEM_PHYSICALDAMAGETOATTACKER.FlatSearch(value)) + 1;
                    break;
                }
            }

            return true;
        }
    };
}
