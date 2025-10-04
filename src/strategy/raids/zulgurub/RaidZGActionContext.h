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

        creators["zg mar'li troll form attack adds"] = &RaidZGActionContext::marli_troll_form_attack_adds;
        creators["zg mar'li troll form position"] = &RaidZGActionContext::marli_troll_form_position;
        creators["zg mar'li spider form set main tank"] = &RaidZGActionContext::marli_spider_form_set_main_tank;
        creators["zg mar'li spider form tank attack"] = &RaidZGActionContext::marli_spider_form_tank_attack;
        creators["zg mar'li spider form position"] = &RaidZGActionContext::marli_spider_form_position;
    }

private:
    static Action* venoxis_phase_one_tank_attack(PlayerbotAI* ai) { return new ZgVenoxisPhaseOneTankAttackAction(ai); }
    static Action* venoxis_phase_one_position(PlayerbotAI* ai) { return new ZgVenoxisPhaseOnePositionAction(ai); }
    static Action* jeklik_phase_one_position(PlayerbotAI* ai) { return new ZgJeklikPhaseOnePositionAction(ai); }
    static Action* marli_troll_form_attack_adds(PlayerbotAI* ai) { return new ZgMarliTrollFormAttackAddsAction(ai); }
    static Action* marli_troll_form_position(PlayerbotAI* ai) { return new ZgMarliTrollFormPositionAction(ai); }
    static Action* marli_spider_form_set_main_tank(PlayerbotAI* ai) { return new ZgMarliSpiderFormSetMainTankAction(ai); }
    static Action* marli_spider_form_tank_attack(PlayerbotAI* ai) { return new ZgMarliSpiderFormTankAttackAction(ai); }
    static Action* marli_spider_form_position(PlayerbotAI* ai) { return new ZgMarliSpiderFormPositionAction(ai); }
};

#endif
