#pragma once
#include <Core/Type/Array.hpp>
#include <Core/Constants.hpp>
#include <Core/Types.hpp>
#include <stdio.h>

namespace Core
{
    /**/
    class Tools
    {
    public:
        /**/
        template<typename TYPE>
        static void Swap( TYPE& a, TYPE& b )
        {
            TYPE temp = a;
            a = b;
            b = temp;
        }

        /**/
        template<typename TYPE>
        static inline Index FirstBitIndex( TYPE value )
        {
            Index index;
            for( index = 0; value >>= 1; index++ );
            return index;
        }

        /**/
        static inline Char UpperCase( Char c )
        {
            return c > 'Z' ? c - ('a'-'A') : c;
        }

        /**/
        static const Char* StrSearch( const Char* needle, const Char* haystack )
        {
            for(; *haystack; haystack++ )
            {
                const Char* h = haystack;
                const Char* n = needle;

                for( ; *n && UpperCase(*n) == UpperCase(*h); n++, h++ );

                if(*n == 0)
                    return haystack;
            }

            return NULL;
        }

        /**/
        static ULong StrLenPrint( const Char* string )
        {
            const Char* current = string;
            for( ; *current >= 0x20 && *current <= 0x7e; current++ );
            return current - string;
        }

        /**/
        static ULong StrToULong( const Char*& string )
        {
            ULong integer = 0;
            ULong decimal = 0;
            ULong* value = &integer;

            for(; *string; string++ )
            {
                Char c = *string;
                if(c == '.')
                {
                    value = &decimal;
                    continue;
                }
                if(c == ',')
                    continue;
                else if(c >= '0' && c <= '9')
                    *value = (c - '0') + (*value * 10);
                else
                    break;
            }

            return integer;
        }

        /**/
        static void StrReadTo( Char* out, const Char*& in, Char terminator )
        {
            Index i;
            for( i = 0; i < (sizeof(TextString)-1) && *in && *in != terminator; i++, in++)
                out[i] = *in;
            out[i] = 0;
        }

        /**/
        static Bool StrFormatRead( ULong& count, const Char* string, const Char* format, ... )
        {
            va_list args;
            assert(format != NULL);
            count = 0;

            // build text from format
            va_start(args, format);
            while(*string && *format)
            {
                if(*format == '%' && *(++format) != '%')
                {
                    switch(*(format++))
                    {
                    case 'u':
                        *((ULong*)va_arg(args, ULong*)) = StrToULong(string);
                        count++;
                        break;
                    case 's':
                        StrReadTo((Char*)va_arg(args, Char*), string, *format);
                        count++;
                        break;
                    }
                }
                else if(*(string++) != *(format++))
                    return false;
            }
            va_end(args);

            return *format == 0;
        }

        /**/
        static void StrNCpy( Char* to, const Char* from, ULong limit )
        {
            Index end = Min(strlen(from), limit - 1);
            MemCopy(to, from, end);
            to[end] = 0;
        }

        /**/
        template<typename TYPE>
        static TYPE Min( TYPE a, TYPE b )
        {
            return a > b ? b : a;
        }
        template<typename TYPE>
        static TYPE Max( TYPE a, TYPE b )
        {
            return a > b ? a : b;
        }

        /**/
        template<typename TYPE>
        static TYPE Conform( const TYPE value, const TYPE min, const TYPE max )
        {
            if( value < min )
                return min;
            else if( value > max )
                return max;
            return value;
        }

        /**/
        static const Byte* MemMem( const Byte* begin, const Byte* end, Byte search )
        {
            for(; begin != end; begin++ )
                if(*begin == search)
                    return begin;

            return NULL;
        }

        /**/
        template<typename TYPE>
        static void MemCopy( TYPE* to, const TYPE* from, ULong count=1 )
        {
            memcpy(to, from, count * sizeof(TYPE));
        }

        /**/
        template<typename TYPE>
        static void MemZero( TYPE* memory, ULong count=1 )
        {
            memset(memory, 0, sizeof(TYPE) * count);
        }

        /**/
        static void Log( LogId id, const Char* format, ... )
        {
            static FILE* handle[LOG_COUNT] = { 0 };
            FILE*& file = handle[id];

            if(format == NULL)
            {
                if(file != NULL)
                {
                    fclose(file);
                    file = NULL;
                }
            }
            else
            {
                if(file == NULL)
                    file = fopen(TOOLS_LOG_PATH[id], "wt");

                if(file)
                {
                    va_list args;
                    va_start(args, format);
                    vfprintf(file, format, args);
                    va_end(args);

                    fflush(file);
                }
            }
        }

        /**/
        template<unsigned LIMIT>
        static ULong UniqueRandom( ULong max = LIMIT )
        {
            static FixedArray<ULong, LIMIT> table;
            ULong value;

            do
            {
                // if empty refill random table
                if(table.GetCount() == 0)
                    for( Index i = 0; i < LIMIT; i++ )
                        table.Push(i);

                // select random value
                Index index = rand() % table.GetCount();
                value = table[index];

                // pop swap value
                ULong popped = table.Pop();
                if(index < table.GetCount())
                    table[index] = popped;
            }
            while(value >= max);

            return value;
        }
    };
}
