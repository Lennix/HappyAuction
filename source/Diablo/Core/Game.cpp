#pragma once
#include <Core/System/Thread.hpp>
#include <Core/System/System.hpp>
#include <Diablo/Constants.hpp>
#include <Diablo/Core/Game.hpp>

namespace Diablo
{
    // public
    //------------------------------------------------------------------------
    Game::Game():
        _trainer(_process),
        _active(false)
    {
    }

    //------------------------------------------------------------------------
    Bool Game::IsActive() const
    {
        return _active && _window.IsActive();
    }

    //------------------------------------------------------------------------
    Bool Game::Start()
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
                    // check if already trained
                    if( _trainer.CheckTrained() ||
                    // else run trainer
                        _trainer.Train())
                    {
                        _active = true;
                        return true;
                    }

                }
            }
        }

        return false;
    }

    //------------------------------------------------------------------------
    void Game::Stop()
    {
        _active = false;
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
    Trainer& Game::GetTrainer()
    {
        return _trainer;
    }

    //------------------------------------------------------------------------
    void Game::MouseClickAbsolute( ULong x, ULong y )
    {
        _window.SendMouseButton(x, y);
        SleepFrames(2);
        Sleep(GAME_GLOBAL_DELAY, GAME_GLOBAL_DELAY * 2);
    }

    void Game::MouseClick( Double x, Double y, Bool centered, Bool random )
    {
        MouseClickAbsolute(centered ? X(x, random) : Y(x, random), Y(y, random));
    }

    //------------------------------------------------------------------------
    void Game::MouseMove( Double x, Double y, Bool direct )
    {
        _window.SendMouseMove(X(x), Y(y), direct);
        SleepFrames(2);
        Sleep(GAME_GLOBAL_DELAY, GAME_GLOBAL_DELAY * 2);
    }

    //------------------------------------------------------------------------
    void Game::SendInputKeys( const Char* text, Bool specials )
    {
        _window.SendInputKeys(text, specials);
        SleepFrames(2);
        Sleep(GAME_GLOBAL_DELAY, GAME_GLOBAL_DELAY * 2);
    }

    //------------------------------------------------------------------------
    void Game::SendInputText( Double x, Double y, const Char* format, ... )
    {
        va_list     args;
        TextString  out;
        assert(format != NULL);

        // build text from format
        va_start(args, format);
        vsnprintf(out, sizeof(out), format, args);
        va_end(args);
    
        // select input
        MouseClick(x, y);

        // if not empty string
        if(*out)
        {
            // send special to select-all old text to be replaced by new text
            SendInputKeys("^CA^c", true);

            // send new text
            SendInputKeys(out, false);
        }
        // else send special to select-all old text and delete
        else
            SendInputKeys("^CA^c^D", true);
    }

    //------------------------------------------------------------------------
    Bool Game::GetInputText( Double x, Double y, Char* text, ULong limit )
    {
        // select input
        MouseClick(x, y);

        // copy text to clipboard
        SendInputKeys("^CAC^c", true);

        // get clipboard text
        Bool status = System::GetClipBoard(text, limit);

        return status;
    }

    //------------------------------------------------------------------------
    void Game::Sleep( ULong min, ULong max )
    {
        ULong delay;

        if(max <= min)
            delay = min;
        else
        {
            ULong   range = max - min;
            ULong   value = rand() % range;
            Float   ratio = (Float)value / (Float)range;
            Float   factor = ratio * ratio;
            
            delay = min + (ULong)(value * factor);
        }

        // slice sleeps allowing termination
        for( ; _active && delay > GAME_SLEEP_SLICE ; delay -= GAME_SLEEP_SLICE )
            Thread::Sleep(GAME_SLEEP_SLICE);
        if(_active)
            Thread::Sleep(delay);
    }

    //------------------------------------------------------------------------
    Bool Game::SleepFrames( ULong count )
    {
        ULong last_count;

        // read last count
        if(!_trainer.ReadFrameCount(last_count))
            return false;

        // iterate for each frame
        for( Index i = 0; i < count && _active; i++ )
        {
            // wait for frame to increment
            ULong current_count;
            do
            {
                if(!_trainer.ReadFrameCount(current_count))
                    return false;
            }
            while(current_count == last_count);
            last_count = current_count;

            // minimum delay
            Sleep(1);
        }

        return true;
    }

    //------------------------------------------------------------------------
    ULong Game::X( Double x, Bool random )
    {
        ULong out = (ULong)(x * (Double)_window.GetHeight() + (Double)_window.GetWidth() / 2);
        return random ? _RandomizeXY(out) : out;
    }

    ULong Game::Y( Double y, Bool random )
    {
        ULong out = (ULong)((y * (Double)_window.GetHeight()) + 0.5);
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
