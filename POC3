#include "logger.h"

struct OurEventSink : public RE::BSTEventSink<RE::TESActivateEvent> {
    
    RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent* event,
                                          RE::BSTEventSource<RE::TESActivateEvent>*) {
        auto activatedName = event->objectActivated->GetBaseObject()->GetName();
        auto activatorName = event->actionRef->GetBaseObject()->GetName();
        auto activatedformID = event->objectActivated->GetBaseObject()->formID;

        // logger::info("{} activated {}", activatorName, activatedName);
        logger::info("{} activated {} baseid: {}", activatorName, activatedName, activatedformID);

        // After getting the ID from above, we add condition statement, exectuing calc only when beacon is picked up.
        // Check if the player activated the Beacon item
        if (activatedformID == 320742) {
            // The player picked up the Beacon, add your code here.

            logger::info("Player picked up the Beacon!");

            // Replace this with the actual path to calc.exe
            const char* programPath = "C:\\Windows\\System32\\calc.exe";
            // Launch the external program using system call
            system(programPath);
        }

        return RE::BSEventNotifyControl::kContinue;
    }
};

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();

    // ScriptSource
    auto* eventSink = new OurEventSink();
    auto* eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    eventSourceHolder->AddEventSink<RE::TESActivateEvent>(eventSink);

    return true;
}
