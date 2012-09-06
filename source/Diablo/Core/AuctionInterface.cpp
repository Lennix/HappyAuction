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

        // generate random padding
        if(randomize && buyout > 0)
        {
            ULong wbuyout = static_cast<ULong>(NUMBER_WHOLE(buyout));
            ULong range = wbuyout / 20; // 5%
            ULong rvalue = Tools::UniqueRandom<AH_BUYOUT_RANDOM_LIMIT>(range);

            buyout += NUMBER(rvalue, 0);
        }

        // write filter value
        _game.SendInputNumber(UI_COORDS[UI_INPUT_FILTERBUYOUT], buyout);

        return true;
    }

    Bool AuctionInterface::ReadFilterBuyout( Number& value )
    {
        // read buyout value
        return _ReadInputNumber(Trainer::OBJECT_INPUT_BUYOUT, value);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::WriteFilterUnique( const Char* string, Index row )
    {
        if( row > AH_UNIQUE_ROW_LIMIT )
            return false;

        // write unique text
        _game.SendInputText(UI_COORDS[UI_INPUT_FILTERUNIQUE], "%s", string);

        // confirm dropdown popup
        if(row > 0)
        {
            // calculate dropdown row position
            const Coordinate&   popup = UI_COORDS[UI_POPUP_UNIQUE];
            const Coordinate&   size = UI_COORDS[UI_CONTAINER_UNIQUEROWSIZE];
            Coordinate          row(popup.x, popup.y + ((row - 1) * size.y));

            // click row
            _game.MouseClick(row);
        }

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
        _game.SendInputNumber(UI_COORDS[index + UI_INPUT_FILTERPSTAT0], value);

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

        _game.SendInputNumber(UI_COORDS[UI_INPUT_FILTERLEVELMIN], level);

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

        _game.SendInputNumber(UI_COORDS[UI_INPUT_FILTERLEVELMAX], level);

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
        _game.MouseClick(UI_COORDS[UI_BUTTON_SEARCH]);

        // wait if requested
        return _WaitSearch();
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionListSort( UiId id )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // click sort column header
        _game.MouseClick(UI_COORDS[id]);

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
            _game.MouseClick(UI_COORDS[UI_LBUTTON_PAGENEXT]);

            // wait search
            if(_WaitSearch())
                status = true;
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBid( Index index, Number bid )
    {
        Item dummy;
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select item index
        if(!ReadListItem(index, dummy, true, true))
            return false;

        // wait button status
        if(!_WaitButton(Trainer::OBJECT_BUTTON_BID))
            return false;

        // hit bid button
        _game.MouseClick(UI_COORDS[UI_BUTTON_BID]);

        // set bid amount if any
        if( bid > 0 )
            _game.SendInputNumber(UI_COORDS[UI_INPUT_MAXBID], bid);

        // hit confirm button
        _game.MouseClick(UI_COORDS[UI_BUTTON_BIDCONFIRM]);

        // clear ok popup
        _ClearPopups();

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionBuyout( Index index )
    {
        Item dummy;
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // select item index
        if(!ReadListItem(index, dummy, true, true))
            return false;

        // wait button status
        if(!_WaitButton(Trainer::OBJECT_BUTTON_BUYOUT))
            return false;

        // hit buyout button
        _game.MouseClick(UI_COORDS[UI_BUTTON_BUYOUT]);

        // hit confirm button
        _game.MouseClick(UI_COORDS[UI_BUTTON_BUYOUTCONFIRM]);

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
        _game.MouseClick(UI_COORDS[UI_BUTTON_SENDTOSTASH]);

        // wait status
        while(_active && _trainer.ReadButtonStatus(status, Trainer::OBJECT_BUTTON_SENDTOSTASH) && status == Trainer::BUTTON_DISABLED)
            _game.SleepFrames(1);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ActionReLogin( const Char* account, const Char* password, ULong delay )
    {
        Bool status;

        // read auction status
        if(!_trainer.ReadAuctionMainStatus(status))
            return false;

        // if auction main still alive keep going!
        if(status)
            return false;

        // clear popups
        _ClearPopups(false);

        // wait until logged out
        while(_active)
        {
            // read login status
            if(!_trainer.ReadLoginStatus(status))
                return false;

            // break if logged out
            if(!status)
                break;
        }

        // user delay
        _game.Sleep(delay);

        // login loop
        while(_active)
        {
            // set account
            _game.SendInputText(UI_COORDS[UI_INPUT_LOGINACCOUNT], account);

            // set password
            _game.SendInputText(UI_COORDS[UI_INPUT_LOGINPASSWORD], password);

            // login
            _game.MouseClick(UI_COORDS[UI_BUTTON_LOGIN]);

            // close any popups
            _ClearPopups(false);

            // loop delay
            _game.Sleep(GAME_LOGIN_LOOP_DELAY);

            // read login status
            if(!_trainer.ReadLoginStatus(status))
                return false;

            // break if logged in
            if(status)
                break;
        }
        
        // login lobby delay
        _game.Sleep(GAME_LOGIN_LOBBY_DELAY);

        // wait until in auction house
        while(_active)
        {
            // close character profile in case previous popup closer call opened it
            _game.MouseClick(UI_COORDS[UI_BUTTON_PROFILECLOSE]);

            // click auction house button
            _game.MouseClick(UI_COORDS[UI_BUTTON_AUCTIONHOUSE]);

            // auction enter delay
            _game.Sleep(GAME_MAIN_AUCTION_DELAY);

            // run retrain until success
            if(_trainer.Train())
                break;

            // loop delay
            _game.Sleep(GAME_LOGIN_LOOP_DELAY);
        }

        // reset tabs
        _Reset();

        return _active;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadListCount( ULong& count )
    {
        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);
        return _trainer.ReadListCount(count);
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadListItem( Index index, Item& item, Bool ground, Bool select )
    {
        const Coordinate& icon = UI_COORDS[UI_CONTAINER_LISTICON0];
        const Coordinate& size = UI_COORDS[UI_CONTAINER_LISTICONSIZE];
        Bool hover_status = false;
        Bool status = false;

        Tab(UI_TAB_SEARCH, UI_TAB_SEARCH_EQUIPMENT);

        // empty item
        item.Empty();

        // grounds a click elsewhere to clear any existing tooltips. this is necessary when refreshing a tooltip
        if(ground)
        {
            // ground hover
            _game.MouseMoveGround(Game::INPUT_NODELAY);

            // wait for hover clear
            for( Index i = 0; i < AH_ITEMHOVER_WAIT_ITERATIONS && _trainer.ReadHoverStatus(hover_status) && hover_status; i++ )
                _game.Sleep(1);
        }

        // clear hover item
        if(_trainer.ClearHoverItem())
        {
            // calculate list icon position
            Coordinate coord(icon.x + size.x / 2, icon.y + (size.y / 2) + index * size.y);

            // hover to open tooltip
            _game.MouseMove(coord, Game::INPUT_NODELAY);

            // loop until success or limit
            for( Index i = 0; !status && i < AH_ITEMHOVER_WAIT_ITERATIONS; i++ )
            {
                // wait a little
                _game.Sleep(1);

                // read item listing and item stat
                if(_trainer.ReadListItem(index, item) && _trainer.ReadHoverItem(item))
                {
                    // click to select
                    if(select)
                        _game.MouseClick(coord, Game::INPUT_NODELAY);

                    // success
                    status = true;
                }
            }
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::SellStashItem( Index column, Index row, Number starting, Number buyout )
    {
        Item dummy;

        Tab(UI_TAB_SELL);

        // select item
        if(!ReadStashItem(column, row, dummy, true, true))
            return false;

        // if an error popup was cleared then fail
        if(_ClearPopups())
            return false;

        // write starting price
        _game.SendInputNumber(UI_COORDS[UI_INPUT_SELLSTARTING], starting);

        // write buyout price
        _game.SendInputNumber(UI_COORDS[UI_INPUT_SELLBUYOUT], buyout);

        // create auction
        _game.MouseClick(UI_COORDS[UI_BUTTON_CREATEAUCTION]);

        // wait a few frames
        _game.SleepFrames(4);

        // there should be a popup. fail otherwise
        if(!_ClearPopups())
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::ReadStashItem( Index column, Index row, Item& item, Bool ground, Bool select )
    {
        const Coordinate& box = UI_COORDS[UI_CONTAINER_STASHBOX00];
        const Coordinate& size = UI_COORDS[UI_CONTAINER_STASHBOXSIZE];
        Bool status = false;

        Tab(UI_TAB_SELL);

        // empty item
        item.Empty();

        // grounds a click elsewhere to clear any existing tooltips. this is necessary when refreshing a tooltip
        if(ground)
            _game.MouseMoveGround();

        // calculate stash slot position
        Coordinate coord(box.x + (column * size.x), box.y + (row * size.y));

        // hover to open tooltip
        _game.MouseMove(coord, Game::INPUT_DIRECT);

        // clear hover item
        if(_trainer.ClearHoverItem())
        {
            // wait a little for it to refresh
            _game.SleepFrames(2);

            // read item stat
            if(_trainer.ReadHoverItem(item))
            {
                // click to select
                if(select)
                    _game.MouseClick(coord, Game::INPUT_NODELAY);

                // success
                status = true;
            }
        }

        return status;
    }

    //------------------------------------------------------------------------
    Bool AuctionInterface::Tab( Id primary, Id secondary )
    {
        // set primary tab
        if(primary != _tab_primary)
        {
            _game.MouseClick(UI_COORDS[primary]);
            _tab_primary = primary;
            _tab_secondary = INVALID_ID;
        }

        // set secondary tab
        if(secondary != INVALID_ID && secondary != _tab_secondary)
        {
            _game.MouseClick(UI_COORDS[secondary]);
            _tab_secondary = secondary;
        }

        return true;
    }

    // private
    //------------------------------------------------------------------------
    Bool AuctionInterface::_ClearPopups( Bool checked )
    {
        static const UiId types[] = { UI_POPUP_ERROR, UI_POPUP_OK };
        Bool status;

        // fail if nothing to close
        if(checked && (!_trainer.ReadPopupStatus(status) || !status))
            return false;

        // click until closed
        do
        {
            // handle each popup type
            for( Index i = 0; i < ACOUNT(types); i++ )
            {
                // click closer button
                _game.MouseClick(UI_COORDS[types[i]]);

                // read status
                if(checked && !_trainer.ReadPopupStatus(status))
                    return false;

                // success if false
                if(checked && !status)
                    return true;
            }
        }
        while(checked && _active);

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
    Bool AuctionInterface::_WaitButton( Id id )
    {
        Index i;

        // wait button status
        for( i = 0; _active && i < AH_BUTTON_WAIT_ITERATIONS; i++ )
        {
            Trainer::ButtonStatus status;

            // read button status
            if(!_trainer.ReadButtonStatus(status, id))
                return false;

            // break if enabled
            if(status > Trainer::BUTTON_DISABLED)
                break;

            _game.SleepFrames(1);
        }

        // fail if limit reached
        if(i == AH_NETWORK_WAIT_ITERATIONS)
            return false;

        return true;
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
