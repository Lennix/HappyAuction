#pragma once
#include <Diablo/Type/Item.hpp>
#include <Core/System/Process.hpp>
#include <Core/System/MemoryScanner.hpp>

namespace Diablo
{
    /**/
    class AuctionTrainer:
        MemoryScanner::IScanHandler
    {
    public:
        enum
        {
            COMBO_RARITY,
            COMBO_CHARACTER,
            COMBO_PRIMARY,
            COMBO_SECONDARY,
            COMBO_PSTAT0,
            COMBO_PSTAT1,
            COMBO_PSTAT2,

            TOOLTIP_STATS,
            TOOLTIP_DPSARMOR,
            TOOLTIP_SOCKET0,
            TOOLTIP_SOCKET1,
            TOOLTIP_SOCKET2,

            LIST_PAGENEXT,
            LIST_SEARCHBUTTON,

            MAIN_POPUP,

            PLAYER_GOLD,

            ITEM_LIST,

            ID_COUNT,
        };

    private:
        struct _UiObject
        {
            ULong   n1[10];
            ULong   visible;
            ULong   n2[3];
            Char    path[0x400];    // 038
            Byte    _2[0x028];
            ULong   addr_child1;    // 460
            Byte    _3[0x018];
            ULong   n3[4];          // 47c
            Byte    _4[0x058];
            ULong   n4;             // 4e4
            Byte    _5[0x5E0];
            ULong   addr_child2;    // ac8
            Byte    _6[0x220];
            ULong   n5;             // cec
        };

        struct _AhList
        {
            Byte    _1[0x14];
            ULong   count;          // 014
            Byte    _2[0x04];
            ULong   addr_items;     // 01C
        };

    private:
        Process&        _process;
        MemoryScanner   _memory;
        ULong           _address[ID_COUNT];
        ULong           _base_address;
        Bool            _trained;

    public:
        /**/
        AuctionTrainer( Process& process );

        /**/
        Bool Train();
        Bool CheckTrained();

        /**/
        Bool WriteComboBox( Id id, Index index );
        Bool ReadComboBox( Id id, Index& index );

        /**/
        Bool ReadHoverItem( Item& item );
        Bool ClearHoverItem();

        /**/
        Bool ReadListItem( Index index, Item& item );
        Bool ReadListTimeLeft( Index index, Item& item );
        Bool ReadListCount( ULong& count );
        Bool ReadListNextStatus( Bool& status );
        Bool ReadListBusyStatus( Bool& status );

        Bool ReadPlayerGold (ULong& gold);

        /**/
        Bool ReadPopupStatus( Bool& active );

    private:
        /**/
        Bool _ReadHoverItemDpsArmor( ULong& value );
        Bool _ReadHoverItemStats( Item::StatCollection& stats );
        Bool _ReadHoverItemSockets( Item::SocketCollection& sockets );

        /**/
        Bool _ClearHoverItemDpsArmor();
        Bool _ClearHoverItemStats();
        Bool _ClearHoverItemSockets();

        /**/
        Bool _ReadUiObject( Id id, _UiObject& object );
        Bool _ReadUiObjectFromAddress( ULong address, _UiObject& object );
        Bool _ReadListRoot( _AhList& object );

        Bool _ReadItemListRoot( ULong address, ULong (&itemList)[11] );

        /**/
        Bool _IsValidUiObject( const _UiObject& object );

        /**/
        const Char* _ParseItemStatText( const Char* text, Item::Stat& stat, Bool is_socket ) const;
        Bool AuctionTrainer::_ParseItemNameText( TextString &text );

        /**/
        Bool OnScan( ULong address, const Byte* memory, ULong length );
    };
}
