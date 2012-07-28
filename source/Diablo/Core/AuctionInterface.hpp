#pragma once
#include <Diablo/Root.hpp>
#include <Diablo/Core/Game.hpp>
#include <Diablo/Core/AuctionTrainer.hpp>

namespace Diablo
{
    /**/
    class AuctionInterface
    {
    private:
        typedef FixedArray<Index, AH_INPUT_PSTAT_LIMIT> IgnoreCollection;
        typedef IgnoreCollection::Iterator              IgnoreIterator;

    private:
        Game&           _game;
        AuctionTrainer  _trainer;
        ULong           _search_delay;

    public:
        /**/
        AuctionInterface( Game& game );

        /**/
        Game&   GetGame();

        /**/
        Bool    Train();
        AuctionTrainer& GetTrainer();

        /**/
        Bool    WriteBuyout( ULong buyout, Bool randomize=false );
        ULong   ReadBuyout();
        Bool    WriteUnique( const Char* string );

        /**/
        Bool    WriteFilterCharacter( FilterCharId id );
        Bool    WriteFilterType( FilterSecondaryId id );
        Bool    WriteFilterLevelMin( ULong level );
        Bool    WriteFilterLevelMax( ULong level );
        Bool    WriteFilterRarity( FilterRarityId id );
        Bool    WriteFilterStat( Index index, ItemStatId id, ULong value );

        /**/
        Bool    ActionSearch();
        Bool    ActionListSortDpsArmor();
        Bool    ActionListSortBuyout();
        Bool    ActionListNextPage();
        Bool    ActionBid( Index index, ULong bid=0 );
        Bool    ActionBuyout( Index index );

        /**/
        Bool    HoverListItem( Index index, Bool select );
        Bool    ReadListCount( ULong& count );
        Bool    ReadListItem( Index index, Item& item );

    private:
        Bool    _WriteComboBox( Id combo_id, Id id );
        Bool    _WriteComboRefresh( Id option_id );

        Bool    _CalculateComboIndex( Index& option_index, Id combo_id, Id option_id );
        Id      _OptionIndexToId( Index option_index, Id group_id, const ComboBox& box ) const;
        Index   _OptionIdToIndex( Id option_id, Id group_id, const ComboBox& box, IgnoreCollection& ignores ) const;
        Bool    _WaitSearch();
    };
}
