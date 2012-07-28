#pragma once
#include <Core/Types.hpp>
#include <windows.h>

namespace Core
{
    /**/
    class MemoryFile
    {
    private:
        HANDLE  _mapping;
        HANDLE  _file;
        Byte*   _memory;
        ULong   _limit;

    public:
        /**/
        MemoryFile():
            _mapping(NULL),
            _file(NULL),
            _limit(0)
        {
        }

        /**/
        ~MemoryFile()
        {
            Close();
        }

        /**/
        Bool Open( ULong size )
        {
            // create temporary file
            _file = CreateFile(SYSTEM_MEMORYFILE_PATH,
                GENERIC_WRITE | GENERIC_READ,
                0,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_TEMPORARY,
                NULL);

            if(_file != INVALID_HANDLE_VALUE)
            {
                // create mapping
                _mapping = CreateFileMapping(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE | SEC_COMMIT,
                    0,
                    size,
                    NULL);

                if(_mapping)
                {
                    // bind to memory
                    _memory = (Byte*)MapViewOfFile(_mapping,
                        FILE_MAP_WRITE,
                        0,
                        0,
                        0);

                    if(_memory)
                    {
                        _limit = size;
                        return true;
                    }

                    CloseHandle(_mapping);
                }

                CloseHandle(_file);
            }

            return false;
        }

         /**/
        void Close()
        {
            if(_memory != NULL)
            {
                UnmapViewOfFile(_memory);
                CloseHandle(_mapping);
                CloseHandle(_file);

                _mapping = NULL;
                _file = NULL;
                _memory = NULL;
                _limit = 0;

                DeleteFile(SYSTEM_MEMORYFILE_PATH);
            }
        }

        /**/
        Byte* operator[]( ULong address )
        {
            assert(_memory);
            assert( address <= _limit );
            return _memory + address;
        }
    };
}