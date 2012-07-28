#pragma once
#include <windows.h>
#include <assert.h>

namespace Core
{
    /**/
    #define ACOUNT(a)  (sizeof(a)/(sizeof(a[0])))
    #define BIT(n)      (1 << (n))
    #define B64(n)      (1i64 << (n))
}
