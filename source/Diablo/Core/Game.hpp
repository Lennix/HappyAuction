#pragma once
#include <Diablo/Core/Trainer.hpp>
#include <Diablo/Types.hpp>
#include <Core/System/Mutex.hpp>
#include <Core/System/Process.hpp>
#include <Core/System/Window.hpp>

namespace Diablo
{
    /**/
    class Game
    {
    private:
        Window  _window;
        Process _process;
        Trainer _trainer;
        Mutex   _mutex;
        Bool    _active;

    public:
        /**/
        Game();

        /**/
        Bool IsActive() const;

        /**/
        Bool Start();
        void Stop();

        /**/
        Window& GetWindow();
        Process& GetProcess();
        Trainer& GetTrainer();

        /**/
        void InputEnable( Bool enable );

        /**/
        void MouseClickAbsolute( ULong x, ULong y );
        void MouseClick( Double x, Double y, Bool centered=true, Bool random=true );
        void MouseClickGround();
        void MouseMove( Double x, Double y, Bool direct=false );
        void MouseMoveGround();

        /**/
        void SendInputKeys( const Char* text, Bool specials );
        void SendInputText( Double x, Double y, const Char* format, ... );
        void SendInputNumber( Double x, Double y, Number number );

        /**/
        Bool ReadInputText( Double x, Double y, Char* text, ULong limit );
        Bool ReadInputNumber( Double x, Double y, Number& number );

        /**/
        Bool WriteCombo( ComboId combo_id, const Char* string=NULL );
        Bool ReadCombo( ComboId combo_id, TextString string );

        /**/
        void Sleep( ULong min, ULong max=0 );
        Bool SleepFrames( ULong count );

        /**/
        ULong X( Double x, Bool random=true );
        ULong Y( Double y, Bool random=true );

    private:
        /**/
        ULong _RandomizeXY( ULong xy );
    };
}
