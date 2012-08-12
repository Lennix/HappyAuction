#pragma once
#include <Diablo/Type/Item.hpp>
#include <Core/System/Process.hpp>
#include <Core/System/MemoryScanner.hpp>

namespace Diablo
{
    /**/
    class Trainer:
        MemoryScanner::IScanHandler
    {
    public:
        enum
        {
            OBJECT_COMBO_RARITY,
            OBJECT_COMBO_CHARACTER,
            OBJECT_COMBO_PRIMARY,
            OBJECT_COMBO_SECONDARY,
            OBJECT_COMBO_PSTAT0,
            OBJECT_COMBO_PSTAT1,
            OBJECT_COMBO_PSTAT2,

            OBJECT_TOOLTIP_STATS,
            OBJECT_TOOLTIP_DPSARMOR,
            OBJECT_TOOLTIP_SOCKET0,
            OBJECT_TOOLTIP_SOCKET1,
            OBJECT_TOOLTIP_SOCKET2,

            OBJECT_BUTTON_PAGENEXT,
            OBJECT_BUTTON_SEARCH,
            OBJECT_BUTTON_SENDTOSTASH,

            OBJECT_MAIN_POPUP,
            OBJECT_MAIN_AUCTION,

            OBJECT_COUNT,
        };

        enum ButtonStatus
        {
            BUTTON_HIDDEN,
            BUTTON_DISABLED,
            BUTTON_ENABLED,
            BUTTON_HIGHLIGHTED,
        };

    private:
        struct _UiObject
        {
            ULong   n1[10];
            ULong   visible;
            ULong   n2[3];
            Char    path[0x100];    // 038
            Byte    _2[0x328];
            ULong   addr_child1;    // 460
            Byte    _3[0x018];
            ULong   n3[4];          // 47c
            Byte    _4[0x058];
            ULong   n4;             // 4e4
            Byte    _5[0x5E0];
            ULong   addr_child2;    // ac8
            Byte    _6[0x220];
            ULong   n5[4];          // cec
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
        ULong           _address[OBJECT_COUNT];
        ULong           _base_address;
        Bool            _trained;

    public:
        /**/
        Trainer( Process& process );

        /**/
        Bool Train( Bool partial=false );
        Bool CheckTrained();

        /**/
        Bool WriteComboIndex( Id id, Index index );
        Bool ReadComboIndex( Id id, Index& index, ULong& count );

        /**/
        Bool ReadHoverItem( Item& item );
        Bool ClearHoverItem();

        /**/
        Bool ReadListItem( Index index, Item& item );
        Bool ReadListCount( ULong& count );
        Bool ReadListNextStatus( Bool& status );
        Bool ReadSearchBusyStatus( Bool& status );
        Bool ReadSendToStashStatus( ButtonStatus& status );

        /**/
        Bool ReadPopupStatus( Bool& active );
        Bool ReadLoginStatus( Bool& active );
        Bool ReadAuctionMainStatus( Bool& active );

        /**/
        Bool ReadFrameCount( ULong& count );

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
        Bool _ReadListRoot( _AhList& object );

        /**/
        Bool _IsValidUiObject( const _UiObject& object );

        /**/
        const Char* _ParseItemStatText( const Char* text, Item::Stat& stat, Bool is_socket ) const;

        /**/
        Bool OnScan( ULong address, const Byte* memory, ULong length );
    };
}
