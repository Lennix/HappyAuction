#pragma once
#include <Core/System/Window.hpp>

namespace Core
{
    /**/
    Window::ActiveCollection    Window::_actives;
    Mutex                       Window::_mutex;
}
