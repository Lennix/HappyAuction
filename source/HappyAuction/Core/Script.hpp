#pragma once
#include <HappyAuction/Root.hpp>
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/State.hpp>
#include <HappyAuction/Enums.hpp>
#include <Diablo/Core/Game.hpp>
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Support.hpp>
#include <Diablo/Type/Item.hpp>
#include <Core/Support/Lua.hpp>
#include <Core/System/System.hpp>

namespace HappyAuction
{
    /**/
    class Script:
        public Lua
    {
    private:
        Game                _game;
        AuctionInterface    _ahi;
        Bool                _active;
        State               _state;
        Index               _instance;

    public:
        /**/
        Script( Index instance ):
            _ahi(_game),
            _active(false),
            _instance(instance)
        {
        }

        /**/
        void Start()
        {
            _active = true;

            try
            {
                // initialize game and auction interface
                if(!_game.Start() || !_ahi.Start())
                    throw EXCEPTION_SCRIPT;

                // sync state
                _StateSync();

                // start lua script
                if(!Lua::Start(SCRIPT_PATH))
                    System::Message(false, EXCEPTION_LUA, Lua::GetError());
            }
            catch(const Char* exception)
            {
                System::Message(false, exception);
            }

            // close user log
            System::Log(LOG_USER, NULL);

            // cleanup
            Stop();
        }

        /**/
        void Stop()
        {
            // stop everything
            _active = false;
            _game.Stop();
            _ahi.Stop();
            Lua::Stop();
        }

    protected:
        /**/
        void _StateSync()
        {
            StateFilters&   filters = _state.filters;
            ULong           global_delay = GAME_GLOBAL_DELAY;

            // disable global delay
            GAME_GLOBAL_DELAY = 0;

            // filters:type
            _ahi.ReadFilterSecondary(filters.type);

            // filters:character
            _ahi.ReadFilterChar(filters.character);

            // filters:rarity
            _ahi.ReadFilterRarity(filters.rarity);

            // filters:stats
            for( Index i = 0; i < AH_PSTAT_LIMIT; i++ )
            {
                StateFiltersStat& stat = filters.stat[i];
                _ahi.ReadFilterStat(i, stat.name, stat.value);
            }

            // filters:level
            _ahi.ReadFilterLevelMin(filters.level_min);
            _ahi.ReadFilterLevelMax(filters.level_max);

            // filters:buyout
            _ahi.ReadFilterBuyout(filters.buyout);

            // filters:unique
            _ahi.ReadFilterUnique(filters.unique);

            GAME_GLOBAL_DELAY = global_delay;
        }

        /**/
        void _StateRestore()
        {
            const StateFilters& filters = _state.filters;
            const StateSearch&  search = _state.search;
            ULong               global_delay = GAME_GLOBAL_DELAY;

            // disable global delay
            GAME_GLOBAL_DELAY = 0;

            // filters:type
            if(*filters.type)
                _ahi.WriteFilterSecondaryAuto(filters.type);

            // filters:character
            if(*filters.character)
                _ahi.WriteFilterChar(filters.character);

            // filters:rarity
            if(*filters.rarity)
                _ahi.WriteFilterRarity(filters.rarity);

            // filters:stats
            for( Index i = 0; i < AH_PSTAT_LIMIT; i++ )
            {
                const StateFiltersStat& stat = filters.stat[i];
                if(*stat.name)
                    _ahi.WriteFilterStat(i, stat.name, stat.value);
            }

            // filters:level
            if(filters.level_min > 0)
                _ahi.WriteFilterLevelMin(filters.level_min);
            if(filters.level_max > 0)
                _ahi.WriteFilterLevelMax(filters.level_max);

            // filters:buyout
            if(filters.buyout > 0)
                _ahi.WriteFilterBuyout(filters.buyout, false);

            // filters:unique
            if(*filters.unique)
                _ahi.WriteFilterUnique(filters.unique);

            // search
            if(search.active && _ahi.ActionSearch())
            {
                // sort
                if(search.sort_id != INVALID_ID && search.sort_count)
                    for( Index i = 0; i < search.sort_count && _ahi.ActionListSort(static_cast<UiId>(search.sort_id)); i++ );

                // restore page
                for( Index i = 0; i < _state.search.page && _ahi.ActionListNextPage(); i++ );
            }

            GAME_GLOBAL_DELAY = global_delay;
        }

        /**/
        Bool _SessionRestore()
        {
            const StateLogin& login = _state.login;

            // relogin check
            if(*login.name && *login.password && _ahi.ActionReLogin(login.name, login.password))
            {
                // restore state
                _StateRestore();
                return true;
            }

            return false;
        }

        /**/
        virtual void _OnInitialized()
        {
            for( Index i = 0; i < SCRIPT_COUNT; i++ )
                _Register(i, SCRIPT_FUNCTIONS[i]);
        }

        /**/
        ULong _OnFunction( Id id )
        {
            ULong pushed = _CallFunction(id);

            // session restore
            _SessionRestore();

            return pushed;
        }

        /**/
        ULong _CallFunction( Id id )
        {
            switch(id)
            {
            //---- AUCTION/SEARCH --------------------------------------------
            // haBid(bid) -> status
            case SCRIPT_HABID:
            case SCRIPT_HAACTIONBID://DEPRECATED
                return _haBid();

            // haBuyout() -> status
            case SCRIPT_HABUYOUT:
            case SCRIPT_HAACTIONBUYOUT://DEPRECATED
                return _haBuyout();

            // haFilterBuyout(amount, randomize) -> status
            // haFilterBuyout() -> buyout
            case SCRIPT_HAFILTERBUYOUT:
                return _haFilterBuyout();

            // haFilterChar(id) -> status
            case SCRIPT_HAFILTERCHAR:
                return _haFilterChar();

            // haFilterLevel(min,  max) -> status
            case SCRIPT_HAFILTERLEVEL:
                return _haFilterLevel();

            // haFilterRarity(id) -> status
            case SCRIPT_HAFILTERRARITY:
                return _haFilterRarity();

            // haFilterStat(index, id, value) -> status
            case SCRIPT_HAFILTERSTAT:
                return _haFilterStat();

            // haFilterStatClear() -> status
            case SCRIPT_HAFILTERSTATCLEAR:
                return _haFilterStatClear();

            // haFilterType(id) -> status
            case SCRIPT_HAFILTERTYPE:
                return _haFilterType();

            // haFilterUnique(name) -> status
            // haFilterUnique() -> name
            case SCRIPT_HAFILTERUNIQUE:
                return _haFilterUnique();

            // haListNext() -> status
            case SCRIPT_HALISTNEXT:
                return _haListNext();

            // haListSelect(index) -> status
            case SCRIPT_HALISTSELECT:
                return _haListSelect();

            // haSearch() -> status
            case SCRIPT_HASEARCH:
            case SCRIPT_HAACTIONSEARCH://DEPRECATED
                return _haSearch();

            // haSortBuyout() -> status
            case SCRIPT_HASORTBUYOUT:
            case SCRIPT_HAACTIONSORTBUYOUT://DEPRECATED
                return _haSort(UI_LBUTTON_SORTBUYOUT);

            // haSortDpsArmor() -> status
            case SCRIPT_HASORTDPSARMOR:
            case SCRIPT_HAACTIONSORTDPSARMOR://DEPRECATED
                return _haSort(UI_LBUTTON_SORTDPSARMOR);

            // haSortTimeLeft() -> status
            case SCRIPT_HASORTTIMELEFT:
                return _haSort(UI_LBUTTON_SORTTIMELEFT);


            //---- AUCTION/SELL ----------------------------------------------
            // haSell(starting, buyout) -> status
            case SCRIPT_HASELL:
            case SCRIPT_HASTASHSELL://DEPRECATED
                return _haSell();

            // haStashNext() -> status
            case SCRIPT_HASTASHNEXT:
                return _haStashNext();

            // haStashSelect(column, row, bag) -> status
            case SCRIPT_HASTASHSELECT:
                return _haStashSelect();


            //---- AUCTION/COMPLETED -----------------------------------------
            // haSendToStash() -> status
            case SCRIPT_HASENDTOSTASH:
                return _haSendToStash();


            //---- ITEM ------------------------------------------------------
            // haItem() -> item[dpsarmor, mbid, buyout, cbid, time, stats, sockets]
            case SCRIPT_HAITEM:
                return _haItem();

            // haItemStat() -> stat[name, value1, value2, value3, value4]
            case SCRIPT_HAITEMSTAT:
                return _haItemStat();


            //---- SETTINGS --------------------------------------------------
            // haGetInstance() -> instance
            case SCRIPT_HAGETINSTANCE:
                return _haGetInstance();

            // haSetGlobalDelay(delay)
            case SCRIPT_HASETGLOBALDELAY:
                return _haSetGlobalDelay();

            // haSetLogin(name, password) -> status
            case SCRIPT_HASETLOGIN:
            case SCRIPT_HARELOGIN://DEPRECATED
            case SCRIPT_HAACTIONRELOGIN://DEPRECATED
                return _haSetLogin();


            //---- UTILITIES -------------------------------------------------
            // haAlert(message)
            case SCRIPT_HAALERT:
                return _haAlert();

            // haBeep()
            case SCRIPT_HABEEP:
                return _haBeep();

            // haLog(message)
            case SCRIPT_HALOG:
                return _haLog();

            // haPrompt(message)
            case SCRIPT_HAPROMPT:
                return _haPrompt();

            // haSleep(delay)
            // haSleep(low, high)
            case SCRIPT_HASLEEP:
                return _haSleep();

            // haUpTime() -> time
            case SCRIPT_HAUPTIME:
                return _haUpTime();


            //----------------------------------------------------------------
            case SCRIPT_HATEST:
                return _haTest();

            case SCRIPT_HALISTITEM:
            case SCRIPT_HALISTITEMSTAT:
            case SCRIPT_HALISTITEMSOCKET:
            case SCRIPT_HASETTINGSLISTDELAY:
                return _haObsolete(id);

            default:
                return 0;
            }
        }

        //---- AUCTION/SEARCH ------------------------------------------------
        /**/
        ULong _haBid()
        {
            Bool status = (_state.search.row > 0) ? _ahi.ActionBid(_state.search.row - 1, _GetStackNumber(1)) : false;
            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haBuyout()
        {
            Bool status = (_state.search.row > 0) ? _ahi.ActionBuyout(_state.search.row - 1) : false;
            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterBuyout()
        {
            Number buyout = _GetStackNumber(1);

            if(buyout)
            {
                Bool randomize = _GetStackBool(2);
                Bool status = _ahi.WriteFilterBuyout(buyout, randomize);

                if(status)
                    _state.filters.buyout = buyout;

                _PushStack(status);
            }
            else
            {
                _ahi.ReadFilterBuyout(buyout);
                _PushStack(buyout);
            }

            return 1;
        }

        /**/
        ULong _haFilterChar()
        {
            const Char* name = _GetStackString(1);
            Bool        status = false;

            if(name && _ahi.WriteFilterChar(name))
            {
                Tools::StrNCpy(_state.filters.character, name, sizeof(_state.filters.character));
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterLevel()
        {
            Number  min = _GetStackNumber(1);
            Bool    status = false;

            if(min >= NUMBER(-1,0) && min <= GAME_LEVEL_MAX && _ahi.WriteFilterLevelMin(min))
            {
                Number max = _GetStackNumber(2);
                if(max == 0)
                    max = min;
                if(max >= NUMBER(-1,0) && max <= GAME_LEVEL_MAX && _ahi.WriteFilterLevelMax(max))
                {
                    _state.filters.level_min = min;
                    _state.filters.level_max = max;
                    status = true;
                }
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterRarity()
        {
            const Char* name = _GetStackString(1);
            Bool        status = false;

            if(name && _ahi.WriteFilterRarity(name))
            {
                Tools::StrNCpy(_state.filters.rarity, name, sizeof(_state.filters.rarity));
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterStat()
        {
            Index       index = _GetStackULong(1) - 1;
            const Char* name = _GetStackString(2);
            Number      value = _GetStackNumber(3);
            Bool        status = false;

            if( index < AH_PSTAT_LIMIT &&
                value <= ITEM_STAT_VALUE_MAX &&
                _ahi.WriteFilterStat(index, name, value))
            {
                StateFiltersStat& stat = _state.filters.stat[index];
                if(name)
                    Tools::StrNCpy(stat.name, name, sizeof(stat.name));
                else
                    *stat.name = 0;
                stat.value = value;
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterStatClear()
        {
            Bool status = true;

            for( Index index = 0; index < AH_PSTAT_LIMIT; index++ )
                status &= _ahi.WriteFilterStat(index, NULL, NUMBER(-1,0));

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterType()
        {
            const Char* name = _GetStackString(1);
            Bool        status = false;

            if(name && _ahi.WriteFilterSecondaryAuto(name))
            {
                Tools::StrNCpy(_state.filters.type, name, sizeof(_state.filters.type));
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterUnique()
        {
            const Char* unique = _GetStackString(1);

            if(unique)
            {
                Bool status = _ahi.WriteFilterUnique(unique);

                if(status)
                    Tools::StrNCpy(_state.filters.unique, unique, sizeof(_state.filters.unique));

                _PushStack(status);
            }
            else
            {
                TextString string;
                _PushStack(_ahi.ReadFilterUnique(string) ? string : "");
            }

            return 1;
        }

        /**/
        ULong _haListNext()
        {
            ULong   list_count;
            Bool    status = false;

            while(_active)
            {
                // read list count
                if(!_ahi.ReadListCount(list_count))
                    break;

                // past list limit
                if(++_state.search.row > list_count)
                {
                    // reset index
                    _state.search.row = 1;

                    // increment page
                    _state.search.page++;

                    // go to next next page
                    if(!_ahi.ActionListNextPage() && !_SessionRestore())
                    {
                        _state.search.row = 0;
                        _state.search.page = 0;
                        break;
                    }
                }

                // read list item and increment index
                if(_ahi.ReadListItem(_state.search.row - 1, _state.item))
                {
                    status = true;
                    break;
                }
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haListSelect()
        {
            Index   index = _GetStackULong(1);
            Bool    status = false;

            // check range
            if(index > 0 && index <= AH_RESULTS_ROW_LIMIT)
            {
                // ground hover to reset duplicate selection
                if(_state.search.row == index)
                    _game.MouseMoveGround();

                // read list item
                if(_ahi.ReadListItem(index - 1, _state.item))
                {
                    // update list index
                    _state.search.row = index;

                    status = true;
                }
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSearch()
        {
            Bool status = false;

            _state.search.active = true;

            if(_ahi.ActionSearch())
            {
                _state.search.row = 0;
                _state.search.page = 0;
                _state.search.sort_id = INVALID_ID;
                _state.search.sort_count = 0;
                status = true;
            }
            else
                status = _SessionRestore();

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSort( UiId id )
        {
            Bool status = false;

            if(_ahi.ActionListSort(id))
            {
                if( id != _state.search.sort_id )
                {
                    _state.search.sort_id = id;
                    _state.search.sort_count = 0;
                }
                _state.search.sort_count++;
                status = true;
            }

            _PushStack(status);
            return 1;
        }


        //---- AUCTION/SELL --------------------------------------------------
        /**/
        ULong _haSell()
        {
            Number  starting = _GetStackNumber(1);
            Number  buyout = _GetStackNumber(2);
            Bool    status = false;

            // must have starting price
            if(starting > 0 && _state.item.IsValid())
            {
                // call sell sequence
                if(_ahi.SellStashItem(_state.stash.column, _state.stash.row, starting, buyout))
                    status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haStashNext()
        {
            Bool status = false;

            // ensure first bag if beginning iteration
            if( _state.stash.column == 0 && _state.stash.row == 0 && _state.stash.bag == 0 )
                _ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1);

            while(_active)
            {
                // next row
                if(_state.stash.row >= AH_STASH_ROWS)
                {
                    _state.stash.row = 0;

                    // next column
                    if(++_state.stash.column >= AH_STASH_COLUMNS)
                    {
                        _state.stash.column = 0;

                        // go to next bag
                        if(++_state.stash.bag >= AH_STASH_BAGS)
                        {
                            _state.stash.bag = 0;
                            break;
                        }

                        _ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1 + _state.stash.bag);
                    }
                }

                // read list item and increment index
                if(_ahi.ReadStashItem(_state.stash.column, _state.stash.row++, _state.item))
                {
                    status = true;
                    break;
                }
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haStashSelect()
        {
            Index   column = _GetStackULong(1) - 1;
            Index   row = _GetStackULong(2) - 1;
            Index   bag = _GetStackULong(3) - 1;
            Bool    status = false;

            // check range
            if(column < AH_STASH_COLUMNS && row < AH_STASH_ROWS && bag < AH_STASH_BAGS)
            {
                // select tab
                if(_ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1 + bag))
                {
                    // select and read stash item
                    if(_ahi.ReadStashItem(column, row, _state.item))
                    {
                        // update stash position
                        _state.stash.column = column;
                        _state.stash.row = row;
                        _state.stash.bag = bag;
                        status = true;
                    }
                }
            }

            _PushStack(status);
            return 1;
        }

        //---- AUCTION/COMPLETED----------------------------------------------
        /**/
        ULong _haSendToStash()
        {
            Bool status = _ahi.ActionSendToStash();
            _PushStack(status);
            return 1;
        }


        //---- ITEM ----------------------------------------------------------
        /**/
        void _PushItemStat( const Item::Stat& stat, Bool socket )
        {
            const Item::ValueCollection& values = stat.values;
            TextString  string;
            Index       index;

            // name
            _SetTable("name", "");//DEPRECATED
            _SetTable("text", stat.text);

            // gem rank and type
            if(socket)
            {
                GemTypeId   type = GEM_TYPE_EMPTY;
                ULong       rank = 0;

                Support::GetGemInfo(type, rank, stat);

                _SetTable("gem", ITEM_GEM_TYPE_IDS.FindName(string, type) ? string : "");
                _SetTable("rank", rank);
            }

            // values
            for( index = 0; index < values.GetLimit(); index++ )
            {
                sprintf(string, "value%u", index + 1);
                _SetTable(string, (index < values.GetCount()) ? values[index] : 0);
            }
        }

        /**/
        template<typename COLLECTION>
        void _PushItemStats( const COLLECTION& stats, Bool socket )
        {
            for( Index i = 0; i < stats.GetCount(); i++ )
            {
                _PushTable(i + 1);
                _PushItemStat(stats[i], socket);
                _PopTable();
            }
        }

        /**/
        ULong _haItem()
        {
            _PushTable(0);

            // fields
            _SetTable("dps", _state.item.dpsarmor);
            _SetTable("armor", _state.item.dpsarmor);
            _SetTable("mbid", _state.item.max_bid);
            _SetTable("cbid", _state.item.current_bid);
            _SetTable("buyout", _state.item.buyout);
            _SetTable("rtime", _state.item.rtime);
            _SetTable("xtime", _state.item.xtime);
            _SetTable("name", _state.item.name);
            _SetTable("id", _state.item.id);
            _SetTable("rarity", _state.item.rarity);
            _SetTable("type", _state.item.type);

            // objects
            _PushTable("stats");
            _PushItemStats(_state.item.stats, false);
            _PopTable();

            _PushTable("sockets");
            _PushItemStats(_state.item.sockets, true);
            _PopTable();

            return 1;
        }

        /**/
        ULong _haItemStat()
        {
            _PushTable(0);

            // find stat
            const Item::Stat* stat = _state.item.FindStat(_GetStackString(1));

            // set stat found else use empty stat
            _PushItemStat(stat ? *stat : Item::Stat::GetDefault(), false);

            return 1;
        }

        //---- SETTINGS ------------------------------------------------------
        /**/
        ULong _haGetInstance()
        {
            _PushStack(_instance + 1);
            return 1;
        }

        /**/
        ULong _haSetGlobalDelay()
        {
            GAME_GLOBAL_DELAY = Tools::Conform<ULong>(_GetStackULong(1), 0, GAME_GLOBAL_DELAY_MAX);
            return 0;
        }

        /**/
        ULong _haSetLogin()
        {
            const Char* name = _GetStackString(1);
            const Char* password = _GetStackString(2);
            Bool        status = false;

            if(name && password)
            {
                StateLogin& login = _state.login;
                Tools::StrNCpy(login.name, name, sizeof(login.name));
                Tools::StrNCpy(login.password, password, sizeof(login.password));
                status = true;
            }

            _PushStack(status);
            return 1;
        }


        //---- UTILITIES -----------------------------------------------------
        /**/
        ULong _haAlert()
        {
            const Char* message = _GetStackString(1);

            if(message)
                System::Message(false, "%s", message);

            return 0;
        }

        /**/
        ULong _haBeep()
        {
            MessageBeep(MB_ICONEXCLAMATION);
            return 0;
        }

        /**/
        ULong _haLog()
        {
            const Char* message = _GetStackString(1);

            if(message && _instance == 0)
                System::Log(LOG_USER, "%s\n", message);

            return 0;
        }

        /**/
        ULong _haPrompt()
        {
            const Char* message =  _GetStackString(1);
            Bool        status = false;

            if(message)
                status = System::Message(true, "%s", message);

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSleep()
        {
            _game.Sleep(_GetStackULong(1), _GetStackULong(2));
            return 0;
        }

        /**/
        ULong _haUpTime()
        {
            _PushStack(static_cast<ULong>(::GetTickCount()));
            return 1;
        }


        //--------------------------------------------------------------------
        /**/
        ULong _haTest()
        {
            return 0;
        }

        /**/
        ULong _haObsolete(Id id)
        {
            System::Message(false, EXCEPTION_OBSOLETED, SCRIPT_FUNCTIONS[id]);
            Lua::Stop(false);
            return 0;
        }
    };
}
