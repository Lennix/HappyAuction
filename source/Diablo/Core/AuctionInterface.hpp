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

    public:
        /**/
        AuctionInterface( Game& game );

        /**/
        Bool    WriteBuyout( Long buyout, Bool randomize=false );
        Bool    ReadBuyout( Long& value );
        Bool    WriteUnique( const Char* string );
        Bool    ReadUnique( TextString& string );

        /**/
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
        Bool    ActionReLogin( const Char* account, const Char* password );

        /**/
        Bool    HoverListItem( Index index, Bool select );
        Bool    ReadListCount( ULong& count );
        Bool    ReadListItem( Index index, Item& item );

        /**/
        void    HoverGround();
        Bool    WaitFrames( ULong count );

    private:
        Bool    _WriteComboBox( Id combo_id, Id id );
        Bool    _WriteComboRefresh( Id option_id );

        Bool    _CalculateComboIndex( Index& option_index, Id combo_id, Id option_id );
        Id      _OptionIndexToId( Index option_index, Id group_id, const ComboBox& box ) const;
        Index   _OptionIdToIndex( Id option_id, Id group_id, const ComboBox& box, IgnoreCollection& ignores ) const;
        Bool    _WaitSearch();
    };
}
