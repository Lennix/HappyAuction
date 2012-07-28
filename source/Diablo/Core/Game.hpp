#pragma once
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

    public:
        /**/
        Game();

        /**/
        Bool IsActive() const;

        /**/
        Bool Initialize();

        /**/
        Window& GetWindow();
        Process& GetProcess();

        /**/
        void InputEnable( Bool enable );

        /**/
        void MouseClick( ULong x, ULong y, ULong delay=0 );
        void MouseClick( Double x, Double y, ULong delay=0 );
        void MouseMove( Double x, Double y, ULong delay=0 );
        void MouseDrag( Double to_x, Double to_y, Double from_x, Double from_y, Bool random=true );

        /**/
        void SendInput( const Char* text, Bool specials, ULong delay );
        void SendInputText( Double x, Double y, const Char* format, ... );

        /**/
        Bool GetInputText( Double x, Double y, Char* text, ULong limit );

        /**/
        void Sleep( ULong min, ULong max=0 );

        /**/
        ULong X( Double x, Bool random=true );
        ULong Y( Double y, Bool random=true );

    private:
        /**/
        ULong _RandomizeXY( ULong xy );
    };
}
