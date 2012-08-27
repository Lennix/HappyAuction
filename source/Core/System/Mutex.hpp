#pragma once
#include <Core/Root.hpp>
#include <windows.h>

namespace Core
{
    /**/
    class Mutex
    {
    private:
        HANDLE _handle;

    public:
        /**/
        Mutex()
        {
            _handle = CreateMutex(NULL, FALSE, NULL);
            assert(_handle);
        }

        /**/
        ~Mutex()
        {
            CloseHandle(_handle);
        }

        /**/
        void Lock() const
        {
            WaitForSingleObject(_handle, INFINITE);
        }

        /**/
        void UnLock() const
        {
            ReleaseMutex(_handle);
        }
    };
}
