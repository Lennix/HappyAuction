#include <Core/Tools.hpp>
#include <HappyAuction/Core/Application.hpp>
#include <HappyAuction/Core/Script.hpp>

/**/
static void _unit_test()
{
    using namespace Core;

    int z = 0; 
}

/**/
int WINAPI WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance, 
    LPSTR       lpCmdLine,
    int         iCmdShow)
{
    using namespace Core;

    try
    {
        HappyAuction::Application().Run();
    }
    catch(const Char* exception)
    {
        System::Message(exception);
    }

    // close error log
    Tools::Log(LOG_ERROR, NULL);

    return 0;
}
