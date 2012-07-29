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

        Index               _list_index;
        Item                _list_item;

        SYSTEMTIME          GAME_LAST_QUERY;

    public:
        /**/
        Script():
            _ahi(_game),
            _list_index(0)
        {
        }

        /**/
        void Start()
        {
            try
            {
                // initialize game
                if(!_game.Initialize())
                    throw EXCEPTION_INITIALIZE;

                // train auction interface
                if(!_ahi.Train())
                    throw EXCEPTION_TRAIN;

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
        }

        /**/
        void Stop()
        {
            Lua::Stop();
        }

    protected:
        /**/
        virtual void _OnInitialized()
        {
            for( Index i = 0; i < SCRIPT_COUNT; i++ )
                _Register(i, SCRIPT_STRINGS[i]);
        }

        /**/
        ULong _OnFunction( Id id )
        {
            Bool    status;
            Index   index;
            ULong   number;

            switch(id)
            {
            // haFilterType(id) -> status
            case SCRIPT_HAFILTERTYPE:
                status = _ahi.WriteFilterType(
                    Tools::Conform(static_cast<FilterSecondaryId>(AH_COMBO_SECONDARY.Find(_GetStackString(1))), FILTER_SEC_1H_ALL, FILTER_SEC_FOLLOWER_TEMPLAR));
                _PushStackBool(status);
                return 1;

            // haFilterLevel(min,  max) -> status
            case SCRIPT_HAFILTERLEVEL:
                number = Tools::Conform(_GetStackULong(1), GAME_LEVEL_MIN, GAME_LEVEL_MAX);
                status = _ahi.WriteFilterLevelMin(number);
                if(status)
                {
                    ULong max = _GetStackULong(2);
                    status = _ahi.WriteFilterLevelMax(max ? Tools::Conform(max, GAME_LEVEL_MIN, GAME_LEVEL_MAX) : number);
                }
                _PushStackBool(status);
                return 1;

            // haFilterRarity(id) -> status
            case SCRIPT_HAFILTERRARITY:
                status = _ahi.WriteFilterRarity(Tools::Conform(static_cast<FilterRarityId>(AH_COMBO_RARITY.Find(_GetStackString(1))), EQRARITY_ALL, EQRARITY_LEGENDARY));
                _PushStackBool(status);
                return 1;

            // haFilterStat(index, id, value) -> status
            case SCRIPT_HAFILTERSTAT:
                status = _ahi.WriteFilterStat(
                    Tools::Conform<Index>(_GetStackULong(1), 1, AH_INPUT_PSTAT_LIMIT) - 1,
                    Tools::Conform(static_cast<ItemStatId>(AH_COMBO_PSTAT.Find(_GetStackString(2))), ITEM_STAT_NONE, ITEM_STAT_REDUCEDLEVELREQUIREMENT),
                    Tools::Conform<ULong>(_GetStackULong(3), 0, ITEM_STAT_VALUE_MAX));
                _PushStackBool(status);
                return 1;

            // haFilterBuyout(amount) -> status
            case SCRIPT_HAFILTERBUYOUT:
                status = _ahi.WriteBuyout(_GetStackULong(1), _GetStackBool(2));
                _PushStackBool(status);
                return 1;

            // haFilterUnique(name) -> status
            case SCRIPT_HAFILTERUNIQUE:
                status = _ahi.WriteUnique(_GetStackString(1));
                _PushStackBool(status);
                return 1;

            // haActionBid(bid) -> status
            case SCRIPT_HAACTIONBID:
                status = (_list_index > 0) ? _ahi.ActionBid(_list_index - 1, _GetStackULong(1)) : false;
                _PushStackBool(status);
                return 1;

            // haActionBuyout() -> status
            case SCRIPT_HAACTIONBUYOUT:
                status = (_list_index > 0) ? _ahi.ActionBuyout(_list_index - 1) : false;
                _PushStackBool(status);
                return 1;

            // haActionSearch(wait) -> status
            case SCRIPT_HAACTIONSEARCH:
                _list_index = 0;
                status = _ahi.ActionSearch();
                _PushStackBool(status);
                return 1;

            // haActionSortDpsArmor() -> status
            case SCRIPT_HAACTIONSORTDPSARMOR:
                status = _ahi.ActionListSortDpsArmor();
                _PushStackBool(status);
                return 1;

            // haActionSortBuyout() -> status
            case SCRIPT_HAACTIONSORTBUYOUT:
                status = _ahi.ActionListSortBuyout();
                _PushStackBool(status);
                return 1;

            // haListSelect(index) -> status
            case SCRIPT_HALISTSELECT:
                index = _GetStackULong(1);
                if(index > 0 && index <= AH_LIST_ROW_LIMIT && (status = _ahi.ReadListItem(index - 1, _list_item)))
                    _list_index = index;
                else
                    status = false;
                _PushStackBool(status);
                return 1;

            // haListNext() -> status
            case SCRIPT_HALISTNEXT:
                status = _haListNext();
                _PushStackBool(status);
                return 1;

            // haListItem() -> dpsarmor, bid, buyout, nstats, nsockets
            case SCRIPT_HALISTITEM:
                _PushStackULong(_list_item.dpsarmor);
                _PushStackULong(_list_item.bid);
                _PushStackULong(_list_item.buyout);
                _PushStackULong(_list_item.stats.GetCount());
                _PushStackULong(_list_item.sockets.GetCount());
                _PushStackULong(_list_item.id);
                _PushStackULong(_list_item.currBid);
                _PushStackULong(_list_item.flags);
                return 8;

            // haListItemStat(stat) -> stat, value1, value2, value3, value4
            case SCRIPT_HALISTITEMSTAT:
                index = _GetStackULong(1) - 1;
                return (index < _list_item.stats.GetCount()) ? _PushItemStat(_list_item.stats[index], false) : _PushZeros(5);

            // haListItemSocket(index) -> stat, type, rank, value1, value2, value3, value4
            case SCRIPT_HALISTITEMSOCKET:
                index = _GetStackULong(1) - 1;
                return (index < _list_item.sockets.GetCount()) ? _PushItemStat(_list_item.sockets[index], true) : _PushZeros(7);

            // haLog(message)
            case SCRIPT_HALOG:
                Tools::Log(LOG_USER, "%s\n", _GetStackString(1));
                return 0;

            // haBeep()
            case SCRIPT_HABEEP:
                MessageBeep(MB_ICONEXCLAMATION);
                return 0;

            // haSleep(ms)
            case SCRIPT_HASLEEP:
                Sleep(_GetStackULong(1));
                return 0;

            // haAlert(message)
            case SCRIPT_HAALERT:
                System::Message("%s", _GetStackString(1));
                return 0;

            // haSettingsListDelay(delay)
            case SCRIPT_HASETTINGSLISTDELAY:
                GAME_ITEMREAD_DELAY = Tools::Conform(_GetStackULong(1), GAME_ITEMREAD_DELAY_MIN, GAME_ITEMREAD_DELAY_MAX);
                return 0;

            // haSettingsNextDelay(delay)
            case SCRIPT_HASETTINGSNEXTDELAY:
                GAME_NEXTPAGE_DELAY = Tools::Conform(_GetStackULong(1), GAME_NEXTPAGE_DELAY_MIN, GAME_NEXTPAGE_DELAY_MAX);
                return 0;

            default:
                return 0;
            }
        }

        /**/
        Bool _haListNext()
        {
            ULong list_count;

            while(true)
            {
                // read list count
                if(!_ahi.ReadListCount(list_count))
                    return false;

                // past list limit
                if(++_list_index > list_count)
                {
                    // go to next next page
                    if(!_ahi.ActionListNextPage())
                        return false;

                    // reset index
                    _list_index = 1;
                }

                // read list item and increment index
                if(_ahi.ReadListItem(_list_index - 1, _list_item))
                    return true;
            }

            return true;
        }

        /**/
        ULong _PushItemStat( const Item::Stat& stat, Bool socket )
        {
            const Item::ValueCollection& values = stat.values;
            Index index;

            // name
            _PushStackString(AH_COMBO_PSTAT[stat.id].name);

            // gem rank and type
            if(socket)
            {
                GemTypeId   type;
                GemRankId   rank;

                if(Support::GetGemInfo(type, rank, stat))
                {
                    _PushStackString(ITEM_GEM_TYPE_STRINGS[type]);
                    _PushStackULong(rank);
                }
                else
                    _PushZeros(2);
            }

            // stats
            for( index = 0; index < values.GetCount(); index++ )
                _PushStackULong(values[index]);
            for( ; index < values.GetLimit(); index++ )
                _PushStackULong(0);

            // total pushed
            return 1 + values.GetLimit() + (socket ? 2 : 0);
        }

        /**/
        ULong _PushZeros( ULong count )
        {
            for( Index i = 0; i < count; i++ )
                _PushStackULong(0);

            return count;
        }
    };
}
