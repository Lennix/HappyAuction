#pragma once
#include <Core/Root.hpp>
#include <Core/Types.hpp>
#include <Core/Tools.hpp>
#include <Core/System/Thread.hpp>
#include <windows.h>

namespace Core
{
    /**/
    class Window
    {
    public:
        enum MouseState
        {
            MOUSE_CLICK,
            MOUSE_DOWN,
            MOUSE_UP,
        };

        struct Color
        {
            Byte b, g ,r, a;
        };

    private:
        HWND    _hwnd;
        Bool    _key_ctrl;
        ULong   _width;
        ULong   _height;

    public:
        /**/
        Window():
            _hwnd(NULL),
            _key_ctrl(false)
        {
        }

        /**/
        HWND GetHandle() const
        {
            return _hwnd;
        }

        /**/
        Bool IsActive() const
        {
            return IsWindow(_hwnd) == TRUE;
        }

        /**/
        ULong GetWidth() const
        {
            return _width;
        }

        ULong GetHeight() const
        {
            return _height;
        }

        /**/
        void InputEnable( Bool enable )
        {
            EnableWindow(_hwnd, enable);
        }

        /**/
        void SendMouseButton( ULong x, ULong y, MouseState state=MOUSE_CLICK )
        {
            LPARAM lparam = (x | (y << 16));
            switch(state)
            {
            case MOUSE_CLICK:
                //SendMouseMove(x, y);
                PostMessage(_hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lparam);
                PostMessage(_hwnd, WM_LBUTTONUP, 0, lparam);
                break;

            case MOUSE_DOWN:
                PostMessage(_hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lparam);
                break;

            case MOUSE_UP:
                PostMessage(_hwnd, WM_LBUTTONUP, 0, lparam);
                break;
            }
        }

        /**/
        void SendMouseMove( ULong x, ULong y )
        {
            LPARAM lparam;

            lparam = (HTCLIENT | (WM_MOUSEMOVE << 16));
            PostMessage(_hwnd, WM_SETCURSOR, (WPARAM)_hwnd, lparam);

            lparam = (x | (y << 16));
            PostMessage(_hwnd, WM_MOUSEMOVE, 0, lparam);
        }

        /**/
        void SendMouseWheel( Short amount, ULong x, ULong y )
        {
            LPARAM lparam = (x | (y << 16));
            PostMessage(_hwnd, WM_MOUSEWHEEL, (amount * WHEEL_DELTA) << 16, lparam);
        }

        /**/
        void SendChar( Char c )
        {
            PostMessage(_hwnd, WM_CHAR, c, 0);
        }

        /**/
        void SendInput( const Char* text, Bool specials )
        {
            Bool special = false;

            for(; *text; text++ )
            {
                Char c = *text;

                if(special)
                {
                    special = false;

                    switch(c)
                    {
                    case 'C': // down
                    case 'c': // up
                        _key_ctrl = (c == 'C');
                        _SendVKey(VK_CONTROL, _key_ctrl);
                        break;

                    case 'D':
                        _SendVKey(VK_DELETE, true);
                        _SendVKey(VK_DELETE, false);
                        break;

                    default:
                        _SendKey(c);
                    }
                }
                else
                {
                    if(specials && c == '^')
                        special = true;
                    else
                        _SendKey(c);
                }
            }
        }

        /**/
        Bool RefreshDimensions()
        {
            RECT rect;

            if(GetClientRect(_hwnd, &rect))
            {
                _width = rect.right - rect.left;
                _height = rect.bottom - rect.top;
                return _width > 0 && _height > 0;
            }
            else
                return false;
        }

        /**/
        Bool Find( const Char* name, const Char* id=NULL )
        {
            _hwnd = FindWindow((LPCTSTR)id, (LPCTSTR)name);
            return (_hwnd != NULL);
        }

        /**/
        void CaptureScreen( Color* buffer, ULong x, ULong y, ULong width, ULong height )
        {
            BITMAPINFOHEADER    bi = {0};
            POINT               screen_point = { x, y };

            // create resources
            HDC         hdc_source = GetDC(NULL);
            HDC         hdc_memory = CreateCompatibleDC(hdc_source);
            HBITMAP     hbitmap = CreateCompatibleBitmap(hdc_source, width, height);
            HBITMAP     hbitmap_old = (HBITMAP)SelectObject(hdc_memory, hbitmap);

            // get screen coordinates
            ClientToScreen(_hwnd, &screen_point);

            // snap image to memory dc
            BitBlt(hdc_memory, 0, 0, width, height, hdc_source, screen_point.x, screen_point.y, SRCCOPY);

            // get image pixels from memory dc
            bi.biSize = sizeof(BITMAPINFOHEADER);
            bi.biWidth = width;
            bi.biHeight = -(LONG)height;
            bi.biPlanes = 1;
            bi.biBitCount =  32;
            bi.biCompression = BI_RGB;

            GetDIBits(hdc_memory, hbitmap, 0, height, buffer, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

            // release resources
            hbitmap = (HBITMAP)SelectObject(hdc_memory, hbitmap_old);
            DeleteDC(hdc_source);
            DeleteDC(hdc_memory);

            HPALETTE hpal = NULL;
        }

    private:
        /**/
        void _SendKey( ULong key )
        {
            if(_key_ctrl)
            {
                PostMessage(_hwnd, WM_KEYDOWN, key, 0x801E0001);
                PostMessage(_hwnd, WM_KEYUP, key, 0xC01E0001);
            }
            else
                PostMessage(_hwnd, WM_CHAR, key, 0x001E0001);
        }

        /**/
        void _SendVKey( ULong vkey, Bool down )
        {
            if(down)
                PostMessage(_hwnd, WM_KEYDOWN, vkey, 0x001D0001);
            else
                PostMessage(_hwnd, WM_KEYUP, vkey, 0xC01D0001);
        }
    };
}
