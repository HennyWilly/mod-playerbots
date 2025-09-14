#ifndef _PLAYERBOT_RAIDMCTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDMCTRIGGERCONTEXT_H

#include "AiObjectContext.h"
#include "NamedObjectContext.h"
#include "RaidMcTriggers.h"

class RaidMcTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidMcTriggerContext()
    {
        creators["mc lucifron shadow resistance trigger"] = &RaidMcTriggerContext::lucifron_shadow_resistance_trigger;
        creators["mc magmadar fire resistance trigger"] = &RaidMcTriggerContext::magmadar_fire_resistance_trigger;
        creators["mc baron geddon fire resistance trigger"] = &RaidMcTriggerContext::baron_geddon_fire_resistance_trigger;
        creators["mc living bomb debuff"] = &RaidMcTriggerContext::living_bomb_debuff;
        creators["mc baron geddon inferno"] = &RaidMcTriggerContext::baron_geddon_inferno;
    }

private:
    static Trigger* lucifron_shadow_resistance_trigger(PlayerbotAI* ai) { return new BossShadowResistanceTrigger(ai, "lucifron"); }
    static Trigger* magmadar_fire_resistance_trigger(PlayerbotAI* ai) { return new BossFireResistanceTrigger(ai, "magmadar"); }
    static Trigger* baron_geddon_fire_resistance_trigger(PlayerbotAI* ai) { return new BossFireResistanceTrigger(ai, "baron geddon"); }
    static Trigger* living_bomb_debuff(PlayerbotAI* ai) { return new McLivingBombDebuffTrigger(ai); }
    static Trigger* baron_geddon_inferno(PlayerbotAI* ai) { return new McBaronGeddonInfernoTrigger(ai); }
};

#endif
