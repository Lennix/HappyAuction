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
        typedef FixedArray<Index, AH_INPUT_PSTAT_LIMIT> IgnoreCollection;
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
        Bool    WriteFilterChar( FilterCharId char_id );
        Bool    ReadFilterChar( FilterCharId& char_id );
        Bool    WriteFilterPrimary( FilterPrimaryId primary_id );
        Bool    ReadFilterPrimary( FilterPrimaryId& primary_id );
        Bool    WriteFilterSecondary( FilterSecondaryId secondary_id );
        Bool    ReadFilterSecondary( FilterSecondaryId& secondary_id );
        Bool    WriteFilterRarity( FilterRarityId rarity_id );
        Bool    ReadFilterRarity( FilterRarityId& rarity_id );
        Bool    WriteFilterStat( Index index, ItemStatId id, Number value );
        Bool    ReadFilterStat( Index index, ItemStatId& id, Number& value );

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
        void    HoverGround();

    private:
        Bool    _ClearPopups();

        Bool    _WriteComboBox( Id combo_id, Id id );
        Bool    _WriteComboRefresh( Id combo_id, Index option_index, ULong option_count );

        Bool    _CalculateOptionIndex( Index& option_index, ULong& option_count, Id combo_id, Id option_id );
        Bool    _OptionIndexToId( Id& option_id, Index option_index, Id group_id, const ComboBox& box, const IgnoreCollection& ignores=IgnoreCollection::GetEmpty() ) const;
        Bool    _OptionIdToIndex( Index& option_index, Id option_id, Id group_id, const ComboBox& box, const IgnoreCollection& ignores=IgnoreCollection::GetEmpty() ) const;
        Bool    _WaitSearch();

        Bool    _ReadInputNumber( Id id, Number& number );
        void    _Reset();
    };
}
