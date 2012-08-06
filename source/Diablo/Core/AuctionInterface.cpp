#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>

namespace Diablo
{
    //------------------------------------------------------------------------
    static const ComboBox* _COMBOBOX_MAP[] =
    {
        &AH_COMBO_CHARACTER,    // COMBO_CHARACTER
        &AH_COMBO_PRIMARY,      // COMBO_PRIMARY
        &AH_COMBO_SECONDARY,    // COMBO_SECONDARY
        &AH_COMBO_RARITY,       // COMBO_RARITY
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
        _trainer(game.GetTrainer())
    {
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteBuyout( Long buyout, Bool randomize )
    {
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

        // read buyout text
        _game.GetInputText(AH_INPUT_BUYOUT.x, AH_INPUT_BUYOUT.y, buyout_text, sizeof(buyout_text));

        // convert
        value = atoi(buyout_text);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteUnique( const Char* string )
    {
        _game.SendInputText(AH_INPUT_UNIQUE.x, AH_INPUT_UNIQUE.y, "%s", string);
        return true;
    }
    
    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadUnique( TextString& string )
    {
        // read unique text
        _game.GetInputText(AH_INPUT_UNIQUE.x, AH_INPUT_UNIQUE.y, string, sizeof(TextString));

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

        // read character id
        if(!_trainer.ReadComboBox(Trainer::COMBO_CHARACTER, reinterpret_cast<Index&>(char_id), option_count) || option_count <= FILTER_CHAR_COUNT)
            return false;
        char_option_offset = (option_count - FILTER_CHAR_COUNT);

        // select different character if item not available
        if((chars_allowed & BIT(char_id - char_option_offset)) == 0)
        {
            char_id = static_cast<FilterCharId>(Tools::FirstBitIndex(chars_allowed));

            // select character
            if(!_WriteComboBox(Trainer::COMBO_CHARACTER, char_id + char_option_offset))
                return false;
        }

        // read primary id
        if(!_trainer.ReadComboBox(Trainer::COMBO_PRIMARY, reinterpret_cast<Index&>(primary_id), option_count))
            return false;

        // select requested primary id if different from read primary id
        if(primary_id != requested_primary_id)
            if(!_WriteComboBox(Trainer::COMBO_PRIMARY, requested_primary_id))
                return false;

        // select secondary
        if(!_WriteComboBox(Trainer::COMBO_SECONDARY, secondary_id))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMin( Long level )
    {
        if( level <= 0 )
            _game.SendInputText(AH_INPUT_LEVEL_MIN.x, AH_INPUT_LEVEL_MIN.y, "");
        else
            _game.SendInputText(AH_INPUT_LEVEL_MIN.x, AH_INPUT_LEVEL_MIN.y, "%u", level);
        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMax( Long level )
    {
        if( level <= 0 )
            _game.SendInputText(AH_INPUT_LEVEL_MAX.x, AH_INPUT_LEVEL_MAX.y, "");
        else
            _game.SendInputText(AH_INPUT_LEVEL_MAX.x, AH_INPUT_LEVEL_MAX.y, "%u", level);
        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterRarity( FilterRarityId id )
    {
        return _WriteComboBox(Trainer::COMBO_RARITY, id);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterStat( Index index, ItemStatId id, ULong value )
    {
        // select stat
        if(!_WriteComboBox(Trainer::COMBO_PSTAT0 + index, id))
            return false;

        // set value
        _game.SendInputText(AH_INPUT_PSTAT_VALUE[index].x, AH_INPUT_PSTAT_VALUE[index].y, "%u", value );

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionSearch()
    {
        // hit search button
        _game.MouseClick(AH_BUTTON_SEARCH.x, AH_BUTTON_SEARCH.y);

        // wait if requested
        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSortDpsArmor()
    {
        // click sort column header
        _game.MouseClick(AH_LIST_SORT_DPSARMOR.x, AH_LIST_SORT_DPSARMOR.y);

        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSortBuyout()
    {
        // click sort column header
        _game.MouseClick(AH_LIST_SORT_BUYOUT.x, AH_LIST_SORT_BUYOUT.y);

        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListNextPage()
    {
        Bool listing_status;
        Bool status = false;

        // disable input
        _game.InputEnable(false);

        // use opportunity to close any popups
        //_game.MouseClick(AH_BUTTON_BUYOUT_CONFIRM_OK.x, AH_BUTTON_BUYOUT_CONFIRM_OK.y);

        // check listing status
        if(_trainer.ReadListNextStatus(listing_status) && listing_status)
        {
            // hit next page button
            _game.MouseClick(AH_LIST_NEXT_BUTTON.x, AH_LIST_NEXT_BUTTON.y);

            // wait search
            if(_WaitSearch())
                status = true;
        }

        // enable input
        _game.InputEnable(true);

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBid( Index index, ULong bid )
    {
        Bool status;

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
        while(_trainer.ReadPopupStatus(status) && status);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBuyout( Index index )
    {
        Bool status;

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
        while(_trainer.ReadPopupStatus(status) && status);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::HoverListItem( Index index, Bool select )
    {
        Double x = AH_LIST_BEGIN.x + AH_LIST_ICON.x / 2;
        Double y = AH_LIST_BEGIN.y + (AH_LIST_ICON.y / 2) + index * AH_LIST_ICON.y;

        // hover item to update current item tooltip
        _game.MouseMove(x, y);

        // also click to select (for use with bid/buyout)
        if(select)
        {
            _game.MouseClick(x, y);
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadListCount( ULong& count )
    {
        return _trainer.ReadListCount(count);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadListItem( Index index, Item& item )
    {
        Bool status = false;

        // disable input
        _game.InputEnable(false);

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
                    status = true;
            }
        }

        // enable input
        _game.InputEnable(true);

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionReLogin( const Char* account, const Char* password )
    {
        // clear errors
        _game.MouseClick(AH_RELOGIN_CLEARERROR.x, AH_RELOGIN_CLEARERROR.y);

        // clear error delay
        _game.Sleep(AH_RELOGIN_CLEARERROR_DELAY);

        // set account
        _game.SendInputText(AH_RELOGIN_ACCOUNT.x, AH_RELOGIN_ACCOUNT.y, account);

        // set password
        _game.SendInputText(AH_RELOGIN_PASSWORD.x, AH_RELOGIN_PASSWORD.y, password);

        // login
        _game.MouseClick(AH_RELOGIN_LOGIN.x, AH_RELOGIN_LOGIN.y);

        // login delay
        _game.Sleep(AH_RELOGIN_LOGIN_DELAY);

        // auction house
        _game.MouseClick(AH_RELOGIN_AUCTIONHOUSE.x, AH_RELOGIN_AUCTIONHOUSE.y, false);

        // auction house delay
        _game.Sleep(AH_RELOGIN_AUCTIONHOUSE_DELAY);

        // click search/equipment
        _game.MouseClick(AH_RELOGIN_EQUIPMENT.x, AH_RELOGIN_EQUIPMENT.y);

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
    Bool AuctionInterface::_WriteComboBox( Id combo_id, Id option_id )
    {
        assert(combo_id >= Trainer::COMBO_RARITY && combo_id <= Trainer::COMBO_PSTAT2);
        Index   option_index;
        Bool    status = false;

        // disable input
        _game.InputEnable(false);

        // calculate option index
        if(_CalculateComboIndex(option_index, combo_id, option_id))
        {
            // write option index
            if(_trainer.WriteComboBox(combo_id, option_index))
            {
                // visual refresh
                if(_WriteComboRefresh(combo_id))
                    status = true;
            }
        }

        // enable input
        _game.InputEnable(true);

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_WriteComboRefresh( Id combo_id )
    {
        const Coordinate&   coordinate =    AH_COMBO_COORDS[combo_id];
        Window&             window =        _game.GetWindow();
        ULong               y =             _game.Y(coordinate.y, false);
        ULong               height =        window.GetHeight() - y;
        Window::Color*      pixels =        new Window::Color[height];
        ULong               h;

        // open dropdown
        _game.MouseClick(coordinate.x, coordinate.y);

        // image scan to selection
        window.CaptureScreen(pixels, _game.X(coordinate.x, false), y, 1, height);

        // determine selection y
        for( h = 0; h < height && (pixels[h].r <= (pixels[h].g + pixels[h].b)); h++ );
        delete[] pixels;
        if(h == height)
            return false;

        // click selection
        _game.MouseClick(_game.X(coordinate.x), y + h + 10);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_CalculateComboIndex( Index& option_index, Id combo_id, Id option_id )
    {
        IgnoreCollection    ignores;
        ULong               option_count;
        option_index = 0;

        // calculate option index
        if(combo_id >= Trainer::COMBO_SECONDARY)
        {
            Index primary_id;

            // read primary
            if(!_trainer.ReadComboBox(Trainer::COMBO_PRIMARY, primary_id, option_count))
                return false;

            // stat
            if(combo_id >= Trainer::COMBO_PSTAT0)
            {
                Index   secondary_index;
                Id      secondary_id;

                // read secondary
                if(!_trainer.ReadComboBox(Trainer::COMBO_SECONDARY, secondary_index, option_count))
                    return false;

                // get secondary id
                if((secondary_id = _OptionIndexToId(secondary_index, primary_id, AH_COMBO_SECONDARY)) == INVALID_ID)
                    return false;

                // read current stat indexes and build ignore list
                if(combo_id != ITEM_STAT_NONE)
                {
                    for( Id stat_id = Trainer::COMBO_PSTAT0; stat_id <= Trainer::COMBO_PSTAT2; stat_id++ )
                    {
                        // ignore target
                        if(stat_id != combo_id)
                        {
                            Index stat_index;

                            // read statN
                            if(!_trainer.ReadComboBox(stat_id, stat_index, option_count))
                                return false;

                            // add ignore
                            if(stat_index != 0)
                                ignores.Push(stat_index);
                        }
                    }
                }

                // calculate stat index
                if((option_index = _OptionIdToIndex(option_id, secondary_id, AH_COMBO_PSTAT, ignores)) == INVALID_INDEX)
                    return false;
            }
            // secondary
            else if((option_index = _OptionIdToIndex(option_id, primary_id, AH_COMBO_SECONDARY, ignores)) == INVALID_INDEX)
                return false;
        }
        // primary
        else
            option_index = option_id;

        return true;
    }

    //------------------------------------------------------------------------
    Id AuctionInterface::_OptionIndexToId( Index option_index, Id group_id, const ComboBox& box ) const
    {
        const ComboBox::OptionCollection& options = box.GetOptions();

        for( Index i = 0, index = 0; i < options.GetCount(); i++ )
            if(B64(group_id) & options[i].group)
                if(option_index == index++)
                    return i;

        return INVALID_ID;
    }

    //------------------------------------------------------------------------
    Index AuctionInterface::_OptionIdToIndex( Id option_id, Id group_id, const ComboBox& box, IgnoreCollection& ignores ) const
    {
        const ComboBox::OptionCollection& options = box.GetOptions();

        for( Index i = 0, index = 0; i < options.GetCount(); i++ )
        {
            if(B64(group_id) & options[i].group)
            {
                IgnoreIterator ignore = ignores.FlatSearch(index);

                if(ignore != ignores.End())
                    *ignore = INVALID_ID;
                else
                {
                    if(i == option_id)
                        return index;
                    index++;
                }
            }
        }

        return INVALID_INDEX;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::_WaitSearch()
    {
        ULong count = 0;

        // poll listing status
        for( Index i = 0; i <AH_LIST_WAIT_ITERATIONS; i++ )
        {
            Bool busy;

            // poll delay
            _game.SleepFrames(1);

            // read listing status
            if(!_trainer.ReadListCount(count))
                return false;

            // success if listing found
            if(count > 0)
                return true;

            // fail if no longer busy but no listing read
            if(!_trainer.ReadListBusyStatus(busy) || !busy)
                return false;
        }

        return false;
    }
}
