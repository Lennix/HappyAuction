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
            OBJECT_COMBO_PSTAT3,
            OBJECT_COMBO_PSTAT4,
            OBJECT_COMBO_PSTAT5,

            OBJECT_INPUT_LEVELMIN,
            OBJECT_INPUT_LEVELMAX,
            OBJECT_INPUT_PSTAT0,
            OBJECT_INPUT_PSTAT1,
            OBJECT_INPUT_PSTAT2,
            OBJECT_INPUT_PSTAT3,
            OBJECT_INPUT_PSTAT4,
            OBJECT_INPUT_PSTAT5,
            OBJECT_INPUT_UNIQUE,
            OBJECT_INPUT_BUYOUT,

            OBJECT_TOOLTIP_STATS,
            OBJECT_TOOLTIP_ASDAMAGE,
            OBJECT_TOOLTIP_DPSARMOR,
            OBJECT_TOOLTIP_TYPE,
            OBJECT_TOOLTIP_ILEVEL,
            OBJECT_TOOLTIP_SOCKET0,
            OBJECT_TOOLTIP_SOCKET1,
            OBJECT_TOOLTIP_SOCKET2,
            OBJECT_TOOLTIP_NAME,

            OBJECT_LBUTTON_PAGENEXT,
            OBJECT_BUTTON_SEARCH,
            OBJECT_BUTTON_SENDTOSTASH,
            OBJECT_BUTTON_BID,
            OBJECT_BUTTON_BUYOUT,

            OBJECT_TOP,
            OBJECT_MAIN_POPUP1,
            OBJECT_MAIN_POPUP2,
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
            ULong   addr1_children; // 460
            Byte    _3[0x004];
            ULong   addr1_count;    // 468
            Byte    _4[0x010];
            ULong   n3[4];          // 47c
            Byte    _5[0x058];
            ULong   n4;             // 4e4
            Byte    _6[0x020];
            Float   x1;             // 508
            Float   y1;             // 50c
            Float   x2;             // 510
            Float   y2;             // 514
            Byte    _7[0x5C8];
            ULong   addr2_value;    // ae0
            Byte    _8[0x00c];
            ULong   addr3_child;    // af0
            Byte    _9[0x418];
            ULong   n5[4];          // f0c
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
        ULong           _d3_base;
        ULong           _bnet_base;
        ULong           _combo_count;
        ULong           _combo_addresses[UI_COMBO_ROW_LIMIT];
        Bool            _trained;

    public:
        /**/
        Trainer( Process& process );

        /**/
        Bool Train( Bool partial=false );
        Bool CheckTrained();

        /**/
        Bool WriteComboIndex( Id id, Index index );
        Bool ReadComboIndex( Id id, Index* index=NULL, ULong* count=NULL );

        Bool ReadComboString( Id id, TextString string, Bool strip=true );
        Bool ReadComboRowBegin();
        Bool ReadComboRow( Index index, TextString string, Double& y );
        Bool ReadComboRowCount( ULong& count );

        /**/
        Bool WriteInputText( Id id, const Char* text );
        Bool ReadInputText( Id id, TextString text );

        /**/
        Bool ReadHoverStatus( Bool& status );
        Bool ReadHoverItem( Item& item );
        Bool ClearHoverItem();

        /**/
        Bool ReadListItem( Index index, Item& item );
        Bool ReadListCount( ULong& count );
        Bool ReadListNextStatus( Bool& status );
        
        /**/
        Bool ReadButtonStatus( ButtonStatus& status, Id button_id );

        /**/
        Bool ReadPopupStatus( Bool& active );
        Bool ReadLoginStatus( Bool& active );
        Bool ReadAuctionMainStatus( Bool& active );

        /**/
        Bool ReadFrameCount( ULong& count );
        Bool ReadGold( ULong& amount );
        Bool ReadAccount( TextString account );

    private:
        /**/
        Bool _ReadHoverItemHeaders( Item& item );
        Bool _ReadHoverItemStats( Item::StatCollection& stats );
        Bool _ReadHoverItemSockets( Item::SocketCollection& sockets );

        /**/
        Bool _ClearHoverItemHeaders();
        Bool _ClearHoverItemStats();
        Bool _ClearHoverItemSockets();

        /**/
        Bool _ReadListRoot( _AhList& object );

        /**/
        Bool _ReadUiObject( _UiObject& object, Id id );
        Bool _ReadUiChild( _UiObject& child, const Char* path, const _UiObject& parent );
        Bool _WriteUiObject( Id id, Bool visible );

        /**/
        Bool _IsValidUiObject( const _UiObject& object );

        /**/
        Bool OnScan( ULong address, const Byte* memory, ULong length );

        /**/
        void        _ParseItemStatString( Item::Stat& stat, const Char* text ) const;
        const Char* _ParseItemStatLine( Item::Stat& stat, const Char* text, Bool is_socket ) const;
    };
}
