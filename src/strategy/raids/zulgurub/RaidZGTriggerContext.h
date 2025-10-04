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
        creators["zg mar'li troll form"] = &RaidZGTriggerContext::marli_troll_form;
        creators["zg mar'li spider form"] = &RaidZGTriggerContext::marli_spider_form;
    }

private:
    static Trigger* venoxis_phase_one(PlayerbotAI* ai) { return new ZgVenoxisPhaseOneTrigger(ai); }
    static Trigger* jeklik_phase_one(PlayerbotAI* ai) { return new ZgJeklikPhaseOneTrigger(ai); }
    static Trigger* marli_troll_form(PlayerbotAI* ai) { return new ZgMarliTrollFormTrigger(ai); }
    static Trigger* marli_spider_form(PlayerbotAI* ai) { return new ZgMarliSpiderFormTrigger(ai); }
};

#endif
