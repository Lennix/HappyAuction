#pragma once
#include <Core/Type/Array.hpp>
#include <Diablo/Enums.hpp>
#include <Diablo/Constants.hpp>

namespace Diablo
{
    /**/
    class Item
    {
    public:
        typedef FixedArray<Number, ITEM_STAT_VALUE_LIMIT> ValueCollection;

        /**/
        struct Stat
        {
            TextString      text;
            ValueCollection values;

            Stat()
            {
                *text = 0;
            }

            static const Stat& GetDefault()
            {
                static const Stat s;
                return s;
            }
        };

        typedef FixedArray<Item::Stat, ITEM_STAT_LIMIT>     StatCollection;
        typedef StatCollection::Iterator                    StatIterator;
        typedef FixedArray<Item::Stat, ITEM_SOCKET_LIMIT>   SocketCollection;

    public:
        TextString          name;
        ULong               id;
        Number              ilevel;

        TextString          rarity;
        TextString          type;

        Number              dpsarmor;
        Number              block_chance;
        Number              block_min;
        Number              block_max;
        Number              damage_aps;
        Number              damage_min;
        Number              damage_max;

        Number              bid_current;
        Number              bid_max;
        Number              buyout;

        ULong               time_remaining;
        ULong               time_expiring;

        StatCollection      stats;
        SocketCollection    sockets;

    public:
        /**/
        Item()
        {
            Empty();
        }

        /**/
        void Empty()
        {
            *name = 0;
            id = 0;
            ilevel = 0;

            *rarity = 0;
            *type = 0;

            dpsarmor = 0;
            block_chance = 0;
            block_min = 0;
            block_max = 0;
            damage_aps = 0;
            damage_min = 0;
            damage_max = 0;

            bid_current = 0;
            bid_max = 0;
            buyout = 0;

            time_remaining = 0;
            time_expiring = 0;

            stats.Empty();
            sockets.Empty();
        }

        /**/
        Bool IsValid()
        {
            return *type != 0;
        }

        /**/
        const Stat* FindStat( const Char* pattern, Bool substring ) const
        {
            ULong       pattern_length = strlen(pattern);
            ULong       best_score = ~0;
            const Stat* best_stat = NULL;

            // search stats for object with matching pattern
            for( Index i = 0; best_score && i < stats.GetCount(); i++ )
            {
                const Stat& stat = stats[i];

                // substring search
                if(Tools::StrSearch(pattern, stat.text, !substring))
                {
                    ULong score = strlen(stat.text) - pattern_length;

                    // elect best match
                    if(score < best_score)
                    {
                        best_score = score;
                        best_stat = &stat;
                    }
                }
            }

            return best_stat;
        }
    };
}
