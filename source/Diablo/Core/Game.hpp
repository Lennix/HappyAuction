#pragma once
#include <Diablo/Core/Trainer.hpp>
#include <Diablo/Types.hpp>
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
        void MouseClick( ULong x, ULong y );
        void MouseClick( Double x, Double y, Bool centered=true );
        void MouseMove( Double x, Double y );
        void MouseDrag( Double to_x, Double to_y, Double from_x, Double from_y, Bool random=true );

        /**/
        void SendInputKeys( const Char* text, Bool specials );
        void SendInputText( Double x, Double y, const Char* format, ... );

        /**/
        Bool GetInputText( Double x, Double y, Char* text, ULong limit );

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
