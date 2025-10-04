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
        // creators["mc living bomb debuff"] = &RaidZGTriggerContext::living_bomb_debuff;
    }

private:
    // static Trigger* living_bomb_debuff(PlayerbotAI* ai) { return new McLivingBombDebuffTrigger(ai); }
};

#endif
