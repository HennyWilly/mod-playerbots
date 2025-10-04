#ifndef _PLAYERBOT_RAIDZGTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDZGTRIGGERCONTEXT_H

#include "AiObjectContext.h"
#include "NamedObjectContext.h"
#include "RaidZGTriggers.h"

class RaidZGTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidZGTriggerContext()
    {
        creators["zg venoxis phase one"] = &RaidZGTriggerContext::venoxis_phase_one;
        creators["zg jeklik phase one"] = &RaidZGTriggerContext::jeklik_phase_one;
    }

private:
    static Trigger* venoxis_phase_one(PlayerbotAI* ai) { return new ZgVenoxisPhaseOneTrigger(ai); }
    static Trigger* jeklik_phase_one(PlayerbotAI* ai) { return new ZgJeklikPhaseOneTrigger(ai); }
};

#endif
