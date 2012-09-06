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
        Number              dpsarmor;
        Number              current_bid;
        Number              max_bid;
        Number              buyout;
        ULong               rtime;
        ULong               xtime;
        TextString          rarity;
        TextString          type;

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
            dpsarmor = 0;
            current_bid = 0;
            max_bid = 0;
            buyout = 0;
            rtime = 0;
            xtime = 0;
            *rarity = 0;
            *type = 0;
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
