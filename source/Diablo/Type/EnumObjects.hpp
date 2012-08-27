#pragma once
#include <Core/Type/Enum.hpp>
#include <Diablo/Root.hpp>

namespace Diablo
{
    /**/
    struct ComboSecondaryDependency
    {
        Id      primary;
        Bits    character;
    };

    /**/
    typedef Enum<ComboSecondaryDependency>  ComboSecDepEnum;
}
