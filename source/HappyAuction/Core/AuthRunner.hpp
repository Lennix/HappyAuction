#pragma once
#include <HappyAuction/Core/ScriptRunner.hpp>
#include <Core/System/Thread.hpp>
#include <Core/System/System.hpp>
#include <WinHttpClient/Common/Include/WinHttpClient.h>

namespace HappyAuction
{
    /**/
    class AuthRunner:
        public Thread
    {
    private:
        ScriptRunner _runner;
        Bool running;

    public:
        /**/
        AuthRunner():
          running(true)
        {
        }

        /**/
        Bool IsActive() const
        {
            return _runner.IsActive();
        }

        /**/
        void Run()
        {
            Bool error = false;
            _runner.Start();
            running = true;
            while (running && !error)
            {
                if (CheckAuth())
                    Thread::Sleep(60000);
                else
                    error = true;
            }
            _runner.Stop();
//            if (error)
//                System::Message("Session expired");
        }

        /**/
        void Stop()
        {
            _runner.Stop();
            running = false;
            //Thread::Wait();
        }

        Bool CheckAuth()
        {
            return true;
            TextString sessionid;
            TextString path;
            GetCurrentDirectory(sizeof(path), path);
            strcat(path, "\\Profiles.ini");
            GetPrivateProfileString("main", "sessionid", "", sessionid, sizeof(sessionid), path);
            // Set URL.
            WinHttpClient client(L"http://d3ahbot.com/index.php?component=backend&action=checkSession");
 
            // Set post data.
            string data = "sid=";
            data.append(sessionid);
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

            int pos = 0;
            wstring httpResponseContent = client.GetResponseContent();
            pos = httpResponseContent.find(L"success");
            if (pos > 0)
                return true;
            else
                return false;
        }
    };
}
