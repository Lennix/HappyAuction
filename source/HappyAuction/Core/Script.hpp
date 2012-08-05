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
            Bool        status;
            Index       index;
            Long        snumber;
            ULong       unumber;
            const Char* pstring;
            TextString  string;

            switch(id)
            {
            // haFilterType(id) -> status
            case SCRIPT_HAFILTERTYPE:
                pstring = _GetStackString(1);
                status = pstring && _ahi.WriteFilterType(
                    Tools::Conform(static_cast<FilterSecondaryId>(AH_COMBO_SECONDARY.Find(pstring)), FILTER_SEC_1H_ALL, FILTER_SEC_FOLLOWER_TEMPLAR));
                _PushStackBool(status);
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
                _PushStackBool(status);
                return 1;

            // haFilterRarity(id) -> status
            case SCRIPT_HAFILTERRARITY:
                pstring = _GetStackString(1);
                status = pstring && _ahi.WriteFilterRarity(Tools::Conform(static_cast<FilterRarityId>(AH_COMBO_RARITY.Find(pstring)), EQRARITY_ALL, EQRARITY_LEGENDARY));
                _PushStackBool(status);
                return 1;

            // haFilterStat(index, id, value) -> status
            case SCRIPT_HAFILTERSTAT:
                pstring = _GetStackString(2);
                status = pstring && _ahi.WriteFilterStat(
                    Tools::Conform<Index>(_GetStackULong(1), 1, AH_INPUT_PSTAT_LIMIT) - 1,
                    Tools::Conform(static_cast<ItemStatId>(AH_COMBO_PSTAT.Find(pstring)), ITEM_STAT_NONE, ITEM_STAT_REDUCEDLEVELREQUIREMENT),
                    Tools::Conform<ULong>(_GetStackULong(3), 0, ITEM_STAT_VALUE_MAX));
                _PushStackBool(status);
                return 1;

            // haFilterBuyout(amount, randomize) -> status
            // haFilterBuyout() -> buyout
            case SCRIPT_HAFILTERBUYOUT:
                snumber = _GetStackLong(1);
                if(snumber)
                    _PushStackBool(_ahi.WriteBuyout(snumber, _GetStackBool(2)));
                else
                    _PushStackLong(_ahi.ReadBuyout(snumber) ? snumber : 0);
                return 1;

            // haFilterUnique(name) -> status
            // haFilterUnique() -> name
            case SCRIPT_HAFILTERUNIQUE:
                pstring = _GetStackString(1);
                if(pstring)
                    _PushStackBool(_ahi.WriteUnique(pstring));
                else
                    _PushStackString(_ahi.ReadUnique(string) ? string : "");
                return 1;

            // haFilterCharacter(id) -> status
            case SCRIPT_HAFILTERCLASS:
                pstring = _GetStackString(1);
                status = pstring && _ahi.WriteFilterCharacter(Tools::Conform(static_cast<FilterCharId>(AH_COMBO_CHARACTER.Find(pstring)), FILTER_CHAR_BARBARIAN, FILTER_CHAR_WIZARD));
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
                return _haListSelect();

            // haListNext() -> status
            case SCRIPT_HALISTNEXT:
                return _haListNext();

            // haListItem() -> dpsarmor, bid, buyout, nstats, nsockets, currBid, id, flags, itemlevel, timeleft, name
            case SCRIPT_HALISTITEM:
                _PushStackULong(_list_item.dpsarmor);
                _PushStackULong(_list_item.max_bid);
                _PushStackULong(_list_item.buyout);
                _PushStackULong(_list_item.stats.GetCount());
                _PushStackULong(_list_item.sockets.GetCount());
                _PushStackULong(_list_item.current_bid);
                _PushStackULong(_list_item.id);
                _PushStackULong(_list_item.flags);
                _PushStackULong(_list_item.ilevel);
                _PushStackString(_list_item.timeleft);
                _PushStackString(_list_item.name);
                return 11;

            // haListItemStat(index) -> stat, value1, value2, value3, value4
            // haListItemStat(stat)  -> value1, value2, value3, value4
            case SCRIPT_HALISTITEMSTAT:
                return _haListItemStat();

            // haListItemSocket(index) -> stat, type, rank, value1, value2, value3, value4
            case SCRIPT_HALISTITEMSOCKET:
                index = _GetStackULong(1) - 1;
                return (index < _list_item.sockets.GetCount()) ? _PushItemStat(_list_item.sockets[index], true) : _PushZeros(7);

            // haGetGold()
            case SCRIPT_HAGETGOLD:
                ULong gold;
                if (_ahi.GetGold(gold))
                    _PushStackULong(gold);
                else
                    return 0;
                return 1;

            // haLog(message)
            case SCRIPT_HALOG:
                pstring = _GetStackString(1);
                if(pstring)
                    Tools::Log(LOG_USER, "%s\n", pstring);
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
                pstring = _GetStackString(1);
                if(pstring)
                    System::Message("%s", pstring);
                return 0;

            case SCRIPT_HAPARSETIME:
                pstring = _GetStackString(1);
                if(pstring)
                {
                    _PushStackULong(_ahi.ParseTime(pstring));
                    return 1;
                }
                return 0;

            // haSettingsListDelay(delay)
            case SCRIPT_HASETTINGSLISTDELAY:
                GAME_ITEMREAD_DELAY = Tools::Conform(_GetStackULong(1), GAME_ITEMREAD_DELAY_MIN, GAME_ITEMREAD_DELAY_MAX);
                return 0;

            // haSettingsNextDelay(delay)
            case SCRIPT_HASETTINGSNEXTDELAY:
                GAME_NEXTPAGE_DELAY = Tools::Conform(_GetStackULong(1), GAME_NEXTPAGE_DELAY_MIN, GAME_NEXTPAGE_DELAY_MAX);
                return 0;

            // haSettingsQueriesPerHour(delay)
            case SCRIPT_HASETTINGSQUERIESPERHOUR:
                unumber = _GetStackLong(1);
                if(unumber)
                {
                    GAME_MAX_QUERIES_PER_HOUR = Tools::Conform(unumber, GAME_MAX_QUERIES_PER_HOUR_MIN, GAME_MAX_QUERIES_PER_HOUR_MAX);
                    return 0;
                }
                else
                {
                    _PushStackULong(GAME_CURRENT_QUERIES_PER_HOUR);
                    return 1;
                }

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
                // ground hover to reset previous item select
                _ahi.HoverGround();

                // read list item
                if(_ahi.ReadListItem(index - 1, _list_item))
                {
                    // update list index
                    _list_index = index;

                    status = true;
                }
            }

            _PushStackBool(status);

            return 1;
        }

        /**/
        ULong _haListNext()
        {
            ULong   list_count;
            Bool    status = false;

            while(true)
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
                if(_ahi.ReadListItem(_list_index - 1, _list_item))
                {
                    status = true;
                    break;
                }
            }

            _PushStackBool(status);

            return 1;
        }

        /**/
        ULong _haListItemStat()
        {
            ULong stat_index = _GetStackULong(1);

            // if index 0 try string
            if(stat_index == 0)
            {
                const Item::Stat* stat = _list_item.FindStat(_GetStackString(1));

                // if stat found
                if(stat)
                    _PushItemStat(*stat, false, true);
                // else zeros
                else
                    _PushZeros(5);
                return 4;
            }
            else
            {
                // if valid stat index
                if(stat_index <= _list_item.stats.GetCount())
                    _PushItemStat(_list_item.stats[stat_index - 1], false);
                // else zeros
                else
                    _PushZeros(5);

                return 5;
            }
        }

        /**/
        ULong _PushItemStat( const Item::Stat& stat, Bool socket, Bool name=true )
        {
            const Item::ValueCollection& values = stat.values;
            Index index;

            // name
            if(name)
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
