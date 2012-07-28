#include <Core/System/System.hpp>
#include <windows.h>

namespace Core
{
    //------------------------------------------------------------------------
    static const Char* _CLASS_NAME =    "Core";
    static const Char* _MESSAGE_TITLE = "Derp";


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


    // local
    //------------------------------------------------------------------------
    static HWND                     _hwnd = NULL;
    static System::HotKeyHandler    _hotkey_handler = NULL;
    static void*                    _hotkey_custom = NULL;
    static const Char*              _title = "";
    static System::Status           _status = System::STATUS_IDLE;
    static Id                       _STATUS_ICONS[System::STATUS_COUNT] = {0};

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
            if(_hotkey_handler)
                _hotkey_handler(_hotkey_custom);
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
        HINSTANCE hinstance = (HINSTANCE)GetModuleHandle(NULL);

        // register window class
        wclass.cbSize = sizeof(wclass);
        wclass.style = 0;
        wclass.lpfnWndProc = _WndProc;
        wclass.cbClsExtra = 0;
        wclass.cbWndExtra = 0;
        wclass.hInstance = hinstance;
        wclass.hIcon = LoadIcon( NULL, MAKEINTRESOURCE(_STATUS_ICONS[System::STATUS_IDLE]) );
        wclass.hIconSm = wclass.hIcon;
        wclass.hCursor = LoadCursor( NULL, IDC_ARROW );
        wclass.hbrBackground = NULL;
        wclass.lpszMenuName = NULL;
        wclass.lpszClassName = _CLASS_NAME;

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
            hinstance,
            NULL );

        if(_hwnd == NULL)
            return false;

        return true;
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
    void System::SetStatus( System::Status status )
    {
        _status = status;
        _SysTrayUpdate(_hwnd, ID_TRAYICON);
    }

    //------------------------------------------------------------------------
    void System::SetStatusIcon( System::Status status, Id icon_id )
    {
        assert(status < System::STATUS_COUNT);
        _STATUS_ICONS[status] = icon_id;
    }

    //------------------------------------------------------------------------
    void System::Message( const Char* format, ... )
    {
        TextString  message;
        va_list     args;
        assert(format != NULL);

        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
        message[sizeof(message) - 1] = 0;

        MessageBox(NULL, message, _MESSAGE_TITLE, MB_OK);
    }

    //------------------------------------------------------------------------
    Bool System::SetHotKey( ULong modifier, ULong key, System::HotKeyHandler handler, void* custom )
    {
        assert(_hwnd);
        assert(_hotkey_handler == NULL);
        assert(_hotkey_custom == NULL);

        if(!RegisterHotKey(_hwnd, 1, modifier, key))
            return false;

        _hotkey_handler = handler;
        _hotkey_custom = custom;

        return true;
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
}
