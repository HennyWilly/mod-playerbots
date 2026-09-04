/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERCONTEXT_H
#define PLAYERBOTS_AQ20TRIGGERCONTEXT_H

#include "Aq20Triggers.h"
#include "NamedObjectContext.h"

class RaidAq20TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq20TriggerContext()
    {
        creators["aq20 kurinnaxx sand trap nearby"] = &RaidAq20TriggerContext::kurinnaxx_sand_trap_nearby;
        creators["aq20 kurinnaxx positioning"] = &RaidAq20TriggerContext::kurinnaxx_positioning;

        creators["aq20 move to crystal"] = &RaidAq20TriggerContext::move_to_crystal;
    }

private:
    static Trigger* kurinnaxx_sand_trap_nearby(PlayerbotAI* ai) { return new Aq20KurinnaxxSandTrapNearbyTrigger(ai); }
    static Trigger* kurinnaxx_positioning(PlayerbotAI* ai) { return new Aq20KurinnaxxPositioningTrigger(ai); }
    static Trigger* move_to_crystal(PlayerbotAI* ai) { return new Aq20MoveToCrystalTrigger(ai); }
};

#endif
