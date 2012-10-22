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
        _override_options(0),
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
        assert(_active == false);

        // close previous window if any
        _window.Close();

        // find window
        if(_window.Open(NULL, GAME_WINDOW_CLASS))
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
                    }
                }
            }
        }

        return _active;
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
    void Game::SetOverrideOptions( Bits options )
    {
        _override_options = options;
    }

    //------------------------------------------------------------------------
    void Game::MouseClick( const Coordinate& coord, Bits options )
    {
                options |= _override_options;
        ULong   x, y;

        _CoordToAbsolute(x, y, coord, options);
        _window.SendMouseButton(x, y);
        _CommonDelay(options);
    }

    void Game::MouseClickGround( Bits options )
    {
        MouseClick(UI_COORDS[UI_OTHER_GROUND], options);
    }

    //------------------------------------------------------------------------
    void Game::MouseMove( const Coordinate& coord, Bits options )
    {
                options |= _override_options;
        Bool    direct = (options & INPUT_DIRECT)!=0;
        ULong   x, y;

        _CoordToAbsolute(x, y, coord, options);

        if(direct)
        {
            _window.Focus(true);
            _window.SendMouseMove(x, y, true);
            _window.Focus(false);
        }
        else
            _window.SendMouseMove(x, y, false);
        
        _CommonDelay(options);
    }

    void Game::MouseMoveGround( Bits options )
    {
        MouseMove(UI_COORDS[UI_OTHER_GROUND], options);
    }

    //------------------------------------------------------------------------
    void Game::SendInputKeys( const Char* text, Bits options )
    {
             options |= _override_options;
        Bool specials = (options & INPUT_SPECIALS)!=0;

        _window.SendInputKeys(text, specials);
        _CommonDelay(options);
    }

    //------------------------------------------------------------------------
    void Game::SendInputText( const Coordinate& coord, const Char* format, ... )
    {
        va_list     args;
        TextString  out;
        assert(format != NULL);

        // build text from format
        va_start(args, format);
        vsnprintf(out, sizeof(out), format, args);
        va_end(args);
    
        // select input
        MouseClick(coord);

        // if not empty string
        if(*out)
        {
            // send special to select-all old text to be replaced by new text
            SendInputKeys("CAc", INPUT_SPECIALS|INPUT_NODELAY);

            // send new text
            SendInputKeys(out);
        }
        // else send special to select-all old text and delete
        else
            SendInputKeys("CAcD", INPUT_SPECIALS);
    }

    void Game::SendInputTextDirect( const Coordinate& coord, Id id, const Char* text )
    {
        // write text directly
        _trainer.WriteInputText(id, text);

        // hack to refresh text
        MouseClick(coord);
        SendInputKeys("1B", INPUT_SPECIALS);
    }

    void Game::SendInputNumber( const Coordinate& coord, Number number )
    {
        TextString nstring;

        // number
        if(number >= 0)
            SendInputText(coord, Tools::NumberToStr(nstring, number));
        else
            SendInputText(coord, "");
    }

    //------------------------------------------------------------------------
    Bool Game::ReadInputText( const Coordinate& coord, Char* text, ULong limit )
    {
        // clipboard mutex
        static Mutex mutex;

        // select input
        MouseClick(coord);

        // lock clipboard
        mutex.Lock();

        // copy text to clipboard
        SendInputKeys("CACc", INPUT_SPECIALS);

        // get clipboard text
        Bool status = System::GetClipBoard(text, limit);

        // unlock clipboard
        mutex.UnLock();

        return status;
    }

    Bool Game::ReadInputNumber( const Coordinate& coord, Number& number )
    {
        TextString out;

        *out = 0;
        if(!ReadInputText(coord, out, sizeof(out)) || *out == 0)
            number = -1;
        else
            Tools::StrToNumber(number, out);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Game::WriteCombo( ComboId combo_id, const Char* pattern )
    {
        const Coordinate&   coordinate = UI_COORDS[combo_id + UI_COMBO_RARITY];
        TextString          row_string;
        Index               row_index;
        Double              select_y;

        // if pattern
        if(pattern && *pattern)
        {
            ULong   pattern_length = strlen(pattern);
            ULong   best_score = ~0;
            
            row_index = INVALID_INDEX;

            // open combo
            MouseClick(coordinate);

            // update combo state
            if(!_trainer.ReadComboRowBegin())
                return false;

            // search combo rows
            for( Index i = 0; best_score && _trainer.ReadComboRow(i, row_string, select_y); i++ )
            {
                // substring search
                if(Tools::StrSearch(pattern, row_string))
                {
                    ULong score = strlen(row_string) - pattern_length;

                    // elect best match
                    if(score < best_score)
                    {
                        best_score = score;
                        row_index = i;
                    }
                }
            }

            // close combo
            MouseClickGround();

            // fail if not found
            if(row_index == INVALID_INDEX)
                return false;
        }
        else
            row_index = 0;

        // write option index
        if(!_trainer.WriteComboIndex(combo_id, row_index))
            return false;

        // open combo
        MouseClick(coordinate);

        // update combo state
        if(!_trainer.ReadComboRowBegin())
            return false;

        // get select y
        if(!_trainer.ReadComboRow(row_index, row_string, select_y))
            return false;

        // click selection
        MouseClick(Coordinate(coordinate.x, select_y));

        return true;
    }

    Bool Game::ReadCombo( ComboId combo_id, TextString string )
    {
        return _trainer.ReadComboString(combo_id + Trainer::OBJECT_COMBO_RARITY, string);
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
        for( ; _active && delay > GAME_SLEEP_SLICE; delay -= GAME_SLEEP_SLICE )
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

                // sleep a while and listen
                Sleep(1);
            }
            while(current_count == last_count);
            last_count = current_count;
        }

        return true;
    }

    //------------------------------------------------------------------------
    void Game::Logout()
    {
        // click options
        MouseClick(UI_COORDS[UI_BUTTON_OPTIONS]);

        // click logout
        MouseClick(UI_COORDS[UI_BUTTON_OPTIONSLOGOUT]);

        // logout delay
        Sleep(GAME_LOGOUT_DELAY);
    }

    // private
    //------------------------------------------------------------------------
    void Game::_CoordToAbsolute( ULong& x, ULong& y, const Coordinate& coord, Bits options )
    {
        Double w = static_cast<Double>(_window.GetWidth());
        Double h = static_cast<Double>(_window.GetHeight());

        // convert x
        switch(coord.type)
        {
        case Coordinate::CENTER:
            x = static_cast<ULong>(coord.x * h + w / 2);
            break;

        case Coordinate::LEFT:
            x = static_cast<ULong>(coord.x * h);
            break;

        case Coordinate::RIGHT:
            x = static_cast<ULong>(w - (coord.x * h));
            break;
        }

        // convert y
        y = static_cast<ULong>(coord.y * h);

        // randomize
        if(!(options & INPUT_EXACT))
        {
            _AxisRandomize(x);
            _AxisRandomize(y);
        }
    }

    //------------------------------------------------------------------------
    void Game::_CommonDelay( Bits options )
    {
        if(!(options & INPUT_NODELAY))
            SleepFrames(2);

        Sleep(GAME_GLOBAL_DELAY, GAME_GLOBAL_DELAY * 2);
    }

    //------------------------------------------------------------------------
    void Game::_AxisRandomize( ULong& xyz )
    {
        ULong range = UI_COORD_SPREAD * 2;
        ULong random = rand() % (range + 1);
        xyz  = xyz - UI_COORD_SPREAD + random;
    }
}
