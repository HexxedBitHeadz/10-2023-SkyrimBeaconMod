#include "logger.h"

struct OurEventSink : public RE::BSTEventSink<RE::TESActivateEvent> {
    RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent* event,
                                          RE::BSTEventSource<RE::TESActivateEvent>*) {
        auto activatedName = event->objectActivated->GetBaseObject()->GetName();
        auto activatorName = event->actionRef->GetBaseObject()->GetName();
        auto activatedformID = event->objectActivated->GetBaseObject()->formID;

        // logger::info("{} activated {}", activatorName, activatedName);
        logger::info("{} activated {} baseid: {}", activatorName, activatedName, activatedformID);

        return RE::BSEventNotifyControl::kContinue;
    }
};


SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();

    auto* eventSink = new OurEventSink();
    auto* eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    eventSourceHolder->AddEventSink<RE::TESActivateEvent>(eventSink);
    return true;
}
