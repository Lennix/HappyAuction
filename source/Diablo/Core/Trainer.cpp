#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>
#include <Diablo/Core/Support.hpp>

namespace Diablo
{
    // local
    //------------------------------------------------------------------------
    static const Double _COORD_HEIGHT =             1200.0;

    static const Char*  _MODULE_D3 =                "Diablo III.exe";
    static const Char*  _MODULE_BNET =              "battle.net.dll";

    static const ULong  _TEXT_COMBO_LIMIT =         64;
    static const ULong  _TEXT_STANDARD_LIMIT =      128;
    static const ULong  _TEXT_POPUP_LIMIT =         1024;
    static const ULong  _TEXT_STATS_LIMIT =         1024;
    static const Char   _CLEAR_CHAR =               '_';

    static const Char*  _HINT_DROPDOWN =            "Root.TopLayer.DropDown";
    static const Char*  _HINT_DROPDOWNCONTENT =     "Root.TopLayer.DropDown._content";
    static const Char*  _HINT_DROPDOWNCONTENTSTACK ="Root.TopLayer.DropDown._content._stackpanel";
    static const Char*  _HINT_LISTITEM_ITEM =       "D3_ITEM";

    static const Char   _FORMAT_COMBO_TEXT[] =      "{c:%s}%s{/c}";
    static const Char   _FORMAT_ITEM_NAME[] =      "{C:%s}%s{/C}";
    static const Char   _FORMAT_ITEM_TYPE[] =       "{c:%s}%s{/c}";
    static const Char   _FORMAT_ITEM_ILEVEL[] =     "%s: %u";
    static const Char   _FORMAT_SOCKET_EMPTY[] =    "{c_bonus}%s{/c}";
    static const Char*  _FORMAT_SOCKET_GEM =        "{icon:bullet} %s\n";
    static const Char*  _FORMAT_STAT[] = {
        "{icon:bullet} {c:%s}%s{c:ffff0000}%s{/c}{/c}\n",
        "{icon:bullet} {c:%s}%s{/c}\n",
        "{c:%s}{icon:bullet}%s{c:ffff0000}%s{/c}{/c}\n",
        "{c:%s}{icon:bullet}%s{/c}\n",
    };
    static const Char*  _FORMAT_SHIELD =
        "+%u%% {c:FF888888}%s{/c:FF888888}\n"
        "%u-%u {c:FF888888}%s{/c:FF888888}";
    static const Char*  _FORMAT_WEAPON =
        "%u-%u {c:FF888888}%s{/c:FF888888}\n"
        "%u {c:FF888888}%s{/c:FF888888}";

    /*
        UI object paths
    */
    static const Char* _UIOBJECT_ROOT = "Root";
    static const Char* _UIOBJECT_PATH[Trainer::OBJECT_COUNT] =
    {
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchRarityFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchCharacterFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchSlotPrimaryFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchSlotSecondaryFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 0 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 1 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 2 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 3 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 4 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 5 list.AdvancedFilterComboBox",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.LevelMinInputTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.LevelMaxInputTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 0 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 1 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 2 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 3 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 4 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 5 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.UniqueItemTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.BuyoutTextBox",

        "Root.TopLayer.item 2.stack.frame body.stack.stats",
        "Root.TopLayer.item 2.stack.frame body.stack.main.stack.special_stats",
        "Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.stack.rating",
        "Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.type",
        "Root.TopLayer.item 2.stack.frame body.stack.wrapper.itemLevel",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 0.text",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 1.text",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 2.text",
        "Root.TopLayer.item 2.stack.top_wrapper.stack.name",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchItemList.PagingButtonsContainer.PageRightButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.SearchButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.CompletedMenu.CompletedMenuContainer.CompletedItemContainer.CompletedItemSendToButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchBidButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchBuyoutButton",

        "Root.TopLayer.BattleNetAuctionHouseNotifications_main.LayoutRoot.ProcessingDialog.LayoutRoot.DialogContent.PendingItemText",
        "Root.TopLayer.BattleNetModalNotifications_main.ModalNotification.Content.List.Message",

        "Root.TopLayer",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.PageHeader",
    };

    /*
        Static address offsets.
        The comments above each are steps taken to find their values after
        patches (using Cheat Engine).
    */
    /*
        1 at d3 login screen search memory for "Root" with valid header according to IsValidUiObject
        2 pointer (re)scan address found. static only. levels=2. offset=4096
        3 confirm and repeat with d3 restart
    */
    static const Process::Link _chain_uiroot[] = { 0x00FB52E4, 0x0D4C }; // _MODULE_D3
    static const Process::Chain _CHAIN_UIROOT(_chain_uiroot, ACOUNT(_chain_uiroot));

    /*
        1 while in AH mem search your total gold value. select lowest address one found.
        2 pointer scan address found. static only. levels=2. offset=1024.
        3 with pointer scan still open restart d3 goto AH and verify
        4 if wrong value goto 1 and select next address
    */
    static const Process::Link _chain_gold[] = { 0x00E879C0 }; // _MODULE_D3
    static const Process::Chain _CHAIN_GOLD(_chain_gold, ACOUNT(_chain_gold));

    /*
        1 while logged in mem search your account name. select lowest address one found.
        2 pointer scan address found. static only. levels=3. offset=1024.
        3 with pointer scan still open restart d3 login and verify
        4 if wrong value goto 1 and select next address
    */
    static const Process::Link _chain_account[] = { 0x00FD5DC0, 0x0010, 0x0268 }; // _MODULE_D3
    static const Process::Chain _CHAIN_ACCOUNT(_chain_account, ACOUNT(_chain_account));

    /*
        1 d3 search such that first page of results is less than 11 items
        2 mem search count of items
        3 adjust count and goto1 until narrowed down
        4 look at address +8 over and verify matches format of _AhListItem (with D3_GOLD and D3_ITEM in memory)
        5 pointer scan address found. static only. levels=3. offset=1024.
        6 with pointer scan still open restart d3 goto 5
    */
    static const Process::Link _chain_searchresults[] = { 0x00E8A468, 0x00000000 }; // _MODULE_D3
    static const Process::Chain _CHAIN_SEARCHRESULTS(_chain_searchresults, ACOUNT(_chain_searchresults));

    /*
        1 visit auctions tab and ensure some items selling
        2 mem search 4byte count of items selling
        3 cancel or add and research for new count
        4 check each address and ensure +8 offset from memory location found contains address pointing to list of auction items (similar to search results)
        5 pointer (re)scan address found. static only. levels=3. offset=1024.
        6 with pointer scan still open restart d3 goto 1
    */
    static const Process::Link _chain_sells[] = { 0x00E8A4B8, 0x00000000 }; // _MODULE_D3
    static const Process::Chain _CHAIN_SELLS(_chain_sells, ACOUNT(_chain_sells));

    /*
        1 visit auctions main
        2 mem search count of items selling (based on auctions tab text)
        3 sell items to change number
        4 exit auctions and goto 1 until narrowed down
        5 pointer (re)scan address found. static only. levels=3. offset=1024.
        6 confirm with d3 restart
    */
    static const Process::Link _chain_sellcount[] = { 0x00E88FA8, 0x00000000 }; // _MODULE_D3
    static const Process::Chain _CHAIN_SELLCOUNT(_chain_sellcount, ACOUNT(_chain_sellcount));

    /*
        1 set low frame rate
        2 mem search 4byte between estimated frames passed
        3 mem research incrementing
        4 keep only static addresses
        5 ensure valid in world, menus, and AH
        6 restart d3 goto 2
    */
    static const ULong _BASEADDRESS_FRAMECOUNT = 0x0110CA7C; // _MODULE_D3
    /*
        1 login and mem search 4byte = 1
        2 logout and mem search 4byte = 0
            - NOTE: should remain 0 during login sequence
        3 keep only static address
        4 ensure value = 1 in menus and AH
        5 restart d3 goto 1
    */
    static const ULong _BASEADDRESS_LOGGEDIN = 0x00E88FB0; // _MODULE_D3

    //------------------------------------------------------------------------
    struct _UiObjectChild
    {
        Byte    _1      [0x04];
        ULong   addr_target2;       // 004
        ULong   addr_target3;       // 008
    };

    struct _AhListItem              // 108
    {
        Byte    _1      [0x020];
        Char    d3item  [0x008];    // 020
        Byte    _2      [0x054];
        Char    d3gold  [0x008];    // 07c
        Byte    _3      [0x02C];
        ULong   id;                 // 0b0
        Byte    _4      [0x00c];
        ULong   bid1;               // 0c0
        Byte    _5      [0x004];
        ULong   buyout;             // 0c8
        Byte    _6      [0x004];
        ULong   bid2;               // 0d0
        Byte    _7      [0x01c];
        UHuge   time;               // 0f0
        Byte    _8      [0x010];
    };

    struct _AhSellItem              // 248
    {
        Byte    _1      [0x0a0];
        UHuge   stime;              // 0a0
        UHuge   xtime;              // 0a8
        Byte    _2      [0x028];
        ULong   buyout;             // 0d8
        Byte    _3      [0x004];
        ULong   bid1;               // 0e0
        Byte    _4      [0x004];
        ULong   bid2;               // 0e8
        Byte    _5      [0x014];
        ULong   id;                 // 100
        Byte    _6      [0x144];
    };
    
    struct _AhGlobal1
    {
        Byte    _1      [0x05C];
        ULong   gold;               // 05C
    };
    
    struct _AhGlobal2
    {
        Byte    _1      [0x018];
        ULong   sellcount;
    };

    // public
    //------------------------------------------------------------------------
    Trainer::Trainer( Process& process ):
        _process(process),
        _scanner(process),
        _d3_base(0),
        _bnet_base(0),
        _combo_count(0),
        _ui_root(0),
        _trained(false)
    {
        assert(_TEXT_COMBO_LIMIT <= sizeof(TextString));
        Tools::MemZero(_ui_addresses, ACOUNT(_ui_addresses));
    }

    //------------------------------------------------------------------------
    Bool Trainer::Train( Bool partial )
    {
        // get base addresses
        if((_d3_base = _process.GetBaseAddress(_MODULE_D3)) == 0)
            return false;
        if((_bnet_base = _process.GetBaseAddress(_MODULE_BNET)) == 0)
            return false;

        _trained = true;


        //UiObject ui_object;
        //ULong found;
        //_RecurseUiObject(ui_object, found, OBJECT_POPUP_ERROR);
        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::CheckTrained()
    {
        // check stat first
        if(!_trained)
            return false;
/*
        // verify all objects
        for( Index i = 0; i < OBJECT_COUNT; i++ )
        {
            UiObject object;
            if(!_ReadUiObject(object, i))
            {
                _trained = false;
                return false;
            }
        }
*/
        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::WriteInputText( Id id, const Char* text )
    {
        UiObject   ui_object;
        TextString  ui_text;

        // read object
        if(!_ReadUiObject(ui_object, id))
            return false;

        // copy text
        Tools::StrNCpy(ui_text, text, _TEXT_STANDARD_LIMIT);

        // write input
        _process.WriteMemory(ui_object.addr2_value, ui_text, strlen(ui_text)+1);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadInputText( Id id, TextString text )
    {
        UiObject   ui_object;
        TextString  ui_text;

        // read object
        if(!_ReadUiObject(ui_object, id))
            return false;

        // read input
        if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
            return false;

        // copy text
        Tools::StrNCpy(text, ui_text, sizeof(TextString));

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::WriteComboIndex( Id id, Index index )
    {
        UiObject   object;
        ULong       address;

        // verify
        if(!_ReadUiObject(object, id, &address))
            return false;

        // write
        _process.WriteMemory(address + FIELD_OFFSET(UiObject, n5[0]), &index, sizeof(index));

        return true;
    }

    Bool Trainer::ReadComboIndex( Id id, Index* index, ULong* count )
    {
        UiObject object;

        // verify
        if(!_ReadUiObject(object, id))
            return false;

        if(index)
            *index = object.n5[0];
        if(count)
            *count = object.n5[3];

        return true;
    }

    Bool Trainer::ReadComboString( Id id, TextString string, Bool strip )
    {
        UiObject   object;
        ULong       count;
        TextString  found;
        TextString  string1;

        // read ui object
        if(!_ReadUiObject(object, id))
            return false;

        // read child object
        if(!_process.ReadMemory(object.addr3_child, &object, sizeof(object)))
            return false;

        // read value
        if(!_process.ReadMemory(object.addr2_value, found, _TEXT_COMBO_LIMIT))
            return false;

        // strip formatting if any else use original string
        if(!strip || !Tools::StrFormatRead(count, found, _FORMAT_COMBO_TEXT, string1, string, string1) || count != 2)
            Tools::StrNCpy(string, found, sizeof(TextString));

        return true;
    }

    Bool Trainer::ReadComboRowBegin()
    {
        UiObject object;

        _combo_count = 0;

        // top layer
        if(!_ReadUiObject(object, OBJECT_TOP))
            return false;

        // drop down
        if(!_ReadUiChild(object, _HINT_DROPDOWN, object))
            return false;

        // drop down content
        if(!_ReadUiChild(object, _HINT_DROPDOWNCONTENT, object))
            return false;

        // drop down content stack
        if(!_ReadUiChild(object, _HINT_DROPDOWNCONTENTSTACK, object))
            return false;

        // read item list
        ULong count = object.addr1_count = Tools::Min(object.addr1_count, UI_COMBO_ROW_LIMIT);
        if(!_process.ReadMemory(object.addr1_children, _combo_addresses, sizeof(ULong) * count))
            return false;

        _combo_count = count;

        return true;
    }

    Bool Trainer::ReadComboRow( Index index, TextString string, Double& y )
    {
        UiObject  object;

        // must be ready
        if(!_trained)
            return false;

        // end of list
        if(index >= _combo_count)
            return false;

        // read item object
        if(!_process.ReadMemory(_combo_addresses[index], &object, sizeof(object)))
            return false;

        // get Y coordinate
        if(object.y1 > 0.0f && object.y2 > 0.0f)
        {
            Float height = (object.y2 - object.y1);
            Float position = height / 2.0f + object.y1;
            y = position / _COORD_HEIGHT;
        }

        // read text
        if(!_process.ReadMemory(object.addr2_value, string, _TEXT_COMBO_LIMIT))
            return false;

        return true;
    }

    Bool Trainer::ReadComboRowCount( ULong& count )
    {
        // require combo state
        if(_combo_count == 0)
            return false;

        count = _combo_count;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadHoverStatus( Bool& status )
    {
        UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME))
            return false;

        // determine status
        status = (ui_object.visible != 0);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadHoverItem( Item& item )
    {
        // name rarity type dps/armor
        if(!_ReadHoverItemHeaders(item))
            return false;

        // stats (can be empty)
        if(!_ReadHoverItemStats(item.stats))
            return false;

        // sockets (can be empty)
        if(!_ReadHoverItemSockets(item.sockets))
            return false;

        // must have something!
        return (item.rarity || item.dpsarmor || item.stats.GetCount() || item.sockets.GetCount());
    }

    //------------------------------------------------------------------------
    Bool Trainer::ClearHoverItem()
    {
        // hide key objects
        if( !_WriteUiObject(OBJECT_TOOLTIP_STATS, false) ||
            !_WriteUiObject(OBJECT_TOOLTIP_DPSARMOR, false) ||
            !_WriteUiObject(OBJECT_TOOLTIP_SOCKET0, false) ||
            !_WriteUiObject(OBJECT_TOOLTIP_SOCKET1, false) ||
            !_WriteUiObject(OBJECT_TOOLTIP_SOCKET2, false) ||
            !_WriteUiObject(OBJECT_TOOLTIP_NAME, false))
            return false;

        // headers
        if(!_ClearHoverItemHeaders())
            return false;

        // stats
        if(!_ClearHoverItemStats())
            return false;

        // sockets
        if(!_ClearHoverItemSockets())
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadListItem( Index index, Item& item )
    {
        AhSearchList     list_object;
        _AhListItem item_object;

        // read list object
        if(!_ReadListRoot(list_object))
            return false;

        // read item object
        if(!_process.ReadMemory(list_object.addr_items + index * sizeof(_AhListItem), &item_object, sizeof(item_object)))
            return false;

        // hint checks
        if( *(UHuge*)item_object.d3item != *(UHuge*)_HINT_LISTITEM_ITEM )
            return false;

        // cbid, mbid
        if(item_object.bid1)
        {
            item.bid_current = NUMBER(item_object.bid1, 0);
            item.bid_max = NUMBER(item_object.bid2, 0);
        }
        else
            item.bid_current = item.bid_max = NUMBER(item_object.bid2, 0);

        // id
        item.id = item_object.id;

        // buyout
        item.buyout = NUMBER(item_object.buyout, 0);

        // time
        UHuge expire = item_object.time / 1000;
        UHuge current = System::GetTimeMs();

        item.time_remaining = expire > current ? static_cast<ULong>(expire - current) : 0;
        item.time_expiring = static_cast<ULong>(expire / 1000);

        // verify
        return (item.bid_current && item.id && item.time_expiring);
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadListCount( ULong& count )
    {
        AhSearchList list_object;

        // read list object
        if(!_ReadListRoot(list_object))
            return false;

        // get values
        count = list_object.count;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadListNextStatus( Bool& status )
    {
        UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_LBUTTON_PAGENEXT))
            return false;

        // determine status
        status = (ui_object.visible && ui_object.anim_state >= 16);

        return true;
    }

    // selling list
    //------------------------------------------------------------------------
    Bool Trainer::ReadSellItem( Index index, Item& item )
    {
        AhSellList    list_object;
        _AhSellItem item_object;

        // read list object
        if(!_ReadSellRoot(list_object))
            return false;

        // read item object
        if(!_process.ReadMemory(list_object.addr_items + index * sizeof(_AhSellItem), &item_object, sizeof(item_object)))
            return false;

        // id
        item.id = item_object.id;

        // start, current, buyout
        item.bid_start = NUMBER(item_object.bid1, 0);
        item.bid_current = NUMBER(item_object.bid2, 0);
        item.buyout = NUMBER(item_object.buyout, 0);

        // time
        UHuge expire = item_object.xtime / 1000;
        UHuge current = System::GetTimeMs();

        item.time_remaining = expire > current ? static_cast<ULong>(expire - current) : 0;
        item.time_expiring = static_cast<ULong>(expire / 1000);

        // verify
        return (item.bid_start && item.id && item.time_expiring);
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadSellCount( ULong& count )
    {
        AhSellList list_object;

        // read list object
        if(!_ReadSellRoot(list_object))
            return false;

        // get values
        count = list_object.count;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadSellStatus( Bool& active )
    {
        _AhGlobal2  object;
        ULong       count;

        // get root object from static chain
        ULong address = _process.ReadChainAddress( _d3_base, _CHAIN_SELLCOUNT );
        if(address == 0)
            return false;

        // read global object
        if(!_process.ReadMemory(address, &object, sizeof(object)))
            return false;

        // read current list count
        if(!ReadSellCount(count))
            return false;

        // compare to global count
        active = (count == object.sellcount);

        return true;
    }

    // etc
    //------------------------------------------------------------------------
    Bool Trainer::ReadButtonStatus( ButtonStatus& status, Id button_id )
    {
        UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, button_id))
            return false;

        // determine button busy status
        if(ui_object.visible)
        {
            switch(ui_object.anim_state)
            {
            case 37:
                status = BUTTON_ENABLED;
                break;
            case 36:
                status = BUTTON_HIGHLIGHTED;
                break;
            case 34:
            default:
                status = BUTTON_DISABLED;
            }
        }
        else
            status = BUTTON_HIDDEN;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadPopupStatus( Bool& active, TextString text, Id popup_id )
    {
        UiObject ui_object;

        // read popup
        if(!_ReadUiObject(ui_object, popup_id))
            return false;

        // read text
        if(ui_object.visible && !_process.ReadMemory(ui_object.addr2_value, text, _TEXT_POPUP_LIMIT))
            return false;

        // active either visible
        active = (ui_object.visible != 0);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadLoginStatus( Bool& active )
    {
        ULong status;
        
        // get login status
        if(!_process.ReadMemory( _d3_base + _BASEADDRESS_LOGGEDIN, &status, sizeof(ULong) ))
            return false;

        // set status
        active = (status > 0);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadAuctionMainStatus( Bool& active )
    {
        UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_MAIN_AUCTION))
            return false;

        // check auction main status
        active = (ui_object.visible != 0);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadFrameCount( ULong& count )
    {
        // get frame count
        return _process.ReadMemory( _d3_base + _BASEADDRESS_FRAMECOUNT, &count, sizeof(ULong) );
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadGold( ULong& amount )
    {
        _AhGlobal1 ah_global;

        // get list root object from static chain
        ULong address = _process.ReadChainAddress( _d3_base, _CHAIN_GOLD );
        if(address == 0)
            return false;

        // read list object
        if(!_process.ReadMemory(address, &ah_global, sizeof(ah_global)))
            return false;

        // get total gold amount
        amount = ah_global.gold;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadAccount( TextString account )
    {
        // get list root object from static chain
        ULong address = _process.ReadChainAddress( _d3_base, _CHAIN_ACCOUNT );
        if(address == 0)
            return false;

        // read list object
        if(!_process.ReadMemory(address, account, sizeof(TextString)))
            return false;

        return true;
    }

    // private
    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemHeaders( Item& item )
    {
        UiObject        ui_object;
        TextString      ui_text;
        TextString      string1;
        ULong           count;

        // read item name
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME) || !ui_object.visible)
            return false;
        if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
            return false;
        if( *ui_text == 0 || *ui_text == _CLEAR_CHAR)
            return false;
        Tools::UpperCase(ui_text);
        if(!Tools::StrFormatRead(count, ui_text, _FORMAT_ITEM_NAME, string1, item.name) || count != 2)
            return false;

        // read rarity/type
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_TYPE) || !ui_object.visible)
            return false;
        if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
            return false;
        if( *ui_text == 0 || *ui_text == _CLEAR_CHAR )
            return false;
        if(Tools::StrFormatRead(count, ui_text, _FORMAT_ITEM_TYPE, string1, item.type) && count == 2)
            ITEM_RARITY_COLORS.FindObject(item.rarity, string1);

        // read item dps/armor
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_DPSARMOR))
            return false;
        if(ui_object.visible)
        {
            if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
                return false;
            if( *ui_text != 0 && *ui_text != _CLEAR_CHAR )
                Tools::StrToNumber(item.dpsarmor, ui_text);
        }

        // read shield block%/range or weapon AS/range
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_ASDAMAGE))
            return false;
        if(ui_object.visible)
        {
            if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
                return false;

            Tools::StrFormatRead(count, ui_text, _FORMAT_SHIELD, &item.block_chance, string1, &item.block_min, &item.block_max, string1) ||
            Tools::StrFormatRead(count, ui_text, _FORMAT_WEAPON, &item.damage_min, &item.damage_max, string1, &item.damage_aps, string1);
        }

        // read ilevel
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_ILEVEL))
            return false;
        if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
            return false;

        // parse ilevel
        if(ui_object.visible)
        {
            if( *ui_text == 0 || *ui_text == _CLEAR_CHAR )
                return false;
            Tools::StrFormatRead(count, ui_text, _FORMAT_ITEM_ILEVEL, string1, &item.ilevel);
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemStats( Item::StatCollection& stats )
    {
        UiObject       ui_object;
        TextString      ui_text;
        Item::Stat      item_stat;
        const Char*     ptext;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_STATS))
            return false;

        // empty stats
        stats.Empty();

        // if stats available
        if(ui_object.visible)
        {
            // read stats
            if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STATS_LIMIT))
                return false;

            // parse
            for( ptext = ui_text; (ptext = _ParseItemStatLine(item_stat, ptext, false)) && !stats.IsFull(); )
                stats.Push(item_stat);
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemSockets( Item::SocketCollection& sockets )
    {
        UiObject       ui_object;
        TextString      ui_text;
        Item::Stat      item_stat;

        assert(sockets.GetLimit() >= (OBJECT_TOOLTIP_SOCKET2 - OBJECT_TOOLTIP_SOCKET0));
        sockets.Empty();

        // iterate
        for( Index i = 0; i < sockets.GetLimit(); i++ )
        {
            // read ui object
            if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_SOCKET0 + i))
                return false;

            // only if visible
            if(ui_object.visible)
            {
                // read socket
                if(!_process.ReadMemory(ui_object.addr2_value, ui_text, _TEXT_STANDARD_LIMIT))
                    return false;

                // ignore nulls
                if(*ui_text == 0 || *ui_text == _CLEAR_CHAR)
                    continue;

                // parse
                if(_ParseItemStatLine(item_stat, ui_text, true) != NULL)
                    sockets.Push(item_stat);
                else
                    return false;
            }
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemHeaders()
    {
        UiObject ui_object;

        // clear rare/type
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_TYPE))
            return false;
        if(!_process.WriteByte(ui_object.addr2_value, _CLEAR_CHAR))
            return false;

        // clear dps/armor
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_DPSARMOR))
            return false;
        if(!_process.WriteByte(ui_object.addr2_value, _CLEAR_CHAR))
            return false;

        // clear name
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME))
            return false;
        if(!_process.WriteByte(ui_object.addr2_value, _CLEAR_CHAR))
            return false;

        // clear ilevel
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_ILEVEL))
            return false;
        if(!_process.WriteByte(ui_object.addr2_value, _CLEAR_CHAR))
            return false;


        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemStats()
    {
        UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_STATS))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr2_value, _CLEAR_CHAR);
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemSockets()
    {
        UiObject ui_object;

        // iterate
        for( Index i = 0; i <= (OBJECT_TOOLTIP_SOCKET2 - OBJECT_TOOLTIP_SOCKET0); i++ )
        {
            // read ui object
            if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_SOCKET0 + i))
                return false;

            // write null char
            if(!_process.WriteByte(ui_object.addr2_value, _CLEAR_CHAR))
                return false;
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadListRoot( AhSearchList& object )
    {
        // get list root object from static chain
        ULong address = _process.ReadChainAddress( _d3_base, _CHAIN_SEARCHRESULTS );
        if(address == 0)
            return false;

        // read list object
        if(!_process.ReadMemory(address, &object, sizeof(object)))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadSellRoot( AhSellList& object )
    {
        // get list root object from static chain
        ULong address = _process.ReadChainAddress( _d3_base, _CHAIN_SELLS );
        if(address == 0)
            return false;

        // read list object
        if(!_process.ReadMemory(address, &object, sizeof(object)))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_UpdateUiRoot()
    {
        UiObject object;

        // if invalid
        if( _ui_root && 
            _process.ReadMemory(_ui_root, &object, sizeof(object)) && 
            IsValidUiObject(object) &&
            strcmp(object.path, _UIOBJECT_ROOT) == 0)
            return true;
        // else update
        else
        {
            // reset
            _ui_root = 0;

            // scan for root
            _scanner.Scan(*this);

            // if nothing found then major fail
            if(_ui_root == 0)
                return false;
        }

        return _ui_root != 0;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_RecurseUiObject( UiObject& object, ULong& found, ULong address, const Char* path, ULong depth )
    {
        ULong children[TRAINER_UIOBJECT_LIMIT];

        // sanity check
        if(depth >= TRAINER_UISEARCH_DEPTH)
            return false;

        // read children
        if(!_process.ReadMemory(address, &object, sizeof(object)))
            return false;
        ULong count = object.addr1_count;

        // compare path
#if 1
        if(strcmp(object.path, path) == 0 && IsValidUiObject(object))
        {
            found = address;
            return true;
        }
#else
        TextString text;
        if(object.visible && object.addr2_value && _process.ReadMemory(object.addr2_value, text, _TEXT_STANDARD_LIMIT))
        {
            if(Tools::StrSearch("establish a connection", text))
            {
                int x = 33;
            }
        }
#endif

        // read children
        if(!_process.ReadMemory(object.addr1_children, children, sizeof(ULong) * count))
            return false;

        // for each child
        for( Index i = 0; i < count; i++ )
            if(_RecurseUiObject(object, found, children[i], path, depth + 1))
                return true;

        return false;
    }

    Bool Trainer::_RecurseUiObject( UiObject& object, ULong& found, Id id )
    {
        const Char* path = _UIOBJECT_PATH[id];

        // get root object address from static chain
        if(!_UpdateUiRoot())
            return false;
//        ULong root_address = _process.ReadChainAddress( _d3_base, _CHAIN_UIROOT );

        return _RecurseUiObject(object, found, _ui_root, path, 0);
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadUiObject( UiObject& object, Id id, ULong* address )
    {
        assert(id < OBJECT_COUNT);
        ULong&  cache_address = _ui_addresses[id];
        Bool    dirty = false;

        // must be trained
        if(!_trained)
            return false;

        // if have cached address
        if(cache_address)
        {
            // read
            if(!_process.ReadMemory(cache_address, &object, sizeof(object)))
                return false;

            // validate
            if(!IsValidUiObject(object))
                dirty = true;
        }
        else
            dirty = true;

        // find object and cache
        if(dirty && !_RecurseUiObject(object, cache_address, id))
            return false;

        // set found address
        if(address)
            *address = cache_address;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadUiChild( UiObject& child, const Char* path, const UiObject& parent )
    {
        ULong address_list[UI_COMBO_ROW_LIMIT];

        // read address list
        if(!_process.ReadMemory(parent.addr1_children, address_list, sizeof(ULong) * parent.addr1_count))
            return false;

        // locate child in reverse order
        for( Long i = parent.addr1_count - 1; i >= 0; i-- )
        {
            // read object
            if(_process.ReadMemory(address_list[i], &child, sizeof(UiObject)))
            {
                // check path
                if(strcmp(child.path, path) == 0)
                    return true;
            }
        }

        return false;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_WriteUiObject( Id id, Bool visible )
    {
        UiObject   object;
        ULong       address;
        ULong       value = visible;

        // verify
        if(!_ReadUiObject(object, id, &address))
            return false;

        // write visibility
        return _process.WriteMemory(address + FIELD_OFFSET(UiObject, visible), &value, sizeof(value));
    }

    //------------------------------------------------------------------------
    Bool Trainer::IsValidUiObject( const UiObject& object )
    {
        return
            object.n1[2]  == 0x00000000 &&
            object.n1[3]  == 0x00000000 &&
            object.n1[4]  == 0x00000000 &&
            object.n1[5]  == 0x00000000 &&
            object.n1[6]  == 0x00000000 &&
            object.n1[7]  == 0xffffffff &&
            object.n1[8]  == 0xffffffff &&
            object.n3[3]  == 0x600DF00D;
    }

    //------------------------------------------------------------------------
    void Trainer::_ParseItemStatString( Item::Stat& stat, const Char* text ) const
    {
        // collect values
        stat.values.Empty();
        for( const Char* ptext = text; *ptext; )
        {
            Number      number;
            const Char* next = Tools::StrToNumber(number, ptext, false);
            if(next > ptext)
            {
                if(stat.values.GetCount() < stat.values.GetLimit())
                    stat.values.Push(number);
                ptext = next;
            }
            else
                ptext++;
        }

        ULong state = 0;
        Char* stext = stat.text;
        const Char* stext_end = stext + sizeof(stat.text) - 1;

        // copy stripped text (exclude numerics and leading/trailing spaces)
        for( const Char* ptext = text; *ptext && *ptext != '(' && stext != stext_end; ptext++ )
        {
            Char c = *ptext;

            if(c & 0x80 || isalpha(c))
            {
                if(state == 2)
                    *(stext++) = ' ';
                *(stext++) = c;
                state = 1;
            }
            else if(state)
                state = 2;
        }
        *stext = 0;
    }

    //------------------------------------------------------------------------
    const Char* Trainer::_ParseItemStatLine( Item::Stat& stat, const Char* text, Bool is_socket ) const
    {
        TextString  dummy_string;
        TextString  stat_text;
        Char*       pstat_text = stat_text;
        ULong       count;
        Index       i;

        // stop at null or newline
        if(*text == 0 || *text == '\n' || *text == _CLEAR_CHAR)
            return NULL;

        // if socket
        if(is_socket)
        {
            // if empty socket
            if( (!Tools::StrFormatRead(count, text, _FORMAT_SOCKET_EMPTY, pstat_text) || count != 1) &&
            // or has gem stats
                (!Tools::StrFormatRead(count, text, _FORMAT_SOCKET_GEM, pstat_text) || count != 1) )
            {
                return NULL;
            }

            System::Log("%s\n", pstat_text);
        }
        else
        {
            // read regular item stat (has different formats)
            for( i = 0; i < ACOUNT(_FORMAT_STAT) && ((count = Tools::StrFormatRead(count, text, _FORMAT_STAT[i], dummy_string, pstat_text, dummy_string)) == 0 || count < 2); i++ );
            if(i == ACOUNT(_FORMAT_STAT))
            {
                return NULL;
            }
        }

        // parse stat text
        _ParseItemStatString(stat, pstat_text);

        // increment to next item
        text += count;

        return text;
    }

    //------------------------------------------------------------------------
    Bool Trainer::OnScan( ULong address, const Byte* memory, ULong length )
    {
        const UiObject& object = *reinterpret_cast<const UiObject*>(memory);

        if(sizeof(UiObject) <= length && IsValidUiObject(object))
        {
            if( strcmp(object.path, _UIOBJECT_ROOT) == 0 )
            {
                // add address
                _ui_root = address;
                return false;
            }
        }

        return true;
    }
}
