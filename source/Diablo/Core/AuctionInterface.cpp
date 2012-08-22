#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>

namespace Diablo
{
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
        _tab_primary(INVALID_ID),
        _tab_secondary(INVALID_ID),
        _active(false)
    {
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
    Bool AuctionInterface::WriteFilterBuyout( Number buyout, Bool randomize )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        if(randomize && buyout > 0)
        {
            ULong wbuyout = static_cast<ULong>(NUMBER_WHOLE(buyout));
            ULong range = wbuyout / 20; // 5%
            ULong rvalue = Tools::UniqueRandom<AH_INPUT_BUYOUT_RANDOM_LIMIT>(range);

            buyout += NUMBER(rvalue, 0);
        }
        _game.SendInputNumber(COORDS[UI_INPUT_FILTERBUYOUT].x, COORDS[UI_INPUT_FILTERBUYOUT].y, buyout);

        return true;
    }

    Bool AuctionInterface::ReadFilterBuyout( Number& value )
    {
        // read buyout value
        return _ReadInputNumber(Trainer::OBJECT_INPUT_BUYOUT, value);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterUnique( const Char* string )
    {
        // write unique text
        _game.SendInputText(COORDS[UI_INPUT_FILTERUNIQUE].x, COORDS[UI_INPUT_FILTERUNIQUE].y, "%s", string);
        return true;
    }
    
    Bool AuctionInterface::ReadFilterUnique( TextString& string )
    {
        // read unique text
        *string = 0;
        return _trainer.ReadInputText(Trainer::OBJECT_INPUT_UNIQUE, string);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterChar( FilterCharId char_id )
    {
        ULong option_count;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // ignore default
        if(char_id == FILTER_CHAR_DEFAULT)
            return false;

        // get option count
        if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_CHARACTER, NULL, &option_count) || option_count <= FILTER_CHAR_COUNT)
            return false;

        // select character
        if(!_WriteComboBox(Trainer::OBJECT_COMBO_CHARACTER, char_id + (option_count - FILTER_CHAR_COUNT)))
            return false;

        return true;
    }

    Bool AuctionInterface::ReadFilterChar( FilterCharId& char_id )
    {
        Index   index;
        ULong   option_count;

        // read character index
        if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_CHARACTER, &index, &option_count) || option_count <= FILTER_CHAR_COUNT)
            return false;
        ULong base = (option_count - FILTER_CHAR_COUNT);

        // if index below base then default character
        if(index < base)
            char_id = FILTER_CHAR_DEFAULT;
        // calculate character id adjusting for instanced characters
        else
            char_id = static_cast<FilterCharId>(index - base);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterPrimary( FilterPrimaryId primary_id )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        return _WriteComboBox(Trainer::OBJECT_COMBO_PRIMARY, primary_id);
    }

    Bool AuctionInterface::ReadFilterPrimary( FilterPrimaryId& primary_id )
    {
        // read primary index/id
        return _trainer.ReadComboIndex(Trainer::OBJECT_COMBO_PRIMARY, reinterpret_cast<Index*>(&primary_id));
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterSecondary( FilterSecondaryId secondary_id )
    {
        Bits            chars_allowed = AH_COMBO_SECONDARY[secondary_id].character;
        FilterCharId    char_id;
        FilterPrimaryId primary_id;
        FilterPrimaryId requested_primary_id = _SecondaryToPrimaryId(secondary_id);

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // read character id
        if(!ReadFilterChar(char_id))
            return false;

        // select different character if type not available for current one
        if( (chars_allowed & BIT(char_id)) == 0 &&
            !WriteFilterChar(static_cast<FilterCharId>(Tools::FirstBitIndex(chars_allowed))))
            return false;

        // read primary id
        if(!ReadFilterPrimary(primary_id))
            return false;

        // select requested primary id if different from read primary id
        if(primary_id != requested_primary_id)
            if(!WriteFilterPrimary(requested_primary_id))
                return false;

        // select secondary
        if(!_WriteComboBox(Trainer::OBJECT_COMBO_SECONDARY, secondary_id))
            return false;

        return true;
    }

    Bool AuctionInterface::ReadFilterSecondary( FilterSecondaryId& secondary_id )
    {
        Index           index;
        FilterPrimaryId primary_id;

        // read primary id
        if(!ReadFilterPrimary(primary_id))
            return false;

        // read secondary index
        if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_SECONDARY, &index))
            return false;

        // calculate secondary id
        if(!_OptionIndexToId(reinterpret_cast<Id&>(secondary_id), index, primary_id, AH_COMBO_SECONDARY))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterRarity( FilterRarityId id )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        return _WriteComboBox(Trainer::OBJECT_COMBO_RARITY, id);
    }

    Bool AuctionInterface::ReadFilterRarity( FilterRarityId& rarity_id )
    {
        // read rarity index/id
        return _trainer.ReadComboIndex(Trainer::OBJECT_COMBO_RARITY, reinterpret_cast<Index*>(&rarity_id));
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterStat( Index index, ItemStatId id, Number value )
    {
        assert(index < AH_INPUT_PSTAT_LIMIT);
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select stat
        if(!_WriteComboBox(Trainer::OBJECT_COMBO_PSTAT0 + index, id))
            return false;

        // set value
        _game.SendInputNumber(COORDS[index + UI_INPUT_FILTERPSTAT0].x, COORDS[index + UI_INPUT_FILTERPSTAT0].y, value);

        return true;
    }

    Bool AuctionInterface::ReadFilterStat( Index index, ItemStatId& id, Number& value )
    {
        assert(index < AH_INPUT_PSTAT_LIMIT);
        IgnoreCollection    ignores;
        Index               existing;
        FilterSecondaryId   secondary_id;

        // read secondary id
        if(!ReadFilterSecondary(secondary_id))
            return false;

        // read existing indexes
        for( Index i = 0; i < AH_INPUT_PSTAT_LIMIT; i++ )
        {
            Index rindex;

            // read index
            if(!_trainer.ReadComboIndex(i + Trainer::OBJECT_COMBO_PSTAT0, &rindex))
                return false;

            // save existing index
            if(i == index)
                existing = rindex;
            // add ignore
            else if(rindex != 0)
                ignores.Push(rindex);
        }

        // calculate stat id
        if(!_OptionIndexToId(reinterpret_cast<Id&>(id), existing, secondary_id, AH_COMBO_PSTAT, ignores))
            return false;

        // read value text
        return _ReadInputNumber(index + Trainer::OBJECT_INPUT_PSTAT0, value);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMin( Number level )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        _game.SendInputNumber(COORDS[UI_INPUT_FILTERLEVELMIN].x, COORDS[UI_INPUT_FILTERLEVELMIN].y, level);

        return true;
    }

    Bool AuctionInterface::ReadFilterLevelMin( Number& level )
    {
        return _ReadInputNumber(Trainer::OBJECT_INPUT_LEVELMIN, level);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMax( Number level )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        _game.SendInputNumber(COORDS[UI_INPUT_FILTERLEVELMAX].x, COORDS[UI_INPUT_FILTERLEVELMAX].y, level);

        return true;
    }

    Bool AuctionInterface::ReadFilterLevelMax( Number& level )
    {
        return _ReadInputNumber(Trainer::OBJECT_INPUT_LEVELMAX, level);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionSearch()
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // hit search button
        _game.MouseClick(COORDS[UI_BUTTON_SEARCH].x, COORDS[UI_BUTTON_SEARCH].y);

        // wait if requested
        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSort( UiId id )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // click sort column header
        _game.MouseClick(COORDS[id].x, COORDS[id].y);

        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListNextPage()
    {
        Bool listing_status;
        Bool status = false;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // check listing status
        if(_trainer.ReadListNextStatus(listing_status) && listing_status)
        {
            // hit next page button
            _game.MouseClick(COORDS[UI_LBUTTON_PAGENEXT].x, COORDS[UI_LBUTTON_PAGENEXT].y);

            // wait search
            if(_WaitSearch())
                status = true;
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBid( Index index, Number bid )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select item index
        HoverListItem(index, true);

        // hit bid button
        _game.MouseClick(COORDS[UI_BUTTON_BID].x, COORDS[UI_BUTTON_BID].y);

        // set bid amount if any
        if( bid != 0 )
            _game.SendInputNumber(COORDS[UI_INPUT_MAXBID].x, COORDS[UI_INPUT_MAXBID].y, bid);

        // hit confirm button
        _game.MouseClick(COORDS[UI_BUTTON_BIDCONFIRM].x, COORDS[UI_BUTTON_BIDCONFIRM].y);

        // clear ok popup
        _ClearPopups();

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBuyout( Index index )
    {
        Trainer::ButtonStatus   button_status;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select item index
        HoverListItem(index, true);

        // check button status
        if(!_trainer.ReadButtonStatus(button_status, Trainer::OBJECT_BUTTON_BUYOUT) || button_status < Trainer::BUTTON_ENABLED)
            return false;

        // hit buyout button
        _game.MouseClick(COORDS[UI_BUTTON_BUYOUT].x, COORDS[UI_BUTTON_BUYOUT].y);

        // hit confirm button
        _game.MouseClick(COORDS[UI_BUTTON_BUYOUTCONFIRM].x, COORDS[UI_BUTTON_BUYOUTCONFIRM].y);

        // clear ok popup
        _ClearPopups();

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionSendToStash()
    {
        Trainer::ButtonStatus status;

        Tab(UI_TAB_COMPLETED);

        // check status
        if(!_trainer.ReadButtonStatus(status, Trainer::OBJECT_BUTTON_SENDTOSTASH) || status < Trainer::BUTTON_ENABLED)
            return false;

        // hit send to stash button
        _game.MouseClick(COORDS[UI_BUTTON_SENDTOSTASH].x, COORDS[UI_BUTTON_SENDTOSTASH].y);

        // wait status
        while(_active && _trainer.ReadButtonStatus(status, Trainer::OBJECT_BUTTON_SENDTOSTASH) && status == Trainer::BUTTON_DISABLED)
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

            // read login status
            if(!_trainer.ReadLoginStatus(status))
                return false;

            // break if logged in
            if(status)
                break;

            // set account
            _game.SendInputText(COORDS[UI_INPUT_LOGINACCOUNT].x, COORDS[UI_INPUT_LOGINACCOUNT].y, account);

            // set password
            _game.SendInputText(COORDS[UI_INPUT_LOGINPASSWORD].x, COORDS[UI_INPUT_LOGINPASSWORD].y, password);

            // login
            _game.MouseClick(COORDS[UI_BUTTON_LOGIN].x, COORDS[UI_BUTTON_LOGIN].y);

            // close any popups
            _game.MouseClick(COORDS[UI_POPUP_ERROR].x, COORDS[UI_POPUP_ERROR].y);

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

            // close character profile in case previous popup closer call opened it
            _game.MouseClick(COORDS[UI_BUTTON_PROFILECLOSE].x, COORDS[UI_BUTTON_PROFILECLOSE].y);

            // click auction house button
            _game.MouseClick(COORDS[UI_BUTTON_MAINAUCTIONHOUSE].x, COORDS[UI_BUTTON_MAINAUCTIONHOUSE].y, false);

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
        Double x = COORDS[UI_CONTAINER_LISTICON0].x + COORDS[UI_CONTAINER_LISTICONSIZE].x / 2;
        Double y = COORDS[UI_CONTAINER_LISTICON0].y + (COORDS[UI_CONTAINER_LISTICONSIZE].y / 2) + index * COORDS[UI_CONTAINER_LISTICONSIZE].y;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // click to select (for use with bid/buyout)
        if(select)
            _game.MouseClick(x, y);
        // hover item to update current item tooltip
        else
            _game.MouseMove(x, y);

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

            // wait a frame
            _game.SleepFrames(1);

            // read item listing
            if(_trainer.ReadListItem(index, item))
            {
                // read item stat
                if(_trainer.ReadHoverItem(item))
                    status = true;
            }
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::SellStashItem( Index column, Index row, Number starting, Number buyout )
    {
        Tab(UI_TAB_SELL);

        // select item
        HoverStashItem(column, row, true);

        // if an error popup was cleared then fail
        if(_ClearPopups())
            return false;

        // write starting price
        _game.SendInputNumber(COORDS[UI_INPUT_SELLSTARTING].x, COORDS[UI_INPUT_SELLSTARTING].y, starting);

        // write buyout price
        _game.SendInputNumber(COORDS[UI_INPUT_SELLBUYOUT].x, COORDS[UI_INPUT_SELLBUYOUT].y, buyout);

        // create auction
        _game.MouseClick(COORDS[UI_BUTTON_CREATEAUCTION].x, COORDS[UI_BUTTON_CREATEAUCTION].y);

        // wait a few frames
        _game.SleepFrames(4);

        // there should be a popup. fail otherwise
        if(!_ClearPopups())
            return false;

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

        // end existing hover
        HoverGround();

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
    Bool AuctionInterface::_ClearPopups()
    {
        static const UiId types[] = { UI_POPUP_ERROR, UI_POPUP_OK };
        Bool status;

        // fail if nothing to close
        if(!_trainer.ReadPopupStatus(status) || !status)
            return false;

        // click until closed
        while(_active)
        {
            // handle each popup type
            for( Index i = 0; i < ACOUNT(types); i++ )
            {
                // click closer button
                _game.MouseClick(COORDS[types[i]].x, COORDS[types[i]].y);

                // read status
                if(!_trainer.ReadPopupStatus(status))
                    return false;

                // success if false
                if(!status)
                    return true;
            }
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_WriteComboBox( Id combo_id, Id option_id )
    {
        assert(combo_id >= Trainer::OBJECT_COMBO_RARITY && combo_id <= Trainer::OBJECT_COMBO_PSTAT5);
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
        ULong               drop_count =  Tools::Min(COMBO_DROP_COUNT[combo_id], option_count);
        ULong               confirm_index;

        // determine box selector height
        Double size_y = window_height > COMBO_BOX_REZMAP_MAX ?
            size.y :
            ( COMBO_SELECTOR_REZMAP[Tools::Max(window_height, COMBO_BOX_REZMAP_MIN) - COMBO_BOX_REZMAP_MIN] / window_height );

        // open dropdown
        _game.MouseClick(coordinate.x + size.x / 2, coordinate.y - size_y * .8);

        // calculate screen index
        Index screen_index = drop_count - Tools::Min(option_count - option_index, drop_count);

        // calculated constrained combo y (due to resolution)
        Double combo_bottom = coordinate.y + (size_y * drop_count);
        Double constrained_y = (combo_bottom > 1.0) ? coordinate.y - (combo_bottom - 1.0) : coordinate.y;

        // click selection
        _game.MouseClick(coordinate.x + size.x / 2, constrained_y + (screen_index * size_y) + (size_y / 2));

        // confirm option index
        if(!_trainer.ReadComboIndex(combo_id, &confirm_index) || confirm_index != option_index)
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_CalculateOptionIndex( Index& option_index, ULong& option_count, Id combo_id, Id option_id )
    {
        IgnoreCollection ignores;

        // get option count
        if(!_trainer.ReadComboIndex(combo_id, &option_index, &option_count))
            return false;

        // calculate option index
        if(combo_id >= Trainer::OBJECT_COMBO_SECONDARY)
        {
            Index   primary_id;

            // read primary
            if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_PRIMARY, &primary_id))
                return false;

            // stat
            if(combo_id >= Trainer::OBJECT_COMBO_PSTAT0)
            {
                Index   secondary_index;
                Id      secondary_id;

                // read secondary
                if(!_trainer.ReadComboIndex(Trainer::OBJECT_COMBO_SECONDARY, &secondary_index))
                    return false;

                // get secondary id
                if(!_OptionIndexToId(secondary_id, secondary_index, primary_id, AH_COMBO_SECONDARY))
                    return false;

                // read current stat indexes and build ignore list
                if(combo_id != ITEM_STAT_NONE)
                {
                    for( Id stat_id = Trainer::OBJECT_COMBO_PSTAT0; stat_id <= Trainer::OBJECT_COMBO_PSTAT5; stat_id++ )
                    {
                        // ignore target
                        if(stat_id != combo_id)
                        {
                            Index stat_index;

                            // read statN
                            if(!_trainer.ReadComboIndex(stat_id, &stat_index))
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
        else if(!_OptionIdToIndex(option_index, option_id, INVALID_ID, *AH_COMBO_MAP[combo_id], ignores))
            option_index = option_id;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_OptionIndexToId( Id& option_id, Index option_index, Id group_id, const ComboBox& box, const IgnoreCollection& ignores ) const
    {
        const ComboBox::OptionCollection& options = box.GetOptions();
        IgnoreCollection tignores = ignores;

        for( Index i = 0, index = 0; i < options.GetCount(); i++ )
        {
            if(B64(group_id) & options[i].group)
            {
                IgnoreIterator ignore = tignores.FlatSearch(index);

                if(option_index == index)
                {
                    option_id = i;
                    return true;
                }
                if(ignore != tignores.End())
                    *ignore = INVALID_ID;
                else
                    index++;
            }
        }

        return false;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_OptionIdToIndex( Index& option_index, Id option_id, Id group_id, const ComboBox& box, const IgnoreCollection& ignores ) const
    {
        const ComboBox::OptionCollection& options = box.GetOptions();
        IgnoreCollection tignores = ignores;

        for( Index i = 0, index = 0; i < options.GetCount(); i++ )
        {
            if(group_id == INVALID_ID || (B64(group_id) & options[i].group))
            {
                IgnoreIterator ignore = tignores.FlatSearch(index);

                if(i == option_id)
                {
                    option_index = index;
                    return true;
                }
                if(ignore != tignores.End())
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
        Trainer::ButtonStatus status = Trainer::BUTTON_DISABLED;
        ULong count = 0;

        // poll listing status
        for( Index i = 0; _active && i < AH_LIST_WAIT_ITERATIONS; i++ )
        {
            Bool auction_status;

            // poll delay
            _game.SleepFrames(1);

            // read auction status
            if(!_trainer.ReadAuctionMainStatus(auction_status) || auction_status==false)
                return false;

            // read listing status
            if(!_trainer.ReadListCount(count))
                return false;

            // success if listing found
            if(count > 0)
            {
                _game.SleepFrames(1);
                return true;
            }

            // fail if search button enabled but no results
            if(status >= Trainer::BUTTON_ENABLED)
                return false;

            // get button status
            if(!_trainer.ReadButtonStatus(status, Trainer::OBJECT_BUTTON_SEARCH))
                return false;
        }

        return false;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_ReadInputNumber( Id id, Number& number )
    {
        TextString out;

        *out = 0;
        if(!_trainer.ReadInputText(id, out) || *out == 0)
            number = NUMBER(-1,0);
        else
            number = Tools::StrToNumber(out);

        return true;
    }

    //------------------------------------------------------------------------
    void AuctionInterface::_Reset()
    {
        _tab_primary = INVALID_ID;
        _tab_secondary = INVALID_ID;
    }
}
