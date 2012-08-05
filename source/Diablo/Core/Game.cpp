#pragma once
#include <Core/System/Thread.hpp>
#include <Core/System/System.hpp>
#include <Diablo/Constants.hpp>
#include <Diablo/Core/Game.hpp>

namespace Diablo
{
    // public
    //------------------------------------------------------------------------
    Game::Game()
    {
    }

    //------------------------------------------------------------------------
    Bool Game::IsActive() const
    {
        return _window.IsActive();
    }

    //------------------------------------------------------------------------
    Bool Game::Initialize()
    {
        // find window
        if(_window.Find(GAME_WINDOW_TITLE, GAME_WINDOW_CLASS))
        {
            // refresh dimensions
            if(_window.RefreshDimensions())
            {
                // get process
                if(_process.FromWindow(_window))
                {
                    // ensure input enabled
                    InputEnable(true);

                    return true;
                }
            }
        }

        return false;
    }

    //------------------------------------------------------------------------
    Window& Game::GetWindow()
    {
        return _window;
    }

    //------------------------------------------------------------------------
    Process& Game::GetProcess()
    {
        return _process;
    }

    //------------------------------------------------------------------------
    void Game::InputEnable( Bool enable )
    {
        _window.InputEnable(enable);
    }

    //------------------------------------------------------------------------
    void Game::MouseClick( ULong x, ULong y, ULong delay )
    {
        _window.SendMouseButton(x, y);
        Sleep(delay, delay * 2);
    }

    void Game::MouseClick( Double x, Double y, ULong delay )
    {
        MouseClick(X(x), Y(y), delay);
    }

    //------------------------------------------------------------------------
    void Game::MouseMove( Double x, Double y, ULong delay )
    {
        _window.SendMouseMove(X(x), Y(y));
        Sleep(delay, delay * 2);
    }

    //------------------------------------------------------------------------
    void Game::MouseDrag( Double to_x, Double to_y, Double from_x, Double from_y, Bool random )
    {
        _window.SendMouseButton(X(from_x, random), Y(from_y, random), Window::MOUSE_DOWN);
        _window.SendMouseMove(X(to_x, random), Y(to_y, random));
        _window.SendMouseButton(X(to_x, random), Y(to_y, random), Window::MOUSE_UP);
    }

    //------------------------------------------------------------------------
    void Game::SendInput( const Char* text, Bool specials, ULong delay )
    {
        _window.SendInput(text, specials);
        Sleep(delay, delay * 2);
    }

    //------------------------------------------------------------------------
    void Game::SendInputText( Double x, Double y, const Char* format, ... )
    {
        va_list     args;
        TextString  out;
        assert(format != NULL);

        // disable input
        InputEnable(false);

        // build text from format
        va_start(args, format);
        vsnprintf(out, sizeof(out), format, args);
        va_end(args);
    
        // select input
        MouseClick(x, y, GAME_ITEMREAD_DELAY);

        // if not empty string
        if(*out)
        {
            // send special to select-all old text to be replaced by new text
            SendInput("^CA^c", true, GAME_ITEMREAD_DELAY);

            // send new text
            SendInput(out, false, GAME_ITEMREAD_DELAY);
        }
        // else send special to select-all old text and delete
        else
            SendInput("^CA^D^c", true, GAME_ITEMREAD_DELAY);

        // enable input
        InputEnable(true);
    }

    //------------------------------------------------------------------------
    Bool Game::GetInputText( Double x, Double y, Char* text, ULong limit )
    {
        // disable input
        InputEnable(false);

        // select input
        MouseClick(x, y, GAME_ITEMREAD_DELAY);

        // copy text to clipboard
        SendInput("^CAC^c", true, GAME_ITEMREAD_DELAY);

        // get clipboard text
        Bool status = System::GetClipBoard(text, limit);

        // enable input
        InputEnable(true);

        return status;
    }

    //------------------------------------------------------------------------
    void Game::Sleep( ULong min, ULong max )
    {
        if(max <= min)
            Thread::Sleep(min);
        else
        {
            ULong   range = max - min;
            ULong   value = rand() % range;
            Float   ratio = (Float)value / (Float)range;
            Float   factor = ratio * ratio;
            ULong   delay = min + (ULong)(value * factor);

            Thread::Sleep(delay);
        }
    }

    //------------------------------------------------------------------------
    ULong Game::X( Double x, Bool random )
    {
        ULong out = (ULong)(x * (Double)_window.GetHeight() + (Double)_window.GetWidth() / 2);
        return random ? _RandomizeXY(out) : out;
    }

    ULong Game::Y( Double y, Bool random )
    {
        ULong out = (ULong)(y * (Double)_window.GetHeight());
        return random ? _RandomizeXY(out) : out;
    }

    // private
    //------------------------------------------------------------------------
    ULong Game::_RandomizeXY( ULong xy )
    {
        ULong range = GAME_COORDINATE_SPREAD * 2;
        ULong random = rand() % (range + 1);
        ULong out = xy - GAME_COORDINATE_SPREAD + random;

        return out;
    }
}
