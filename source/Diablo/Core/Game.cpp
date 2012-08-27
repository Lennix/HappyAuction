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
        assert(_active == false);

        // close previous window if any
        _window.Close();

        // find window
        if(_window.Open(GAME_WINDOW_TITLE, GAME_WINDOW_CLASS))
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

    void Game::MouseClickGround()
    {
        MouseClick(UI_COORDS[UI_OTHER_GROUND].x, UI_COORDS[UI_OTHER_GROUND].y);
    }

    //------------------------------------------------------------------------
    void Game::MouseMove( Double x, Double y, Bool direct )
    {
        _window.SendMouseMove(X(x), Y(y), direct);
        SleepFrames(2);
        Sleep(GAME_GLOBAL_DELAY, GAME_GLOBAL_DELAY * 2);
    }

    void Game::MouseMoveGround()
    {
        MouseMove(UI_COORDS[UI_OTHER_GROUND].x, UI_COORDS[UI_OTHER_GROUND].y);
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

    void Game::SendInputNumber( Double x, Double y, Number number )
    {
        TextString nstring;

        // number
        if(number >= 0)
            SendInputText(x, y, Tools::NumberToStr(nstring, number));
        else
            SendInputText(x, y, "");
    }

    //------------------------------------------------------------------------
    Bool Game::ReadInputText( Double x, Double y, Char* text, ULong limit )
    {
        // clipboard mutex
        static Mutex mutex;

        // select input
        MouseClick(x, y);

        // lock clipboard
        mutex.Lock();

        // copy text to clipboard
        SendInputKeys("^CAC^c", true);

        // get clipboard text
        Bool status = System::GetClipBoard(text, limit);

        // unlock clipboard
        mutex.UnLock();

        return status;
    }

    Bool Game::ReadInputNumber( Double x, Double y, Number& number )
    {
        TextString out;

        *out = 0;
        if(!ReadInputText(x, y, out, sizeof(out)) || *out == 0)
            number = -1;
        else
            Tools::StrToNumber(number, out);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Game::WriteCombo( ComboId combo_id, const Char* pattern )
    {
        const Coordinate&   coordinate =    UI_COORDS[combo_id + UI_COMBO_RARITY];
        const Coordinate&   row_size =      UI_COORDS[UI_CONTAINER_COMBOROWSIZE];
        TextString          row_string;
        Index               row_index;
        ULong               row_count;
        ULong               drop_count =    UI_COMBO_DROP_COUNT[combo_id];
        Index               screen_index;
        ULong               window_height = _window.GetHeight();

        // determine box selector height
        Double row_size_y = window_height > UI_COMBO_REZMAP_MAX ?
            row_size.y :
            ( UI_COMBO_REZMAP[Tools::Max(window_height, UI_COMBO_REZMAP_MIN) - UI_COMBO_REZMAP_MIN] / window_height );

        // determine open point
        Double open_x = coordinate.x + row_size.x / 2;
        Double open_y = coordinate.y - row_size_y * .8;

        // if pattern
        if(pattern && *pattern)
        {
            ULong   pattern_length = strlen(pattern);
            ULong   best_score = ~0;
            
            row_index = INVALID_INDEX;

            // open combo
            MouseClick(open_x, open_y);

            // update combo state
            if(!_trainer.ReadComboRowBegin())
                return false;

            // get combo count
            if(!_trainer.ReadComboRowCount(row_count))
                return false;

            // search combo rows
            for( Index i = 0; best_score && _trainer.ReadComboRow(i, row_string); i++ )
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

            // write option index
            if(!_trainer.WriteComboIndex(combo_id, row_index))
                return false;

            // open combo
            MouseClick(open_x, open_y);

            // calculate screen index
            screen_index = (row_count > drop_count) ?
                drop_count - Tools::Min(row_count - row_index, drop_count) :
                row_index;
        }
        // else set default
        else
        {
            screen_index = 0;

            // write 0 index
            if(!_trainer.WriteComboIndex(combo_id, 0))
                return false;

            // open combo
            MouseClick(open_x, open_y);
        }

        // calculated constrained combo y (due to resolution)
        Double combo_bottom = coordinate.y + (row_size_y * drop_count);
        Double constrained_y = (combo_bottom > 1.0) ? coordinate.y - (combo_bottom - 1.0) : coordinate.y;

        // click selection
        MouseClick(open_x, constrained_y + (screen_index * row_size_y) + (row_size_y / 2));

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

                // sleep a while and listen
                Sleep(1);
            }
            while(current_count == last_count);
            last_count = current_count;
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
        ULong out = (ULong)(y * (Double)_window.GetHeight());
        return random ? _RandomizeXY(out) : out;
    }

    // private
    //------------------------------------------------------------------------
    ULong Game::_RandomizeXY( ULong xy )
    {
        ULong range = UI_COORD_SPREAD * 2;
        ULong random = rand() % (range + 1);
        ULong out = xy - UI_COORD_SPREAD + random;

        return out;
    }
}
