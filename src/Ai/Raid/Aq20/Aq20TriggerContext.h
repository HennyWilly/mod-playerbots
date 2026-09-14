/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERCONTEXT_H
#define PLAYERBOTS_AQ20TRIGGERCONTEXT_H

#include "Aq20Triggers.h"
#include "BossAuraTriggers.h"
#include "NamedObjectContext.h"

class RaidAq20TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq20TriggerContext()
    {
        creators["aq20 kurinnaxx sand trap nearby"] = &RaidAq20TriggerContext::kurinnaxx_sand_trap_nearby;
        creators["aq20 kurinnaxx positioning"] = &RaidAq20TriggerContext::kurinnaxx_positioning;

        creators["aq20 ayamiss nature resistance"] = &RaidAq20TriggerContext::ayamiss_nature_resistance;
        creators["aq20 ayamiss larva found"] = &RaidAq20TriggerContext::ayamiss_larva_found;

        creators["aq20 move to crystal"] = &RaidAq20TriggerContext::move_to_crystal;
    }

private:
    static Trigger* kurinnaxx_sand_trap_nearby(PlayerbotAI* ai) { return new Aq20KurinnaxxSandTrapNearbyTrigger(ai); }
    static Trigger* kurinnaxx_positioning(PlayerbotAI* ai) { return new Aq20KurinnaxxPositioningTrigger(ai); }
    static Trigger* ayamiss_nature_resistance(PlayerbotAI* ai) { return new BossNatureResistanceTrigger(ai, "ayamiss the hunter"); }
    static Trigger* ayamiss_larva_found(PlayerbotAI* ai) { return new Aq20AyamissLarvaFoundTrigger(ai); }
    static Trigger* move_to_crystal(PlayerbotAI* ai) { return new Aq20MoveToCrystalTrigger(ai); }
};

#endif
