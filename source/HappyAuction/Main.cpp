#include <Core/Tools.hpp>
#include <HappyAuction/Core/Application.hpp>
#include <HappyAuction/Core/Script.hpp>
#include <time.h>

/**/
int WINAPI WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance, 
    LPSTR       lpCmdLine,
    int         iCmdShow)
{
    using namespace Core;
    using namespace Diablo;

    try
    {
        HappyAuction::Application().Run();
    }
    catch(const Char* exception)
    {
        System::Message(false, exception);
    }

    // close error log
    Tools::Log(LOG_ERROR, NULL);

    return 0;
}
