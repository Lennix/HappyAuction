#pragma once
#include <Core/Constants.hpp>
#include <windows.h>

namespace Core
{
    // private
    //------------------------------------------------------------------------
    static const BitsEnum::Item _system_hotkey_modifiers[] =
    {
        { "A",  MOD_ALT },
        { "C",  MOD_CONTROL },
        { "S",  MOD_SHIFT },
        { "W",  MOD_WIN },
    };

    static const IdEnum::Item _system_hotkey_keys[] =
    {
        { "0",      '0' },
        { "1",      '1' },
        { "2",      '2' },
        { "3",      '3' },
        { "4",      '4' },
        { "5",      '5' },
        { "6",      '6' },
        { "7",      '7' },
        { "8",      '8' },
        { "9",      '9' },

        { "A",      'A' },
        { "B",      'B' },
        { "C",      'C' },
        { "D",      'D' },
        { "E",      'E' },
        { "F",      'F' },
        { "G",      'G' },
        { "H",      'H' },
        { "I",      'I' },
        { "J",      'J' },
        { "K",      'K' },
        { "L",      'L' },
        { "M",      'M' },
        { "N",      'N' },
        { "O",      'O' },
        { "P",      'P' },
        { "Q",      'Q' },
        { "R",      'R' },
        { "S",      'S' },
        { "T",      'T' },
        { "U",      'U' },
        { "V",      'V' },
        { "W",      'W' },
        { "X",      'X' },
        { "Y",      'Y' },
        { "Z",      'Z' },

        { "F1",     VK_F1 },
        { "F2",     VK_F2 },
        { "F3",     VK_F3 },
        { "F4",     VK_F4 },
        { "F5",     VK_F5 },
        { "F6",     VK_F6 },
        { "F7",     VK_F7 },
        { "F8",     VK_F8 },
        { "F9",     VK_F9 },
        { "F10",    VK_F10 },
        { "F11",    VK_F11 },
        { "F12",    VK_F12 },

        { "NUM0",   VK_NUMPAD0 },
        { "NUM1",   VK_NUMPAD1 },
        { "NUM2",   VK_NUMPAD2 },
        { "NUM3",   VK_NUMPAD3 },
        { "NUM4",   VK_NUMPAD4 },
        { "NUM5",   VK_NUMPAD5 },
        { "NUM6",   VK_NUMPAD6 },
        { "NUM7",   VK_NUMPAD7 },
        { "NUM8",   VK_NUMPAD8 },
        { "NUM9",   VK_NUMPAD9 },
    };

    // public
    //------------------------------------------------------------------------
    const Char*  SYSTEM_MESSAGE_TITLE =     "Derp";
    const Char*  SYSTEM_CLASS_NAME =        "HappyCore";
    const Char*  TOOLS_LOG_PATH[LOG_COUNT] =
    {
        "User.log",
        "Error.log"
    };

    //------------------------------------------------------------------------
    const BitsEnum  SYSTEM_HOTKEY_MODIFIERS(_system_hotkey_modifiers,  ACOUNT(_system_hotkey_modifiers));
    const IdEnum    SYSTEM_HOTKEY_KEYS     (_system_hotkey_keys,       ACOUNT(_system_hotkey_keys));
}
