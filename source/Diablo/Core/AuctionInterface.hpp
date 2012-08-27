#pragma once
#include <Diablo/Root.hpp>
#include <Diablo/Core/Game.hpp>
#include <Diablo/Core/Trainer.hpp>

namespace Diablo
{
    /**/
    class AuctionInterface
    {
    private:
        typedef FixedArray<Index, AH_PSTAT_LIMIT> IgnoreCollection;
        typedef IgnoreCollection::Iterator              IgnoreIterator;

    private:
        Game&       _game;
        Trainer&    _trainer;
        ULong       _search_delay;
        Id          _tab_primary;
        Id          _tab_secondary;
        Bool        _active;

    public:
        /**/
        AuctionInterface( Game& game );

        /**/
        Bool    Start();
        void    Stop();

        /**/
        Bool    WriteFilterBuyout( Number buyout, Bool randomize=false );
        Bool    ReadFilterBuyout( Number& value );
        Bool    WriteFilterUnique( const Char* string );
        Bool    ReadFilterUnique( TextString& string );

        /**/
        Bool    WriteFilterChar( const Char* name );
        Bool    ReadFilterChar( TextString name );
        Bool    WriteFilterPrimary( const Char* name );
        Bool    ReadFilterPrimary( TextString name );
        Bool    WriteFilterSecondary( const Char* name );
        Bool    WriteFilterSecondaryAuto( const Char* name );
        Bool    ReadFilterSecondary( TextString name );
        Bool    WriteFilterRarity( const Char* name );
        Bool    ReadFilterRarity( TextString name );
        Bool    WriteFilterStat( Index index, const Char* name, Number value );
        Bool    ReadFilterStat( Index index, TextString name, Number& value );

        Bool    WriteFilterLevelMin( Number level );
        Bool    ReadFilterLevelMin( Number& level );
        Bool    WriteFilterLevelMax( Number level );
        Bool    ReadFilterLevelMax( Number& level );

        /**/
        Bool    ActionSearch();
        Bool    ActionListSort( UiId id );
        Bool    ActionListNextPage();
        Bool    ActionBid( Index index, Number bid=0 );
        Bool    ActionBuyout( Index index );
        Bool    ActionSendToStash();
        Bool    ActionReLogin( const Char* account, const Char* password );

        /**/
        Bool    HoverListItem( Index index, Bool select );
        Bool    ReadListCount( ULong& count );
        Bool    ReadListItem( Index index, Item& item );

        /**/
        Bool    SellStashItem( Index column, Index row, Number starting, Number buyout );
        Bool    HoverStashItem( Index x, Index y, Bool select );
        Bool    ReadStashItem( Index x, Index y, Item& item );

        /**/
        Bool    Tab( Id primary, Id secondary=INVALID_ID );

    private:
        Bool    _ClearPopups();
        Bool    _WaitSearch();
        Bool    _ReadInputNumber( Id id, Number& number );
        void    _Reset();
    };
}
