#pragma once
#include <Core/Array.hpp>
#include <Core/Tools.hpp>
#include <Diablo/Root.hpp>

namespace Diablo
{
    /**/
    struct ComboOption
    {
        const Char* name;
        const Char* format[2];
        UHuge       group;
        ULong       character;

        /**/
        Bool Match( const Char* pattern ) const
        {
            assert(name);

            // search name and format
            return Tools::StrSearch(pattern, name) ||
                (format[0] != NULL && Tools::StrSearch(pattern, format[0])) ||
                (format[1] != NULL && Tools::StrSearch(pattern, format[1]));
        }
    };

    /**/
    class ComboBox
    {
    public:
        typedef Array<ComboOption>          OptionCollection;
        typedef OptionCollection::Iterator  OptionIterator;

    private:
        Array<ComboOption> _options;

    public:
        /**/
        ComboBox( const ComboOption* options, ULong count ):
            _options(options, count)
        {
        }

        /**/
        const OptionCollection& GetOptions() const
        {
            return _options;
        }

        /**/
        const ComboOption& operator[]( Id id ) const
        {
            return _options[id];
        }

        /**/
        Id Find( const Char* pattern ) const
        {
            ULong best_score = ~0;
            ULong best_id = INVALID_ID;
            ULong pattern_length = strlen(pattern);

            // search options for pattern
            for( Index i = 0; i < _options.GetCount(); ++i )
            {
                const ComboOption& option = _options[i];
                assert(option.name);

                // match pattern
                if(option.Match(pattern))
                {
                    ULong score = strlen(option.name) - pattern_length;

                    if(score < best_score)
                    {
                        best_score = score;
                        best_id = static_cast<Id>(i);
                    }
                }
            }

            return best_id;
        }
    };
}
