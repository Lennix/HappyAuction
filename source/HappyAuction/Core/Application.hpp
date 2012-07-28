#pragma once
#include <HappyAuction/Constants.hpp>
#include <HappyAuction/Core/ScriptRunner.hpp>
#include <HappyAuction/Resource/resource.h>
#include <Core/System/System.hpp>
#include <WinHttpClient/Common/Include/WinHttpClient.h>

namespace HappyAuction
{
    /**/
    class Application
    {
    private:
        ScriptRunner _runner;

    public:
        /**/
        void Run()
        {
            // Set URL.
            WinHttpClient client(L"http://d3ahbot.com/index.php?component=backend&action=login");
 
            // Set post data.
            string data = "username=lennix&password=fa79010cf00be721e94e8d804c490f9b0658d5c7f69c0337dbdb4248dcfa3c9f";
            client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());
 
            // Set request headers.
            wchar_t szSize[50] = L"";
            swprintf_s(szSize, L"%d", data.size());
            wstring headers = L"Content-Length: ";
            headers += szSize;
            headers += L"\r\nContent-Type: application/x-www-form-urlencoded\r\n";
            client.SetAdditionalRequestHeaders(headers);
 
            // Send HTTP post request.
            client.SendHttpRequest(L"POST");
 
            wstring httpResponseHeader = client.GetResponseHeader();
            wstring httpResponseContent = client.GetResponseContent();

            // init system
            if(!_InitSystem())
                throw EXCEPTION_FATAL;

            // init application
            if(!_InitApplication())
                throw EXCEPTION_FATAL;

            // run system
            if(!System::Run())
                throw EXCEPTION_FATAL;

            // stop bot
            _runner.Stop();
        }

        /**/
        void ToggleBot()
        {
            if(_runner.IsActive())
                _runner.Stop();
            else
                _runner.Start();
        }

    private:
        /**/
        Bool _InitApplication()
        {
            return System::SetHotKey(MOD_CONTROL, VK_F12, _OnHotKey, this);
        }

        /**/
        Bool _InitSystem()
        {
            // init system
            System::SetStatusIcon(System::STATUS_IDLE, IDI_ICON_IDLE);
            System::SetStatusIcon(System::STATUS_ACTIVE, IDI_ICON_ACTIVE);

            // init system
            return System::Initialize(APPLICATION_NAME);
        }

        /**/
        static void _OnHotKey( void* custom )
        {
            Application& app = *reinterpret_cast<Application*>(custom);
            app.ToggleBot();
        }
    };
}
