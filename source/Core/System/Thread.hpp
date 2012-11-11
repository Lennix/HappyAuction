#pragma once
#include <Core/Types.hpp>

namespace Core
{
    /**/
    struct Runnable
    {
        virtual void Run() {}
    };

    /**/
    class Thread:
        public Runnable
    {
    private:
        HANDLE      _handle;
        Runnable*   _runnable;
        ULong       _stack_size;

    public:
        /**/
        Thread( ULong stack_size = 0 ):
            _handle(NULL),
            _stack_size(stack_size)
        {
            _runnable = this;
        }

        /**/
        Thread( Runnable& runnable, ULong stack_size = 0 ):
            _handle(NULL),
            _runnable(&runnable),
            _stack_size(stack_size)
        {
        }

        /**/
        ~Thread()
        {
            CloseHandle(_handle);
        }

        /**/
        void Start()
        {
            if(_handle != NULL)
            {
                CloseHandle(_handle);
                _handle = NULL;
            }
            _handle = CreateThread(NULL, _stack_size, (LPTHREAD_START_ROUTINE)_ThreadWrapper, (void*)_runnable, 0, NULL);
            assert(_handle);
        }

        /**/
        void Wait()
        {
            WaitForSingleObject(_handle, INFINITE);
        }

        /**/
        static void Sleep( ULong ms )
        {
            ::Sleep(static_cast<DWORD>(ms));
        }

    private:
        /**/
        static DWORD _ThreadWrapper( Runnable& runnable )
        {
            runnable.Run();
            return 0;
        }
    };
}
