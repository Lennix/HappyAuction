#pragma once
#include <HappyAuction/Root.hpp>
#include <HappyAuction/Constants.hpp>
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

        Index               _list_index;
        Index               _stash_column;
        Index               _stash_row;
        Index               _stash_bag;
        Item                _item;

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
                // initialize local
                _Initialize();

                // initialize game and auction interface
                if(!_game.Start() || !_ahi.Start())
                    throw EXCEPTION_INITIALIZE;

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
        void _Initialize()
        {
            _list_index = 0;
            _stash_column = 0;
            _stash_row = 0;
            _stash_bag = 0;
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
            Bool        status;
            Index       index;
            Long        snumber;
            const Char* pstring1;
            const Char* pstring2;
            TextString  string;

            switch(id)
            {
            // haFilterType(id) -> status
            case SCRIPT_HAFILTERTYPE:
                pstring1 = _GetStackString(1);
                status = pstring1 && _ahi.WriteFilterType(
                    Tools::Conform(static_cast<FilterSecondaryId>(AH_COMBO_SECONDARY.Find(pstring1)), FILTER_SEC_1H_ALL, FILTER_SEC_FOLLOWER_TEMPLAR));
                _PushStack(status);
                return 1;

            // haFilterLevel(min,  max) -> status
            case SCRIPT_HAFILTERLEVEL:
                snumber = Tools::Conform<Long>(_GetStackLong(1), -1, GAME_LEVEL_MAX);
                status = _ahi.WriteFilterLevelMin(snumber);
                if(status)
                {
                    Long max = _GetStackLong(2);
                    status = _ahi.WriteFilterLevelMax(max ? Tools::Conform<Long>(max, -1, GAME_LEVEL_MAX) : snumber);
                }
                _PushStack(status);
                return 1;

            // haFilterRarity(id) -> status
            case SCRIPT_HAFILTERRARITY:
                pstring1 = _GetStackString(1);
                status = pstring1 && _ahi.WriteFilterRarity(Tools::Conform(static_cast<FilterRarityId>(AH_COMBO_RARITY.Find(pstring1)), EQRARITY_ALL, EQRARITY_LEGENDARY));
                _PushStack(status);
                return 1;

            // haFilterStat(index, id, value) -> status
            case SCRIPT_HAFILTERSTAT:
                pstring1 = _GetStackString(2);
                status = pstring1 && _ahi.WriteFilterStat(
                    Tools::Conform<Index>(_GetStackULong(1), 1, AH_INPUT_PSTAT_LIMIT) - 1,
                    Tools::Conform(static_cast<ItemStatId>(AH_COMBO_PSTAT.Find(pstring1)), ITEM_STAT_NONE, ITEM_STAT_REDUCEDLEVELREQUIREMENT),
                    Tools::Conform<ULong>(_GetStackULong(3), 0, ITEM_STAT_VALUE_MAX));
                _PushStack(status);
                return 1;

            // haFilterBuyout(amount, randomize) -> status
            // haFilterBuyout() -> buyout
            case SCRIPT_HAFILTERBUYOUT:
                snumber = _GetStackLong(1);
                if(snumber)
                    _PushStack(_ahi.WriteBuyout(snumber, _GetStackBool(2)));
                else
                    _PushStack(_ahi.ReadBuyout(snumber) ? snumber : 0);
                return 1;

            // haFilterUnique(name) -> status
            // haFilterUnique() -> name
            case SCRIPT_HAFILTERUNIQUE:
                pstring1 = _GetStackString(1);
                if(pstring1)
                    _PushStack(_ahi.WriteUnique(pstring1));
                else
                    _PushStack(_ahi.ReadUnique(string) ? string : "");
                return 1;

            // haActionBid(bid) -> status
            case SCRIPT_HAACTIONBID:
                status = (_list_index > 0) ? _ahi.ActionBid(_list_index - 1, _GetStackULong(1)) : false;
                _PushStack(status);
                return 1;

            // haActionBuyout() -> status
            case SCRIPT_HAACTIONBUYOUT:
                status = (_list_index > 0) ? _ahi.ActionBuyout(_list_index - 1) : false;
                _PushStack(status);
                return 1;

            // haActionSearch(wait) -> status
            case SCRIPT_HAACTIONSEARCH:
                _list_index = 0;
                status = _ahi.ActionSearch();
                _PushStack(status);
                return 1;

            // haActionSortDpsArmor() -> status
            case SCRIPT_HAACTIONSORTDPSARMOR:
                status = _ahi.ActionListSortDpsArmor();
                _PushStack(status);
                return 1;

            // haActionSortBuyout() -> status
            case SCRIPT_HAACTIONSORTBUYOUT:
                status = _ahi.ActionListSortBuyout();
                _PushStack(status);
                return 1;

            // haActionReLogin(name, password) -> status
            case SCRIPT_HAACTIONRELOGIN:
                pstring1 = _GetStackString(1);
                pstring2 = _GetStackString(2);
                if(pstring1 && pstring1)
                    status = _ahi.ActionReLogin(pstring1, pstring2);
                else
                    status = false;
                _PushStack(status);
                return 1;

            // haListSelect(index) -> status
            case SCRIPT_HALISTSELECT:
                return _haListSelect();

            // haListNext() -> status
            case SCRIPT_HALISTNEXT:
                return _haListNext();

            // haStashSell(starting, buyout) -> status
            case SCRIPT_HASTASHSELL:
                return _haStashSell();

            // haStashNext() -> status
            case SCRIPT_HASTASHNEXT:
                return _haStashNext();

            // haItem() -> item[dpsarmor, mbid, buyout, cbid, time, stats, sockets]
            case SCRIPT_HAITEM:
                return _haItem();

            // haItemStat() -> stat[name, value1, value2, value3, value4]
            case SCRIPT_HAITEMSTAT:
                return _haItemStat();

            // haLog(message)
            case SCRIPT_HALOG:
                pstring1 = _GetStackString(1);
                if(pstring1)
                    Tools::Log(LOG_USER, "%s\n", pstring1);
                return 0;

            // haBeep()
            case SCRIPT_HABEEP:
                MessageBeep(MB_ICONEXCLAMATION);
                return 0;

            // haSleep(delay)
            // haSleep(low, high)
            case SCRIPT_HASLEEP:
                _game.Sleep(_GetStackULong(1), _GetStackULong(2));
                return 0;

            // haAlert(message)
            case SCRIPT_HAALERT:
                pstring1 = _GetStackString(1);
                if(pstring1)
                    System::Message("%s", pstring1);
                return 0;

            // haSetGlobalDelay(delay)
            case SCRIPT_HASETGLOBALDELAY:
                GAME_ACTION_DELAY = Tools::Conform<ULong>(_GetStackULong(1), 0, GAME_ACTION_DELAY_MAX);
                return 0;

            case SCRIPT_HATEST:
                return _haTest();


            //----------------------- DEPRECATED ---------------------------------
            // haListItem() -> dpsarmor, mbid, buyout, nstats, nsockets, cbid, time
            case SCRIPT_HALISTITEM:
                _PushStack(_item.dpsarmor);
                _PushStack(_item.max_bid);
                _PushStack(_item.buyout);
                _PushStack(_item.stats.GetCount());
                _PushStack(_item.sockets.GetCount());
                _PushStack(_item.current_bid);
                _PushStack(_item.time);
                return 7;

            // haListItemStat(index) -> stat, value1, value2, value3, value4
            // haListItemStat(stat)  -> value1, value2, value3, value4
            case SCRIPT_HALISTITEMSTAT:
                return _haListItemStat();

            // haListItemSocket(index) -> stat, type, rank, value1, value2, value3, value4
            case SCRIPT_HALISTITEMSOCKET:
                index = _GetStackULong(1) - 1;
                return (index < _item.sockets.GetCount()) ? _PushItemStat_OLD(_item.sockets[index], true) : _PushZeros(7);

            // haSettingsListDelay(delay)
            case SCRIPT_HASETTINGSLISTDELAY:
                GAME_ACTION_DELAY = Tools::Conform<ULong>(_GetStackULong(1), 0, GAME_ACTION_DELAY_MAX);
                return 0;

            default:
                return 0;
            }
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
                if(_list_index == index)
                    _ahi.HoverGround();

                // read list item
                if(_ahi.ReadListItem(index - 1, _item))
                {
                    // update list index
                    _list_index = index;

                    status = true;
                }
            }

            _PushStack(status);

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
                if(++_list_index > list_count)
                {
                    // go to next next page
                    if(!_ahi.ActionListNextPage())
                        break;

                    // reset index
                    _list_index = 1;
                }

                // read list item and increment index
                if(_ahi.ReadListItem(_list_index - 1, _item))
                {
                    status = true;
                    break;
                }
            }

            _PushStack(status);

            return 1;
        }

        /**/
        ULong _haStashSell()
        {
            ULong   starting = _GetStackULong(1);
            ULong   buyout = _GetStackULong(2);
            Bool    status = false;

            // must have starting price
            if(starting > 0)
            {
                // call sell sequence
                if(_ahi.SellStashItem(_stash_column, _stash_row, starting, buyout))
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
            if( _stash_column == 0 && _stash_row == 0 && _stash_bag == 0 )
                _ahi.Tab(UI_TAB_SELL, UI_STASH_BAG_1);

            while(_active)
            {
                // next row
                if(_stash_row >= AH_STASH_ROWS)
                {
                    _stash_row = 0;

                    // next column
                    if(++_stash_column >= AH_STASH_COLUMNS)
                    {
                        _stash_column = 0;

                        // go to next bag
                        if(++_stash_bag >= AH_STASH_BAGS)
                        {
                            _stash_bag = 0;
                            break;
                        }

                        _ahi.Tab(UI_TAB_SELL, UI_STASH_BAG_1 + _stash_bag);
                    }
                }

                // read list item and increment index
                if(_ahi.ReadStashItem(_stash_column, _stash_row++, _item))
                {
                    status = true;
                    break;
                }
            }

            _PushStack(status);

            return 1;
        }

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
            _SetTable("dps", _item.dpsarmor);
            _SetTable("armor", _item.dpsarmor);
            _SetTable("mbid", _item.max_bid);
            _SetTable("cbid", _item.current_bid);
            _SetTable("buyout", _item.buyout);
            _SetTable("time", _item.time);

            // objects
            _PushTable("stats");
            _PushItemStats(_item.stats, false);
            _PopTable();

            _PushTable("sockets");
            _PushItemStats(_item.sockets, true);
            _PopTable();

            return 1;
        }

        /**/
        ULong _haItemStat()
        {
            _PushTable(0);

            // find stat
            const Item::Stat* stat = _item.FindStat(_GetStackString(1));

            // set stat found else use empty stat
            _PushItemStat(stat ? *stat : Item::Stat::GetDefault(), false);

            return 1;
        }

        /**/
        ULong _haTest()
        {
            return 1;
        }


        // DEPRECATED
        //--------------------------------------------------------------------
        /**/
        ULong _haListItemStat()
        {
            ULong stat_index = _GetStackULong(1);

            // if index 0 try string
            if(stat_index == 0)
            {
                const Item::Stat* stat = _item.FindStat(_GetStackString(1));

                // if stat found
                if(stat)
                    _PushItemStat_OLD(*stat, false, true);
                // else zeros
                else
                    _PushZeros(5);
                return 4;
            }
            else
            {
                // if valid stat index
                if(stat_index <= _item.stats.GetCount())
                    _PushItemStat_OLD(_item.stats[stat_index - 1], false);
                // else zeros
                else
                    _PushZeros(5);

                return 5;
            }
        }

        /**/
        ULong _PushItemStat_OLD( const Item::Stat& stat, Bool socket, Bool name=true )
        {
            const Item::ValueCollection& values = stat.values;
            Index index;

            // name
            if(name)
                _PushStack(AH_COMBO_PSTAT[stat.id].name);

            // gem rank and type
            if(socket)
            {
                GemTypeId   type;
                GemRankId   rank;

                if(Support::GetGemInfo(type, rank, stat))
                {
                    _PushStack(ITEM_GEM_TYPE_STRINGS[type]);
                    _PushStack(rank);
                }
                else
                    _PushZeros(2);
            }

            // stats
            for( index = 0; index < values.GetCount(); index++ )
                _PushStack(values[index]);
            for( ; index < values.GetLimit(); index++ )
                _PushStack(0);

            // total pushed
            return 1 + values.GetLimit() + (socket ? 2 : 0);
        }

        /**/
        ULong _PushZeros( ULong count )
        {
            for( Index i = 0; i < count; i++ )
                _PushStack(0);

            return count;
        }
    };
}
