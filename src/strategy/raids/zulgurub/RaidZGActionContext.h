#ifndef _PLAYERBOT_RAIDZGACTIONCONTEXT_H
#define _PLAYERBOT_RAIDZGACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidZGActions.h"

class RaidZGActionContext : public NamedObjectContext<Action>
{
public:
    RaidZGActionContext()
    {
        creators["zg venoxis phase one tank attack"] = &RaidZGActionContext::venoxis_phase_one_tank_attack;
        creators["zg venoxis phase one position"] = &RaidZGActionContext::venoxis_phase_one_position;

        creators["zg jeklik phase one position"] = &RaidZGActionContext::jeklik_phase_one_position;
    }

private:
    static Action* venoxis_phase_one_tank_attack(PlayerbotAI* ai) { return new ZgVenoxisPhaseOneTankAttackAction(ai); }
    static Action* venoxis_phase_one_position(PlayerbotAI* ai) { return new ZgVenoxisPhaseOnePositionAction(ai); }
    static Action* jeklik_phase_one_position(PlayerbotAI* ai) { return new ZgJeklikPhaseOnePositionAction(ai); }
};

#endif
