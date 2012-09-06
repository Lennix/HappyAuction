//MUTEX AROUND EVERYTHING
#pragma once
#include <Core/Constants.hpp>
#include <Core/Type/Array.hpp>
#include <Core/Types.hpp>
#include <Core/System/Mutex.hpp>
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

        struct _EnumWindowParameters
        {
            const Char*     search_name;
            const Char*     search_class;
            HWND            found_hwnd;
            Bool            unique;
        };

        typedef FixedArray<HWND, WINDOW_ACTIVE_LIMIT>   ActiveCollection;
        typedef ActiveCollection::Iterator              ActiveIterator;

    private:
        HWND    _hwnd;
        Bool    _key_ctrl;
        ULong   _width;
        ULong   _height;

        static ActiveCollection _actives;
        static Mutex            _mutex;

    public:
        /**/
        Window():
            _hwnd(NULL),
            _key_ctrl(false)
        {
        }

        /**/
        Bool Open( const Char* name, const Char* id, Bool unique=true )
        {
            _EnumWindowParameters param = { name, id, NULL, unique };
            assert(_hwnd == NULL);

            // lock
            _mutex.Lock();

            // fail if active full
            if(!_actives.IsFull())
            {
                // enum windows
                EnumWindows( _EnumWindowsProc, (LPARAM)&param );

                // success if hwnd found
                _hwnd = param.found_hwnd;
            }

            // unlock
            _mutex.UnLock();

            return (_hwnd != NULL);
        }

        void Close()
        {
            if(_hwnd)
            {
                // remove hwnd from actives
                _mutex.Lock();
                _actives.PopSwap(_actives.IndexOf(_actives.FlatSearch(_hwnd)));
                _mutex.UnLock();

                // null handle
                _hwnd = NULL;
            }
        }

        /**/
        HWND GetHandle() const
        {
            return _hwnd;
        }

        /**/
        Bool IsActive() const
        {
            return _hwnd && IsWindow(_hwnd) == TRUE;
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
        void SendMouseButton( ULong x, ULong y )
        {
            //SendMouseMove(x, y, false);

            LPARAM lparam = (x | (y << 16));
            PostMessage(_hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lparam);
            PostMessage(_hwnd, WM_LBUTTONUP, 0, lparam);
        }

        /**/
        void SendMouseMove( ULong x, ULong y, Bool direct )
        {
            if(direct)
            {
                POINT screen_point = { x, y };

                // get screen coordinates
                ClientToScreen(_hwnd, &screen_point);

                // set cursor position
                SetCursorPos(screen_point.x, screen_point.y);
            }
            else
            {
                LPARAM lparam;

                lparam = (x | (y << 16));
                PostMessage(_hwnd, WM_MOUSEMOVE, 0, lparam);

                lparam = (HTCLIENT | (WM_MOUSEMOVE << 16));
                PostMessage(_hwnd, WM_SETCURSOR, (WPARAM)_hwnd, lparam);

            }
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

                    case 'E':
                        _SendKey(VK_ESCAPE, true);
                        _SendKey(VK_ESCAPE, true, true);
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
        Bool SetDimensions( ULong x, ULong y, ULong width, ULong height )
        {
            RECT rect;

            // get current window dimensions
            if(!GetWindowRect(_hwnd, &rect))
                return false;

            // convert from client to window dimensions
            _width = width + (rect.right - rect.left) - _width;
            _height = height + (rect.bottom - rect.top) - _height;

            // move/resize
            if(MoveWindow(_hwnd, x, y, _width, _height, TRUE) != TRUE)
                return false;
            PostMessage(_hwnd, WM_EXITSIZEMOVE, 0, 0);

            // update dimensions
            return RefreshDimensions();
        }

        /**/
        void CaptureScreen( Color* buffer, ULong x, ULong y, ULong width, ULong height )
        {
            //TODO: something caused crash here!
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
        static BOOL CALLBACK _EnumWindowsProc( HWND hwnd, LPARAM lparam )
        {
            _EnumWindowParameters&  param = *reinterpret_cast<_EnumWindowParameters*>(lparam);
            TextString              class_name;

            // ignore if unique requested and already active
            if(param.unique && _actives.FlatSearch(hwnd) != _actives.End())
                return TRUE;

            // compare class name
            if( GetClassName(hwnd, class_name, sizeof(class_name)) && strcmp(param.search_class, class_name) == 0 )
            {
                param.found_hwnd = hwnd;
                _actives.Push(hwnd);
                return FALSE;
            }

            return TRUE;
        }

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
        }
    };
}
