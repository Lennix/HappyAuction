#pragma once
#include <Core/Type/Array.hpp>
#include <Core/Tools.hpp>
#include <stdio.h>

namespace Core
{
    /**/
    class Settings
    {
    public:
        struct Item
        {
            const Char* key;
            TextString  value;
            Index       custom1;
            Index       custom2;
        };

        typedef Array<Item>                 ItemCollection;
        typedef ItemCollection::Iterator    ItemIterator;

    private:
        ItemCollection  _items;
        Bool            _ready;
        ULong           _accessed;

    public:
        /**/
        Settings( ItemCollection& items ):
            _items(items),
            _ready(false),
            _accessed(0)
        {
        }

        /**/
        Bool Load( const Char* path, Bool readonly=false )
        {
            Bool status = _ReadFile(path);
            if(readonly)
                return status;
            else
                return _WriteFile(path);
        }

        /**/
        const ItemCollection& GetItems() const
        {
            return _items;
        }

        /**/
        const Char* operator[]( Index index ) const
        {
            if( index < _items.GetCount() )
                return _items[index].value;
            else
                return "";
        }

        /**/
        Index GetIndex( const Char* key )
        {
            for( Index i = 0; i < _items.GetCount(); ++i )
                if(strcmp(key, _items[i].key) == 0)
                    return i;

            return INVALID_INDEX;
        }

    private:
        /**/
        void _Set( Index index, const char* value )
        {
            strcpy(_items[index].value, value);
        }

        /**/
        Bool _ReadFile( const Char* path )
        {
            Bool        status = true;
            TextString  line;

            FILE* file = fopen(path,"rt");
            if(file == NULL)
                return false;

            while(fgets(line, sizeof(line), file))
            {
                Char* equal = strchr(line, '=');
                if(equal)
                {
                    Char* nl = strchr(line, '\n');
                    if(nl)
                        *nl = 0;
                    *equal = 0;

                    Index index = GetIndex(line);
                    if(index != INVALID_INDEX)
                        _Set(index, equal+1);
                    else
                        status = false;
                }
            }

            fclose(file);
            return status;
        }

        /**/
        Bool _WriteFile( const Char* path )
        {
            FILE* file = fopen(path,"wt");
            if(file == NULL)
                return false;

            for( ItemIterator i = _items.Begin(); i != _items.End(); ++i )
                fprintf(file, "%s=%s\n", i->key, i->value);

            fclose(file);
            return true;
        }
    };
}
