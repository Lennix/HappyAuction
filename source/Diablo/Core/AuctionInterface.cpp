#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>

namespace Diablo
{
    //------------------------------------------------------------------------
    static const ComboBox* _COMBOBOX_MAP[] =
    {
        &AH_COMBO_RARITY,       // COMBO_RARITY
        &AH_COMBO_CHARACTER,    // COMBO_CHARACTER
        &AH_COMBO_PRIMARY,      // COMBO_PRIMARY
        &AH_COMBO_SECONDARY,    // COMBO_SECONDARY
        &AH_COMBO_PSTAT,        // COMBO_STATS0
        &AH_COMBO_PSTAT,        // COMBO_STATS1
        &AH_COMBO_PSTAT,        // COMBO_STATS2
    };

    // private
    //------------------------------------------------------------------------
    static FilterPrimaryId _SecondaryToPrimaryId( FilterSecondaryId id )
    {
        if( id < FILTER_SEC_2H_ALL )
            return FILTER_PRI_1H;
        if( id < FILTER_SEC_OH_ALL )
            return FILTER_PRI_2H;
        if( id < FILTER_SEC_ARMOR_ALL )
            return FILTER_PRI_OH;
        if( id < FILTER_SEC_FOLLOWER_ALL )
            return FILTER_PRI_ARMOR;
        return FILTER_PRI_FOLLOWER;
    }

    // public
    //------------------------------------------------------------------------
    AuctionInterface::AuctionInterface( Game& game ):
        _game(game),
        _trainer(game.GetTrainer()),
        queries(0),
        _tab_primary(INVALID_ID),
        _tab_secondary(INVALID_ID),
        _active(false)
    {
        init = clock();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::Start()
    {
        _active = true;
        _Reset();
        return true;
    }

    //------------------------------------------------------------------------
    void AuctionInterface::Stop()
    {
        _active = false;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteBuyout( Long buyout, Bool randomize )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        if(buyout < 0)
            _game.SendInputText(AH_INPUT_BUYOUT.x, AH_INPUT_BUYOUT.y, "");
        else
        {
            if(randomize)
                buyout += rand() % (60 + buyout / 100);
            _game.SendInputText(AH_INPUT_BUYOUT.x, AH_INPUT_BUYOUT.y, "%u", buyout);
        }
        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadBuyout( Long& value )
    {
        TextString buyout_text;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // read buyout text
        _game.GetInputText(AH_INPUT_BUYOUT.x, AH_INPUT_BUYOUT.y, buyout_text, sizeof(buyout_text));

        // convert
        value = atoi(buyout_text);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteUnique( const Char* string )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // write unique text
        _game.SendInputText(AH_INPUT_UNIQUE.x, AH_INPUT_UNIQUE.y, "%s", string);

        return true;
    }
    
    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadUnique( TextString& string )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // read unique text
        _game.GetInputText(AH_INPUT_UNIQUE.x, AH_INPUT_UNIQUE.y, string, sizeof(TextString));

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterChar( FilterCharId char_id )
    {
        ULong   option_count;
        Index   dummy_id;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // read character id
        if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_CHARACTER, dummy_id, option_count) || option_count <= FILTER_CHAR_COUNT)
            return false;

        // select character
        if(!_WriteComboBox(Trainer::OBJECT_COMBO_CHARACTER, char_id + (option_count - FILTER_CHAR_COUNT)))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterType( FilterSecondaryId secondary_id )
    {
        Bits            chars_allowed = AH_COMBO_SECONDARY[secondary_id].character;
        ULong           option_count;
        ULong           char_option_offset;
        FilterCharId    char_id;
        FilterPrimaryId primary_id;
        FilterPrimaryId requested_primary_id = _SecondaryToPrimaryId(secondary_id);

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // read character id
        if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_CHARACTER, reinterpret_cast<Index&>(char_id), option_count) || option_count <= FILTER_CHAR_COUNT)
            return false;
        char_option_offset = (option_count - FILTER_CHAR_COUNT);

        // select different character if item not available
        if((chars_allowed & BIT(char_id - char_option_offset)) == 0)
        {
            char_id = static_cast<FilterCharId>(Tools::FirstBitIndex(chars_allowed));

            // select character
            if(!_WriteComboBox(Trainer::OBJECT_COMBO_CHARACTER, char_id + char_option_offset))
                return false;
        }

        // read primary id
        if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_PRIMARY, reinterpret_cast<Index&>(primary_id), option_count))
            return false;

        // select requested primary id if different from read primary id
        if(primary_id != requested_primary_id)
            if(!_WriteComboBox(Trainer::OBJECT_COMBO_PRIMARY, requested_primary_id))
                return false;

        // select secondary
        if(!_WriteComboBox(Trainer::OBJECT_COMBO_SECONDARY, secondary_id))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMin( Long level )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        if( level <= 0 )
            _game.SendInputText(AH_INPUT_LEVEL_MIN.x, AH_INPUT_LEVEL_MIN.y, "");
        else
            _game.SendInputText(AH_INPUT_LEVEL_MIN.x, AH_INPUT_LEVEL_MIN.y, "%u", level);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMax( Long level )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        if( level <= 0 )
            _game.SendInputText(AH_INPUT_LEVEL_MAX.x, AH_INPUT_LEVEL_MAX.y, "");
        else
            _game.SendInputText(AH_INPUT_LEVEL_MAX.x, AH_INPUT_LEVEL_MAX.y, "%u", level);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterRarity( FilterRarityId id )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        return _WriteComboBox(Trainer::OBJECT_COMBO_RARITY, id);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterStat( Index index, ItemStatId id, ULong value )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select stat
        if(!_WriteComboBox(Trainer::OBJECT_COMBO_PSTAT0 + index, id))
            return false;

        // set value
        _game.SendInputText(AH_INPUT_PSTAT_VALUE[index].x, AH_INPUT_PSTAT_VALUE[index].y, "%u", value );

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionSearch()
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // wait if needed
        _WaitForQueriesPerHour();

        // hit search button
        _game.MouseClick(AH_BUTTON_SEARCH.x, AH_BUTTON_SEARCH.y);

        // wait if requested
        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSortDpsArmor()
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // wait if needed
        _WaitForQueriesPerHour();

        // click sort column header
        _game.MouseClick(AH_LIST_SORT_DPSARMOR.x, AH_LIST_SORT_DPSARMOR.y);

        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSortBuyout()
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // wait if needed
        _WaitForQueriesPerHour();

        // click sort column header
        _game.MouseClick(AH_LIST_SORT_BUYOUT.x, AH_LIST_SORT_BUYOUT.y);

        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListNextPage()
    {
        Bool listing_status;
        Bool status = false;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // use opportunity to close any popups
        //_game.MouseClick(AH_BUTTON_BUYOUT_CONFIRM_OK.x, AH_BUTTON_BUYOUT_CONFIRM_OK.y);

        // check listing status
        if(_trainer.ReadListNextStatus(listing_status) && listing_status)
        {
            clock_t timeElapsed = _WaitForQueriesPerHour();
            // wait before clicking next
            if (timeElapsed < GAME_NEXTPAGE_DELAY)
                Sleep(GAME_NEXTPAGE_DELAY - timeElapsed);

            // hit next page button
            _game.MouseClick(AH_LIST_NEXT_BUTTON.x, AH_LIST_NEXT_BUTTON.y);

            // wait search
            if(_WaitSearch())
                status = true;
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBid( Index index, ULong bid )
    {
        Bool status;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select item index
        HoverListItem(index, true);

        // hit bid button
        _game.MouseClick(AH_BUTTON_BID.x, AH_BUTTON_BID.y);

        // set bid amount if any
        if( bid != 0 )
            _game.SendInputText(AH_INPUT_BID.x, AH_INPUT_BID.y, "%u", bid);

        // hit confirm button
        _game.MouseClick(AH_BUTTON_BUYOUT_CONFIRM.x, AH_BUTTON_BUYOUT_CONFIRM.y);

        // hit ok button until done
        do
        {
            _game.MouseClick(AH_BUTTON_BUYOUT_CONFIRM_OK.x, AH_BUTTON_BUYOUT_CONFIRM_OK.y);
        }
        while(_active && _trainer.ReadPopupStatus(status) && status);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBuyout( Index index )
    {
        Bool status;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select item index
        HoverListItem(index, true);

        // hit buyout button
        _game.MouseClick(AH_BUTTON_BUYOUT.x, AH_BUTTON_BUYOUT.y);

        // hit confirm button
        _game.MouseClick(AH_BUTTON_BUYOUT_CONFIRM.x, AH_BUTTON_BUYOUT_CONFIRM.y);

        // hit ok button until done
        do
        {
            _game.MouseClick(AH_BUTTON_BUYOUT_CONFIRM_OK.x, AH_BUTTON_BUYOUT_CONFIRM_OK.y);
        }
        while(_active && _trainer.ReadPopupStatus(status) && status);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionSendToStash()
    {
        Trainer::ButtonStatus status;

        Tab(UI_TAB_COMPLETED);

        // check status
        if(!_trainer.ReadSendToStashStatus(status) || status < Trainer::BUTTON_ENABLED)
            return false;

        // hit send to stash button
        _game.MouseClick(COORDS[UI_BUTTON_SENDTOSTASH].x, COORDS[UI_BUTTON_SENDTOSTASH].y);

        // wait status
        while(_active && _trainer.ReadSendToStashStatus(status) && status == Trainer::BUTTON_DISABLED)
            _game.SleepFrames(1);

        return true;
    }


    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionReLogin( const Char* account, const Char* password )
    {
        Bool status;

        // read auction status
        if(!_trainer.ReadAuctionMainStatus(status))
            return false;

        // if auction main still alive keep going!
        if(status)
            return false;

        // clear error
        _game.MouseClick(COORDS[UI_POPUP_ERROR].x, COORDS[UI_POPUP_ERROR].y);

        // logout delay
        _game.Sleep(AH_RELOGIN_LOGOUT_DELAY);

        // login loop
        while(true)
        {
            // active check
            if(!_active)
                return false;

            // set account
            _game.SendInputText(AH_RELOGIN_ACCOUNT.x, AH_RELOGIN_ACCOUNT.y, account);

            // set password
            _game.SendInputText(AH_RELOGIN_PASSWORD.x, AH_RELOGIN_PASSWORD.y, password);

            // login
            _game.MouseClick(AH_RELOGIN_LOGIN.x, AH_RELOGIN_LOGIN.y);

            // close any popups
            _game.MouseClick(COORDS[UI_POPUP_ERROR].x, COORDS[UI_POPUP_ERROR].y);

            // read login status
            if(!_trainer.ReadLoginStatus(status))
                return false;

            // break if logged in
            if(status)
                break;

            // wait a little
            _game.Sleep(10);
        }

        // wait until in auction house
        while(true)
        {
            // active check
            if(!_active)
                return false;

            // post login delay
            _game.Sleep(AH_RELOGIN_POSTLOGIN_DELAY);

            // click auction house button
            _game.MouseClick(AH_RELOGIN_AUCTIONHOUSE.x, AH_RELOGIN_AUCTIONHOUSE.y, false);

            // auction enter delay
            _game.Sleep(AH_RELOGIN_AUCTIONHOUSE_DELAY);

            // run retrain
            if(_trainer.Train())
                break;
        }

        // reset tabs
        _Reset();

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::HoverListItem( Index index, Bool select )
    {
        Double x = AH_LIST_BEGIN.x + AH_LIST_ICON.x / 2;
        Double y = AH_LIST_BEGIN.y + (AH_LIST_ICON.y / 2) + index * AH_LIST_ICON.y;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // hover item to update current item tooltip
        _game.MouseMove(x, y);

        // also click to select (for use with bid/buyout)
        if(select)
            _game.MouseClick(x, y);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadListCount( ULong& count )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);
        return _trainer.ReadListCount(count);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadListItem( Index index, Item& item )
    {
        Bool status = false;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // empty item
        item.Empty();

        // clear hover item
        if(_trainer.ClearHoverItem())
        {
            // select item
            HoverListItem(index, false);

            // read item listing
            if(_trainer.ReadListItem(index, item))
            {
                // read item stat
                if(_trainer.ReadHoverItem(item))
                {
                    // read time left
                    if(_trainer.ReadListTimeLeft(index, item))
                        status = true;
                }
            }
        }

        return status;
    }

    Bool AuctionInterface::GetGold(ULong& gold)
    {
        return _trainer.ReadPlayerGold(gold);
    }

    //------------------------------------------------------------------------
    ULong AuctionInterface::ParseTime( const Char* text )
    {
        TextString target1, target2;
        if (sscanf(text, "%s %s",target1, target2) == 0)
            return 0;

        long days = 0, hours = 0, minutes = 0;

        if (strchr(target1, 'd'))
            days = atol(target1);

        if (strchr(target1, 'h'))
            hours = atol(target1);

        if (strchr(target1, 'm'))
            minutes = atol(target1);

        if (strchr(target2, 'h'))
            hours = atol(target2);

        if (strchr(target2, 'm'))
            minutes = atol(target2);

        return 1440*days + 60*hours + minutes;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::SellStashItem( Index column, Index row, ULong starting, ULong buyout )
    {
        Bool status;

        Tab(UI_TAB_SELL);

        // select item
        HoverStashItem(column, row, true);

        // get popup status
        if(!_trainer.ReadPopupStatus(status))
            return false;

        // clear popup if true and fail
        if(status)
        {
            _game.MouseClick(COORDS[UI_POPUP_ERROR].x, COORDS[UI_POPUP_ERROR].y);
            return false;
        }

        // write starting price
        _game.SendInputText(COORDS[UI_INPUT_SELLSTARTING].x, COORDS[UI_INPUT_SELLSTARTING].y, "%u", starting);

        // write buyout price
        _game.SendInputText(COORDS[UI_INPUT_SELLBUYOUT].x, COORDS[UI_INPUT_SELLBUYOUT].y, "%u", buyout);

        // create auction
        _game.MouseClick(COORDS[UI_INPUT_CREATEAUCTION].x, COORDS[UI_INPUT_CREATEAUCTION].y);

        // wait a few frames
        _game.SleepFrames(4);

        // there should be a popup. fail otherwise
        if(!_trainer.ReadPopupStatus(status) || !status)
            return false;

        // hit ok button until done
        do
        {
            _game.MouseClick(COORDS[UI_POPUP_OK].x, COORDS[UI_POPUP_OK].y);
        }
        while(_active && _trainer.ReadPopupStatus(status) && status);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::HoverStashItem( Index column, Index row, Bool select )
    {
        Double x = COORDS[UI_CONTAINER_STASHBOX00].x + (column * COORDS[UI_CONTAINER_STASHBOXSIZE].x);
        Double y = COORDS[UI_CONTAINER_STASHBOX00].y + (row * COORDS[UI_CONTAINER_STASHBOXSIZE].y);

        Tab(UI_TAB_SELL);

        // hover item to update current item tooltip
        _game.MouseMove(x, y, true);

        // also click to select (for use with bid/buyout)
        if(select)
            _game.MouseClick(x, y);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadStashItem( Index column, Index row, Item& item )
    {
        Bool status = false;

        Tab(UI_TAB_SELL);

        // empty item
        item.Empty();

        // clear hover item
        if(_trainer.ClearHoverItem())
        {
            // select item
            HoverStashItem(column, row, false);

            // read item stat
            if(_trainer.ReadHoverItem(item))
                status = true;
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::Tab( Id primary, Id secondary )
    {
        // set primary tab
        if(primary != _tab_primary)
        {
            _game.MouseClick(COORDS[primary].x, COORDS[primary].y);
            _tab_primary = primary;
            _tab_secondary = INVALID_ID;
        }

        // set secondary tab
        if(secondary != INVALID_ID && secondary != _tab_secondary)
        {
            _game.MouseClick(COORDS[secondary].x, COORDS[secondary].y);
            _tab_secondary = secondary;
        }

        return true;
    }

    //------------------------------------------------------------------------
    void AuctionInterface::HoverGround()
    {
        // hover to reset another hover
        _game.MouseMove(0, 0.005);

    }

    // private
    //------------------------------------------------------------------------
    Bool AuctionInterface::_WriteComboBox( Id combo_id, Id option_id)
    {
        assert(combo_id >= Trainer::OBJECT_COMBO_RARITY && combo_id <= Trainer::OBJECT_COMBO_PSTAT2);
        Index   option_index;
        ULong   option_count;
        Bool    status = false;

        // calculate option index
        if(_CalculateOptionIndex(option_index, option_count, combo_id, option_id))
        {
            // write option index
            if(_trainer.WriteComboIndex(combo_id, option_index))
            {
                // refresh combobox
                if(_WriteComboRefresh(combo_id, option_index, option_count))
                    status = true;
            }
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_WriteComboRefresh( Id combo_id, Index option_index, ULong option_count )
    {
        const Coordinate&   coordinate =    COORDS[combo_id + UI_COMBO_RARITY];
        const Coordinate&   size =          COORDS[UI_COMBO_SIZE];
        ULong               window_height = _game.GetWindow().GetHeight();
        ULong               combo_height =  Tools::Min(COMBO_HEIGHT[combo_id], option_count);
        ULong               dummy_count;
        ULong               confirm_index;

        // determine box selector height
        Double size_y = window_height > COMBO_BOX_REZMAP_MAX ?
            (size.y * window_height) :
            COMBO_SELECTOR_REZMAP[Tools::Max(window_height, COMBO_BOX_REZMAP_MIN) - COMBO_BOX_REZMAP_MIN];

        // open dropdown
        _game.MouseClickAbsolute(_game.X(coordinate.x + size.x / 2, true), _game.Y(coordinate.y, true) - (ULong)(size_y * .8));

        // calculate screen index
        Index screen_index = combo_height - Tools::Min(option_count - option_index, combo_height);

        // click selection
        _game.MouseClickAbsolute(_game.X(coordinate.x + size.x / 2, true), _game.Y(coordinate.y, true) + (ULong)((screen_index * size_y) + (size_y / 2)));

        // confirm option index
        if(!_trainer.ReadComboIndex(combo_id, confirm_index, dummy_count) || confirm_index != option_index)
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_CalculateOptionIndex( Index& option_index, ULong& option_count, Id combo_id, Id option_id )
    {
        IgnoreCollection ignores;

        // get option count
        if(!_trainer.ReadComboIndex(combo_id, option_index, option_count))
            return false;

        // calculate option index
        if(combo_id >= Trainer::OBJECT_COMBO_SECONDARY)
        {
            Index   primary_id;
            ULong   dummy_count;

            // read primary
            if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_PRIMARY, primary_id, dummy_count))
                return false;

            // stat
            if(combo_id >= Trainer::OBJECT_COMBO_PSTAT0)
            {
                Index   secondary_index;
                Id      secondary_id;

                // read secondary
                if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_SECONDARY, secondary_index, dummy_count))
                    return false;

                // get secondary id
                if(!_OptionIndexToId(secondary_id, secondary_index, primary_id, AH_COMBO_SECONDARY))
                    return false;

                // read current stat indexes and build ignore list
                if(combo_id != ITEM_STAT_NONE)
                {
                    for( Id stat_id = Trainer::OBJECT_COMBO_PSTAT0; stat_id <= Trainer::OBJECT_COMBO_PSTAT2; stat_id++ )
                    {
                        // ignore target
                        if(stat_id != combo_id)
                        {
                            Index stat_index;

                            // read statN
                            if(!_trainer.ReadComboIndex(stat_id, stat_index, dummy_count))
                                return false;

                            // add ignore
                            if(stat_index != 0)
                                ignores.Push(stat_index);
                        }
                    }
                }

                // calculate stat index
                if(!_OptionIdToIndex(option_index, option_id, secondary_id, AH_COMBO_PSTAT, ignores))
                    return false;

                // adjust option count by ignore count
                //option_count -= ignores.GetCount();
            }
            // secondary
            else if(!_OptionIdToIndex(option_index, option_id, primary_id, AH_COMBO_SECONDARY, ignores))
                return false;
        }
        // rarity, character, primary
        else if(!_OptionIdToIndex(option_index, option_id, INVALID_ID, *_COMBOBOX_MAP[combo_id], ignores))
            option_index = option_id;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_OptionIndexToId( Id& option_id, Index option_index, Id group_id, const ComboBox& box ) const
    {
        const ComboBox::OptionCollection& options = box.GetOptions();

        for( Index i = 0, index = 0; i < options.GetCount(); i++ )
            if(B64(group_id) & options[i].group)
                if(option_index == index++)
                {
                    option_id = i;
                    return true;
                }

        return false;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_OptionIdToIndex( Index& option_index, Id option_id, Id group_id, const ComboBox& box, IgnoreCollection& ignores ) const
    {
        const ComboBox::OptionCollection& options = box.GetOptions();

        for( Index i = 0, index = 0; i < options.GetCount(); i++ )
        {
            if(group_id == INVALID_ID || (B64(group_id) & options[i].group))
            {
                IgnoreIterator ignore = ignores.FlatSearch(index);

                if(i == option_id)
                {
                    option_index = index;
                    return true;
                }
                if(ignore != ignores.End())
                    *ignore = INVALID_ID;
                else
                    index++;
            }
        }

        return false;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_WaitSearch()
    {
        ULong count = 0;

        // poll listing status
        for( Index i = 0; _active && i < AH_LIST_WAIT_ITERATIONS; i++ )
        {
            Bool busy;

            // poll delay
            _game.SleepFrames(1);

            // read listing status
            if(!_trainer.ReadListCount(count))
                return false;

            // success if listing found
            if(count > 0)
            {
                queries++;
                return true;
            }

            // fail if no longer busy but no listing read
            if(!_trainer.ReadSearchBusyStatus(busy) || !busy)
                return false;
        }

        return false;
    }

    //------------------------------------------------------------------------
    clock_t AuctionInterface::_WaitForQueriesPerHour()
    {
        clock_t currTime = clock();
        if (GAME_MAX_QUERIES_PER_HOUR > 0)
        {
            GAME_CURRENT_QUERIES_PER_HOUR = ((float)queries/((currTime - init)/1000))*60*60;

            while (GAME_CURRENT_QUERIES_PER_HOUR > GAME_MAX_QUERIES_PER_HOUR)
            {
                _game.Sleep(25);
                GAME_CURRENT_QUERIES_PER_HOUR = ((float)queries/((clock() - init)/1000))*60*60;
            }
        }
        return clock() - currTime; // time waited
    }

    //------------------------------------------------------------------------
    void AuctionInterface::_Reset()
    {
        _tab_primary = INVALID_ID;
        _tab_secondary = INVALID_ID;
    }
}
