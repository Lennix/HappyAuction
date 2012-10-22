#pragma once
#include <Core/Types.hpp>
#include <Core/Enums.hpp>
#include <Core/Type/Enum.hpp>

namespace Core
{
    //------------------------------------------------------------------------
    static const ULong      WINDOW_ACTIVE_LIMIT = 64;

    //------------------------------------------------------------------------
    static const ULong      SYSTEM_HOTKEY_LIMIT = 64;
    static const ULong      SYSTEM_STATUS_LIMIT = 64;
    extern const Char*      SYSTEM_CLASS_NAME;
    extern const WChar*     SYSTEM_MESSAGE_TITLE;
    extern const Char*      SYSTEM_LOG_PATH;
    extern const BitsEnum   SYSTEM_HOTKEY_MODIFIERS;
    extern const IdEnum     SYSTEM_HOTKEY_KEYS;
}
