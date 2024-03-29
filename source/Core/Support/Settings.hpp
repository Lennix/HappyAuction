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
        };

        typedef Array<Item>                 ItemCollection;
        typedef ItemCollection::Iterator    ItemIterator;

    private:
        const Char*     _path;
        ItemCollection  _items;
        Bool            _ready;
        ULong           _accessed;

    public:
        /**/
        Settings( const Char* path, ItemCollection& items ):
            _path(path),
            _items(items),
            _ready(false),
            _accessed(0)
        {
            _ReadFile();
            _WriteFile();
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
        Bool _ReadFile()
        {
            Bool        status = true;
            TextString  line;

            FILE* file = fopen(_path,"rt");
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
        Bool _WriteFile()
        {
            FILE* file = fopen(_path,"wt");
            if(file == NULL)
                return false;

            for( ItemIterator i = _items.Begin(); i != _items.End(); ++i )
                fprintf(file, "%s=%s\n", i->key, i->value);

            fclose(file);
            return true;
        }
    };
}
