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
        void Focus()
        {
            SetForegroundWindow(_hwnd);
        }

        /**/
        void SendMouseButton( ULong x, ULong y )
        {
            SendMouseMove(x, y);

            LPARAM lparam = (x | (y << 16));
            PostMessage(_hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lparam);
            PostMessage(_hwnd, WM_LBUTTONUP, 0, lparam);

            /*
            INPUT input[2] = {0};

            input[0].type = INPUT_MOUSE;
            input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            input[1].type = INPUT_MOUSE;
            input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(2, input, sizeof(INPUT));
            */
        }

        /**/
        void SendMouseMove( ULong x, ULong y )
        {
            POINT screen_point = { x, y };

            // get screen coordinates
            ClientToScreen(_hwnd, &screen_point);

            // set cursor position
            SetCursorPos(screen_point.x, screen_point.y);
        }

        /**/
        void SendChar( Char c )
        {
            _SendKey(c, false);
        }

        /**/
        void SendInputKeys( const Char* text, Bool specials )
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
                        _SendKey(VK_CONTROL, true, !_key_ctrl);
                        break;

                    case 'D':
                        _SendKey(VK_DELETE, true);
                        _SendKey(VK_DELETE, true, true);
                        break;

                    default:
                        SendChar(c);
                    }
                }
                else
                {
                    if(specials && c == '^')
                        special = true;
                    else
                        SendChar(c);
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
        void _SendKey( ULong key, Bool extended, Bool up=false )
        {
            if(extended)
            {
                if(up)
                    PostMessage(_hwnd, WM_KEYUP, key, 0xC01D0001);
                else
                    PostMessage(_hwnd, WM_KEYDOWN, key, 0x001D0001);
            }
            else
            {
                if(_key_ctrl)
                {
                    PostMessage(_hwnd, WM_KEYDOWN, key, 0x801E0001);
                    PostMessage(_hwnd, WM_KEYUP, key, 0xC01E0001);
                }
                else
                    PostMessage(_hwnd, WM_CHAR, key, 0x001E0001);
            }

            /*
            //TODO: interferes with windows hook
            INPUT input = {0};

            input.type = INPUT_KEYBOARD;
            input.ki.dwFlags = (extended * KEYEVENTF_EXTENDEDKEY) | (up * KEYEVENTF_KEYUP);
            input.ki.wVk = extended ? key : VkKeyScan(key);

            SendInput(1, &input, sizeof(INPUT));
            */
        }
    };
}
