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
            //---- AUCTION/SEARCH --------------------------------------------
            // haBid(bid) -> status
            case SCRIPT_HABID:
            case SCRIPT_HAACTIONBID://DEPRECATED
                status = (_list_index > 0) ? _ahi.ActionBid(_list_index - 1, _GetStackULong(1)) : false;
                _PushStack(status);
                return 1;

            // haBuyout() -> status
            case SCRIPT_HABUYOUT:
            case SCRIPT_HAACTIONBUYOUT://DEPRECATED
                status = (_list_index > 0) ? _ahi.ActionBuyout(_list_index - 1) : false;
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

            // haFilterChar(id) -> status
            case SCRIPT_HAFILTERCHAR:
                pstring1 = _GetStackString(1);
                status = pstring1 && _ahi.WriteFilterChar(
                    Tools::Conform(static_cast<FilterCharId>(AH_COMBO_CHARACTER.Find(pstring1)), FILTER_CHAR_BARBARIAN, FILTER_CHAR_WIZARD));
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

            // haFilterStatClear() -> status
            case SCRIPT_HAFILTERSTATCLEAR:
                status = true;
                for( index = 0; index < AH_INPUT_PSTAT_LIMIT; index++ )
                    status &= _ahi.WriteFilterStat(index, ITEM_STAT_NONE, 0);
                _PushStack(status);
                return 1;

            // haFilterType(id) -> status
            case SCRIPT_HAFILTERTYPE:
                pstring1 = _GetStackString(1);
                status = pstring1 && _ahi.WriteFilterType(
                    Tools::Conform(static_cast<FilterSecondaryId>(AH_COMBO_SECONDARY.Find(pstring1)), FILTER_SEC_1H_ALL, FILTER_SEC_FOLLOWER_TEMPLAR));
                _PushStack(status);
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

            // haListNext() -> status
            case SCRIPT_HALISTNEXT:
                return _haListNext();

            // haListSelect(index) -> status
            case SCRIPT_HALISTSELECT:
                return _haListSelect();

            // haSearch() -> status
            case SCRIPT_HASEARCH:
            case SCRIPT_HAACTIONSEARCH://DEPRECATED
                _list_index = 0;
                status = _ahi.ActionSearch();
                _PushStack(status);
                return 1;

            // haSortBuyout() -> status
            case SCRIPT_HASORTBUYOUT:
            case SCRIPT_HAACTIONSORTBUYOUT://DEPRECATED
                status = _ahi.ActionListSortBuyout();
                _PushStack(status);
                return 1;

            // haSortDpsArmor() -> status
            case SCRIPT_HASORTDPSARMOR:
            case SCRIPT_HAACTIONSORTDPSARMOR://DEPRECATED
                status = _ahi.ActionListSortDpsArmor();
                _PushStack(status);
                return 1;


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


            //---- AUCTION/COMPLETED------------------------------------------
            // haSendToStash() -> status
            case SCRIPT_HASENDTOSTASH:
                status = _ahi.ActionSendToStash();
                _PushStack(status);
                return 1;


            //---- ITEM ------------------------------------------------------
            // haItem() -> item[dpsarmor, mbid, buyout, cbid, time, stats, sockets]
            case SCRIPT_HAITEM:
                return _haItem();

            // haItemStat() -> stat[name, value1, value2, value3, value4]
            case SCRIPT_HAITEMSTAT:
                return _haItemStat();


            //---- ETC -------------------------------------------------------
            // haReLogin(name, password) -> status
            case SCRIPT_HARELOGIN:
            case SCRIPT_HAACTIONRELOGIN://DEPRECATED
                pstring1 = _GetStackString(1);
                pstring2 = _GetStackString(2);
                if(pstring1 && pstring1)
                    status = _ahi.ActionReLogin(pstring1, pstring2);
                else
                    status = false;
                _PushStack(status);
                return 1;


            //---- SETTINGS --------------------------------------------------
            // haSetGlobalDelay(delay)
            case SCRIPT_HASETGLOBALDELAY:
                GAME_ACTION_DELAY = Tools::Conform<ULong>(_GetStackULong(1), 0, GAME_ACTION_DELAY_MAX);
                return 0;


            //---- UTILITIES -------------------------------------------------
            // haAlert(message)
            case SCRIPT_HAALERT:
                pstring1 = _GetStackString(1);
                if(pstring1)
                    System::Message("%s", pstring1);
                return 0;

            // haBeep()
            case SCRIPT_HABEEP:
                MessageBeep(MB_ICONEXCLAMATION);
                return 0;

            // haLog(message)
            case SCRIPT_HALOG:
                pstring1 = _GetStackString(1);
                if(pstring1)
                    Tools::Log(LOG_USER, "%s\n", pstring1);
                return 0;

            // haSleep(delay)
            // haSleep(low, high)
            case SCRIPT_HASLEEP:
                _game.Sleep(_GetStackULong(1), _GetStackULong(2));
                return 0;


            //----------------------------------------------------------------
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
        ULong _haSell()
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
                _ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1);

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

                        _ahi.Tab(UI_TAB_SELL, UI_TAB_STASHBAG1 + _stash_bag);
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
                    if(_ahi.ReadStashItem(column, row, _item))
                    {
                        // update stash position
                        _stash_column = column;
                        _stash_row = row;
                        _stash_bag = bag;
                        status = true;
                    }
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






        ULong _DropHeight()
        {
            const Coordinate&       coordinate =    COORDS[UI_COMBO_SECONDARY];
            const Coordinate&       size =          COORDS[UI_COMBO_SIZE];
            Window&                 window =        _game.GetWindow();
            ULong                   y =             _game.Y(coordinate.y, false);
            ULong                   height =        window.GetHeight() - y;
            static Window::Color    pixels[2000];
            ULong                   h;

            // open dropdown
            _game.MouseClick(coordinate.x + size.x / 2, coordinate.y - (size.y * .8));
            Sleep(50);

            // image scan to selection
            window.CaptureScreen(pixels, _game.X(coordinate.x + size.x / 2, false), y, 1, height);

            // determine selection y
            for( h = 0; h < height && (pixels[h].r <= (pixels[h].g + pixels[h].b)); h++ );
            if(h == height)
                return 0;

            // click selection
            _game.MouseClickAbsolute(2, 2);
            Sleep(50);

            return h;
        }

        /**/
        ULong _haTest()
        {
            for( Index i=1601; _active && i<=2000; i++)
            {
                _game.GetWindow().SetDimensions( 0, 0, (i * 2560) / 1600, i );
                Sleep(1500);

                ULong h = _DropHeight();
                Tools::Log(LOG_USER, "%u\t%u\t%f\n", i, h, (double)h/14.0);
            }
            return 0;
        }
    };
}
