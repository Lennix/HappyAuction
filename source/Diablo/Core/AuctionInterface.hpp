#pragma once
#include <Diablo/Root.hpp>
#include <Diablo/Core/Game.hpp>
#include <time.h>
#include <Diablo/Core/Trainer.hpp>

namespace Diablo
{
    /**/
    class AuctionInterface
    {
    private:
        typedef FixedArray<Index, AH_INPUT_PSTAT_LIMIT> IgnoreCollection;
        typedef IgnoreCollection::Iterator              IgnoreIterator;

    private:
        Game&       _game;
        Trainer&    _trainer;
        ULong       _search_delay;
        Id          _tab_primary;
        Id          _tab_secondary;
        Bool        _active;

        clock_t         init;
        ULong           queries;
        ULong           use_color;

    public:
        /**/
        AuctionInterface( Game& game );

        /**/
        Bool    Start();
        void    Stop();

        /**/
        Bool    WriteBuyout( Long buyout, Bool randomize=false );
        Bool    ReadBuyout( Long& value );
        Bool    WriteUnique( const Char* string );
        Bool    ReadUnique( TextString& string );

        /**/
        Bool    WriteFilterChar( FilterCharId char_id );
        Bool    WriteFilterType( FilterSecondaryId id );
        Bool    WriteFilterLevelMin( Long level );
        Bool    WriteFilterLevelMax( Long level );
        Bool    WriteFilterRarity( FilterRarityId id );
        Bool    WriteFilterStat( Index index, ItemStatId id, ULong value );

        /**/
        Bool    ActionSearch();
        Bool    ActionListSortDpsArmor();
        Bool    ActionListSortBuyout();
        Bool    ActionListNextPage();
        Bool    ActionBid( Index index, ULong bid=0 );
        Bool    ActionBuyout( Index index );
        Bool    ActionSendToStash();
        Bool    ActionReLogin( const Char* account, const Char* password );

        /**/
        Bool    HoverListItem( Index index, Bool select );
        Bool    ReadListCount( ULong& count );
        Bool    ReadListItem( Index index, Item& item );

        Bool    GetGold(ULong& gold);

        ULong   ParseTime( const Char* text );
        /**/
        Bool    SellStashItem( Index column, Index row, ULong starting, ULong buyout );
        Bool    HoverStashItem( Index x, Index y, Bool select );
        Bool    ReadStashItem( Index x, Index y, Item& item );

        /**/
        Bool    Tab( Id primary, Id secondary=INVALID_ID );
        void    HoverGround();

    private:
        Bool    _WriteComboBox( Id combo_id, Id id );
        Bool    _WriteComboRefresh( Id combo_id, Index option_index, ULong option_count );

        Bool    _CalculateOptionIndex( Index& option_index, ULong& option_count, Id combo_id, Id option_id );
        Bool    _OptionIndexToId( Id& option_id, Index option_index, Id group_id, const ComboBox& box ) const;
        Bool    _OptionIdToIndex( Index& option_index, Id option_id, Id group_id, const ComboBox& box, IgnoreCollection& ignores ) const;
        Bool    _WaitSearch();
        clock_t _WaitForQueriesPerHour();

        void    _Reset();
    };
}
