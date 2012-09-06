#pragma once
#include <Core/Root.hpp>
#include <Core/System/Window.hpp>

namespace Core
{
    /**/
    class System
    {
    public:
        typedef void (*HotKeyHandler)( void* custom );

    public:
        /**/
        static Bool     Initialize( const Char* title=NULL );
        static void     Finalize();
        static Bool     Run();

        /**/
        static void     SetStatus( Index index );
        static void     SetStatusIcon( Index index, Id icon_id );
        static Index    GetStatus();

        /**/
        static Bool     AddHotKey( Index index, Bits modifiers, Id key, System::HotKeyHandler handler, void* custom );
        static Bool     RemoveHotKey( Index index );
        static Bool     ParseHotKey( Bits& modifiers, Id& key, const Char* string );

        /**/
        static Bool     Message( Bool cancel, const Char* format, ... );
        static Bool     GetClipBoard( Char* buffer, ULong limit );

        /**/
        static UHuge    GetTimeMs();
    };
}
