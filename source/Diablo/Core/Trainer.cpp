#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>
#include <Diablo/Core/Support.hpp>

namespace Diablo
{
    // local
    //------------------------------------------------------------------------
    static const ULong  _DROPDOWN_STRING_LIMIT =    64;

    static const Char*  _D3_MODULE =                "Diablo III.exe";
    static const Char*  _BNET_MODULE =              "battle.net.dll";

    static const Char*  _HINT_DROPDOWN =            "Root.TopLayer.DropDown";
    static const Char*  _HINT_DROPDOWNCONTENT =     "Root.TopLayer.DropDown._content";
    static const Char*  _HINT_DROPDOWNCONTENTSTACK ="Root.TopLayer.DropDown._content._stackpanel";

    static const Char   _FORMAT_COMBO_TEXT[] =      "{c:%s}%s{/c}";
    static const Char   _FORMAT_ITEM_NAME[] =       "{C:%s}%s{/C}";
    static const Char   _FORMAT_ITEM_RARITYTYPE[] = "{c:%s}%s %s{/c}";
    static const Char   _FORMAT_SOCKET_EMPTY[] =    "{c_bonus}%s{/c}";
    static const Char*  _FORMAT_SOCKET_GEM =        "{icon:bullet} %s\n";
    static const Char*  _FORMAT_STAT[] = {
        "{icon:bullet} {c:%s}%s{c:ffff0000}%s{/c}{/c}\n",
        "{icon:bullet} {c:%s}%s{/c}\n",
        "{c:%s}{icon:bullet}%s{c:ffff0000}%s{/c}{/c}\n",
        "{c:%s}{icon:bullet}%s{/c}\n",
    };

    static const Char*  _HINT_LISTITEM_ITEM =       "D3_ITEM";
    static const Char*  _HINT_UIOBJECT_PATH[Trainer::OBJECT_COUNT] =
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
        "Root.TopLayer.item 2.stack.frame body.stack.main.large_itembutton",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 0.text",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 1.text",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 2.text",
        "Root.TopLayer.item 2.stack.top_wrapper.stack.name",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchItemList.PagingButtonsContainer.PageRightButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.SearchButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.CompletedMenu.CompletedMenuContainer.CompletedItemContainer.CompletedItemSendToButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchBuyoutButton",

        "Root.TopLayer",
        "Root.TopLayer.BattleNetLightBox_main.LayoutRoot.LightBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.PageHeader",
    };

    /*
        1 d3 search with buyout
        2 mem search 4byte buyout of item in row 1
        3 goto next page and compare to buyout in row 1 until unique
        4 pointer (re)scan address found. static only. levels=4. offset=1024.
        5 with pointer scan still open restart d3 goto 1
    */
    static const Process::Link _chain_searchresults[] = { 0x00F75DF8, 0x00000000 }; // _D3_MODULE
    static const Process::Chain _CHAIN_SEARCHRESULTS(_chain_searchresults, ACOUNT(_chain_searchresults));

    /*
        1 set low frame rate
        2 mem search 4byte between estimated frames passed
        3 mem research incrementing
        4 keep only static addresses
        5 ensure valid in world, menus, and AH
        6 restart d3 goto 2
    */
    static const ULong _BASEADDRESS_FRAMECOUNT =   0x00FC90FC; // _D3_MODULE
    /*
        1 login and mem search 4byte = 1
        2 logout and mem search 4byte = 0
        3 keep only static address
        4 ensure value = 1 in world, menus, and AH
        5 restart d3 goto 1
    */
    static const ULong _BASEADDRESS_LOGGEDIN =     0x007132F4; // _BNET_MODULE

    //------------------------------------------------------------------------
    struct _UiObjectChild
    {
        Byte    _1      [0x04];
        ULong   addr_target2;       // 004
        ULong   addr_target3;       // 008
    };

    struct _UiHoverHeader
    {
        Byte    _1      [0x50];
        Char    raretype[0x28];     // 050
        Char    dpsarmor[0x20];     // 078
    };

    struct _UiHoverStats
    {
        Char    text    [0x400];    // 000
    };

    struct _UiHoverName
    {
        Char    text    [0x80];    // 000
    };

    struct _UiHoverSocket
    {
        Char    text    [0x060];    // 000
    };

    struct _UiInputText
    {
        Char    text    [0x040];    // 000
    };

    struct _AhListItem              // 118
    {
        Byte    _1      [0x024];
        Char    d3item  [0x008];    // 024
        Byte    _2      [0x064];
        Char    d3gold  [0x008];    // 090
        Byte    _3      [0x028];
        ULong   id;                 // 0C0
        Byte    _4      [0x00c];
        ULong   bid1;               // 0D0
        Byte    _5      [0x004];
        ULong   buyout;             // 0D8
        Byte    _6      [0x004];
        ULong   bid2;               // 0E0
        Byte    _7      [0x01c];
        UHuge   time;               // 100
        Byte    _8      [0x010];
    };


    // public
    //------------------------------------------------------------------------
    Trainer::Trainer( Process& process ):
        _process(process),
        _memory(process),
        _d3_base(0),
        _bnet_base(0),
        _combo_count(0),
        _trained(false)
    {
        assert(_DROPDOWN_STRING_LIMIT <= sizeof(TextString));
    }

    //------------------------------------------------------------------------
    Bool Trainer::Train( Bool partial )
    {
        Tools::MemZero(_address, ACOUNT(_address));
        _trained = false;

        // get base addresses
        if((_d3_base = _process.GetBaseAddress(_D3_MODULE)) == 0)
            return false;
        if((_bnet_base = _process.GetBaseAddress(_BNET_MODULE)) == 0)
            return false;

        // scan memory
        if(_memory.Scan(*this))
        {
            Index i;

            // verify all addresses
            for( i = 0; i < OBJECT_COUNT && _address[i] != 0; i++ );

            // ready when no null addresses
            _trained = partial ? i > 0 : (i == OBJECT_COUNT);
        }

        return _trained;
    }

    //------------------------------------------------------------------------
    Bool Trainer::CheckTrained()
    {
        _UiObject object;

        // check stat first
        if(!_trained)
            return false;

        // verify all objects
        for( Index i = 0; i < OBJECT_COUNT; i++ )
        {
            if(!_ReadUiObject(object, i))
            {
                _trained = false;
                return false;
            }
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::WriteInputText( Id id, const Char* text )
    {
        _UiObject       ui_object;
        _UiInputText    ui_input;

        // must be trained
        if(!_trained)
            return false;

        // read object
        if(!_ReadUiObject(ui_object, id))
            return false;

        // copy text
        Tools::StrNCpy(ui_input.text, text, sizeof(ui_input.text));

        // write input
        _process.WriteMemory(ui_object.addr2_value, &ui_input, strlen(ui_input.text)+1);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadInputText( Id id, TextString text )
    {
        _UiObject       ui_object;
        _UiInputText    ui_input;

        // must be trained
        if(!_trained)
            return false;

        // read object
        if(!_ReadUiObject(ui_object, id))
            return false;

        // read input
        if(!_process.ReadMemory(ui_object.addr2_value, &ui_input, sizeof(ui_input)))
            return false;

        // copy text
        Tools::StrNCpy(text, ui_input.text, sizeof(TextString));

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::WriteComboIndex( Id id, Index index )
    {
        _UiObject object;

        // must be trained
        if(!_trained)
            return false;

        // verify
        if(!_ReadUiObject(object, id))
            return false;

        // write
        _process.WriteMemory(_address[id] + FIELD_OFFSET(_UiObject, n5[0]), &index, sizeof(index));

        return true;
    }

    Bool Trainer::ReadComboIndex( Id id, Index* index, ULong* count )
    {
        _UiObject object;

        // must be trained
        if(!_trained)
            return false;

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
        _UiObject   object;
        ULong       count;
        TextString  found;
        TextString  dummy;

        // must be trained
        if(!_trained)
            return false;

        // read ui object
        if(!_ReadUiObject(object, id))
            return false;

        // read child object
        if(!_process.ReadMemory(object.addr3_child, &object, sizeof(object)))
            return false;

        // read value
        if(!_process.ReadMemory(object.addr2_value, found, _DROPDOWN_STRING_LIMIT))
            return false;

        // strip formatting if any else use original string
        if(!strip || !Tools::StrFormatRead(count, found, _FORMAT_COMBO_TEXT, dummy, string, dummy) || count != 2)
            Tools::StrNCpy(string, found, sizeof(TextString));

        return true;
    }

    Bool Trainer::ReadComboRowBegin()
    {
        _UiObject object;

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

    Bool Trainer::ReadComboRow( Index index, TextString string )
    {
        _UiObject  object;

        // must be ready
        if(!_trained)
            return false;

        // end of list
        if(index >= _combo_count)
            return false;

        // read item object
        if(!_process.ReadMemory(_combo_addresses[index], &object, sizeof(object)))
            return false;

        // read text
        if(!_process.ReadMemory(object.addr2_value, string, _DROPDOWN_STRING_LIMIT))
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
    Bool Trainer::ReadHoverItem( Item& item )
    {
        // must be trained
        if(!_trained)
            return false;

        // name rarity type dps/armor
        _ReadHoverItemHeaders(item);

        // stats (can be empty)
        if(!_ReadHoverItemStats(item.stats))
            return false;

        // sockets (can be empty)
        if(!_ReadHoverItemSockets(item.sockets))
            return false;

        // must have something!
        return (*item.name || item.dpsarmor || item.stats.GetCount() || item.sockets.GetCount());
    }

    //------------------------------------------------------------------------
    Bool Trainer::ClearHoverItem()
    {
        // must be trained
        if(!_trained)
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
        _AhList     list_object;
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
            item.current_bid = NUMBER(item_object.bid1, 0);
            item.max_bid = NUMBER(item_object.bid2, 0);
        }
        else
            item.current_bid = item.max_bid = NUMBER(item_object.bid2, 0);

        // id
        item.id = item_object.id;

        // buyout
        item.buyout = NUMBER(item_object.buyout, 0);

        // time
        UHuge expire = item_object.time / 1000;
        UHuge current = System::GetTimeMs();

        item.rtime = expire > current ? static_cast<ULong>(expire - current) : 0;
        item.xtime = static_cast<ULong>(expire / 1000);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadListCount( ULong& count )
    {
        _AhList list_object;

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
        _UiObject ui_object;

        // must be trained
        if(!_trained)
            return false;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_LBUTTON_PAGENEXT))
            return false;

        // determine status
        status = (ui_object.visible && ui_object.n4 >= 16);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadButtonStatus( ButtonStatus& status, Id button_id )
    {
        _UiObject ui_object;

        // must be trained
        if(!_trained)
            return false;

        // read ui object
        if(!_ReadUiObject(ui_object, button_id))
            return false;

        // determine button busy status
        if(ui_object.visible)
        {
            switch(ui_object.n4)
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
    Bool Trainer::ReadPopupStatus( Bool& active )
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_MAIN_POPUP))
            return false;

        // check popup status
        active = (ui_object.visible != 0);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadLoginStatus( Bool& active )
    {
        ULong status;
        
        // get login status
        if(!_process.ReadMemory( _bnet_base + _BASEADDRESS_LOGGEDIN, &status, sizeof(ULong) ))
            return false;

        // set status
        active = (status > 0);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadAuctionMainStatus( Bool& active )
    {
        _UiObject ui_object;

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


    // private
    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemHeaders( Item& item )
    {
        _UiObject       ui_object;
        _UiHoverHeader  ui_header;
        _UiHoverName    ui_name;
        TextString      color;
        ULong           count;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME))
            return false;

        // read hover name
        if(!_process.ReadMemory(ui_object.addr2_value, &ui_name, sizeof(ui_name)))
            return false;

        // parse name
        if( *ui_name.text == 0 ||
            !Tools::StrFormatRead(count, ui_name.text, _FORMAT_ITEM_NAME, color, item.name) ||
            count != 2 )
            return false;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_DPSARMOR))
            return false;

        // read hover header
        if(!_process.ReadMemory(ui_object.addr2_value, &ui_header, sizeof(ui_header)))
            return false;

        // parse dps/armor
        Tools::StrToNumber(item.dpsarmor, ui_header.dpsarmor);

        // parse rarity/type
        if( *ui_header.raretype )
            Tools::StrFormatRead(count, ui_header.raretype, _FORMAT_ITEM_RARITYTYPE, color, item.rarity, item.type);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemStats( Item::StatCollection& stats )
    {
        _UiObject       ui_object;
        _UiHoverStats   ui_stats;
        Item::Stat      item_stat;
        const Char*     ptext;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_STATS))
            return false;

        // read stats
        if(!_process.ReadMemory(ui_object.addr2_value, &ui_stats, sizeof(ui_stats)))
            return false;

        // parse
        stats.Empty();
        for( ptext = ui_stats.text; (ptext = _ParseItemStatLine(item_stat, ptext, false)) && !stats.IsFull(); )
            stats.Push(item_stat);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemSockets( Item::SocketCollection& sockets )
    {
        _UiObject       ui_object;
        _UiHoverSocket  ui_socket;
        Item::Stat      item_stat;

        assert(sockets.GetLimit() >= (OBJECT_TOOLTIP_SOCKET2 - OBJECT_TOOLTIP_SOCKET0));
        sockets.Empty();

        // iterate
        for( Index i = 0; i < sockets.GetLimit(); i++ )
        {
            // read ui object
            if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_SOCKET0 + i))
                return false;

            // read socket
            if(!_process.ReadMemory(ui_object.addr2_value, &ui_socket, sizeof(ui_socket)))
                return false;

            // ignore nulls
            if(*ui_socket.text == 0)
                continue;

            // parse
            if(_ParseItemStatLine(item_stat, ui_socket.text, true) != NULL)
                sockets.Push(item_stat);
            else
                return false;
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemHeaders()
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_DPSARMOR))
            return false;

        // write null chars
        if(!_process.WriteByte(ui_object.addr2_value + FIELD_OFFSET(_UiHoverHeader, dpsarmor), 0))
            return false;
        if(!_process.WriteByte(ui_object.addr2_value + FIELD_OFFSET(_UiHoverHeader, raretype), 0))
            return false;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr2_value + FIELD_OFFSET(_UiHoverName, text), 0);
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemStats()
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_STATS))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr2_value + FIELD_OFFSET(_UiHoverStats, text), 0);
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemSockets()
    {
        _UiObject ui_object;

        // iterate
        for( Index i = 0; i <= (OBJECT_TOOLTIP_SOCKET2 - OBJECT_TOOLTIP_SOCKET0); i++ )
        {
            // read ui object
            if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_SOCKET0 + i))
                return false;

            // write null char
            if(!_process.WriteByte(ui_object.addr2_value + FIELD_OFFSET(_UiHoverSocket, text), 0))
                return false;
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadListRoot( _AhList& object )
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
    Bool Trainer::_ReadUiObject( _UiObject& object, Id id )
    {
        assert(id < OBJECT_COUNT);

        // read
        if(!_process.ReadMemory(_address[id], &object, sizeof(object)))
            return false;

        // validate
        if(!_IsValidUiObject(object))
            return false;

        // check path
        if(strcmp(object.path, _HINT_UIOBJECT_PATH[id]) != 0)
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadUiChild( _UiObject& child, const Char* path, const _UiObject& parent )
    {
        ULong address_list[UI_COMBO_ROW_LIMIT];

        // read address list
        if(!_process.ReadMemory(parent.addr1_children, address_list, sizeof(ULong) * parent.addr1_count))
            return false;

        // locate child in reverse order
        for( Long i = parent.addr1_count - 1; i >= 0; i-- )
        {
            // read object
            if(_process.ReadMemory(address_list[i], &child, sizeof(_UiObject)))
            {
                // check path
                if(strcmp(child.path, path) == 0)
                    return true;
            }
        }

        return false;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_IsValidUiObject( const _UiObject& object )
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
    Bool Trainer::OnScan( ULong address, const Byte* memory, ULong length )
    {
        const _UiObject& object = *reinterpret_cast<const _UiObject*>(memory);

        if(sizeof(_UiObject) <= length && _IsValidUiObject(object))
        {
            for( Id id = 0; id < ACOUNT(_HINT_UIOBJECT_PATH); id++ )
            {
                if( strcmp(object.path, _HINT_UIOBJECT_PATH[id]) == 0 )
                {
                    // fail if duplicate
                    if(_address[id] != 0)
                        return false;

                    // add address
                    _address[id] = address;
                }
            }
        }

        return true;
    }

    //------------------------------------------------------------------------
    void Trainer::_ParseItemStatString( Item::Stat& stat, const Char* text ) const
    {
        // copy text
        Tools::StrNCpy(stat.text, text, sizeof(stat.text));

        // collect values
        stat.values.Empty();
        while(*text)
        {
            Number      number;
            const Char* next = Tools::StrToNumber(number, text, false);
            if(next > text)
            {
                if(stat.values.GetCount() < stat.values.GetLimit())
                    stat.values.Push(number);
                text = next;
            }
            else
                text++;
        }
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
        if(*text == 0 || *text == '\n')
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
        }
        else
        {
            // read regular item stat (has different formats)
            for( i = 0; i < ACOUNT(_FORMAT_STAT) && ((count = Tools::StrFormatRead(count, text, _FORMAT_STAT[i], dummy_string, pstat_text, dummy_string)) == 0 || count < 2); i++ );
            if(i == ACOUNT(_FORMAT_STAT))
            {
                return NULL;
            }

            // remove leading whitespace
            for(; *pstat_text && isspace(*pstat_text); pstat_text++);

        }

        // parse stat text
        _ParseItemStatString(stat, pstat_text);

        // increment to next item
        text += count;

        return text;
    }
}
