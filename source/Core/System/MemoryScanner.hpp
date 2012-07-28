#pragma once
#include <Core/LocalList.hpp>
#include <Core/System/MemoryFile.hpp>
#include <Core/System/Process.hpp>

namespace Core
{
    /**/
    class MemoryScanner
    {
    public:
        struct IScanHandler
        {
            virtual Bool OnScan( ULong address, const Byte* memory ) = 0;
        };

    private:
        struct Segment:
            public LocalList<Segment>::Node
        {
            ULong   address;
            ULong   length;
            Byte*   memory;
        };

        typedef LocalList<Segment>          SegmentCollection;
        typedef SegmentCollection::Iterator SegmentIterator;

    private:
        Process&            _process;
        MemoryFile          _memory_file;
        LocalList<Segment>  _segments;

    public:
        /**/
        MemoryScanner( Process& process ):
            _process(process)
        {
        }

        /**/
        ~MemoryScanner()
        {
            End();
        }

        /**/
        Bool Begin()
        {
            ULong length;

            if(!_memory_file.Open(_process.GetHigh() - _process.GetLow()))
                return false;

            for( ULong address = _process.GetLow(); _process.QueryMemory(address, length) && (address + length) <= _process.GetHigh(); address += length )
            {
                Byte* memory = _memory_file[address - _process.GetLow()];

                if(_process.ReadMemory((ULong)address, memory, length))
                {
                    Segment& segment = *(new Segment);

                    segment.address = address;
                    segment.length = length;
                    segment.memory = memory;

                    _segments.Push(segment);
                }
            }

            return true;
        }

        /**/
        Bool Scan( IScanHandler& handler )
        {
            for( SegmentIterator i = _segments.Begin(); i != _segments.End(); ++i )
            {
                const Byte* memory = i->memory;
                ULong       address = i->address;
                ULong       end = address + i->length;

                for( ; address < end; address += sizeof(ULong), memory += sizeof(ULong))
                    if(!handler.OnScan( address, memory ))
                        return false;
            }

            return true;
        }

        /**/
        void End()
        {
            _memory_file.Close();
            for( Segment* segment; (segment = _segments.Pop()); )
                delete segment;
        }

        /**/
        template<typename TYPE>
        TYPE* Access( ULong address, ULong limit=sizeof(TYPE) )
        {
            if( address < _process.GetLow() || (address + limit) > _process.GetHigh() )
                return NULL;

            return reinterpret_cast<TYPE*>(_memory_file[address - _process.GetLow()]);
        }
    };
}
