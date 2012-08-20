#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/Trainer.hpp>
#include <Diablo/Core/Support.hpp>

namespace Diablo
{
    // local
    //------------------------------------------------------------------------
    static const Char*  _PROCESS_MODULE =           "Diablo III.exe";

    static const Char   _FORMAT_ITEM_LOWERCASE[] =  "{c:%s}%s{/c}";
    static const Char   _FORMAT_ITEM_NAME[] =       "{C:%s}%s{/C}";
    static const Char   _FORMAT_ITEM_RARITYTYPE[] = "{c:%s}%s %s{/c}";
    static const Char   _FORMAT_SOCKET_EMPTY[] =    "{c_bonus}Empty Socket{/c}";
    static const Char*  _FORMAT_SOCKET_GEM =        "{icon:bullet} %[a-zA-Z0-9+.\% ]s\n";
    static const Char*  _FORMAT_STAT[] = {
        "{icon:bullet} {c:ff6969ff}%[a-zA-Z0-9+.()\% -]s{/c}\n",
        "{c:ff6969ff}{icon:bullet}%[a-zA-Z0-9+.()\% -]s{/c}\n"
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
        //text string: ac8 @ "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 0 list.AdvancedFilterComboBox.text",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.LevelMinInputTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.LevelMaxInputTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 0 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 1 list.AdvancedFilterTextBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 2 list.AdvancedFilterTextBox",
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

        "Root.TopLayer.BattleNetLightBox_main.LayoutRoot.LightBox",
        
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.PageHeader",

        // Happy Auction Advanced:
        "Root.TopLayer.item 2.stack.frame body.stack.wrapper.itemLevel",
        "Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.type",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SellTabContent.Inventory.GoldAmount",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchItemList.ItemListContainer.ItemList",

    };

    static const Process::Link _chain_listroot[] =
    {
        0x00FC75B0,
        0x00000000
    };
    static const Process::Chain _CHAIN_LISTROOT(_chain_listroot, ACOUNT(_chain_listroot));
    static const ULong          _BASEADDRESS_FRAMECOUNT =   0x00FD5EE4;
    static const ULong          _BASEADDRESS_LOGGEDIN =     0x00FB40E0;

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
        ULong   current_bid;        // 0D0
        Byte    _5      [0x004];
        ULong   buyout;             // 0D8
        Byte    _6      [0x004];
        ULong   max_bid;            // 0E0
        Byte    _7      [0x004];
        ULong   flags;              // 0E8
        Byte    _8      [0x014];
        UHuge   time;               // 100
        Byte    _9      [0x010];
    };


    // public
    //------------------------------------------------------------------------
    Trainer::Trainer( Process& process ):
        _process(process),
        _memory(process),
        _trained(false)
    {
    }

    //------------------------------------------------------------------------
    Bool Trainer::Train( Bool partial )
    {
        Tools::MemZero(_address, ACOUNT(_address));
        _trained = false;

        // get base address
        _base_address = _process.GetBaseAddress(_PROCESS_MODULE);
        if(_base_address == 0)
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
        _process.WriteMemory(ui_object.addr_child2, &ui_input, strlen(ui_input.text)+1);

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
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_input, sizeof(ui_input)))
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

        // itemlevel
        if(!_ReadHoverItemLevel(item.ilevel))
            return false;

        // deprecated with 0.9.10
        // item type
        //if(!_ReadHoverItemType(item.type))
        //   return false;

        // this is the 0.9.9 readout, but its CAPS and thus sucks
        // name
        //if(!_ReadHoverItemName(item.name))
        //    return false;

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
    Bool Trainer::ReadListTimeLeft( Index index, Item& item )
    {
        // must be trained
        if(!_trained)
            return false;

        ULong itemList[11];

        // Get root item list
        if(!_ReadItemListRoot(0, itemList))
            return false;

        _UiObject ui_object;
        // get items list
        if(!_ReadItemListRoot(itemList[index], itemList))
            return false;

        // get sizing container
        if(!_ReadItemListRoot(itemList[2], itemList))
            return false;

        // get column container
        if(!_ReadItemListRoot(itemList[0], itemList))
            return false;

        // get 4th colum
        ULong subList[11];
        if(!_ReadItemListRoot(itemList[4], subList))
            return false;

        if(_ReadUiObjectFromAddress(subList[0], ui_object))
            if(!_process.ReadMemory(ui_object.addr_child2, &item.timeleft, sizeof(item.timeleft)))
                return false;

        // With 0.9.9 no longer necessary, but better than 0.9.9 feature
        // get 0th colum
        if(!_ReadItemListRoot(itemList[0], subList))
            return false;

        if(_ReadUiObjectFromAddress(subList[3], ui_object))
        {
            if(_process.ReadMemory(ui_object.addr_child2, &item.name, sizeof(item.name)))
            {
                ULong count = 0;
                TextString color;
                // parse name
                if( *item.name == 0 ||
                    !Tools::StrFormatRead(count, item.name, _FORMAT_ITEM_LOWERCASE, color, item.name) ||
                    count != 2 )
                    return false;
            }
        }
        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::ReadPlayerGold(ULong& gold)
    {
        _UiObject ui_object;
        if(!_ReadUiObject(ui_object, OBJECT_PLAYER_GOLD))
            return false;

        TextString goldString;

        if(!_process.ReadMemory(ui_object.addr_child2, &goldString, sizeof(goldString)))
            return false;

        TextString ret = "";

        int count = 0;
        for (int i = 0; i < sizeof(goldString); i++)
        {
            if (goldString[i] == 0 || goldString[i] == ' ')
                break;
            else if (goldString[i] != ',')
            {
                ret[count] = goldString[i];
                count++;
            }
        }
        gold = atol(ret);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadItemListRoot( ULong address, ULong (&itemList)[11] )
    {
        _UiObject ui_object;

        if (address)
        {
            if(!_ReadUiObjectFromAddress(address, ui_object))
                return false;
        }
        else
        {
            if(!_ReadUiObject(ui_object, OBJECT_ITEM_LIST))
                return false;
        }

        if(!_process.ReadMemory(ui_object.addr_child1, &itemList, sizeof(itemList)))
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

        // bid values
        item.current_bid = item_object.current_bid;
        item.max_bid = item_object.max_bid;

        // flags
        item.flags = item_object.flags;

        // id
        item.id = item_object.id;

        // buyout
        item.buyout = item_object.buyout;

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
        if(!_process.ReadMemory( _base_address + _BASEADDRESS_LOGGEDIN, &status, sizeof(ULong) ))
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
        return _process.ReadMemory( _base_address + _BASEADDRESS_FRAMECOUNT, &count, sizeof(ULong) );
    }


    // private
    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemHeaders( Item& item )
    {
        _UiObject       ui_object;
        _UiHoverHeader  ui_header;
        _UiHoverName    ui_name;
        TextString      color;
        TextString      rarity;
        TextString      type;
        ULong           count;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME))
            return false;

        // read hover name
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_name, sizeof(ui_name)))
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
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_header, sizeof(ui_header)))
            return false;

        // parse dps/armor
        ULong dpsarmor = atoi(ui_header.dpsarmor);
        if(dpsarmor >= ITEM_STAT_VALUE_MIN && dpsarmor <= ITEM_STAT_VALUE_MAX)
            item.dpsarmor = dpsarmor;

        // parse rarity/type
        if( *ui_header.raretype != 0 &&
            Tools::StrFormatRead(count, ui_header.raretype, _FORMAT_ITEM_RARITYTYPE, color, rarity, type) &&
            count == 3 )
        {
            item.rarity = ENUM_RARITIES.GetId(rarity);
            if(item.rarity != INVALID_ID)
                item.type = AH_COMBO_SECONDARY.Find(type);
        }

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
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_stats, sizeof(ui_stats)))
            return false;

        // parse
        stats.Empty();
        for( ptext = ui_stats.text; (ptext = _ParseItemStatText(ptext, item_stat, false)) && !stats.IsFull(); )
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
            if(!_process.ReadMemory(ui_object.addr_child2, &ui_socket, sizeof(ui_socket)))
                return false;

            // ignore nulls
            if(*ui_socket.text == 0)
                continue;

            // parse
            if(_ParseItemStatText(ui_socket.text, item_stat, true) != NULL)
                sockets.Push(item_stat);
            else
                return false;
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemLevel( ULong& ilevel )
    {
        _UiObject       ui_object;
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_ITEMLEVEL))
            return false;

        TextString ilevelText;

        if(!_process.ReadMemory(ui_object.addr_child2, &ilevelText, sizeof(ilevelText)))
            return false;

        if (sscanf(ilevelText, "Item Level: %[0-9+]s",ilevelText) == 0)
            return false;

        ilevel = atol(ilevelText);

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadHoverItemType( TextString string )
    {
        _UiObject       ui_object;
        _UiHoverName    ui_name;
        TextString      color;
        ULong           count;

        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_ITEMTYPE))
            return false;

        if(!_process.ReadMemory(ui_object.addr_child2, &ui_name, sizeof(ui_name)))
            return false;

        // parse name
        if( *ui_name.text == 0 ||
            !Tools::StrFormatRead(count, ui_name.text, _FORMAT_ITEM_LOWERCASE, color, string) ||
            count != 2 )
            return false;

        return true;
    }

    Bool Trainer::_ClearHoverItemHeaders()
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_DPSARMOR))
            return false;

        // write null chars
        if(!_process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverHeader, dpsarmor), 0))
            return false;
        if(!_process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverHeader, raretype), 0))
            return false;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_NAME))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverName, text), 0);
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ClearHoverItemStats()
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(ui_object, OBJECT_TOOLTIP_STATS))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverStats, text), 0);
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
            if(!_process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverSocket, text), 0))
                return false;
        }

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
    Bool Trainer::_ReadUiObjectFromAddress( ULong address, _UiObject& object )
    {
        // read
        if(!_process.ReadMemory(address, &object, sizeof(object)))
            return false;

        // validate
        if(!_IsValidUiObject(object))
            return false;

        // check path
        //if(strcmp(object.path, _HINT_UIOBJECT_PATH[id]) != 0)
        //   return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ReadListRoot( _AhList& object )
    {
        // get list root object from static chain
        ULong address = _process.ReadChainAddress( _base_address, _CHAIN_LISTROOT );
        if(address == 0)
            return false;

        // read list object
        if(!_process.ReadMemory(address, &object, sizeof(object)))
            return false;

        return true;
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
    const Char* Trainer::_ParseItemStatText( const Char* text, Item::Stat& stat, Bool is_socket ) const
    {
        Index       i;
        TextString  stat_string;
        Char*       pstat_string = stat_string;

        // stop at null
        if(*text == 0)
            return NULL;

        // if socket
        if(is_socket)
        {
            // if empty socket
            if(memcmp(text, _FORMAT_SOCKET_EMPTY, sizeof(_FORMAT_SOCKET_EMPTY)) == 0)
            {
                stat.id = ITEM_STAT_EMPTYSOCKET;
                return text + sizeof(_FORMAT_SOCKET_EMPTY);
            }
            // else read gem stats
            else if(sscanf(text, _FORMAT_SOCKET_GEM, pstat_string) != 1)
                return NULL;
        }
        else
        {
            // read regular item stat
            for( i = 0; i < ACOUNT(_FORMAT_STAT) && sscanf(text, _FORMAT_STAT[i], pstat_string) != 1; i++ );
            if(i == ACOUNT(_FORMAT_STAT))
                return NULL;

            // remove leading whitespace
            for(; *pstat_string && isspace(*pstat_string); pstat_string++);

            // increment to next item
            text += Tools::StrLenPrint(text);
            if(*text)
                text++;
        }

        // parse stat text
        if(!Support::ParseItemStatString(stat, pstat_string))
            return NULL;

        return text;
    }

    //------------------------------------------------------------------------
    Bool Trainer::_ParseText( TextString &text )
    {
        if (sscanf(text, "%[a-zA-Z0-9+'.()\% -]s{/c}",text) == 0)
            return false;
        return true;
    }
}
