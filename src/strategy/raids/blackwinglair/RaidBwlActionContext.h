#ifndef _PLAYERBOT_RAIDBWLACTIONCONTEXT_H
#define _PLAYERBOT_RAIDBWLACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidBwlActions.h"

class RaidBwlActionContext : public NamedObjectContext<Action>
{
public:
    RaidBwlActionContext()
    {
        creators["bwl razorgore fire resistance"] = &RaidBwlActionContext::razorgore_fire_resistance;
        creators["bwl razorgore mark boss skull"] = &RaidBwlActionContext::razorgore_mark_boss_skull;
        creators["bwl check onyxia scale cloak"] = &RaidBwlActionContext::check_onyxia_scale_cloak;
        creators["bwl turn off suppression device"] = &RaidBwlActionContext::turn_off_suppression_device;
        creators["bwl use hourglass sand"] = &RaidBwlActionContext::use_hourglass_sand;
    }

private:
    static Action* razorgore_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "razorgore the untamed"); }
    static Action* razorgore_mark_boss_skull(PlayerbotAI* botAI) { return new BwlRazorgoreMarkBossSkullAction(botAI); }
    static Action* check_onyxia_scale_cloak(PlayerbotAI* botAI) { return new BwlOnyxiaScaleCloakAuraCheckAction(botAI); }
    static Action* turn_off_suppression_device(PlayerbotAI* botAI) { return new BwlTurnOffSuppressionDeviceAction(botAI); }
    static Action* use_hourglass_sand(PlayerbotAI* botAI) { return new BwlUseHourglassSandAction(botAI); }
};

#endif
