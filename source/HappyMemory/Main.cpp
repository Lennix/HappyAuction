#include <Core/Root.hpp>
#include <Core/Tools.hpp>
#include <Core/Type/Array.hpp>
#include <Diablo/Types.hpp>
#include <Diablo/Core/Game.hpp>
#include <Core/System/Process.hpp>
#include <Core/System/MemoryScanner.hpp>
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


#if 0
/**/
class SpiderProcess:
    MemoryScanner::IScanHandler
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
    MemoryScanner::IScanHandler
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

#endif

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
    MemoryScanner       _scanner;

public:
    /**/
    StructureMole( Process& process ):
        _process(process),
        _scanner(process)
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
        ULong       offset0 = offset;
        ULong       depth = 3;
        ULong       address1 = 0x235F6100;
        ULong       address2 = 0x235F6100;
        ULong       address3 = 0x235F6100;
        ULong       address4 = 0x235F6100;

//        Char        v1[128] = "Root.TopLayer.DropDown._content._stackpanel";
        Char        v1[128] = "Root.TopLayer.DropDown._content._stackpanel._item0";
        ULong       v1size = strlen(v1);
        Char        v2[128] = "Root.TopLayer.DropDown._content._stackpanel._item1";
        ULong       v2size = strlen(v2);
        Char        v3[128] = "Root.TopLayer.DropDown._content._stackpanel._item2";
        ULong       v3size = strlen(v3);
        Char        v4[128] = "Root.TopLayer.DropDown._content._stackpanel._item3";
        ULong       v4size = strlen(v4);

        PointerAnalysis analysis1;
        PointerAnalysis analysis2;
        PointerAnalysis analysis3;
        PointerAnalysis analysis4;

//        if(!_scanner.Scan(*this))
//            return false;

        analysis1.SetDepth(depth);
        analysis2.SetDepth(depth);
        analysis3.SetDepth(depth);
        analysis4.SetDepth(depth);

        _Mole( analysis1, address1, offset, offset0, v1, v1size, depth );
        _Mole( analysis2, address2, offset, offset0, v2, v2size, depth );
        _Mole( analysis3, address3, offset, offset0, v3, v3size, depth );
        //_Mole( analysis4, address4, offset, offset0, v4, v4size, depth );

        puts("Analyzing...");
        analysis1.Print();
        analysis2.Print();
        analysis3.Print();
        //analysis4.Print();

//        puts("Comparing...");
//        analysis1.PrintSameStructs(analysis2);

        return true;
    }

private:
    /**/
    Bool _Mole( PointerAnalysis& analysis, ULong address, ULong offset, ULong offset0, const void* value, ULong size, ULong depth, Index level=0 )
    {
        Byte begin[8192];

        if( level < depth )
        {
            assert(offset <= _BUFFER_SIZE);
            ULong   level_offset = level == 0 ? offset0 : offset;


            if(_process.ReadMemory((ULong)address, begin, level_offset))
            {
                //Byte*   begin = _map.Access<Byte>(address, level_offset);//[_BUFFER_SIZE];
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
        }

        return false;
    }
};


















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
    //_run_test_trainer(); return 0;

    //_CompareFiles("1.txt", "2.txt"); return 0;
    puts("Waiting...");
    //Sleep(1000);

    Window  window;
    Process process;

    if(window.Find("Diablo III", "D3 Main Window Class") && process.FromWindow(window))
    {
        StructureMole       application(process);
        //ComparePair<ULong>  application(process);
        //SpiderProcess       application(process);

        process.SetLow( 0x00400000 ); process.SetHigh( 0x32000000 );

        puts("Running...");
        //process.Scan();
        application.Run();
    }

    return 0;
}
