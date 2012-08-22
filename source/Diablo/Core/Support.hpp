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
        static Bool GetGemInfo( GemTypeId& type, GemRankId& rank, const Item::Stat& stat )
        {
            if(stat.values.GetCount() > 0)
            {
                ULong   value = static_cast<ULong>(NUMBER_WHOLE(stat.values[0]));
                Index   rank_index;

                // get type from stat id
                switch(stat.id)
                {
                // amethyst
                case ITEM_STAT_VITALITY:
                case ITEM_STAT_LIFEP:
                case ITEM_STAT_LIFEONHIT:
                    type = GEM_TYPE_AMETHYST;
                    break;

                // emerald
                case ITEM_STAT_DEXTERITY:
                case ITEM_STAT_GOLDFIND:
                case ITEM_STAT_CRITICALHITDAMAGE:
                    type = GEM_TYPE_EMERALD;
                    break;

                // ruby
                case ITEM_STAT_STRENGTH:
                case ITEM_STAT_BONUSEXPERIENCE:
                case ITEM_STAT_AVERAGEDAMAGE:
                    type = GEM_TYPE_RUBY;
                    break;

                // topaz
                case ITEM_STAT_INTELLIGENCE:
                case ITEM_STAT_MAGICFIND:
                case ITEM_STAT_PHYSICALDAMAGETOATTACKER:
                    type = GEM_TYPE_TOPAZ;
                    break;

                default:
                    return false;
                }

                // get rank from stat value
                switch(stat.id)
                {
                case ITEM_STAT_VITALITY:
                case ITEM_STAT_DEXTERITY:
                case ITEM_STAT_STRENGTH:
                case ITEM_STAT_INTELLIGENCE:
                    rank_index = ((value - 6) / 4 + 1);
                    break;
                
                case ITEM_STAT_GOLDFIND:
                case ITEM_STAT_MAGICFIND:
                case ITEM_STAT_BONUSEXPERIENCE:
                    rank_index = ((value - 5) / 2 + 1);
                    break;

                case ITEM_STAT_LIFEP:
                    rank_index = (value - 4);
                    break;

                case ITEM_STAT_LIFEONHIT:
                    rank_index = ITEM_GEM_LIFEONHIT.IndexOf(ITEM_GEM_LIFEONHIT.FlatSearch(value)) + 1;
                    break;

                case ITEM_STAT_CRITICALHITDAMAGE:
                    rank_index = ITEM_GEM_CRITICALHITDAMAGE.IndexOf(ITEM_GEM_CRITICALHITDAMAGE.FlatSearch(value)) + 1;
                    break;

                case ITEM_STAT_AVERAGEDAMAGE:
                    rank_index = ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE.IndexOf(ITEM_GEM_BONUSMINIMUMWEAPONDAMAGE.FlatSearch(value)) + 1;
                    break;

                case ITEM_STAT_PHYSICALDAMAGETOATTACKER:
                    rank_index = ITEM_GEM_PHYSICALDAMAGETOATTACKER.IndexOf(ITEM_GEM_PHYSICALDAMAGETOATTACKER.FlatSearch(value)) + 1;
                    break;
                }

                if(rank_index >= GEM_RANK_LIMIT)
                    return false;
                rank = static_cast<GemRankId>(rank_index);
            }
            else
            {
                type = GEM_TYPE_EMPTY;
                rank = GEM_RANK_NONE;
            }

            return true;
        }

        /**/
        static Bool ParseItemStatString( Item::Stat& stat, const Char* string )
        {
            const ComboBox::OptionCollection& options = AH_COMBO_PSTAT.GetOptions();
            Item::ValueCollection& values = stat.values;

            values.SetCount(values.GetLimit());

            for( Index i = 0; i < options.GetCount(); i++ )
            {
                const ComboOption& option = options[i];

                if( option.format )
                {
                    ULong count;
                    
                    for( Index j = 0; option.format[j] && j < ACOUNT(option.format); j++ )
                    {
                        if(Tools::StrFormatRead(count, string, option.format[j], &values[0], &values[1], &values[2], &values[3]))
                        {
                            if(count == 0 || (values[0] >= ITEM_STAT_VALUE_MIN && values[0] <= ITEM_STAT_VALUE_MAX))
                            {
                                values.SetCount(count);
                                stat.id = static_cast<ItemStatId>(i);
                                return true;
                            }
                        }
                    }
                }
            }

            values.SetCount(0);
            return false;
        }
    };
}
