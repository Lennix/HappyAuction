#pragma once
#include <Core/System/Process.hpp>

namespace Core
{
    /**/
    class MemoryScanner
    {
    public:
        /**/
        struct IScanHandler
        {
            virtual Bool OnScan( ULong address, const Byte* memory, ULong length ) = 0;
        };

    private:
        Process& _process;

    public:
        /**/
        MemoryScanner( Process& process ):
            _process(process)
        {
        }

        /**/
        Bool Scan( IScanHandler& handler )
        {
            Byte*   buffer = new Byte[0];
            ULong   buffer_length = 0;
            ULong   query_length;
            Bool    status = true;

            for( ULong address = _process.GetLow();
                status &&
                _process.QueryMemory(address, query_length) &&
                (address + query_length) <= _process.GetHigh();
                address += query_length )
            {
                // update buffer
                if(query_length > buffer_length)
                {
                    delete[] buffer;
                    buffer = new Byte[query_length];
                    buffer_length = query_length;
                }

                // read memory
                if(_process.ReadMemory((ULong)address, buffer, query_length))
                {
                    // iterator scan handler
                    for( ULong offset = 0; offset < query_length; offset += Process::ALIGNMENT )
                    {
                        if(!handler.OnScan( address + offset, buffer + offset, query_length - offset ))
                        {
                            status = false;
                            break;
                        }
                    }
                }
            }

            delete[] buffer;

            return status;
        }
    };
}
