#ifndef _PLAYERBOT_RAIDBWLTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDBWLTRIGGERCONTEXT_H

#include "AiObjectContext.h"
#include "NamedObjectContext.h"
#include "RaidBwlTriggers.h"

class RaidBwlTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidBwlTriggerContext()
    {
        // Common
        creators["bwl suppression device"] = &RaidBwlTriggerContext::suppression_device;

        // Razorgore
        creators["bwl razorgore fire resistance"] = &RaidBwlTriggerContext::razorgore_fire_resistance;
        creators["bwl razorgore phase 2 mark target"] = &RaidBwlTriggerContext::razorgore_phase_2_mark_target;

        // Chromaggus
        creators["bwl affliction bronze"] = &RaidBwlTriggerContext::affliction_bronze;
    }

private:
    static Trigger* razorgore_fire_resistance(PlayerbotAI* botAI) { return new BwlRazorgoreP2FireResistanceTrigger(botAI); }
    static Trigger* razorgore_phase_2_mark_target(PlayerbotAI* botAI) { return new BwlRazorgoreP2TriggerMarkTarget(botAI); }
    static Trigger* suppression_device(PlayerbotAI* botAI) { return new BwlSuppressionDeviceTrigger(botAI); }
    static Trigger* affliction_bronze(PlayerbotAI* botAI) { return new BwlAfflictionBronzeTrigger(botAI); }
};

#endif
