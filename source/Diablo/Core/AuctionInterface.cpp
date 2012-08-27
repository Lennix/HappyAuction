#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>

namespace Diablo
{
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
            ULong rvalue = Tools::UniqueRandom<AH_BUYOUT_RANDOM_LIMIT>(range);

            buyout += NUMBER(rvalue, 0);
        }
        _game.SendInputNumber(UI_COORDS[UI_INPUT_FILTERBUYOUT].x, UI_COORDS[UI_INPUT_FILTERBUYOUT].y, buyout);

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
        _game.SendInputText(UI_COORDS[UI_INPUT_FILTERUNIQUE].x, UI_COORDS[UI_INPUT_FILTERUNIQUE].y, "%s", string);

        // confirm dropdown popup
        _game.MouseClick(UI_COORDS[UI_POPUP_UNIQUE].x, UI_COORDS[UI_POPUP_UNIQUE].y);

        return true;
    }
    
    Bool AuctionInterface::ReadFilterUnique( TextString& string )
    {
        // read unique text
        *string = 0;
        return _trainer.ReadInputText(Trainer::OBJECT_INPUT_UNIQUE, string);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterChar( const Char* name )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // write combo
        return _game.WriteCombo(COMBO_CHARACTER, name);
    }

    Bool AuctionInterface::ReadFilterChar( TextString name )
    {
        // read combo
        if(!_game.ReadCombo(COMBO_CHARACTER, name))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterPrimary( const Char* name )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // write combo
        return _game.WriteCombo(COMBO_PRIMARY, name);
    }

    Bool AuctionInterface::ReadFilterPrimary( TextString name )
    {
        // read combo
        return _game.ReadCombo(COMBO_PRIMARY, name);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterSecondary( const Char* name )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // write combo
        return _game.WriteCombo(COMBO_SECONDARY, name);
    }

    Bool AuctionInterface::WriteFilterSecondaryAuto( const Char* name )
    {
        TextString                  temp_name;
        ComboSecondaryDependency    secdep;
        Id                          id = FILTER_CHAR_DEFAULT;
        Id                          primary_id;

        // read secondary object
        if(!AH_COMBO_SECONDARY_DEPS.FindObject(secdep, name))
            return false;

        // read character
        if(!ReadFilterChar(temp_name))
            return false;
        AH_COMBO_CHAR_IDS.FindObject(id, temp_name);

        // if necessary change character as required by secondary type
        if((secdep.character & BIT(id)) == 0)
        {
            id = Tools::FirstBitIndex(secdep.character);

            if(!AH_COMBO_CHAR_IDS.FindName(temp_name, id))
                return false;
            
            if(!WriteFilterChar(temp_name))
                return false;
        }
        
        // read primary id
        if(!ReadFilterPrimary(temp_name))
            return false;
        if(!AH_COMBO_PRIMARY_IDS.FindObject(primary_id, temp_name))
            return false;
        
        // if necessary change primary as required by secondary type
        if(primary_id != secdep.primary)
        {
            if(!AH_COMBO_PRIMARY_IDS.FindName(temp_name, secdep.primary))
                return false;

            if(!WriteFilterPrimary(temp_name))
                return false;
        }

        // select secondary
        if(!WriteFilterSecondary(name))
            return false;

        return true;
    }

    Bool AuctionInterface::ReadFilterSecondary( TextString name )
    {
        // read combo
        return _game.ReadCombo(COMBO_SECONDARY, name);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterRarity( const Char* name )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // write combo
        return _game.WriteCombo(COMBO_RARITY, name);
    }

    Bool AuctionInterface::ReadFilterRarity( TextString name )
    {
        // read combo
        return _game.ReadCombo(COMBO_RARITY, name);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterStat( Index index, const Char* name, Number value )
    {
        assert(index < AH_PSTAT_LIMIT);
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select stat
        if(!_game.WriteCombo(static_cast<ComboId>(COMBO_PSTAT0 + index), name))
            return false;

        // set value
        _game.SendInputNumber(UI_COORDS[index + UI_INPUT_FILTERPSTAT0].x, UI_COORDS[index + UI_INPUT_FILTERPSTAT0].y, value);

        return true;
    }

    Bool AuctionInterface::ReadFilterStat( Index index, TextString name, Number& value )
    {
        // read combo
        if(!_game.ReadCombo(static_cast<ComboId>(COMBO_PSTAT0 + index), name))
            return false;

        // read value text
        return _ReadInputNumber(index + Trainer::OBJECT_INPUT_PSTAT0, value);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterLevelMin( Number level )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        _game.SendInputNumber(UI_COORDS[UI_INPUT_FILTERLEVELMIN].x, UI_COORDS[UI_INPUT_FILTERLEVELMIN].y, level);

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

        _game.SendInputNumber(UI_COORDS[UI_INPUT_FILTERLEVELMAX].x, UI_COORDS[UI_INPUT_FILTERLEVELMAX].y, level);

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
        _game.MouseClick(UI_COORDS[UI_BUTTON_SEARCH].x, UI_COORDS[UI_BUTTON_SEARCH].y);

        // wait if requested
        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSort( UiId id )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // click sort column header
        _game.MouseClick(UI_COORDS[id].x, UI_COORDS[id].y);

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
            _game.MouseClick(UI_COORDS[UI_LBUTTON_PAGENEXT].x, UI_COORDS[UI_LBUTTON_PAGENEXT].y);

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
        _game.MouseClick(UI_COORDS[UI_BUTTON_BID].x, UI_COORDS[UI_BUTTON_BID].y);

        // set bid amount if any
        if( bid != 0 )
            _game.SendInputNumber(UI_COORDS[UI_INPUT_MAXBID].x, UI_COORDS[UI_INPUT_MAXBID].y, bid);

        // hit confirm button
        _game.MouseClick(UI_COORDS[UI_BUTTON_BIDCONFIRM].x, UI_COORDS[UI_BUTTON_BIDCONFIRM].y);

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
        _game.MouseClick(UI_COORDS[UI_BUTTON_BUYOUT].x, UI_COORDS[UI_BUTTON_BUYOUT].y);

        // hit confirm button
        _game.MouseClick(UI_COORDS[UI_BUTTON_BUYOUTCONFIRM].x, UI_COORDS[UI_BUTTON_BUYOUTCONFIRM].y);

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
        _game.MouseClick(UI_COORDS[UI_BUTTON_SENDTOSTASH].x, UI_COORDS[UI_BUTTON_SENDTOSTASH].y);

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
        _game.MouseClick(UI_COORDS[UI_POPUP_ERROR].x, UI_COORDS[UI_POPUP_ERROR].y);

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
            _game.SendInputText(UI_COORDS[UI_INPUT_LOGINACCOUNT].x, UI_COORDS[UI_INPUT_LOGINACCOUNT].y, account);

            // set password
            _game.SendInputText(UI_COORDS[UI_INPUT_LOGINPASSWORD].x, UI_COORDS[UI_INPUT_LOGINPASSWORD].y, password);

            // login
            _game.MouseClick(UI_COORDS[UI_BUTTON_LOGIN].x, UI_COORDS[UI_BUTTON_LOGIN].y);

            // close any popups
            _game.MouseClick(UI_COORDS[UI_POPUP_ERROR].x, UI_COORDS[UI_POPUP_ERROR].y);

            // wait a little
            _game.Sleep(100);
        }

        // wait until in auction house
        while(true)
        {
            // active check
            if(!_active)
                return false;

            // post login retry delay
            _game.Sleep(AH_RELOGIN_POSTLOGIN_DELAY);

            // close character profile in case previous popup closer call opened it
            _game.MouseClick(UI_COORDS[UI_BUTTON_PROFILECLOSE].x, UI_COORDS[UI_BUTTON_PROFILECLOSE].y);

            // click auction house button
            _game.MouseClick(UI_COORDS[UI_BUTTON_MAINAUCTIONHOUSE].x, UI_COORDS[UI_BUTTON_MAINAUCTIONHOUSE].y, false);

            // auction enter delay
            _game.Sleep(AH_RELOGIN_AUCTIONHOUSE_DELAY);

            // run retrain until success
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
        Double x = UI_COORDS[UI_CONTAINER_LISTICON0].x + UI_COORDS[UI_CONTAINER_LISTICONSIZE].x / 2;
        Double y = UI_COORDS[UI_CONTAINER_LISTICON0].y + (UI_COORDS[UI_CONTAINER_LISTICONSIZE].y / 2) + index * UI_COORDS[UI_CONTAINER_LISTICONSIZE].y;

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
        _game.SendInputNumber(UI_COORDS[UI_INPUT_SELLSTARTING].x, UI_COORDS[UI_INPUT_SELLSTARTING].y, starting);

        // write buyout price
        _game.SendInputNumber(UI_COORDS[UI_INPUT_SELLBUYOUT].x, UI_COORDS[UI_INPUT_SELLBUYOUT].y, buyout);

        // create auction
        _game.MouseClick(UI_COORDS[UI_BUTTON_CREATEAUCTION].x, UI_COORDS[UI_BUTTON_CREATEAUCTION].y);

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
        Double x = UI_COORDS[UI_CONTAINER_STASHBOX00].x + (column * UI_COORDS[UI_CONTAINER_STASHBOXSIZE].x);
        Double y = UI_COORDS[UI_CONTAINER_STASHBOX00].y + (row * UI_COORDS[UI_CONTAINER_STASHBOXSIZE].y);

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
        _game.MouseMoveGround();

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
            _game.MouseClick(UI_COORDS[primary].x, UI_COORDS[primary].y);
            _tab_primary = primary;
            _tab_secondary = INVALID_ID;
        }

        // set secondary tab
        if(secondary != INVALID_ID && secondary != _tab_secondary)
        {
            _game.MouseClick(UI_COORDS[secondary].x, UI_COORDS[secondary].y);
            _tab_secondary = secondary;
        }

        return true;
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
                _game.MouseClick(UI_COORDS[types[i]].x, UI_COORDS[types[i]].y);

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
    Bool AuctionInterface::_WaitSearch()
    {
        Trainer::ButtonStatus status = Trainer::BUTTON_DISABLED;
        ULong count = 0;

        // poll listing status
        for( Index i = 0; _active && i < AH_NETWORK_WAIT_ITERATIONS; i++ )
        {
            Bool auction_status;

            // poll delay
            _game.SleepFrames(1);

            // read auction house status
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
            Tools::StrToNumber(number, out);

        return true;
    }

    //------------------------------------------------------------------------
    void AuctionInterface::_Reset()
    {
        _tab_primary = INVALID_ID;
        _tab_secondary = INVALID_ID;
    }
}
