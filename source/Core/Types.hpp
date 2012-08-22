#pragma once
#include <Core/Root.hpp>

namespace Core
{
    /**/
    typedef bool                Bool;
    typedef char                Char;
    typedef unsigned char       Byte;
    typedef short               Short;
    typedef unsigned short      UShort;
    typedef int                 Long;
    typedef unsigned int        ULong;
    typedef long long           Huge;
    typedef unsigned long long  UHuge;
    typedef float               Float;
    typedef double              Double;
    typedef long                Int;
    typedef unsigned long       UInt;

    typedef ULong               Bits;
    typedef Long                Id;
    typedef ULong               Index;
    typedef void*               Resource;
    typedef Huge                Number;

    /**/
    static const Id     INVALID_ID =    0x7fffffff;
    static const Index  INVALID_INDEX = INVALID_ID;

    /**/
    typedef Char TextString[512];

    /**/
    #define NUMBER_ACCURACY     1000
    #define NUMBER(w,d)         (((Number)w * NUMBER_ACCURACY) + (d))
    #define NUMBER_WHOLE(w)     ((w) / NUMBER_ACCURACY)
    #define NUMBER_DECIMAL(d)   static_cast<ULong>((d) % NUMBER_ACCURACY)
    #define NUMBER_BOTTOM(n)    (NUMBER_WHOLE(w) * NUMBER_ACCURACY)
    #define NUMBER_TODOUBLE(n)  (static_cast<Double>(n) / static_cast<Double>(NUMBER_ACCURACY))
}
