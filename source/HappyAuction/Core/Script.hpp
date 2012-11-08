#pragma once
#include <HappyAuction/Root.hpp>
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/State.hpp>
#include <HappyAuction/Enums.hpp>
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Game.hpp>
#include <Diablo/Core/Locale.hpp>
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
        Bool                _paused;
        State               _state;
        Index               _instance;
        FILE*               _log[APPLICATION_APPLET_LIMIT];

    public:
        /**/
        Script( Index instance ):
            _ahi(_game),
            _active(false),
            _paused(false),
            _instance(instance)
        {
            Tools::MemZero(_log, ACOUNT(_log));
        }

        /**/
        void Start()
        {
            // reset state
            _active = true;
            _paused = false;
            _state = State();
            _game.SetOverrideOptions(0);

            try
            {
                // initialize game and auction interface
                if(!_game.Start() || !_ahi.Start())
                    throw EXCEPTION_SCRIPT;

                // set direct input if in focus
                if(_game.GetWindow().HasFocus())
                    _game.SetOverrideOptions(Game::INPUT_DIRECT);

                // sync state
                _StateSync();

                // start lua script
                if(!Lua::Start(SCRIPT_MAIN_PATH))
                    System::Message(false, EXCEPTION_LUA, Lua::GetError());
            }
            catch(const Char* exception)
            {
                System::Message(false, exception);
            }

            // cleanup
            Stop();
        }

        /**/
        void Stop()
        {
            FILE*& log = _log[_instance];

            // close logs
            if(log != NULL)
            {
                fclose(log);
                log = NULL;
            }
            if(_instance == 0)
                System::Log(NULL);

            // stop everything
            _active = false;
            _game.Stop();
            _ahi.Stop();
            Lua::Stop();
        }

        /**/
        void Pause( Bool enable )
        {
            _paused = enable;
        }

        Bool IsPaused() const
        {
            return _paused;
        }

    protected:
        /**/
        virtual void _OnInitialized()
        {
            for( Index i = 0; i < SCRIPT_COUNT; i++ )
                _Register(i, SCRIPT_FUNCTIONS[i]);
        }

        /**/
        void _StateSync()
        {
            StateFilters&   filters = _state.filters;
            ULong           last_delay = _game.GetGlobalDelay();

            // disable global delay
            _game.SetGlobalDelay(0);

            // filters:character
            _ahi.ReadFilterChar(filters.character);

            // filters:primary
            _ahi.ReadFilterPrimary(filters.primary);

            // filters:secondary
            _ahi.ReadFilterSecondary(filters.secondary);

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

            // restore global delay
            _game.SetGlobalDelay(last_delay);
        }

        /**/
        void _StateRestore()
        {
            const StateFilters& filters = _state.filters;
            const StateSearch&  search = _state.search;
            ULong               last_delay = _game.GetGlobalDelay();

            // disable global delay
            _game.SetGlobalDelay(0);

            // filters:character
            if(*filters.character)
                _ahi.WriteFilterChar(filters.character);

            // filters:primary
            if(*filters.primary)
                _ahi.WriteFilterPrimary(filters.primary);

            // filters:secondary
            if(*filters.secondary)
                _ahi.WriteFilterSecondary(filters.secondary);

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
                _ahi.WriteFilterUnique(filters.unique, filters.unique_row);

            // search
            if(search.active && _ahi.ActionSearch())
            {
                // sort
                if(search.sort_id != INVALID_ID && search.sort_count)
                {
                    ULong count = (search.sort_count + 1) % 2;
                    for( Index i = 0; i <= count && _ahi.ActionListSort(static_cast<UiId>(search.sort_id)); i++ );
                }

                // restore page
                for( Index i = 0; i < _state.search.page && _ahi.ActionListNextPage(); i++ );
            }

            // restore global delay
            _game.SetGlobalDelay(last_delay);
        }

        /**/
        Bool _SessionCheck()
        {
            const StateLogin& login = _state.login;

            // pause while paused and active state
            while(_paused && _active)
                _game.Sleep(SCRIPT_PAUSE_SLICE);

            // relogin check
            if(*login.name && *login.password && _ahi.ActionReLogin(login.name, login.password, login.delay))
            {
                // restore state
                _StateRestore();
                return true;
            }

            return false;
        }

        /**/
        Bool _LocaleCheck( Id id )
        {
            if(Locale::GetInstance().IsDefault())
                return true;

            System::Message(false, EXCEPTION_LOCALE_NOTSUPPORTED, SCRIPT_FUNCTIONS[id], Locale::GetInstance().GetLocale());
            Lua::Stop(false);

            return false;
        }
            
        /**/
        ULong _OnFunction( Id id )
        {
            ULong pushed = _CallFunction(id);

            // session check
            _SessionCheck();

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

            // haFilterPrimary(id) -> status
            case SCRIPT_HAFILTERPRIMARY:
                return _haFilterPrimary();

            // haFilterRarity(id) -> status
            case SCRIPT_HAFILTERRARITY:
                return _haFilterRarity();

            // haFilterSecondary(id) -> status
            case SCRIPT_HAFILTERSECONDARY:
                return _haFilterSecondary();

            // haFilterStat(index, id, value) -> status
            case SCRIPT_HAFILTERSTAT:
                return _haFilterStat();

            // haFilterStatClear() -> status
            case SCRIPT_HAFILTERSTATCLEAR:
                return _haFilterStatClear();

            // haFilterType(id) -> status
            case SCRIPT_HAFILTERTYPE:
                return _haFilterType();

            // haFilterUnique(name, row) -> status
            // haFilterUnique(name) -> status
            // haFilterUnique() -> name
            case SCRIPT_HAFILTERUNIQUE:
                return _haFilterUnique();

            // haListAt() -> [row, page]
            case SCRIPT_HALISTAT:
                return _haListAt();

            // haListIterate() -> status
            case SCRIPT_HALISTNEXT://DEPRECATED
            case SCRIPT_HALISTITERATE:
                return _haListIterate();

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

            // haSellCancel() -> status
            case SCRIPT_HASELLCANCEL:
                return _haSellCancel();

            // haSellIterate() -> status
            case SCRIPT_HASELLITERATE:
                return _haSellIterate();

            // haStashAt() -> [column, row, bag]
            case SCRIPT_HASTASHAT:
                return _haStashAt();

            // haStashIterate() -> status
            case SCRIPT_HASTASHITERATE:
            case SCRIPT_HASTASHNEXT://DEPRECATED
                return _haStashIterate();

            // haStashSelect(column, row, bag) -> status
            case SCRIPT_HASTASHSELECT:
                return _haStashSelect();


            //---- AUCTION/COMPLETED -----------------------------------------
            // haSendToStash() -> status
            case SCRIPT_HASENDTOSTASH:
                return _haSendToStash();


            //---- ITEM ------------------------------------------------------
            // haItem() -> [dpsarmor, mbid, buyout, cbid, time, stats, sockets]
            case SCRIPT_HAITEM:
                return _haItem();

            // haItemStat(pattern) -> stat[name, value1, value2, value3, value4]
            // haItemStat(pattern, substring) -> stat
            case SCRIPT_HAITEMSTAT:
                return _haItemStat();


            //---- ETC -------------------------------------------------------
            // haGetAccount() -> account
            case SCRIPT_HAGETACCOUNT:
                return _haGetAccount();

            // haGetGold() -> gold
            case SCRIPT_HAGETGOLD:
                return _haGetGold();

            // haGetInstance() -> instance
            case SCRIPT_HAGETINSTANCE:
                return _haGetInstance();

            // haLogout()
            case SCRIPT_HALOGOUT:
                return _haLogout();

            // haSetGlobalDelay(delay)
            case SCRIPT_HASETGLOBALDELAY:
                return _haSetGlobalDelay();

            // haSetLogin(name, password) -> status
            case SCRIPT_HASETLOGIN:
            case SCRIPT_HARELOGIN://DEPRECATED
            case SCRIPT_HAACTIONRELOGIN://DEPRECATED
                return _haSetLogin();

            // haSetLoginDelay(delay)
            case SCRIPT_HASETLOGINDELAY:
                return _haSetLoginDelay();


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
            Number  bid = _GetStackNumber(1);
            Bool    status = false;

            // do bid if active row selected
            if(_state.search.row > 0)
                status = _ahi.ActionBid(_state.search.row - 1, bid);

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haBuyout()
        {
            Bool status = false;

            // do buyout if active row selected
            if(_state.search.row > 0)
                status = _ahi.ActionBuyout(_state.search.row - 1);

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterBuyout()
        {
            Number buyout = _GetStackNumber(1);

            // set filter buyout
            if(buyout)
            {
                Bool randomize = _GetStackBool(2);
                Bool status = _ahi.WriteFilterBuyout(buyout, randomize);

                if(status)
                    _state.filters.buyout = buyout;

                _PushStack(status);
            }
            // get filter buyout
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
                // update state
                Tools::StrNCpy(_state.filters.character, name, sizeof(_state.filters.character));
                _ahi.ReadFilterSecondary(_state.filters.secondary);
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
                    // update state
                    _state.filters.level_min = min;
                    _state.filters.level_max = max;
                    status = true;
                }
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterPrimary()
        {
            const Char* name = _GetStackString(1);
            Bool        status = false;

            if(name && _ahi.WriteFilterPrimary(name))
            {
                // update state
                Tools::StrNCpy(_state.filters.primary, name, sizeof(_state.filters.primary));
                _ahi.ReadFilterSecondary(_state.filters.secondary);
                status = true;
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
                // update state
                Tools::StrNCpy(_state.filters.rarity, name, sizeof(_state.filters.rarity));
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterSecondary()
        {
            const Char* name = _GetStackString(1);
            Bool        status = false;

            if(name && _ahi.WriteFilterSecondary(name))
            {
                // update state
                Tools::StrNCpy(_state.filters.secondary, name, sizeof(_state.filters.secondary));
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

                // update state
                if(name)
                {
                    Tools::StrNCpy(stat.name, name, sizeof(stat.name));
                    stat.value = value;
                }
                else
                {
                    *stat.name = 0;
                    stat.value = NUMBER(-1,0);
                }

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
            {
                status &= _ahi.WriteFilterStat(index, NULL, NUMBER(-1,0));

                // update state
                for( Index i = 0; i < AH_PSTAT_LIMIT; i++ )
                    *_state.filters.stat[i].name = 0;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterType()
        {
            const Char* name = _GetStackString(1);
            Bool        status = false;

            // locale check
            if(!_LocaleCheck(SCRIPT_HAFILTERTYPE))
                return 0;

            // write auto filter
            if(name && _ahi.WriteFilterSecondaryAuto(name))
            {
                // update state
                _ahi.ReadFilterChar(_state.filters.character);
                _ahi.ReadFilterPrimary(_state.filters.primary);
                _ahi.ReadFilterSecondary(_state.filters.secondary);
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterUnique()
        {
            const Char* unique = _GetStackString(1);
            Index       row = _GetStackULong(2);

            if(unique)
            {
                Bool status = _ahi.WriteFilterUnique(unique, row);

                // update state
                if(status)
                {
                    Tools::StrNCpy(_state.filters.unique, unique, sizeof(_state.filters.unique));
                    _state.filters.unique_row = row;
                }

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
        ULong _haListAt()
        {
            _PushTable(0);

            // fields
            _SetTable("page",   _state.search.page + 1);
            _SetTable("row",    _state.search.row);

            return 1;
        }

        /**/
        ULong _haListIterate()
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
                    if(!_ahi.ActionListNextPage() && !_SessionCheck())
                    {
                        _state.search.row = 0;
                        _state.search.page = 0;
                        break;
                    }
                }

                // read list item and increment index
                if(_ahi.ReadListItem(_state.search.row - 1, _state.item, false, false))
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
                Bool ground = (_state.search.row == index);

                // read list item
                if(_ahi.ReadListItem(index - 1, _state.item, ground, false))
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
                status = true;
            }
            else
                status = _SessionCheck();

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
            if( starting > 0 && _state.item.IsValid() &&
                _state.stash.column > 0 && _state.stash.row > 0)
            {
                // call sell sequence
                status = _ahi.SellStashItem(_state.stash.column - 1, _state.stash.row - 1, starting, buyout);
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSellCancel()
        {
            Bool status = false;

            // row must be valid
            if(_state.sell.row > 0)
            {
                // cancel sale
                status = _ahi.ReadSellCancel(_state.sell.row - 1);

                // decrement row state
                if(status)
                    _state.sell.row--;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSellIterate()
        {
            ULong   sell_count;
            Bool    status = false;
            Bool    reset = _state.sell.row == 0;

            while(_active)
            {
                // read list count
                if(!_ahi.ReadSellCount(sell_count))
                    break;

                // past list limit
                if(_state.sell.row > sell_count)
                {
                    // reset index
                    _state.sell.row = 0;
                    break;
                }

                // read list item
                if(_ahi.ReadSellItem(++_state.sell.row - 1, _state.item, reset))
                {
                    status = true;
                    break;
                }
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haStashAt()
        {
            _PushTable(0);

            // fields
            _SetTable("bag",    _state.stash.bag);
            _SetTable("column", _state.stash.column);
            _SetTable("row",    _state.stash.row);

            return 1;
        }

        /**/
        ULong _haStashIterate()
        {
            Bool status = false;

            // ensure first bag if beginning iteration
            if( _state.stash.row == 0 )
                _ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1);

            while(_active)
            {
                // next row
                _state.stash.row++;

                // next column
                if(_state.stash.row > AH_STASH_ROWS)
                {
                    _state.stash.row = 1;
                    _state.stash.column++;
                }

                // next bag
                if(_state.stash.column > AH_STASH_COLUMNS)
                {
                    _state.stash.column = 1;
                    if(++_state.stash.bag > AH_STASH_BAGS)
                    {
                        _state.stash.row = 0;
                        _state.stash.bag = 1;
                        break;
                    }
                    _ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1 + _state.stash.bag - 1);
                }

                // read list item and increment index
                if(_ahi.ReadStashItem(_state.stash.column - 1, _state.stash.row - 1, _state.item, false, false))
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
            Index   column = _GetStackULong(1);
            Index   row = _GetStackULong(2);
            Index   bag = _GetStackULong(3);
            Bool    status = false;

            // check range
            if( column > 0 &&   column <= AH_STASH_COLUMNS &&
                row > 0 &&      row <= AH_STASH_ROWS &&
                bag > 0 &&      bag <= AH_STASH_BAGS )
            {
                // select tab
                if(_ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1 + bag - 1))
                {
                    // ground hover to reset duplicate selection
                    Bool ground = (_state.stash.column == column && _state.stash.row == row);

                    // select and read stash item
                    if(_ahi.ReadStashItem(column - 1, row - 1, _state.item, ground, false))
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
            TextString rarity;

            _PushTable(0);

            // conversions
            ITEM_RARITY_STRINGS.FindName(rarity, _state.item.rarity);

            // fields
            _SetTable("name",   _state.item.name);
            _SetTable("id",     _state.item.id);
            _SetTable("ilevel", _state.item.ilevel);

            _SetTable("rarity", rarity);
            _SetTable("type",   _state.item.type);

            _SetTable("dps",    _state.item.dpsarmor);
            _SetTable("armor",  _state.item.dpsarmor);
            _SetTable("cblock", _state.item.block_chance);
            _SetTable("mblock", _state.item.block_min);
            _SetTable("xblock", _state.item.block_max);
            _SetTable("aps",    _state.item.damage_aps);
            _SetTable("mdamage",_state.item.damage_min);
            _SetTable("xdamage",_state.item.damage_max);

            _SetTable("sbid",   _state.item.bid_start);
            _SetTable("cbid",   _state.item.bid_current);
            _SetTable("mbid",   _state.item.bid_max);
            _SetTable("buyout", _state.item.buyout);

            _SetTable("rtime",  _state.item.time_remaining);
            _SetTable("xtime",  _state.item.time_expiring);

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
            const Char* pattern = _GetStackString(1);
            Bool        substring = _GetStackBool(2);
            _PushTable(0);

            // find stat
            const Item::Stat* stat = _state.item.FindStat(pattern, substring);

            // set stat found else use empty stat
            _PushItemStat(stat ? *stat : Item::Stat::GetDefault(), false);

            return 1;
        }

        //---- ETC -----------------------------------------------------------
        /**/
        ULong _haGetAccount()
        {
            TextString account = {0};

            _game.GetTrainer().ReadAccount(account);
            _PushStack(account);

            return 1;
        }

        /**/
        ULong _haGetGold()
        {
            ULong amount = 0;

            _game.GetTrainer().ReadGold(amount);
            _PushStack(amount);

            return 1;
        }

        /**/
        ULong _haGetInstance()
        {
            _PushStack(_instance + 1);
            return 1;
        }

        /**/
        ULong _haLogout()
        {
            _game.Logout();
            return 0;
        }

        /**/
        ULong _haSetGlobalDelay()
        {
            ULong delay = Tools::Conform<ULong>(_GetStackULong(1), 0, GAME_GLOBAL_DELAY_MAX);
            _game.SetGlobalDelay(delay);
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

        /**/
        ULong _haSetLoginDelay()
        {
            _state.login.delay = _GetStackULong(1);
            return 0;
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

            if(message)
            {
                FILE*& file = _log[_instance];

                if(file == NULL)
                {
                    TextString path;
                    sprintf(path, SCRIPT_LOG_PATH, _instance + 1);
                    file = fopen(path, "wt");
                }

                if(file)
                {
                    fprintf(file, "%s\n", message);
                    fflush(file);
                }
            }

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
            TextString text;
            Bool active;
            _game.GetTrainer().ReadPopupStatus(active, text, Trainer::OBJECT_POPUP_AH);
            _game.GetTrainer().ReadPopupStatus(active, text, Trainer::OBJECT_POPUP_ERROR);
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
