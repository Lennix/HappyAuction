#pragma once
#include <Core/Root.hpp>
#include <Core/System/Window.hpp>

namespace Core
{
    /**/
    class System
    {
    public:
        /**/
        enum Status
        {
            STATUS_IDLE ,
            STATUS_ACTIVE,
            STATUS_COUNT
        };

    public:
        typedef void (*HotKeyHandler)( void* custom );

    public:
        /**/
        static Bool Run( const Char* title=NULL );

        /**/
        static void SetStatus( Status status );
        static void SetStatusIcon( Status status, Id icon_id );

        /**/
        static void Message( const Char* format, ... );
        static Bool SetHotKey( ULong modifier, ULong key, HotKeyHandler handler, void* custom );
        static Bool GetClipBoard( Char* buffer, ULong limit );

        /**/
        static UHuge GetTimeMs();
    };
}
