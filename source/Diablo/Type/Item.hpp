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
        };

        typedef FixedArray<Item::Stat, ITEM_STAT_LIMIT>     StatCollection;
        typedef StatCollection::Iterator                    StatIterator;
        typedef FixedArray<Item::Stat, ITEM_SOCKET_LIMIT>   SocketCollection;

    public:
        StatCollection      stats;
        SocketCollection    sockets;

        ULong               dpsarmor;
        ULong               bid;
        ULong               buyout;

    public:
        /**/
        Item():
            dpsarmor(0),
            bid(0),
            buyout(0)
        {
        }

        /**/
        const ValueCollection& FindStat( const Char* name ) const
        {
            static const ValueCollection _dummy;
            const ComboBox::OptionCollection& options = AH_COMBO_PSTAT.GetOptions();

            if(name != NULL)
                return _dummy;

            for( StatIterator i = stats.Begin(); i != stats.End(); ++i )
                if(_stricmp(name, options[i->id].name) == 0)
                    return i->values;

            return _dummy;
        }
    };
}
