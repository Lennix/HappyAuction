#pragma once
#include <Diablo/Core/AuctionInterface.hpp>
#include <Diablo/Core/AuctionTrainer.hpp>
#include <Diablo/Core/Support.hpp>
#include <string>

namespace Diablo
{
    // local
    //------------------------------------------------------------------------
    static const Char*  _PROCESS_MODULE =           "Diablo III.exe";

    static const Char   _FORMAT_SOCKET_EMPTY[] =    "{c_bonus}Empty Socket{/c}";
    static const Char*  _FORMAT_SOCKET_GEM =        "{icon:bullet} %[a-zA-Z0-9+.\% ]s\n";
    static const Char*  _FORMAT_STAT[] = {
        "{icon:bullet} {c:ff6969ff}%[a-zA-Z0-9+.()\% -]s{/c}\n",
        "{c:ff6969ff}{icon:bullet}%[a-zA-Z0-9+.()\% -]s{/c}\n"
    };

    static const Char*  _HINT_LISTITEM_ITEM =       "D3_ITEM";
    static const Char*  _HINT_LISTITEM_GOLD =       "D3_GOLD";
    static const Char*  _HINT_UIOBJECT_PATH[AuctionTrainer::ID_COUNT] =
    {
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchRarityFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchCharacterFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchSlotPrimaryFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchSlotSecondaryFilter",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 0 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 1 list.AdvancedFilterComboBox",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.EquipmentSearch.SearchStatsFilterList.slot 2 list.AdvancedFilterComboBox",

        "Root.TopLayer.item 2.stack.frame body.stack.stats",
        "Root.TopLayer.item 2.stack.frame body.stack.main.large_itembutton",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 0.text",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 1.text",
        "Root.TopLayer.item 2.stack.frame body.stack.socket 2.text",
        "Root.TopLayer.item 2.stack.frame body.stack.wrapper.itemLevel",
        "Root.TopLayer.item 2.stack.frame body.stack.main.stack.wrapper.col1.type",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchItemList.PagingButtonsContainer.PageRightButton",
        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.MenuContentContainer.SearchMenu.SearchMenuContent.SearchItemListContent.SearchButton",

        "Root.TopLayer.BattleNetLightBox_main.LayoutRoot.LightBox",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SellTabContent.Inventory.GoldAmount",

        "Root.NormalLayer.BattleNetAuctionHouse_main.LayoutRoot.OverlayContainer.TabContentContainer.SearchTabContent.SearchListContent.SearchItemList.ItemListContainer.ItemList",
    };

    static const Process::Link _chain_listroot[] =
    {
        0x00FC75B0,
        0x00000000
    };
    static const Process::Chain _CHAIN_LISTROOT(_chain_listroot, ACOUNT(_chain_listroot));


    //------------------------------------------------------------------------
    struct _UiObjectChild
    {
        Byte    _1      [0x04];
        ULong   addr_target2;       // 004
        ULong   addr_target3;       // 008
    };

    struct _UiHoverHeader
    {
        Byte    _1      [0x78];
        Char    dpsarmor[0x20];     // 078
    };

    struct _UiHoverStats
    {
        Char    text    [0x400];    // 000
    };

    struct _UiHoverSocket
    {
        Char    text    [0x060];    // 000
    };

    struct _AhListItem
    {
        Byte    _1      [0x024];
        Char    d3item  [0x008];    // 024
        Byte    _2      [0x064];
        Char    d3gold  [0x008];    // 090
        Byte    _3      [0x028];
        ULong   id;                 // 0C0
        Byte    _4      [0x00C];
        ULong   currBid;
        Byte    _5      [0x004];
        ULong   buyout;             // 0D8
        Byte    _6      [0x004];
        ULong   bid;                // 0E0
        Byte    _7      [0x004];
        ULong   flags;
        Byte    _8      [0x02C];
    };

    /*
    struct _AhListItem
    {
        Byte    _1      [0x024];
        Char    d3item  [0x008];    // 024
        Byte    _2      [0x064];
        Char    d3gold  [0x008];    // 090
        Byte    _3      [0x040];
        ULong   buyout;             // 0D8
        Byte    _4      [0x004];
        ULong   bid;                // 0DC
        Byte    _5      [0x034];
    };*/


    // public
    //------------------------------------------------------------------------
    AuctionTrainer::AuctionTrainer( Process& process ):
        _process(process),
        _memory(process),
        _trained(false)
    {
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::Train()
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
            for( i = 0; i < ID_COUNT && _address[i] != 0; i++ );

            // ready when no null addresses
            _trained = (i == ID_COUNT);
        }

        return _trained;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::CheckTrained()
    {
        _UiObject object;

        // check stat first
        if(!_trained)
            return false;

        // verify all objects
        for( Index i = 0; i < ID_COUNT; i++ )
        {
            if(!_ReadUiObject(i, object))
            {
                _trained = false;
                return false;
            }
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::WriteComboBox( Id id, Index index )
    {
        _UiObject object;

        // must be trained
        if(!_trained)
            return false;

        // verify
        if(!_ReadUiObject(id, object))
            return false;

        // write
        _process.WriteMemory(_address[id] + FIELD_OFFSET(_UiObject, n5[0]), &index, sizeof(index));

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ReadComboBox( Id id, Index& index, ULong& count )
    {
        _UiObject object;

        // must be trained
        if(!_trained)
            return false;

        // verify
        if(!_ReadUiObject(id, object))
            return false;

        index = object.n5[0];
        count = object.n5[3];

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ReadHoverItem( Item& item )
    {
        // must be trained
        if(!_trained)
            return false;

        // dps (only applies to weapons/armor)
        if(!_ReadHoverItemDpsArmor(item.dpsarmor))
            item.dpsarmor = 0;

        // stats (can be empty)
        if(!_ReadHoverItemStats(item.stats))
            return false;

        // sockets (can be empty)
        if(!_ReadHoverItemSockets(item.sockets))
            return false;

        if(!_ReadHoverItemLevel(item.ilevel))
            return false;

        // must have something!
        return (item.dpsarmor || item.stats.GetCount() || item.sockets.GetCount());
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ClearHoverItem()
    {
        // must be trained
        if(!_trained)
            return false;

        // dps
        if(!_ClearHoverItemDpsArmor())
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
    Bool AuctionTrainer::ReadListTimeLeft( Index index, Item& item )
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

        // get 0th colum
        if(!_ReadItemListRoot(itemList[0], subList))
            return false;

        if(_ReadUiObjectFromAddress(subList[3], ui_object))
            if(_process.ReadMemory(ui_object.addr_child2+0xc, &item.name, sizeof(item.name)))
                if(!_ParseItemNameText(item.name))
                    return false;

        return true;
    }

    Bool AuctionTrainer::ReadPlayerGold(ULong& gold)
    {
        _UiObject ui_object;
        if(!_ReadUiObject(PLAYER_GOLD, ui_object))
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
    Bool AuctionTrainer::_ReadItemListRoot( ULong address, ULong (&itemList)[11] )
    {
        _UiObject ui_object;

        if (address)
        {
            if(!_ReadUiObjectFromAddress(address, ui_object))
                return false;
        }
        else
        {
            if(!_ReadUiObject(ITEM_LIST, ui_object))
                return false;
        }

        if(!_process.ReadMemory(ui_object.addr_child1, &itemList, sizeof(itemList)))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ReadListItem( Index index, Item& item )
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
        if( *(UHuge*)item_object.d3item != *(UHuge*)_HINT_LISTITEM_ITEM ||
            *(UHuge*)item_object.d3gold != *(UHuge*)_HINT_LISTITEM_GOLD)
            return false;

        // get values
        item.bid =      item_object.bid;
        item.buyout =   item_object.buyout;

        item.currBid =  item_object.currBid;
        item.id =       item_object.id;
        item.flags =    item_object.flags;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ReadListCount( ULong& count )
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
    Bool AuctionTrainer::ReadListNextStatus( Bool& status )
    {
        _UiObject ui_object;

        // must be trained
        if(!_trained)
            return false;

        // read ui object
        if(!_ReadUiObject(LIST_PAGENEXT, ui_object))
            return false;

        // determine status
        status = (ui_object.visible && ui_object.n4 >= 16);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ReadListBusyStatus( Bool& status )
    {
        _UiObject ui_object;

        // must be trained
        if(!_trained)
            return false;

        // read ui object
        if(!_ReadUiObject(LIST_SEARCHBUTTON, ui_object))
            return false;

        // determine button busy status
        status = (ui_object.visible && ui_object.n4 == 0x22);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::ReadPopupStatus( Bool& active )
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(MAIN_POPUP, ui_object))
            return false;

        // check popup status
        active = (ui_object.visible != 0);

        return true;
    }


    // private
    //------------------------------------------------------------------------
    Bool AuctionTrainer::_ReadHoverItemDpsArmor( ULong& value )
    {
        _UiObject       ui_object;
        _UiHoverHeader  ui_header;

        // read ui object
        if(!_ReadUiObject(TOOLTIP_DPSARMOR, ui_object))
            return false;

        // read hover header
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_header, sizeof(ui_header)))
            return false;

        // parse dps/armor
        value = atoi(ui_header.dpsarmor);

        // verify
        if(value < ITEM_STAT_VALUE_MIN || value > ITEM_STAT_VALUE_MAX)
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::_ReadHoverItemStats( Item::StatCollection& stats )
    {
        _UiObject       ui_object;
        _UiHoverStats   ui_stats;
        Item::Stat      item_stat;
        const Char*     ptext;

        // read ui object
        if(!_ReadUiObject(TOOLTIP_STATS, ui_object))
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
    Bool AuctionTrainer::_ReadHoverItemSockets( Item::SocketCollection& sockets )
    {
        _UiObject       ui_object;
        _UiHoverSocket  ui_socket;
        Item::Stat      item_stat;

        assert(sockets.GetLimit() >= (TOOLTIP_SOCKET2 - TOOLTIP_SOCKET0));
        sockets.Empty();

        // iterate
        for( Index i = 0; i < sockets.GetLimit(); i++ )
        {
            // read ui object
            if(!_ReadUiObject(TOOLTIP_SOCKET0 + i, ui_object))
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

    Bool AuctionTrainer::_ReadHoverItemLevel( ULong& ilevel )
    {
        _UiObject       ui_object;
        if(!_ReadUiObject(TOOLTIP_ITEMLEVEL, ui_object))
            return false;

        TextString ilevelText;

        if(!_process.ReadMemory(ui_object.addr_child2, &ilevelText, sizeof(ilevelText)))
            return false;

        if (sscanf(ilevelText, "Item Level: %[a-zA-Z0-9+'.()\% -]s",ilevelText) == 0)
            return false;

        ilevel = atol(ilevelText);

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::_ClearHoverItemDpsArmor()
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(TOOLTIP_DPSARMOR, ui_object))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverHeader, dpsarmor), 0);
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::_ClearHoverItemStats()
    {
        _UiObject ui_object;

        // read ui object
        if(!_ReadUiObject(TOOLTIP_STATS, ui_object))
            return false;

        // write null char
        return _process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverStats, text), 0);
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::_ClearHoverItemSockets()
    {
        _UiObject ui_object;

        // iterate
        for( Index i = 0; i <= (TOOLTIP_SOCKET2 - TOOLTIP_SOCKET0); i++ )
        {
            // read ui object
            if(!_ReadUiObject(TOOLTIP_SOCKET0 + i, ui_object))
                return false;

            // write null char
            if(!_process.WriteByte(ui_object.addr_child2 + FIELD_OFFSET(_UiHoverSocket, text), 0))
                return false;
        }

        return true;
    }

    //------------------------------------------------------------------------
    Bool AuctionTrainer::_ReadUiObject( Id id, _UiObject& object )
    {
        assert(id < ID_COUNT);

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
    Bool AuctionTrainer::_ReadUiObjectFromAddress( ULong address, _UiObject& object )
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
    Bool AuctionTrainer::_ReadListRoot( _AhList& object )
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
    Bool AuctionTrainer::_IsValidUiObject( const _UiObject& object )
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
    Bool AuctionTrainer::OnScan( ULong address, const Byte* memory, ULong length )
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
    const Char* AuctionTrainer::_ParseItemStatText( const Char* text, Item::Stat& stat, Bool is_socket ) const
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

    Bool AuctionTrainer::_ParseItemNameText( TextString &text )
    {
        if (sscanf(text, "%[a-zA-Z0-9+'.()\% -]s{/c}",text) == 0)
            return false;
        return true;
    }
}
