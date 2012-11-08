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
    public:
        enum
        {
            INPUT_EXACT =       BIT(0),
            INPUT_DIRECT =      BIT(1),
            INPUT_NODELAY =     BIT(2),
            INPUT_SPECIALS =    BIT(3),
        };

    private:
        Window  _window;
        Process _process;
        Trainer _trainer;
        Mutex   _mutex;
        ULong   _delay;
        Bits    _override_options;
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
        void SetOverrideOptions( Bits options );

        /**/
        void SetGlobalDelay( ULong delay );
        ULong GetGlobalDelay() const;

        /**/
        void MouseClick( const Coordinate& coord, Bits options=0 );
        void MouseClickGround( Bits options=0 );
        void MouseMove( const Coordinate& coord, Bits options=0 );
        void MouseMoveGround( Bits options=0 );

        /**/
        void SendInputKeys( const Char* text, Bits options=0 );
        void SendInputText( const Coordinate& coord, const Char* format, ... );
        void SendInputTextDirect( const Coordinate& coord, Id id, const Char* text );
        void SendInputNumber( const Coordinate& coord, Number number );

        /**/
        Bool ReadInputText( const Coordinate& coord, Char* text, ULong limit );
        Bool ReadInputNumber( const Coordinate& coord, Number& number );

        /**/
        Bool WriteCombo( ComboId combo_id, const Char* string=NULL );
        Bool ReadCombo( ComboId combo_id, TextString string );

        /**/
        void Sleep( ULong min, ULong max=0 );
        Bool SleepFrames( ULong count );

        /**/
        void Logout();

    private:
        /**/
        void _CommonDelay( Bits options );
        void _CoordToAbsolute( ULong& x, ULong& y, const Coordinate& coord, Bits options );
        void _AxisRandomize( ULong& xyz );
    };
}
