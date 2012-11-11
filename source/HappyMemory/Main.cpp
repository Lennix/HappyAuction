#include <Core/Root.hpp>
#include <Core/Tools.hpp>
#include <Core/Type/Array.hpp>
#include <Diablo/Types.hpp>
#include <Diablo/Core/Game.hpp>
#include <Diablo/Core/Trainer.hpp>
#include <Core/System/Process.hpp>
#include <Core/System/MemoryScanner.hpp>
#include <windows.h>
#include <stdio.h>
using namespace Core;
using namespace Diablo;
using namespace Core;


static const ULong ALIGNMENT = 4;
static const ULong DEPTH = 5;


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
        ULong       depth = 4;
        ULong       address1 = 0x1ddc4000;
        //ULong       address1 = 0x1c413700;
        //ULong       address2 = 0x235F6100;
        //ULong       address3 = 0x235F6100;
        //ULong       address4 = 0x235F6100;

//        Char        v1[128] = "Root.TopLayer.DropDown._content._stackpanel";
        Char        v1[128] = "Only 10 auctions are allowed";
        ULong       v1size = strlen(v1);// + 1;
        //Char        v2[128] = "Root.TopLayer.DropDown._content._stackpanel._item1";
        //ULong       v2size = strlen(v2);
        //Char        v3[128] = "Root.TopLayer.DropDown._content._stackpanel._item2";
        //ULong       v3size = strlen(v3);
        //Char        v4[128] = "Root.TopLayer.DropDown._content._stackpanel._item3";
        //ULong       v4size = strlen(v4);

        PointerAnalysis analysis1;
        //PointerAnalysis analysis2;
        //PointerAnalysis analysis3;
        //PointerAnalysis analysis4;

//        if(!_scanner.Scan(*this))
//            return false;

        analysis1.SetDepth(depth);
        //analysis2.SetDepth(depth);
        //analysis3.SetDepth(depth);
        //analysis4.SetDepth(depth);

        _Mole( analysis1, address1, offset, offset0, v1, v1size, depth );
        //_Mole( analysis2, address2, offset, offset0, v2, v2size, depth );
        //_Mole( analysis3, address3, offset, offset0, v3, v3size, depth );
        //_Mole( analysis4, address4, offset, offset0, v4, v4size, depth );

        puts("Analyzing...");
        analysis1.Print();
        //analysis2.Print();
        //analysis3.Print();
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















/**/
class PatchTrainer:
    MemoryScanner::IScanHandler
{
private:
    const Char*     _path;
    ULong           _address;
    MemoryScanner   _scanner;

public:
    PatchTrainer(Process& process):
        _scanner(process)
    {
    }

    void Run()
    {

        _path = "Root";
        _address = 0;

        _scanner.Scan(*this);
    }

private:
    Bool OnScan( ULong address, const Byte* memory, ULong length )
    {
        const Trainer::UiObject& object = *reinterpret_cast<const Trainer::UiObject*>(memory);

        if(sizeof(Trainer::UiObject) <= length && Trainer::IsValidUiObject(object, Trainer::OBJECT_ROOT))
        {
            // add address
            _address = address;
            printf("%x\n", address);
            return false;
        }

        return true;
    }
};


/**/
int main()
{
    puts("Waiting...");
    //Sleep(1000);

    Window  window;
    Process process;

    if(window.Open(NULL, GAME_WINDOW_CLASS) && process.FromWindow(window))
    {
        PatchTrainer        application(process);
        //StructureMole       application(process);
        //ComparePair<ULong>  application(process);
        //SpiderProcess       application(process);

        process.SetLow( 0x00400000 ); process.SetHigh( 0x32000000 );

        puts("Running...");
        //process.Scan();
        application.Run();
    }

    return 0;
}
