#pragma once
#include <Core/Root.hpp>
#include <Lua/lua.h>
#include <Lua/lualib.h>
#include <Lua/lauxlib.h>

namespace HappyAuction
{
    /**/
    class Lua
    {
    private:
        lua_State*  _lua;
        TextString  _error;
        Bool        _active;

    public:
        /**/
        Lua():
            _lua(NULL),
            _active(false)
        {
            *_error = 0;
        }

        /**/
        ~Lua()
        {
            Stop();
        }

        /**/
        const Char* GetError() const
        {
            return _error;
        }

        /**/
        Bool Start( const Char* path )
        {
            Bool status = false;

            // initialize
            _active = true;
            _lua = luaL_newstate();
            lua_SetActive(_lua, 1);

            if(_lua != NULL)
            {
                // add standard libs
                luaL_openlibs(_lua);

                // notify initialized
                _OnInitialized();

                try
                {
                    // load file
                    if(luaL_loadfile(_lua, path) == 0)
                    {
                        // execute
                        status = (lua_pcall(_lua, 0, LUA_MULTRET, 0) == 0);

                        // if stopped manually ignore any lua status
                        if(!lua_GetActive(_lua))
                            status = true;
                    }
                }
                catch(int){}

                // get error
                if(!status)
                    Tools::StrNCpy(_error, lua_tostring(_lua, -1), sizeof(_error));

                // cleanup
                lua_close(_lua);
                _lua = NULL;
            }

            _active = false;
            return status;
        }

        /**/
        void Stop()
        {
            if(_active && _lua != NULL)
            {
                lua_SetActive(_lua, 0);

                while(_active)
                    Sleep(50);
            }
        }

    protected:
        /**/
        virtual ULong _OnFunction( Id id ) = 0;
        virtual void _OnInitialized() {}

        /**/
        Bool _Register( Id id, const Char* name )
        {
            lua_pushlightuserdata(_lua, this);
            lua_pushinteger(_lua, id);
            lua_pushcclosure(_lua, _OnClosure, 2);
            lua_setglobal(_lua, name);

            return true;
        }

        /**/
        const Bool _GetStackBool( Index index )
        {
            return lua_toboolean( _lua, index ) != 0;
        }

        const Long _GetStackLong( Index index )
        {
            return lua_tointeger( _lua, index );
        }

        const ULong _GetStackULong( Index index )
        {
            return lua_tounsigned( _lua, index );
        }

        const Char* _GetStackString( Index index )
        {
            return lua_tostring( _lua, index );
        }

        /**/
        void _PushStack( Bool boolean )
        {
            lua_pushboolean( _lua, boolean );
        }

        void _PushStack( Long value )
        {
            lua_pushinteger( _lua, value );
        }

        void _PushStack( ULong value )
        {
            lua_pushunsigned( _lua, value );
        }

        void _PushStack( const Char* string )
        {
            lua_pushstring( _lua, string );
        }

        /**/
        template<typename KEY>
        void _PushTable( KEY key=0 )
        {
            if(key)
                _PushStack(key);
            lua_newtable(_lua);
        }

        void _PopTable()
        {
            lua_settable(_lua, -3);
        }

        template<typename KEY, typename VALUE>
        void _SetTable( KEY key, VALUE value )
        {
            _PushStack(key);
            _PushStack(value);
            lua_settable(_lua, -3);
        }

    private:
        /**/
        static int _OnClosure( lua_State* lua )
        {
            Lua*    object = (Lua*)lua_touserdata(lua, lua_upvalueindex(1));
            Id      id = lua_tointeger(lua, lua_upvalueindex(2));

            return object->_OnFunction(id);
        }
    };
}
