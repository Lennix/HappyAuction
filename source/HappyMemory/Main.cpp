#include <Core/Root.hpp>
#include <Core/Tools.hpp>
#include <Core/System/Thread.hpp>
#include <Core/Array.hpp>
#include <Diablo/Types.hpp>
#include <Diablo/Core/Game.hpp>
#include <Core/System/Process.hpp>
#include <windows.h>
#include <stdio.h>
using namespace Core;
using namespace Diablo;
using namespace Core;


static const ULong ALIGNMENT = 4;
static const ULong DEPTH = 4;


#pragma pack(2)
struct Pointer
{
    ULong   address;
    UShort  offset;
};

struct PointerPath
{
    UShort  depth;
    Pointer pointers[DEPTH];
};
#pragma pack()

/**/
class PointerAnalysis
{
private:
    static const ULong _PATH_LIMIT = 11500000;
    static const ULong _COMPARE_LIMIT = 3;

public:
    typedef FixedArray<PointerPath, _PATH_LIMIT>            PathCollection;
    typedef PathCollection::Iterator                        PathIterator;
    typedef FixedArray<const PointerPath*, _COMPARE_LIMIT>  CompareCollection;

private:
    ULong           _max_depth;
    ULong           _current_depth;
    PointerPath     _current;
    PathCollection* _paths;

public:
    //
    PointerAnalysis():
        _max_depth(0),
        _current_depth(0)
    {
        _current.depth = 0;
        _paths = new PathCollection();
        assert(_paths);
    }

    //
    ~PointerAnalysis()
    {
        delete _paths;
    }

    //
    void SetDepth( ULong depth )
    {
        assert(depth <= _PATH_LIMIT);
        _max_depth = depth;
    }

    //
    void Reset()
    {
        _current_depth = 0;
        _paths->Empty();
    }

    //
    Bool PathPush()
    {
        if(_paths->GetCount() == _paths->GetLimit())
        {
            //puts("PathPush: FULL");
            return false;
        }
        _current.depth = _current_depth;
        _paths->Push(_current);
        return true;
    }

    //
    void PointerPush( ULong address, ULong offset )
    {
        assert( _current_depth < _max_depth );
        Pointer& pointer = _current.pointers[_current_depth];
        pointer.address = address;
        pointer.offset = offset;
        _current_depth++;
    }

    //
    void PointerPop()
    {
        assert( _current_depth > 0 );
        _current_depth--;
    }

    //
    void Print()
    {
        for( Index i = 0; i < _paths->GetCount(); i++ )
        {
            PrintPointerPath(0, (*_paths)[i]);
        }
        printf("\n");
    }

    //
    void PrintBest()
    {
        PointerPath best = {0};

        best.pointers[0].offset = ~0;

        for( Index i = 0; i < _paths->GetCount(); i++ )
        {
            const PointerPath &compare = (*_paths)[i];

            for( Index j = 0; j < compare.depth; j++ )
            {
                if(compare.pointers[j].offset < best.pointers[j].offset)
                {
                    best = compare;
                    break;
                }
            }
        }

        PrintPointerPath(0, best);
        printf("\n");
    }

    //
    void PrintCompare( const PointerAnalysis* others, ULong count )
    {
        for( PathIterator i = _paths->Begin(); i != _paths->End(); ++i )
        {
            CompareCollection   compare_list;
            const PointerPath*  compare;

            for( Index j = 0; j < count && (compare = _FindSimilarPath(*i, others[j])); j++ )
                compare_list.Push(compare);

            if(compare_list.GetCount() == count)
            {
                PrintPointerPath(0, *i);

                for( Index j = 0; j < count; j++ )
                    PrintPointerPath(j + 1, *compare_list[j]);

                printf("\n\n");
            }
        }
        printf("\n");
    }

    //
    void PrintSameStructs( const PointerAnalysis& other )
    {
        for( PathIterator i = _paths->Begin(); i != _paths->End(); ++i )
        {
            _PrintSameStructs(*i, other);
        }
        printf("\n");
    }

    static void PrintPointerPath( Id id, const PointerPath& path )
    {
        printf("%u ", id);
        for( Index i = 0; i < path.depth; i++ )
            _PrintPointer(path.pointers[i]);
        printf("\n");
    }


private:
    //
    const PointerPath* _FindSimilarPath( const PointerPath& path, const PointerAnalysis& analysis )
    {
//*
        for( PathIterator i = analysis._paths->Begin(); i != analysis._paths->End(); ++i )
            for( Index j = 0; j < i->depth; j++ )
                for( Index k = 0; k < path.depth; k++ )
                    if( path.pointers[k].address == i->pointers[j].address )
                        return &*i;
//*/
/*
        for( PathIterator i = analysis._paths->Begin(); i != analysis._paths->End(); ++i )
            if( i->depth == path.depth )
                for( Index j = 0; j < path.depth; j++ )
                    if( path.pointers[j].address == i->pointers[j].address )
                        return &*i;
//*/
        return NULL;
    }

    //
    void _PrintSameStructs( const PointerPath& path, const PointerAnalysis& other )
    {
        for( PathIterator i = other._paths->Begin(); i != other._paths->End(); ++i )
        {
            if(i->depth == path.depth)
            {
                Index j = 0;

                for(; j < path.depth && path.pointers[j].offset == i->pointers[j].offset; j++ );

                if(path.pointers[path.depth-1].offset == i->pointers[path.depth-1].offset)
//                if(j >= path.depth)
                {
                    PrintPointerPath(0, path);
                    PrintPointerPath(1, *i);
                    printf("\n");
                }
            }
        }
    }

    //
    static void _PrintPointer( const Pointer& pointer )
    {
        printf("[%0.8x + %0.3x] ", pointer.address, pointer.offset);
    }
};

/**/
class StructureSpider
{
private:
    static const ULong _MAPPING_LIMIT = 15000000;

private:
    struct Mapping
    {
        ULong address;
        ULong pointer;

        Bool operator < ( const Mapping& other ) const
        {
            return (pointer < other.pointer);
        }
    };

    typedef FixedArray<Mapping, _MAPPING_LIMIT> MapCollection;
    typedef MapCollection::Iterator             MapIterator;

private:
    MapCollection*  _map;

public:
    /**/
    StructureSpider()
    {
        _map = new MapCollection();
        assert(_map);
    }

    /**/
    ~StructureSpider()
    {
        delete _map;
    }

    /**/
    void CollectBegin()
    {
        _map->Empty();
    }

    /**/
    void CollectAdd( ULong address, ULong pointer )
    {
        if( (pointer % ALIGNMENT) == 0 )
        {
            Mapping& mapping = _map->Push();

            mapping.address = address;
            mapping.pointer = pointer;
        }
    }

    /**/
    void CollectComplete()
    {
        _map->Sort();
    }

    /**/
    void Analyze( PointerAnalysis& analysis, ULong address, ULong offset, ULong offset0, ULong depth )
    {
        analysis.Reset();
        analysis.SetDepth(depth);

        _Build(analysis, address, offset, offset0, depth, 0);
    }

private:
    /**/
    void _Build( PointerAnalysis& analysis, ULong address, ULong offset, ULong offset0, ULong depth, Index level )
    {
        if( level < depth )
        {
            ULong       current_offset = (level == 0 ? offset0 : offset);
            Mapping     search = { 0, address - current_offset };
            MapIterator mapping = _map->BinarySearch(search);

            for( ; mapping != _map->End() && mapping->pointer <= address; ++mapping )
            {
                ULong pointer_offset = address - mapping->pointer;

                //_Print(mapping->pointer, mapping->address, pointer_offset, level);

                analysis.PointerPush(mapping->address, pointer_offset);
                _Build(analysis, mapping->address, offset, offset0, depth, level + 1);
                analysis.PointerPop();
            }
        }
        else
            analysis.PathPush();
    }

    /**/
    void _Print( ULong pointer, ULong at, ULong offset, Index level )
    {
        for( Index i = 0; i < level; i++ )
            printf("\t");
        printf("%0.8x -> %0.8x + %0.4x\n", at, pointer, offset);
    }
};



/**/
class SpiderProcess:
    ProcessMemoryMap::IScanHandler
{
private:
    StructureSpider     _spider;
    Process&            _process;
    ProcessMemoryMap    _map;

public:
    /**/
    SpiderProcess( Process& process ):
        _process(process),
        _map(process)
    {
    }

    /**/
    Bool Run()
    {
        #define ANA_COUNT 2

        PointerAnalysis analysis_base;
        PointerAnalysis analysis_compare[ANA_COUNT];

        if(!_map.Build())
            return false;

        ULong offset =  4096;
        ULong offset0 = offset;//offset;
        ULong depth =   4;

        _RunSpider( 0, analysis_base,       0x1b3cfcec, offset, offset0, depth );
        _RunSpider( 1, analysis_compare[0], 0x178e4cec, offset, offset0, depth );
        _RunSpider( 2, analysis_compare[1], 0x178e5cec, offset, offset0, depth );

        puts("Comparing...");
        analysis_base.PrintCompare(analysis_compare, ANA_COUNT);

        return true;
    }
/*
    BASES
    -0xCEC   ah combo boxes
    -0x028   item first socket      Root.TopLayer.item 2.stack.frame body.stack.socket 0

    -0x000   item stats text        Root.TopLayer.item 2.stack.frame body.stack.enhancement
                                ->  [Root.TopLayer.item 2.stack.frame body.stack.stats - 0x38 + 0xac8]
                                ->  []
*/
private:
    /**/
    void _RunSpider( Id id, PointerAnalysis& analysis, ULong address, ULong offset, ULong offset0, ULong depth )
    {
        ULong               s_address = 0;
        ULong               s_next = 0;
        const Byte*         s_begin = NULL;
        const Byte*         s_end = NULL;

        // collect
        printf("[%u] Spider: Collect\n", id);
        _spider.CollectBegin();
        

        _map.Scan(*this);
//        while(IterateSlim(s_next, s_address, s_begin, s_end))
//            _OnScan(s_address, s_begin, s_end);

        _spider.CollectComplete();

        // analyze
        printf("[%u] Spider: Analyze\n", id);
        _spider.Analyze( analysis, address, offset, offset0, depth );

        // print
        printf("[%u] Spider: Results\n", id);
        //analysis.Print();
    }

    /**/
    Bool OnScan( ULong address, const Byte* memory )
    {
        ULong pointer = *(ULong*)memory;

        // ensure pointer is in address range
        if(_process.IsPossiblePointer(pointer))
            _spider.CollectAdd(address, pointer);

        return true;
    }
};



/**/
template<typename TYPE>
class ComparePair:
    ProcessMemoryMap::IScanHandler
{
private:
    TYPE    _value1;
    TYPE    _value2;
    ULong   _offset;

    ULong   _last_address;
    TYPE    _last_value;

    Process&            _process;
    ProcessMemoryMap    _map;

public:
    /**/
    ComparePair( Process& process ):
        _process(process),
        _map(process),
        _value1(0),
        _value2(0),
        _offset(0),
        _last_address(0),
        _last_value(0)
    {
    }

    /**/
    Bool Run()
    {
        _value1 = 0x198DCAB0;
        _value2 = 0x1EA54AB0;
        _offset = 32;
        if(_map.Build())
            _map.Scan(*this);

        return true;
    }


private:
    /**/
    Bool OnScan( ULong address, const Byte* memory )
    {
        TYPE value = *(const TYPE*)memory;

        if(value == _value1 || value == _value2)
        {
            if(_last_address && _last_value != value)
            {
                ULong diff = abs((Long)address - (Long)_last_address);
                if(diff <= _offset)
                    printf("[%0.8u @ %0.8x] ... %0.3u ... [%0.8u @ %0.8x]\n", _last_value, _last_address, diff, value, address);
            }

            _last_address = address;
            _last_value = value;
        }

        return true;
    }
};



/**/
class StructureMole
{
private:
    static const ULong _BUFFER_SIZE = 4096;
    struct Value
    {
        void*   value;
        ULong   length;
    };

    Process&            _process;
    ProcessMemoryMap    _map;

public:
    /**/
    StructureMole( Process& process ):
        _process(process),
        _map(process)
    {
    }

    ULong _MakeUnicode( Char* string )
    {
        ULong length = strlen(string);
        Char* end = string + length;

        for(; end-- != string; )
        {
            ULong offset = (end - string) * 2;

            string[offset] = *end;
            string[offset+1] = 0;
        }

        return length * 2;
    }

    /**/
    Bool Run()
    {
        ULong       offset = 4096;
        ULong       offset0 = 0x30;
        ULong       depth = 5;
        ULong       address1 = 0x1b034440;
//        ULong       address2 = 0x25252240;

//        Char        v1[128] = "{icon:bullet} {c:ff6969ff}+305 Minimum Damage{/c}";
        Char        v1[128] = "1271.6";
//        Char        v1[128] = "853";
        ULong       v1size = strlen(v1);
//        Char        v2[128] = "{c:ffffff00}War Abyss";
//        ULong       v2size = strlen(v2);

        PointerAnalysis analysis1;
//        PointerAnalysis analysis2;

        if(!_map.Build())
            return false;

        analysis1.SetDepth(depth);
//        analysis2.SetDepth(depth);

        _Mole( analysis1, address1, offset, offset0, v1, v1size, depth );
//        _Mole( analysis2, address2, offset, v2, v2size, depth );

        puts("Analyzing...");
        analysis1.Print();
//        analysis2.Print();

//        puts("Comparing...");
//        analysis1.PrintSameStructs(analysis2);

        return true;
    }

private:
    /**/
    Bool _Mole( PointerAnalysis& analysis, ULong address, ULong offset, ULong offset0, const void* value, ULong size, ULong depth, Index level=0 )
    {
        if( level < depth )
        {
            assert(offset <= _BUFFER_SIZE);
            ULong   level_offset = level == 0 ? offset0 : offset;
            Byte*   begin = _map.Access<Byte>(address, level_offset);//[_BUFFER_SIZE];
            Byte*   end = begin + level_offset;

//            if(Process::ReadMemory(address, begin, offset))
            if(begin)
            {
                // collect
                for( const Byte* current = begin; current < end; current+=ALIGNMENT )
                {
                    ULong pointer_offset = (current - begin);

                    if(memcmp(current, value, size) == 0)
                    {
                        analysis.PointerPush(address, pointer_offset);
                        analysis.PathPush();
                        analysis.PointerPop();
                    }
                    else
                    {
                        ULong pointer = *(ULong*)current;
                        if(_process.IsPossiblePointer(pointer))
                        {
                            analysis.PointerPush(address, pointer_offset);
                            _Mole(analysis, pointer, offset, offset, value, size, depth, level+1);
                            analysis.PointerPop();
                        }
                    }
                }
            }
        }

        return false;
    }
};


































#if 0





















































namespace Diablo
{


    const SelectOption AH_OPTION_PREFSTATS[] =
    {
        { EQSTAT_NONE, "NONE",                         ~0 },

        // damage
        { EQSTAT_DAMAGE, "DAMAGE",                       B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL) },
        { EQSTAT_ALLRESISTANCE, "ALLRESISTANCE",                B64(EQITEM_ARMOR_ALL), 0,            "+%u Resistance to All Elements" },
        { EQSTAT_ARCANERESISTANCE, "ARCANERESISTANCE",             B64(EQITEM_ARMOR_ALL), 0,            "+%u Arcane Resistance" },
        { EQSTAT_ARMOR, "ARMOR",                        B64(EQITEM_ARMOR_ALL), 0,            "+%u Armor" },
        { EQSTAT_ATTACKSPEEDP_W, "ATTACKSPEEDP_W",               B64(EQITEM_1H_ALL), 0,            "Increases Attack Speed by %u%%" },
        { EQSTAT_ATTACKSPEEDP_A, "ATTACKSPEEDP_A",               B64(EQITEM_ARMOR_ALL), 0,            "Attack Speed Increased by %u%%" },
        { EQSTAT_BLEEDCHANCE, "BLEEDCHANCE",                  B64(EQITEM_1H_ALL), 0,            "%u%% Chance to inflict Bleed for %u-%u damage over %u seconds." },
        { EQSTAT_BLOCKP, "BLOCKP",                       B64(EQITEM_ARMOR_ALL), 0,            "+%u%% Chance to Block" },
        { EQSTAT_BONUSDAMAGE, "BONUSDAMAGE",                  0, 0,            "+%u-%u Damage" },
        { EQSTAT_BONUSMAXIMUMWEAPONDAMAGE, "BONUSMAXIMUMWEAPONDAMAGE",     0, 0,            "+%u Maximum Damage" },
        { EQSTAT_BONUSMINIMUMARCANEDAMAGE, "BONUSMINIMUMARCANEDAMAGE",     B64(EQITEM_1H_ALL), 0,            "+%u-%u Arcane Damage" },
        { EQSTAT_BONUSMINIMUMCOLDDAMAGE, "BONUSMINIMUMCOLDDAMAGE",       B64(EQITEM_1H_ALL), 0,            "+%u-%u Cold Damage" },
        { EQSTAT_BONUSMINIMUMFIREDAMAGE, "BONUSMINIMUMFIREDAMAGE",       B64(EQITEM_1H_ALL), 0,            "+%u-%u Fire Damage" },
        { EQSTAT_BONUSMINIMUMHOLYDAMAGE, "BONUSMINIMUMHOLYDAMAGE",       B64(EQITEM_1H_ALL), 0,            "+%u-%u Holy Damage" },
        { EQSTAT_BONUSMINIMUMLIGHTNINGDAMAGE, "BONUSMINIMUMLIGHTNINGDAMAGE",  B64(EQITEM_1H_ALL), 0.334,            "+%u-%u Lightning Damage" },
        { EQSTAT_BONUSMINIMUMPHYSICALDAMAGE, "BONUSMINIMUMPHYSICALDAMAGE",   B64(EQITEM_ARMOR_ALL), 0,            "+%u Minimum Damage" },
        { EQSTAT_BONUSMINIMUMPOISONDAMAGE, "BONUSMINIMUMPOISONDAMAGE",     B64(EQITEM_1H_ALL), 0,            "+%u-%u Poison Damage" },
        { EQSTAT_BONUSMINIMUMWEAPONDAMAGE, "BONUSMINIMUMWEAPONDAMAGE",     B64(EQITEM_1H_ALL), 0,            "+%u Minimum Damage" },
        { EQSTAT_BONUSVSELITES, "BONUSVSELITES",                B64(EQITEM_1H_ALL), 0,            "Increases Damage Against Elites by %u%%" },
        { EQSTAT_COLDRESISTANCE, "COLDRESISTANCE",               B64(EQITEM_ARMOR_ALL), 0,            "+%u Cold Resistance" },
        { EQSTAT_CRITICALHITCHANCE, "CRITICALHITCHANCE",            B64(EQITEM_ARMOR_ALL), 0,            "Critical Hit Chance Increased by %u%%" },
        { EQSTAT_CRITICALHITDAMAGE, "CRITICALHITDAMAGE",            B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Critical Hit Damage Increased by %u%%" },
        { EQSTAT_FIRERESISTANCE, "FIRERESISTANCE",               B64(EQITEM_ARMOR_ALL), 0,            "+%u Fire Resistance" },
        { EQSTAT_LIGHTNINGRESISTANCE, "LIGHTNINGRESISTANCE",          B64(EQITEM_ARMOR_ALL), 0,            "+%u Lightning Resistance" },
        { EQSTAT_MINBLEEDDAMAGE, "MINBLEEDDAMAGE",               B64(EQITEM_1H_ALL), 0,            "%u%% Chance to inflict Bleed for %u-%u damage over %u seconds." },
        { EQSTAT_PHYSICALDAMAGETOATTACKER, "PHYSICALDAMAGETOATTACKER",     B64(EQITEM_ARMOR_ALL), 0,            "Melee attackers take %u damage per hit" },
        { EQSTAT_PHYSICALRESISTANCE, "PHYSICALRESISTANCE",           B64(EQITEM_ARMOR_ALL), 0,            "+%u Physical Resistance" },
        { EQSTAT_POISONRESISTANCE, "POISONRESISTANCE",             B64(EQITEM_ARMOR_ALL), 0,            "+%u Poison Resistance" },
        { EQSTAT_REDUCEDDAMAGEFROMELITES, "REDUCEDDAMAGEFROMELITES",      B64(EQITEM_ARMOR_ALL), 0,            "Reduces damage from elites by %u%%" },
        { EQSTAT_REDUCEDDAMAGEFROMMELEE, "REDUCEDDAMAGEFROMMELEE",       B64(EQITEM_ARMOR_ALL), 0,            "Reduces damage from melee attacks by %u%%" },
        { EQSTAT_REDUCEDDAMAGEFROMRANGED, "REDUCEDDAMAGEFROMRANGED",      B64(EQITEM_ARMOR_ALL), 0,            "Reduces damage from ranged attacks by %u%%" },
        { EQSTAT_WEAPONDAMAGEP, "WEAPONDAMAGEP",                B64(EQITEM_1H_ALL), 0,            "+%u%% Damage" },

        // crowd control
        { EQSTAT_CROWDCONTROL, "CROWDCONTROL",                 B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL)},
        { EQSTAT_CHANCETOBLINDONHIT, "CHANCETOBLINDONHIT",           B64(EQITEM_1H_ALL), 0,            "%u%% Chance to Blind on Hit" },
        { EQSTAT_CHANCETOCHILLONHIT, "CHANCETOCHILLONHIT",           B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Chill on Hit" },
        { EQSTAT_CHANCETOFEARONHIT, "CHANCETOFEARONHIT",            B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Fear on Hit" },
        { EQSTAT_CHANCETOFREEZEONHIT, "CHANCETOFREEZEONHIT",          B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Freeze on Hit" },
        { EQSTAT_CHANCETOIMMOBILIZEONHIT, "CHANCETOIMMOBILIZEONHIT",      B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Immobilize on Hit" },
        { EQSTAT_CHANCETOKNOCKBACKONHIT, "CHANCETOKNOCKBACKONHIT",       B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Knockback on Hit" },
        { EQSTAT_CHANCETOSLOWONHIT, "CHANCETOSLOWONHIT",            B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Slow on Hit" },
        { EQSTAT_CHANCETOSTUNONHIT, "CHANCETOSTUNONHIT",            B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u%% Chance to Stun on Hit" },
        { EQSTAT_CROWDCONTROLREDUCTION, "CROWDCONTROLREDUCTION",        B64(EQITEM_ARMOR_ALL), 0,            "Reduces duration of control impairing effects by %u" },

        // life
        { EQSTAT_LIFE, "LIFE",                         B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL)},
        { EQSTAT_EXTRAHEALTHFROMGLOBES, "EXTRAHEALTHFROMGLOBES",        B64(EQITEM_ARMOR_ALL), 0,            "Health Globes Grant +%u Life." },
        { EQSTAT_LIFEP, "LIFEP",                        B64(EQITEM_ARMOR_ALL), 0,            "+%u%% Life" },
        { EQSTAT_LIFEREGENERATION, "LIFEREGENERATION",             B64(EQITEM_ARMOR_ALL), 0,            "Regenerates %u Life per Second" },
        { EQSTAT_LIFESTEAL, "LIFESTEAL",                    B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "%u of Damage Dealt is Converted to Life" },
        { EQSTAT_LIFEAFTERKILL, "LIFEAFTERKILL",                B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "+%u Life after Each Kill" },
        { EQSTAT_LIFEONHIT, "LIFEONHIT",                    B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Each Hit Adds +%u Life" },
        { EQSTAT_LIFEPERSPIRITSPENT, "LIFEPERSPIRITSPENT",           B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Gain %u Life per Spirit Spent" },

        // resource
        { EQSTAT_RESOURCE, "RESOURCE",                     B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL)},
        { EQSTAT_ARCANEPOWERONCRIT, "ARCANEPOWERONCRIT",            B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Critical Hits grant %u Arcane Power" },
        { EQSTAT_HATREDREGENERATION, "HATREDREGENERATION",           B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Increases Hatred Regeneration by %u per Second" },
        { EQSTAT_MANAREGENERATION, "MANAREGENERATION",             B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Increases Mana Regeneration by %u per Second" },
        { EQSTAT_MAXARCANEPOWER, "MAXARCANEPOWER",               B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "+%u Maximum Arcane Power" },
        { EQSTAT_MAXDISCIPLINE, "MAXDISCIPLINE",                B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "+%u Maximum Discipline" },
        { EQSTAT_MAXFURY, "MAXFURY",                      B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "+%u Maximum Fury" },
        { EQSTAT_MAXMANA, "MAXMANA",                      B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "+%u Maximum Mana" },
        { EQSTAT_SPIRITREGENERATION, "SPIRITREGENERATION",           B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Increases Spirit Regeneration by %u per Second" },

        // attributes
        { EQSTAT_ATTRIBUTES, "ATTRIBUTES",                   ~0 },
        { EQSTAT_DEXTERITY, "DEXTERITY",                    ~0, 0,            "+%u Dexterity" },
        { EQSTAT_EXPERIENCE, "EXPERIENCE",                   ~0, 0,            "Monster kills grant +%u experience." },
        { EQSTAT_INTELLIGENCE, "INTELLIGENCE",                 ~0, 0,            "+%u Intelligence" },
        { EQSTAT_STRENGTH, "STRENGTH",                     ~0, 0,            "+%u Strength" },
        { EQSTAT_VITALITY, "VITALITY",                     ~0, 0,            "+%u Vitality" },

        // skills
        { EQSTAT_SKILLS, "SKILLS",                       B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL) },
        { EQSTAT_BAR_BASH, "BAR_BASH",                     B64(EQITEM_ARMOR_ALL), 0,            "Increases Bash Damage by %u%%" },
        { EQSTAT_BAR_CLEAVE, "BAR_CLEAVE",                   B64(EQITEM_ARMOR_ALL), 0,            "Increases Cleave Damage by %u%%" },
        { EQSTAT_BAR_FRENZY, "BAR_FRENZY",                   B64(EQITEM_ARMOR_ALL), 0,            "Increases Frenzy Damage by %u%%" },
        { EQSTAT_BAR_REND, "BAR_REND",                     B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Rend by %u Fury." },
        { EQSTAT_BAR_REVENGE, "BAR_REVENGE",                  B64(EQITEM_ARMOR_ALL), 0,            "Increases Critical Hit Chance of Revenge by %u%%" },
        { EQSTAT_BAR_WEAPONTHROW, "BAR_WEAPONTHROW",              B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Weapon Throw by %u Fury." },
        { EQSTAT_DH_CHAKRAM, "DH_CHAKRAM",                   B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Chakram by %u Hatred." },
        { EQSTAT_DH_EVASIVEFIRE, "DH_EVASIVEFIRE",               B64(EQITEM_ARMOR_ALL), 0,            "Increases Evasive Fire Damage by %u%%" },
        { EQSTAT_DH_GRENADES, "DH_GRENADES",                  B64(EQITEM_ARMOR_ALL), 0,            "Increases Grenades Damage by %u%%" },
        { EQSTAT_DH_IMPALE, "DH_IMPALE",                    B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Impale by %u Hatred." },
        { EQSTAT_DH_SPIKETRAP, "DH_SPIKETRAP",                 B64(EQITEM_ARMOR_ALL), 0,            "Increases Spike Trap Damage by %u%%" },
        { EQSTAT_MONK_CRIPPLINGWAVE, "MONK_CRIPPLINGWAVE",           B64(EQITEM_ARMOR_ALL), 0,            "Increases Crippling Wave Damage by %u%%" },
        { EQSTAT_MONK_CYCLONESTRIKE, "MONK_CYCLONESTRIKE",           B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Cyclone Strike by %u Spirit." },
        { EQSTAT_MONK_DEADLYREACH, "MONK_DEADLYREACH",             B64(EQITEM_ARMOR_ALL), 0,            "Increases Deadly Reach Damage by %u%%" },
        { EQSTAT_MONK_EXPLODINGPALM, "MONK_EXPLODINGPALM",           B64(EQITEM_ARMOR_ALL), 0,            "Increases Exploding Palm Damage by %u%%" },
        { EQSTAT_MONK_FISTSOFTHUNDER, "MONK_FISTSOFTHUNDER",          B64(EQITEM_ARMOR_ALL), 0,            "Increases Fists of Thunder Damage by %u%%" },
        { EQSTAT_MONK_SWEEPINGWIND, "MONK_SWEEPINGWIND",            B64(EQITEM_ARMOR_ALL), 0,            "Increases Sweeping Wind Damage by %u%%" },
        { EQSTAT_MONK_WAYOFHUNDREDFISTS, "MONK_WAYOFHUNDREDFISTS",       B64(EQITEM_ARMOR_ALL), 0,            "Increases Way of the Hundred Fists Damage by %u%%" },
        { EQSTAT_WD_ACIDCLOUD, "WD_ACIDCLOUD",                 B64(EQITEM_ARMOR_ALL), 0,            "Increases Critical Hit Chance of Acid Cloud by %u%%" },
        { EQSTAT_WD_FIREBATS, "WD_FIREBATS",                  B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Firebats by %u Mana." },
        { EQSTAT_WD_FIREBOMB, "WD_FIREBOMB",                  B64(EQITEM_1H_ALL), 0,            "Reduces resource cost of Firebomb by %u Mana." },
        { EQSTAT_WD_HAUNT, "WD_HAUNT",                     B64(EQITEM_1H_ALL), 0,            "Increases Haunt Damage by %u%%" },
        { EQSTAT_WD_LOCUSTSWARM, "WD_LOCUSTSWARM",               B64(EQITEM_ARMOR_ALL), 0,            "Increases Locust Swarm Damage by %u%%" },
        { EQSTAT_WD_PLAGUEOFTOADS, "WD_PLAGUEOFTOADS",             B64(EQITEM_1H_ALL), 0,            "Increases Plague of Toads Damage by %u%%" },
        { EQSTAT_WD_SUMMONZOMBIEDOGS, "WD_SUMMONZOMBIEDOGS",          B64(EQITEM_ARMOR_ALL), 0.340625,            "Reduces cooldown of Summon Zombie Dogs by %u seconds." },
        { EQSTAT_WIZ_ARCANETORRENT, "WIZ_ARCANETORRENT",            B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Arcane Torrent by %u Arcane Power." },
        { EQSTAT_WIZ_DISINTEGRATE, "WIZ_DISINTEGRATE",             B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Disintegrate by %u Arcane Power." },
        { EQSTAT_WIZ_ELECTROCUTE, "WIZ_ELECTROCUTE",              B64(EQITEM_ARMOR_ALL), 0,            "Increases Electrocute Damage by %u%%" },
        { EQSTAT_WIZ_ENERGYTWISTER, "WIZ_ENERGYTWISTER",            B64(EQITEM_1H_ALL), 0,            "Increases Critical Hit Chance of Energy Twister by %u%%" },
        { EQSTAT_WIZ_EXPLOSIVEBLAST, "WIZ_EXPLOSIVEBLAST",           B64(EQITEM_ARMOR_ALL), 0,            "Increases Critical Hit Chance of Explosive Blast by %u%%" },
        { EQSTAT_WIZ_HYDRA, "WIZ_HYDRA",                    B64(EQITEM_ARMOR_ALL), 0,            "Reduces resource cost of Hydra by %u Arcane Power." },
        { EQSTAT_WIZ_MAGICMISSILE, "WIZ_MAGICMISSILE",             B64(EQITEM_1H_ALL), 0,            "Increases Magic Missile Damage by %u%%" },
        { EQSTAT_WIZ_RAYOFFROST, "WIZ_RAYOFFROST",               B64(EQITEM_ARMOR_ALL), 0,            "Increases Critical Hit Chance of Ray of Frost by %u%%" },

        // properties
        { EQSTAT_PROPERTIES, "PROPERTIES",                   B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL) },
        { EQSTAT_GOLDFIND, "GOLDFIND",                     B64(EQITEM_ARMOR_ALL), 0,            "%u%% Extra Gold from Monsters" },
        { EQSTAT_HASSOCKETS, "HASSOCKETS",                   B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL) },
        { EQSTAT_INDESTRUCTIBLE, "INDESTRUCTIBLE",               B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Ignores Durability Loss" },
        { EQSTAT_MAGICFIND, "MAGICFIND",                    B64(EQITEM_ARMOR_ALL), 0,            "%u%% Better Chance of Finding Magical Items" },
        { EQSTAT_MOVEMENTSPEED, "MOVEMENTSPEED",                B64(EQITEM_ARMOR_ALL), 0,            "+%u%% Movement Speed" },
        { EQSTAT_PICKUPRADIUS, "PICKUPRADIUS",                 B64(EQITEM_ARMOR_ALL), 0,            "Increases Gold and Health Pickup by %u Yards." },
        { EQSTAT_REDUCEDLEVELREQUIREMENT, "REDUCEDLEVELREQUIREMENT",      B64(EQITEM_1H_ALL)|B64(EQITEM_ARMOR_ALL), 0,            "Level Requirement Reduced by %u" },

        // other
        { EQSTAT_EMPTYSOCKET, "EMPTYSOCKET", 0, 0, "" },
        { EQSTAT_BONUSEXPERIENCE, "BONUS_EXPERIENCE",       0, 0,            "Increases Bonus Experience by %u%%" },
        { INVALID_ID },
    };

}
















/**/
class TestTrainer:
    ProcessMemoryMap::IScanHandler
{
public:

private:
    struct UiObject
    {
        ULong   n1[14];
        Char    path[0x100];        // 038
        Byte    _2[0x328];
        ULong   addr_child1;        // 460
        Byte    _3[0x018];
        ULong   n2[4];              // 47c
        Byte    _4[0x63C];
        ULong   addr_child2;        // ac8
        Byte    _5[0x220];
        ULong   n3;                 // cec
    };

    struct UiObjectChild
    {
        Byte    _1[0x04];
        ULong   addr_target2;       // 004
        ULong   addr_target3;       // 008
    };

    struct UiHoverHeader
    {
        Byte    _1[0x78];
        Char    dpsarmor[0x20];     // 078
    };

    struct UiHoverStats
    {
        Char    text[0x400];        // 000
    };

    struct UiHoverSocket
    {
        Char    text[0x060];        // 000
    };

    struct AhSearchResult
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
    };

private:
    Process&            _process;
    ProcessMemoryMap    _memory;
    ULong               _address[ID_COUNT];
    ULong               _base_address;
    Bool                _trained;

public:
    /**/
    TestTrainer( Process& process ):
        _process(process),
        _memory(process),
        _trained(false)
    {
    }

    Bool Train()
    {
        Tools::MemZero(_address, ACOUNT(_address));
        _trained = false;

        // get base address
        _base_address = _process.GetBaseAddress(_PROCESS_MODULE);
        if(_base_address == 0)
            return false;

        // build memory map
        if(!_memory.Build())
            return false;

        // scan memory
        if(!_memory.Scan(*this))
            return false;

        // verify all addresses
        for( Index i = 0; i < ID_COUNT; i++ )
            if(_address[i] == 0)
                return false;

        _trained = true;
        return true;
    }

    void Run()
    {
        if(Train())
        {
            Item item;
            ReadHoverItem(item);
            ReadListing(3, item);
            WriteComboBox(FILTER_SECONDARY, 2);
        }
        //WriteComboBox(UI_FILTER_STATS0, 2);
    }

    /**/
    Bool WriteComboBox( Id id, Index index )
    {
        UiObject object;

        // must be trained
        if(!_trained)
            return false;

        // verify
        if(!_ReadObject(id, object))
            return false;

        // write
        _process.WriteMemory(_address[id] + FIELD_OFFSET(UiObject, n3), &index, sizeof(index));

        return true;
    }

    /**/
    Bool ReadHoverItem( Item& item )
    {
        // must be trained
        if(!_trained)
            return false;

        // dps
        if(!_ReadHoverItemDpsArmor(item.dpsarmor))
            return false;

        // stats
        if(!_ReadHoverItemStats(item.stats))
            return false;

        // sockets
        if(!_ReadHoverItemSockets(item.sockets))
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool ReadListing( Index index, Item& item )
    {
        AhSearchResult object;

        // get listing pointer from base static address
        ULong listing_address = _process.ReadChainAddress( _base_address, _CHAIN_SEARCHRESULTS );
        if(listing_address == 0)
            return false;

        // read listing object
        if(!_process.ReadMemory(listing_address + index * sizeof(AhSearchResult), &object, sizeof(object)))
            return false;

        // hint checks
        if( *(UHuge*)object.d3item != *(UHuge*)_HINT_SEARCHRESULT_ITEM ||
            *(UHuge*)object.d3gold != *(UHuge*)_HINT_SEARCHRESULT_GOLD)
            return false;

        // get values
        item.bid = object.bid;
        item.buyout = object.buyout;

        return true;
    }

private:
    //------------------------------------------------------------------------
    Bool _ReadHoverItemDpsArmor( ULong& value )
    {
        UiObject        ui_object;
        UiHoverHeader   ui_header;

        // read ui ui_object
        if(!_ReadObject(TOOLTIP_DPSARMOR, ui_object))
            return false;

        // read hover header
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_header, sizeof(ui_header)))
            return false;

        // parse dps/armor
        value = atoi(ui_header.dpsarmor);

        // verify
        if(value < _ITEM_HEADER_DPSARMOR_MIN || value > _ITEM_HEADER_DPSARMOR_MAX)
            return false;

        return true;
    }

    //------------------------------------------------------------------------
    Bool _ReadHoverItemStats( ItemStatCollection& stats )
    {
        UiObject        ui_object;
        UiHoverStats    ui_stats;
        ItemStat        item_stat;
        const Char*     ptext;

        // read ui object
        if(!_ReadObject(TOOLTIP_STATS, ui_object))
            return false;

        // read stats
        if(!_process.ReadMemory(ui_object.addr_child2, &ui_stats, sizeof(ui_stats)))
            return false;

        // parse
        stats.Empty();
        stats.MemoryZero();
        for( ptext = ui_stats.text; (ptext = _ParseItemStatText(ptext, item_stat, false)) && !stats.IsFull(); )
            stats.Push(item_stat);

        return true;
    }

    //------------------------------------------------------------------------
    Bool _ReadHoverItemSockets( ItemSocketCollection& sockets )
    {
        sockets.Empty();

        // iterate
        for( Index i = 0; i < sockets.GetLimit(); i++ )
        {
            UiObject        ui_object;
            UiHoverSocket   ui_socket;
            ItemStat        item_stat;

            // read ui object
            if(!_ReadObject(TOOLTIP_SOCKET0 + i, ui_object))
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

    /**/
    const Char* _ParseItemStatText( const Char* text, ItemStat& stat, Bool is_socket ) const
    {
        TextString stat_string;

        // stop at null
        if(*text == 0)
            return NULL;

        // if socket
        if(is_socket)
        {
            // if empty socket
            if(memcmp(text, _FORMAT_SOCKET_EMPTY, sizeof(_FORMAT_SOCKET_EMPTY)) == 0)
            {
                stat.id = EQSTAT_EMPTYSOCKET;
                return text + sizeof(_FORMAT_SOCKET_EMPTY);
            }
            // else read gem stats
            else if(sscanf(text, _FORMAT_SOCKET_GEM, stat_string) != 1)
                return NULL;
        }
        else
        {
            // read regular item stat
            if(sscanf(text, _FORMAT_STAT, stat_string) != 1)
                return NULL;

            // increment to next item
            text += Tools::StrLenPrint(text);
            if(*text)
                text++;
        }

        // parse stat text
        if(!Game::ParseItemString(stat, stat_string))
            return NULL;

        return text;
    }

    /**/
    Bool _ReadObject( Id id, UiObject& object )
    {
        assert(id < ID_COUNT);

        // verify
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

    /**/
    Bool OnScan( ULong address, const Byte* memory )
    {
        const UiObject& object = *_memory.Access<UiObject>(address);

        if(_IsValidUiObject(object))
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
                    printf("%d %.8x == %u\n", id, address, object.n3);
                }
            }
        }

        return true;
    }

    /*
const ULong TRAINING_HINT =                 *(ULong*)"Root";
const Char* TRAINING_TOOLTIP_STATS =        "Root.TopLayer.item 2.stack.frame body.stack.stats";
    Bool _OnScanTooltip( ULong address, const Byte* memory )
    {
        UiObject*           object;
        UiObjectChild*      child;
        Char*               text;
        const UiTooltip*    tt = (const UiTooltip*)memory;

        // read base
        for( Index i = 0; i < ACOUNT(tt->addr); i++ )
            if(!_process.IsPossiblePointer(tt->addr[i]))
                return false;

        // read stats
        if((object = _memory.Access<UiObject>(tt->addr_stats)) && strcmp(object->path, TRAINING_TOOLTIP_STATS) == 0)
        {
            UiHoverHeader* tt_header;

            printf("----\n%x\n%s\n----\n", tt->addr_stats, object->path);
            if((text = _memory.Access<Char>(object->addr_child2)) == NULL)
                return false;
            printf("STATS:\n%s\n\n", text);

            // read dps/values
            if((object = _memory.Access<UiObject>(tt->addr_main)) == NULL)
                return false;
            if((child = _memory.Access<UiObjectChild>(object->addr_child1)) == NULL)
                return false;
            if((object = _memory.Access<UiObject>(child->addr_target2)) == NULL)
                return false;
            printf("----\n%x\n%s\n----\n", child->addr_target2, object->path);
            if((tt_header = _memory.Access<UiHoverHeader>(object->addr_child2)) == NULL)
                return false;
            printf("DPS/ARMOR:\n%s\n\n", tt_header->dpsarmor);

            // read sockets
            for( Index i = 0; i < 3; i++ )
            {
                if((object = _memory.Access<UiObject>(tt->addr_socket[i])) == NULL)
                    return false;
                if((child = _memory.Access<UiObjectChild>(object->addr_child1)) == NULL)
                    return false;
                if((object = _memory.Access<UiObject>(child->addr_target3)) == NULL)
                    return false;
                printf("----\n%x\n%s\n----\n", child->addr_target3, object->path);
                if((text = _memory.Access<Char>(object->addr_child2)) == NULL)
                    return false;

                printf("SOCKET[%d]:\n%s\n\n", i, text);
            }

        }

        return true;
    }
    */

    /**/
    Bool _IsValidUiObject( const UiObject& object )
    {
        return
            object.n1[2]  == 0x00000000 &&
            object.n1[3]  == 0x00000000 &&
            object.n1[4]  == 0x00000000 &&
            object.n1[5]  == 0x00000000 &&
            object.n1[6]  == 0x00000000 &&
            object.n1[7]  == 0xffffffff &&
            object.n1[8]  == 0xffffffff &&
            object.n1[9]  == 0x00000001 &&
            object.n2[3]  == 0x600DF00D;
    }

};








#endif




static void _run_test_trainer()
{
    Window          window;
    Process         process;

    if(window.Find("Diablo III", "D3 Main Window Class") && process.FromWindow(window))
    {
        //TestTrainer trainer(process);

        process.SetLow( 0x01000000 );
        process.SetHigh( 0x32000000 );

        //trainer.Run();
    }
};




/**/
static Bool _ParseLine( PointerPath& path, const Char* line )
{
    path.depth = 0;
    Index i = 0;
    for( ; i < DEPTH; )
    {
        if(sscanf(line, "%x:%x", &path.pointers[i].address, &path.pointers[i].offset) != 2)
            break;
        i++;

        if((line = strchr(line, ',')) == NULL)
            break;
        line++;
    }
    path.depth = i;
    return i > 0;
}

static void _CompareFiles( const Char* path1, const Char* path2 )
{
    FILE*       f1 = fopen(path1, "rt");
    FILE*       f2 = fopen(path2, "rt");
    PointerPath p1;
    PointerPath p2;
    TextString  line;

    if(f1 && f2)
    {
        while(fgets(line, sizeof(line), f1) && _ParseLine(p1, line))
        {
            while(fgets(line, sizeof(line), f2) && _ParseLine(p2, line))
            {
                Bool greater = false;

                if(p1.depth > 0 && p1.depth == p2.depth)
                {
                    Index i = 0;

                    for( ; i < p1.depth && p1.pointers[i].offset == p2.pointers[i].offset; i++ );

                    if(i == p1.depth)
                    {
                        PointerAnalysis::PrintPointerPath(0, p1);
                        PointerAnalysis::PrintPointerPath(1, p2);
                        puts("");
                    }
                }
            }
            fseek(f2, 0, SEEK_SET);
        }
    }

    fclose(f1);
    fclose(f2);
}


/**/
int main()
{
    _run_test_trainer(); return 0;

    //_CompareFiles("1.txt", "2.txt"); return 0;
    puts("Waiting...");
    Sleep(1000);

    Window  window;
    Process process;

    if(window.Find("Diablo III", "D3 Main Window Class") && process.FromWindow(window))
    {
        //StructureMole       application(process);
        //ComparePair<ULong>  application(process);
        SpiderProcess       application(process);

        process.SetLow( 0x00400000 ); process.SetHigh( 0x32000000 );

        puts("Running...");
        //process.Scan();
        application.Run();
    }

    return 0;
}




/*
24937AB0
24935AB0
24951AB0


*/