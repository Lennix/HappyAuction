#pragma once
#include <HappyAuction/Root.hpp>
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/State.hpp>
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

    public:
        /**/
        Script():
            _ahi(_game),
            _active(false)
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
                    throw EXCEPTION_INITIALIZE;

                // sync state
                _StateSync();

                // start lua script
                if(!Lua::Start(SCRIPT_PATH))
                    System::Message(EXCEPTION_SCRIPT, Lua::GetError());
            }
            catch(const Char* exception)
            {
                System::Message(exception);
            }

            // close user log
            Tools::Log(LOG_USER, NULL);

            _active = false;
        }

        /**/
        void Stop()
        {
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
            _ahi.ReadFilterSecondary(reinterpret_cast<FilterSecondaryId&>(filters.type));

            // filters:character
            _ahi.ReadFilterChar(reinterpret_cast<FilterCharId&>(filters.character));

            // filters:rarity
            _ahi.ReadFilterRarity(reinterpret_cast<FilterRarityId&>(filters.rarity));

            // filters:stats
            for( Index i = 0; i < AH_INPUT_PSTAT_LIMIT; i++ )
            {
                StateFiltersStat& stat = filters.stat[i];
                _ahi.ReadFilterStat(i, reinterpret_cast<ItemStatId&>(stat.id), stat.value);
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
            const StateSearch& search = _state.search;
            ULong           global_delay = GAME_GLOBAL_DELAY;

            // disable global delay
            GAME_GLOBAL_DELAY = 0;

            // filters:type
            if(filters.type != INVALID_ID)
                _ahi.WriteFilterSecondary(static_cast<FilterSecondaryId>(filters.type));

            // filters:character
            if(filters.character != INVALID_ID)
                _ahi.WriteFilterChar(static_cast<FilterCharId>(filters.character));

            // filters:rarity
            if(filters.rarity != INVALID_ID)
                _ahi.WriteFilterRarity(static_cast<FilterRarityId>(filters.rarity));

            // filters:stats
            for( Index i = 0; i < AH_INPUT_PSTAT_LIMIT; i++ )
            {
                const StateFiltersStat& stat = filters.stat[i];
                if(stat.id != INVALID_ID)
                    _ahi.WriteFilterStat(i, static_cast<ItemStatId>(stat.id), stat.value);
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
                // sort buyout
                if(search.sort_buyout)
                    for( Index i = 0; i < search.sort_buyout && _ahi.ActionListSortBuyout(); i++ );
                // sort dpsarmor
                else if(search.sort_dpsarmor)
                    for( Index i = 0; i < search.sort_dpsarmor && _ahi.ActionListSortDpsArmor(); i++ );

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
                _Register(i, SCRIPT_STRINGS[i]);
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
                return _haSortBuyout();

            // haSortDpsArmor() -> status
            case SCRIPT_HASORTDPSARMOR:
            case SCRIPT_HAACTIONSORTDPSARMOR://DEPRECATED
                return _haSortDpsArmor();


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
            Bool status = (_state.search.row > 0) ? _ahi.ActionBid(_state.search.row - 1, _GetStackULong(1)) : false;
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
            Long buyout = _GetStackLong(1);

            if(buyout)
            {
                Bool randomize = _GetStackBool(2);
                Bool status = _ahi.WriteFilterBuyout(buyout, randomize);

                if(status && buyout > 0)
                    _state.filters.buyout = buyout;

                _PushStack(status);
            }
            else
                _PushStack(_ahi.ReadFilterBuyout(buyout) ? buyout : 0);

            return 1;
        }

        /**/
        ULong _haFilterChar()
        {
            Id      id = AH_COMBO_CHARACTER.Find(_GetStackString(1));
            Bool    status = false;

            if(id != INVALID_ID && _ahi.WriteFilterChar(static_cast<FilterCharId>(id)))
            {
                _state.filters.character = id;
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterLevel()
        {
            Long    min = _GetStackLong(1);
            Bool    status = false;

            if(min >= -1 && min <= GAME_LEVEL_MAX && _ahi.WriteFilterLevelMin(min))
            {
                Long max = _GetStackLong(2);
                if(max == 0)
                    max = min;
                if(max >= -1 && max <= GAME_LEVEL_MAX && _ahi.WriteFilterLevelMax(max))
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
            Id      id = AH_COMBO_RARITY.Find(_GetStackString(1));
            Bool    status = false;

            if(id != INVALID_ID && _ahi.WriteFilterRarity(static_cast<FilterRarityId>(id)))
            {
                _state.filters.rarity = id;
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterStat()
        {
            Index   index = _GetStackULong(1) - 1;
            Id      id =    AH_COMBO_PSTAT.Find(_GetStackString(2));
            ULong   value = _GetStackULong(3);
            Bool    status = false;

            if( index < AH_INPUT_PSTAT_LIMIT &&
                id != INVALID_ID &&
                value <= ITEM_STAT_VALUE_MAX &&
                _ahi.WriteFilterStat(index, static_cast<ItemStatId>(id), value))
            {
                StateFiltersStat& stat = _state.filters.stat[index];
                stat.id = id;
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

            for( Index index = 0; index < AH_INPUT_PSTAT_LIMIT; index++ )
                status &= _ahi.WriteFilterStat(index, ITEM_STAT_NONE, 0);

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haFilterType()
        {
            Id      id = AH_COMBO_SECONDARY.Find(_GetStackString(1));
            Bool    status = false;

            if(id != INVALID_ID && _ahi.WriteFilterSecondary(static_cast<FilterSecondaryId>(id)))
            {
                _state.filters.type = id;
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
            if(index > 0 && index <= AH_LIST_ROW_LIMIT)
            {
                // ground hover to reset duplicate selection
                if(_state.search.row == index)
                    _ahi.HoverGround();

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
                _state.search.sort_buyout = 0;
                _state.search.sort_dpsarmor = 0;
                status = true;
            }
            else
                status = _SessionRestore();

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSortBuyout()
        {
            Bool status = false;

            if(_ahi.ActionListSortBuyout())
            {
                _state.search.sort_dpsarmor = 0;
                _state.search.sort_buyout++;
                status = true;
            }

            _PushStack(status);
            return 1;
        }

        /**/
        ULong _haSortDpsArmor()
        {
            Bool status = false;

            if(_ahi.ActionListSortDpsArmor())
            {
                _state.search.sort_buyout = 0;
                _state.search.sort_dpsarmor++;
                status = true;
            }

            _PushStack(status);
            return 1;
        }


        //---- AUCTION/SELL --------------------------------------------------
        /**/
        ULong _haSell()
        {
            ULong   starting = _GetStackULong(1);
            ULong   buyout = _GetStackULong(2);
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
            Index index;

            // name
            _SetTable("name", AH_COMBO_PSTAT[stat.id].name);

            // gem rank and type
            if(socket)
            {
                GemTypeId type = GEM_TYPE_EMPTY;
                GemRankId rank = GEM_RANK_NONE;

                Support::GetGemInfo(type, rank, stat);

                _SetTable("gem", ITEM_GEM_TYPE_STRINGS[type]);
                _SetTable("rank", rank);
            }

            // values
            for( index = 0; index < values.GetLimit(); index++ )
            {
                TextString key;

                sprintf(key, "value%u", index + 1);
                _SetTable(key, (index < values.GetCount()) ? values[index] : 0);
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
            _SetTable("rarity", (_state.item.rarity != INVALID_ID) ? ENUM_RARITIES[_state.item.rarity] : "");
            _SetTable("type", (_state.item.type != INVALID_ID) ? AH_COMBO_SECONDARY[_state.item.type].name : "");

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
            const Char* pstring1 = _GetStackString(1);
            if(pstring1)
                System::Message("%s", pstring1);
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
            const Char* pstring1 = _GetStackString(1);
            if(pstring1)
                Tools::Log(LOG_USER, "%s\n", pstring1);
            return 0;
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
            System::Message(EXCEPTION_OBSOLETED, SCRIPT_STRINGS[id]);
            Lua::Stop(false);
            return 0;
        }
    };
}
