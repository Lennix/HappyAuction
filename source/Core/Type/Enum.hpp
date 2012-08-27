#pragma once
#include <Core/Tools.hpp>
#include <Core/Types.hpp>
#include <Core/Type/Array.hpp>

namespace Core
{
    /**/
    template<typename TYPE>
    struct EnumItem
    {
        const Char* name;
        TYPE        object;
    };

    /**/
    template<typename TYPE>
    class Enum
    {
    public:
        typedef EnumItem<TYPE>                      Item;
        typedef Array<const Item>                   ItemCollection;
        typedef typename ItemCollection::Iterator   ItemIterator;

    private:
        ItemCollection _items;

    public:
        /**/
        Enum( const Item* items, UShort count ):
            _items(items, count)
        {
        }

        /**/
        Bool FindName( TextString name, const TYPE& object ) const
        {
            for(ItemIterator i = _items.Begin(); i != _items.End(); i++)
            {
                if( object == i->object )
                {
                    Tools::StrNCpy(name, i->name, sizeof(TextString));
                    return true;
                }
            }

            return false;
        }

        /**/
        Bool FindObject( TYPE& object, const Char* pattern, Bool invert=false ) const
        {
            ULong   pattern_length = strlen(pattern);
            ULong   best_score = ~0;
            Index   best_index = INVALID_INDEX;

            // search items for object with matching pattern
            for( Index i = 0; best_score && i < _items.GetCount(); i++ )
            {
                const Item& item = _items[i];

                // substring search
                if(invert ? Tools::StrSearch(item.name, pattern) : Tools::StrSearch(pattern, item.name))
                {
                    ULong   name_length = strlen(item.name);
                    ULong   score = invert ? (pattern_length - name_length) : (name_length - pattern_length);

                    // elect best match
                    if(score < best_score)
                    {
                        best_score = score;
                        best_index = i;
                    }
                }
            }

            if(best_index == INVALID_INDEX)
                return false;
            object = _items[best_index].object;

            return true;
        }
    };

    /* common enum types */
    typedef Enum<Id>    IdEnum;
    typedef Enum<Bits>  BitsEnum;
}
