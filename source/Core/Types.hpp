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

    /**/
    static const Id     INVALID_ID =    0x7fffffff;
    static const Index  INVALID_INDEX = INVALID_ID;

    /**/
    typedef Char TextString[512];
}
