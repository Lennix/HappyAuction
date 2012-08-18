#pragma once
#include <Core/Types.hpp>
#include <algorithm>

namespace Core
{
    /**/
    template<typename TYPE>
    class Array
    {
    public:
        typedef TYPE Type;

    protected:
        TYPE*   _memory;
        ULong   _count;
        ULong   _limit;

    public:
        typedef TYPE*   Iterator;
        typedef Array   ArrayType;

    public:
        /**/
        Array( Long null ):
            _memory(NULL),
            _count(0),
            _limit(0)
        {
        }

        /**/
        Array( const TYPE* memory, ULong count ):
            _memory(const_cast<TYPE*>(memory)),
            _count(count),
            _limit(count)
        {
        }

        /**/
        Array( const TYPE* memory, ULong count, ULong limit ):
            _memory(const_cast<TYPE*>(memory)),
            _count(count),
            _limit(limit)
        {
            assert(count <= limit);
        }

        /**/
        inline const TYPE& operator[]( Index index ) const
        {
            assert(index < _count);
            return _memory[index];
        }

        inline TYPE& operator[]( Index index )
        {
            assert(index < _count);
            return _memory[index];
        }

        /**/
        inline const TYPE* GetMemory() const
        {
            return _memory;
        }

        /**/
        inline void SetCount( ULong count )
        {
            _count = count;
        }
        inline ULong GetCount() const
        {
            return _count;
        }
        inline ULong GetLimit() const
        {
            return _limit;
        }

        /**/
        inline Bool IsEmpty() const
        {
            return _count == 0;
        }
        inline Bool IsFull() const
        {
            return _count == _limit;
        }

        /**/
        inline Iterator Begin() const
        {
            return _memory;
        }
        inline Iterator End() const
        {
            return _memory + _count;
        }

        /**/
        inline Index IndexOf( Iterator iterator ) const
        {
            return (iterator - _memory);
        }

        /**/
        inline void Push( const TYPE& value )
        {
            assert(_count < _limit);
            _memory[_count++] = value;
        }

        inline TYPE& Push()
        {
            assert(_count < _limit);
            return _memory[_count++];
        }

        inline const TYPE& Pop()
        {
            assert(_count > 0);
            return _memory[--_count];
        }

        /**/
        inline void Empty()
        {
            _count = 0;
        }

        /**/
        inline Bool operator != ( const Array<TYPE>& other ) const
        {
            if( _count != other._count )
                return true;
            for( Index i = 0; i < _count; ++i )
                if( _memory[i] != other._memory[i] )
                    return true;
            return false;
        }

        /**/
        inline void Sort()
        {
            std::sort(Begin(), End());
        }

        /**/
        inline Iterator BinarySearch( const TYPE& value ) const
        {
            return std::lower_bound(Begin(), End(), value);
        }

        /**/
        inline Iterator FlatSearch( const TYPE& value ) const
        {
            Iterator i = Begin();
            for(; i != End() && *i != value; ++i );
            return i;
        }

        /**/
        inline void MemoryZero()
        {
            memset(_memory, 0, sizeof(TYPE) * _limit);
        }

        /**/
        inline void MemorySet( const TYPE& value )
        {
            for( Iterator i = Begin(); i != End() && *i != value; ++i )
                *i = value;
        }

        /**/
        template<class COLLECTION>
        void CopyCollection( const COLLECTION& other )
        {
            _count = 0;
            for(typename COLLECTION::Iterator i = other.Begin(); i != other.End() && _count < _limit; ++i)
                Push(*i);
        }

        /**/
        static const ArrayType& GetDummy()
        {
            static ArrayType dummy(0);
            return dummy;
        }
    };

    /**/
    template<typename TYPE, unsigned LIMIT>
    class FixedArray:
        public Array<TYPE>
    {
    private:
        TYPE _fixed_memory[LIMIT];

    public:
        typedef FixedArray FixedArrayType;

    public:
        /**/
        FixedArray():
            Array<TYPE>(_fixed_memory, 0, LIMIT)
        {
        }

        /**/
        FixedArray( ULong count ):
            Array<TYPE>(_fixed_memory, count, LIMIT)
        {
        }

        /**/
        FixedArray( const FixedArray& copy ):
            Array<TYPE>(_fixed_memory, 0, LIMIT)
        {
            assert(copy.GetCount() <= LIMIT);
            Array::CopyCollection(copy);
        }

        /**/
        void operator = ( const FixedArray& copy )
        {
            assert(copy.GetCount() <= LIMIT);
            _memory = _fixed_memory;
            Array::CopyCollection(copy);
        }
    };

    /**/
    typedef Array<ULong> ULongArray;
}
