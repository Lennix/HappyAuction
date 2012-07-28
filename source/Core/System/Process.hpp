#pragma once
#include <Core/Array.hpp>
#include <Core/System/Window.hpp>
#include <Psapi.h>

namespace Core
{
    /**/
    class Process
    {
    public:
        static const ULong ALIGNMENT = 4;

    public:
        struct Link
        {
            ULong   offset;
        };

        typedef Array<Link>     Chain;
        typedef Chain::Iterator ChainIterator;

    private:
        static const ULong _READABLE_BITS = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY;

    protected:
        HANDLE      _handle;
        ULong       _low;
        ULong       _high;

    public:
        /**/
        Process():
            _handle(NULL),
            _low(0x00400000),
            _high(0x7fffffff)
        {
        }

        /**/
        ~Process()
        {
            if(_handle != NULL)
                CloseHandle(_handle);
        }

        /**/
        void SetLow( ULong low )
        {
            _low = low;
        }
        ULong GetLow() const
        {
            return _low;
        }

        void SetHigh( ULong high )
        {
            _high = high;
        }
        ULong GetHigh() const
        {
            return _high;
        }

        /**/
        ULong GetBaseAddress( const Char* name ) 
        {
            DWORD       size;
            HMODULE     modules[32]; 
            TextString  enum_name;
            EnumProcessModules(_handle, modules, sizeof(modules), &size);

            for( Index i = 0; i < (size / sizeof(modules)); i++ )
            {
                if(GetModuleBaseName(_handle, modules[i], enum_name, sizeof(enum_name)) && strcmp(name, enum_name) == 0)
                    return (DWORD)modules[i];
            }

            return 0;
        }

        /**/
        ULong ReadChainAddress( ULong address, const Chain& chain ) 
        {
            for( ChainIterator i = chain.Begin(); i != chain.End(); ++i )
                if(!ReadMemory(address + i->offset, &address, sizeof(address)))
                    return false;

            return address;
        }

        /**/
        Bool QueryMemory( ULong& address, ULong& length )
        {
            MEMORY_BASIC_INFORMATION    mbi;
            Bool                        status;
            
            // get beginning
            for( status = false; VirtualQueryEx(_handle, (PVOID)(address+1), &mbi, sizeof(mbi)); address += mbi.RegionSize)
            {
                address = (ULong)mbi.BaseAddress;
                status = true;
                if((mbi.State & MEM_COMMIT) && (mbi.Protect & _READABLE_BITS) && !(mbi.Protect & PAGE_GUARD))
                    break;
            }

            // first query must have succeeded
            if(!status)
                return false;

            // set next address
            ULong current = address + mbi.RegionSize;

            // query continuous sequence
            for(; VirtualQueryEx(_handle, (PVOID)current, &mbi, sizeof(mbi)) &&
                current == (ULong)mbi.BaseAddress &&
                (mbi.State & MEM_COMMIT) && (mbi.Protect & _READABLE_BITS) && !(mbi.Protect & PAGE_GUARD);
                current += mbi.RegionSize );

            length = current - address;

            return true;
        }

        /**/
        Bool ReadMemory( ULong address, void* memory, ULong count )
        {
            return ReadProcessMemory(_handle, (void*)address, memory, count, 0) == TRUE;
        }

        Bool WriteMemory( ULong address, const void* memory, ULong count )
        {
            return WriteProcessMemory(_handle, (void*)address, memory, count, 0) == TRUE;
        }

        Bool WriteByte( ULong address, Byte byte )
        {
            return WriteProcessMemory(_handle, (void*)address, &byte, 1, 0) == TRUE;
        }

        /**/
        Bool FromWindow( const Window& window )
        {
            DWORD process_id = 0;
            
            GetWindowThreadProcessId(window.GetHandle(), &process_id);
            _handle = OpenProcess(
                PROCESS_QUERY_INFORMATION|
                PROCESS_VM_OPERATION|
                PROCESS_VM_READ|
                PROCESS_VM_WRITE,
                FALSE, process_id);

            return (_handle != NULL);
        }

        /**/
        Bool IsPossiblePointer( ULong value )
        {
            return (value >= _low && value <= _high && (value % ALIGNMENT)==0);
        }
    };
}
