#include <Core/System/System.hpp>
#include <Core/Tools.hpp>
#include <windows.h>

namespace Core
{
    //------------------------------------------------------------------------
    static const Char _FORMAT_HOTKEY[] = "%s.%s";


    //------------------------------------------------------------------------
    enum
    {
        ID_TRAYICON         = 1,
        ID_EXIT             = 2000,
    };

    enum
    {
        APPWM_TRAYICON      = WM_APP,
        APPWM_NOP           = WM_APP + 1,
    };

    struct HotKeyEntry
    {
        System::HotKeyHandler   handler;
        void*                   custom;
    };

    // local
    //------------------------------------------------------------------------
    static HWND                     _hwnd = NULL;
    static HINSTANCE                _hinstance = NULL;
    static const Char*              _title = "";
    static HotKeyEntry              _hotkeys[SYSTEM_HOTKEY_LIMIT];
    static Index                    _status = 0;
    static Id                       _STATUS_ICONS[SYSTEM_STATUS_LIMIT] = {0};

    //------------------------------------------------------------------------
    static void _SysTrayAdd( HWND hwnd, Id uid, Id callbackmsg, const Char* tooltip )
    {
        NOTIFYICONDATA nid = {0};

        nid.cbSize              = sizeof( nid );
        nid.hWnd                = hwnd;
        nid.uID                 = uid;
        nid.uFlags              = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        nid.uCallbackMessage    = callbackmsg;
        nid.hIcon               = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(_STATUS_ICONS[_status]), IMAGE_ICON, 16, 16, 0);

        strcpy( nid.szTip, tooltip );

        Shell_NotifyIcon( NIM_ADD, &nid );
    }

    //------------------------------------------------------------------------
    static void _SysTrayRemove( HWND hwnd, Id uid )
    {
        NOTIFYICONDATA nid = {0};

        nid.cbSize  = sizeof( nid );
        nid.hWnd    = hwnd;
        nid.uID     = uid;

        Shell_NotifyIcon( NIM_DELETE, &nid );
    }

    //------------------------------------------------------------------------
    static void _SysTrayShow( HWND hwnd  )
    {
        HMENU   menu = NULL;
        Index   i = 0;
        WORD    command;
        POINT   curpos;

        menu = CreatePopupMenu();

        GetCursorPos(&curpos);

        InsertMenu( menu, i++, MF_BYPOSITION | MF_STRING, ID_EXIT, "Exit" );
        SetMenuDefaultItem( menu, ID_EXIT, FALSE );

        SetFocus( hwnd );
        SendMessage( hwnd, WM_INITMENUPOPUP, (WPARAM)menu, 0 );

        command = TrackPopupMenu(
            menu,
            TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY,
            curpos.x, curpos.y,
            0,
            hwnd,
            NULL );

        SendMessage( hwnd, WM_COMMAND, command, 0 );
        DestroyMenu( menu );
    }

    //------------------------------------------------------------------------
    static void _SysTrayUpdate( HWND hwnd, Id uid )
    {
        NOTIFYICONDATA nid = {0};

        nid.cbSize  = sizeof( nid );
        nid.hWnd    = _hwnd;
        nid.uID     = ID_TRAYICON;
        nid.uFlags  = NIF_ICON;
        nid.hIcon   = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(_STATUS_ICONS[_status]), IMAGE_ICON, 16, 16, 0);

        Shell_NotifyIcon( NIM_MODIFY, &nid );
    }

    //------------------------------------------------------------------------
    static void _SysTrayOnOpen( HWND hwnd )
    {
        SetForegroundWindow( hwnd );
        _SysTrayShow( hwnd );
        PostMessage( hwnd, APPWM_NOP, 0, 0 );
    }

    //------------------------------------------------------------------------
    static Bool _CommandProc( HWND hwnd, WORD wid, HWND htcl )
    {
        switch(wid)
        {
        case ID_EXIT:
            PostMessage( hwnd, WM_CLOSE, 0, 0 );
            return true;
        }

        return false;
    }

    //------------------------------------------------------------------------
    static LRESULT CALLBACK _WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
    {
        switch(message)
        {
        case WM_CREATE:
            _SysTrayAdd( hwnd, ID_TRAYICON, APPWM_TRAYICON, _title );
            return 0;

        case APPWM_NOP:
            return 0;

        case APPWM_TRAYICON:
            SetForegroundWindow( hwnd );
            switch( lparam )
            {
                case WM_RBUTTONUP:
                    _SysTrayOnOpen(hwnd);
                    return 0;
            }
            return 0;

        case WM_HOTKEY:
            if( wparam < SYSTEM_HOTKEY_LIMIT )
            {
                HotKeyEntry& entry = _hotkeys[wparam];
                entry.handler(entry.custom);
            }
            return 0;

        case WM_COMMAND:
            if(_CommandProc( hwnd, LOWORD(wparam), (HWND)lparam ))
                return 0;
            break;

        case WM_CLOSE:
            _SysTrayRemove(hwnd, ID_TRAYICON);
            PostQuitMessage(0);
            return 0;

        case WM_DESTROY:
            return 0;
        }

        return DefWindowProc( hwnd, message, wparam, lparam );
    }

    // class
    //------------------------------------------------------------------------
    Bool System::Initialize( const Char* title )
    {
        WNDCLASSEX wclass;

        // set title
        if(title)
            _title = title;

        // get instance
        _hinstance = (HINSTANCE)GetModuleHandle(NULL);

        // register window class
        wclass.cbSize = sizeof(wclass);
        wclass.style = 0;
        wclass.lpfnWndProc = _WndProc;
        wclass.cbClsExtra = 0;
        wclass.cbWndExtra = 0;
        wclass.hInstance = _hinstance;
        wclass.hIcon = LoadIcon( NULL, MAKEINTRESOURCE(_STATUS_ICONS[0]) );
        wclass.hIconSm = wclass.hIcon;
        wclass.hCursor = LoadCursor( NULL, IDC_ARROW );
        wclass.hbrBackground = NULL;
        wclass.lpszMenuName = NULL;
        wclass.lpszClassName = SYSTEM_CLASS_NAME;

        // register class
        RegisterClassEx(&wclass);

        // create window
        _hwnd = CreateWindow(
            wclass.lpszClassName,
            "",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            _hinstance,
            NULL );

        if(_hwnd == NULL)
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    void System::Finalize()
    {
        // destroy window
        DestroyWindow(_hwnd);

        // unregister class
        UnregisterClass(SYSTEM_CLASS_NAME, _hinstance);
    }

    //------------------------------------------------------------------------
    Bool System::Run()
    {
        MSG msg;

        // run loop
        while(GetMessage(&msg, NULL, 0, 0 ) > 0)
        { 
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }

        return true;
    }

    //------------------------------------------------------------------------
    void System::SetStatus( Index index )
    {
        assert(index < SYSTEM_HOTKEY_LIMIT);
        _status = index;
        _SysTrayUpdate(_hwnd, ID_TRAYICON);
    }

    //------------------------------------------------------------------------
    void System::SetStatusIcon( Index index, Id icon_id )
    {
        assert(index < SYSTEM_STATUS_LIMIT);
        _STATUS_ICONS[index] = icon_id;
    }

    //------------------------------------------------------------------------
    Index System::GetStatus()
    {
        return _status;
    }

    //------------------------------------------------------------------------
    Bool System::AddHotKey( Index index, Bits modifiers, Id key, System::HotKeyHandler handler, void* custom )
    {
        assert(index < SYSTEM_HOTKEY_LIMIT);
        HotKeyEntry& entry = _hotkeys[index];

        // register hotkey
        if(!RegisterHotKey(_hwnd, index, modifiers, key))
            return false;

        // set hotkey entry
        entry.handler = handler;
        entry.custom = custom;

        return true;
    }

    Bool System::RemoveHotKey( Index index )
    {
        assert(index < SYSTEM_HOTKEY_LIMIT);
        HotKeyEntry& entry = _hotkeys[index];

        // remove hotkey
        UnregisterHotKey(_hwnd, index);
        entry.handler = NULL;
        entry.custom = NULL;

        return true;
    }

    Bool System::ParseHotKey( Bits& modifiers, Id& key, const Char* string )
    {
        TextString  s1;
        TextString  s2;
        const Char* ps;
        ULong       scount;

        key = 0;
        modifiers = 0;

        if( *string == 0 )
            return false;

        // parse string
        Tools::StrFormatRead(scount, string, _FORMAT_HOTKEY, s1, s2);
        if(scount == 0 || scount > 2)
            return false;

        // parse modifiers
        if(scount == 2)
        {
            for( ps = s1; *ps; *ps++)
            {
                ULong   modifier;
                Char    modifier_pattern[] = { *ps, 0 };

                if(!SYSTEM_HOTKEY_MODIFIERS.FindObject(modifier, modifier_pattern))
                    return false;

                modifiers |= modifier;
            }

            ps = s2;
        }
        else
            ps = s1;

        // parse key
        if(!SYSTEM_HOTKEY_KEYS.FindObject(key, ps))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool System::Message( Bool prompt, const Char* format, ... )
    {
        TextString  message;
        va_list     args;
        assert(format != NULL);

        // create message
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
        message[sizeof(message) - 1] = 0;

        // show message box
        Bits flags = MB_OK|MB_SETFOREGROUND;
        if(prompt)
            flags |= MB_YESNO;
        Int status = MessageBox(NULL, message, SYSTEM_MESSAGE_TITLE, flags);

        // success if user hit yes or did not fail
        return status != 0 && status != IDNO;
    }

    //------------------------------------------------------------------------
    Bool System::GetClipBoard( Char* buffer, ULong limit )
    {
        if(!OpenClipboard(NULL))
            return false;

        const Char* text = (const Char*)GetClipboardData(CF_TEXT);
        if(text)
            strncpy(buffer, text, limit);
        CloseClipboard();

        return text != NULL;
    }

    //------------------------------------------------------------------------
    UHuge System::GetTimeMs()
    {
        UHuge time;

        // get time
        GetSystemTimeAsFileTime((FILETIME*)&time);

        // adjust to 1970
        time -= 116444736000000000LL;

        // convert to milliseconds
        return time / 10000;
    }

    //------------------------------------------------------------------------
    void System::Log( LogId id, const Char* format, ... )
    {
        static FILE* handle[LOG_COUNT] = { 0 };

        FILE*& file = handle[id];

        if(format == NULL)
        {
            if(file != NULL)
            {
                fclose(file);
                file = NULL;
            }
        }
        else
        {
            if(file == NULL)
                file = fopen(TOOLS_LOG_PATH[id], "wt");

            if(file)
            {
                va_list args;
                va_start(args, format);
                vfprintf(file, format, args);
                va_end(args);

                fflush(file);
            }
        }
    }
}
