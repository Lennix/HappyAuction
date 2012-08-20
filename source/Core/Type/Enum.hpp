#pragma once
#include <Core/Types.hpp>
#include <Core/Type/Array.hpp>

namespace Core
{
    /**/
    class EnumItem
    {
    public:
        Id          _id;
        const Char* _string;

    public:
        /**/
        EnumItem( Id id, const Char* string ):
            _id(id),
            _string(string)
        {
        }

        /**/
        Id GetId() const
        {
            return _id;
        }

        /**/
        const Char* GetString() const
        {
            return _string;
        }
    };

    /**/
    class Enum
    {
    public:
        typedef Array<const EnumItem>       ItemCollection;
        typedef ItemCollection::Iterator    ItemIterator;

    private:
        ItemCollection _items;

    public:
        /**/
        Enum( const EnumItem* items, UShort count ):
            _items(items, count)
        {
        }

        /**/
        const Char* operator[]( Index index ) const
        {
            if(index < _items.GetCount())
                return _items[index].GetString();
            else
                return "";
        }

        /**/
        const Char* GetString( Id id ) const
        {
            for(ItemIterator i = _items.Begin(); i != _items.End(); i++)
                if(i->GetId() == id)
                    return i->GetString();

            return NULL;
        }

        /**/
        Id GetId( const Char* string ) const
        {
            const EnumItem* found = NULL;

            for(ItemIterator i = _items.Begin(); i != _items.End(); i++)
                if(strcmp(string, i->GetString()) == 0)
                    return i->GetId();

            return INVALID_ID;
        }
    };
}
