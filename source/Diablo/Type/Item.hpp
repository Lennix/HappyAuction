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
        typedef FixedArray<ULong, ITEM_STAT_VALUE_LIMIT>    ValueCollection;

        /**/
        struct Stat
        {
            ItemStatId      id;
            ValueCollection values;

            Stat():
                id(ITEM_STAT_NONE)
            {
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
        ULong               dpsarmor;
        ULong               current_bid;
        ULong               max_bid;
        ULong               buyout;
        ULong               rtime;
        ULong               xtime;
        Id                  rarity;
        Id                  type;

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
            name[0] = 0;
            id = 0;
            dpsarmor = 0;
            current_bid = 0;
            max_bid = 0;
            buyout = 0;
            rtime = 0;
            xtime = 0;
            rarity = INVALID_ID;
            type = INVALID_ID;
            stats.Empty();
            sockets.Empty();
        }

        /**/
        Bool IsValid()
        {
            return type != INVALID_ID;
        }

        /**/
        const Stat* FindStat( const Char* pattern ) const
        {
            const ComboBox::OptionCollection& options = AH_COMBO_PSTAT.GetOptions();

            if(pattern != NULL)
                for( StatIterator i = stats.Begin(); i != stats.End(); ++i )
                    if(options[i->id].Match(pattern))
                        return i;

            return NULL;
        }
    };
}
