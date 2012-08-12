#pragma once
#include <Core/Array.hpp>
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
        ULong               dpsarmor;
        ULong               max_bid;
        ULong               buyout;
        ULong               id;
        ULong               current_bid;
        ULong               flags;
        ULong               ilevel;

        TextString          timeleft;
        TextString          name;
        TextString          type;

        StatCollection      stats;
        SocketCollection    sockets;

    public:
        /**/
        Item():
            dpsarmor(0),
            max_bid(0),
            buyout(0),
            id(0),
            current_bid(0),
            flags(0)
        {
        }

        /**/
        void Empty()
        {
            dpsarmor = 0;
            current_bid = 0;
            max_bid = 0;
            buyout = 0;
            stats.Empty();
            sockets.Empty();
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
