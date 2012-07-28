#pragma once
#include <Core/Root.hpp>

namespace Core
{
    /**/
    template<typename TYPE>
    class LocalList
    {
    public:
        /**/
        class Node
        {
            friend class LocalList;

        private:
            TYPE* _next;
            TYPE* _last;

        protected:
            /**/
            Node():
                _next(NULL),
                _last(NULL)
            {
            }

        public:
            /**/
            inline TYPE* GetNext() const
            {
                return _next;
            }

            /**/
            inline TYPE* GetLast() const
            {
                return _last;
            }
        };

    public:
        /**/
        template<typename ITYPE>
        class BaseIterator
        {
        public:
            /**/
            BaseIterator( TYPE* node ):
                _node(node)
            {}

            /**/
            inline ITYPE& operator*() const
            {
                assert(_node != NULL);
                return *_node;
            }

            /**/
            inline ITYPE* operator->()
            {
                return _node;
            }

            /**/
            inline operator ITYPE*() const
            {
                return _node;
            }

            /**/
            inline operator ITYPE&() const
            {
                return *_node;
            }

            /* ++i */
            inline BaseIterator& operator++()
            {
                assert(_node != NULL);
                _node = _node->GetNext();
                return *this;
            }

            /* i++ */
            inline BaseIterator operator++(int)
            {
                BaseIterator temp = *this;
                assert(_node != NULL);
                _node = _node->GetNext();
                return temp;
            }

            /* --i */
            inline BaseIterator& operator--()
            {
                assert(_node != NULL);
                _node = _node->GetLast();
                return *this;
            }

            /* i-- */
            inline BaseIterator operator--(int)
            {
                BaseIterator temp = *this;
                assert(_node != NULL);
                _node = _node->GetLast();
                return temp;
            }

        public:
            TYPE* _node;
        };

        /**/
        typedef BaseIterator<TYPE>          Iterator;
        typedef BaseIterator<const TYPE>    ConstIterator;

    public:
        /**/
        LocalList():
            _begin(NULL),
            _end(NULL)
        {
        }

        /**/
        inline Iterator Begin() const
        {
            return Iterator(_begin);
        }
        inline Iterator BeginConst() const
        {
            return ConstIterator(_begin);
        }

        /**/
        inline Iterator End() const
        {
            return Iterator(NULL);
        }
        inline Iterator EndConst() const
        {
            return ConstIterator(NULL);
        }

        /**/
        inline Iterator ReverseBegin() const
        {
            return Iterator(_end);
        }

        /**/
        inline Iterator ReverseEnd() const
        {
            return Iterator(NULL);
        }

        /**/
        inline Bool IsEmpty() const
        {
            return (_begin == NULL);
        }

        /**/
        inline void Empty()
        {
            _begin = NULL;
            _end = NULL;
        }

        /**/
        void Push( TYPE& node )
        {
            // if empty make begin
            if( _begin == NULL )
            {
                node._last = NULL;
                node._next = NULL;
                _begin = _end = &node;
            }
            // else append to last and update new last
            else
            {
                node._last = _end;
                node._next = NULL;
                _end = _end->_next = &node;
            }
        }

        /**/
        TYPE* Pop()
        {
            return Remove(ReverseBegin());
        }

        /**/
        void Insert( Iterator iterator, TYPE& node )
        {
            if(iterator._node == NULL || _begin == NULL)
                Push(node);
            else
            {
                if(iterator == _begin)
                {
                    node._last = NULL;
                    node._next = _begin;
                    _begin = _begin->_last = &node;
                }
                else
                {
                    TYPE* follower = iterator._node;
                    node._last = follower->_last;
                    node._next = follower;
                    follower->_last = node._last->_next = &node;
                }
            }
        }

        /**/
        TYPE* Remove( Iterator iterator )
        {
            TYPE* node = iterator._node;

            // is begin
            if( node == _begin )
            {
                // is also end (solo)
                if( node == _end )
                    _begin = _end = NULL;
                // has next
                else
                    _begin = node->_next;
            }
            // is end
            else if( node == _end )
            {
                _end = _end->_last;
                _end->_next = NULL;
            }
            // is middle
            else
            {
                TYPE* last = node->_last;
                TYPE* next = node->_next;

                last->_next = next;
                next->_last = last;
            }

            return node;
        }

        /**/
        template<typename FTYPE>
        Iterator Find( const FTYPE& match ) const
        {
            Iterator i = Begin();
            for(; i != End() && *i != match; i++ );
            return i;
        }

    private:
        TYPE*   _begin;
        TYPE*   _end;
    };
}
