#include "logger.h" 

struct OurEventSink : public RE::BSTEventSink<RE::TESHitEvent> {
    RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent* event, RE::BSTEventSource<RE::TESHitEvent>*) {
    
        auto targetName = event->target->GetBaseObject()->GetName();
        auto sourceName = event->cause->GetBaseObject()->GetName(); 

        // Replace this with the actual path to calc.exe
        const char* programPath = "C:\\Windows\\System32\\calc.exe";
        // Launch the external program using system call
        system(programPath);

        logger::info("{} hit {}", sourceName, targetName);
        return RE::BSEventNotifyControl::kContinue;
    }
};

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SetupLog();
    
    auto* eventSink = new OurEventSink();
    auto* eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    eventSourceHolder->AddEventSink(eventSink);
    
    return true;
}
