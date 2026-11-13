/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONCONTEXT_H
#define PLAYERBOTS_AQ20ACTIONCONTEXT_H

#include "Action.h"
#include "Aq20Actions.h"
#include "BossAuraActions.h"
#include "NamedObjectContext.h"

class RaidAq20ActionContext : public NamedObjectContext<Action>
{
public:
    RaidAq20ActionContext()
    {
        creators["aq20 kurinnaxx avoid sand trap"] = &RaidAq20ActionContext::kurinnaxx_avoid_sand_trap;
        creators["aq20 kurinnaxx avoid wide slash"] = &RaidAq20ActionContext::kurinnaxx_avoid_wide_slash;
        creators["aq20 kurinnaxx tank swap"] = &RaidAq20ActionContext::kurinnaxx_tank_swap;

        creators["aq20 moam drain mana"] = &RaidAq20ActionContext::moam_drain_mana;

        creators["aq20 ayamiss nature resistance"] = &RaidAq20ActionContext::ayamiss_nature_resistance;
        creators["aq20 ayamiss mark larva as skull"] = &RaidAq20ActionContext::ayamiss_mark_larva_as_skull;

        creators["aq20 use crystal"] = &RaidAq20ActionContext::use_crystal;
    }

private:
    static Action* kurinnaxx_avoid_sand_trap(PlayerbotAI* botAI) { return new Aq20KurinnaxxAvoidSandTrapAction(botAI); }
    static Action* kurinnaxx_avoid_wide_slash(PlayerbotAI* botAI) { return new Aq20KurinnaxxAvoidWideSlashAction(botAI); }
    static Action* kurinnaxx_tank_swap(PlayerbotAI* botAI) { return new Aq20KurinnaxxTankSwapAction(botAI); }
    static Action* moam_drain_mana(PlayerbotAI* botAI) { return new Aq20MoamDrainManaAction(botAI); }
    static Action* ayamiss_nature_resistance(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "ayamiss the hunter"); }
    static Action* ayamiss_mark_larva_as_skull(PlayerbotAI* botAI) { return new Aq20AyamissMarkLarvaAsSkullAction(botAI); }
    static Action* use_crystal(PlayerbotAI* botAI) { return new Aq20UseCrystalAction(botAI); }
};

#endif
