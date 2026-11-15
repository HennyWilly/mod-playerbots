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

        creators["aq20 rajaxx pull wave from andorov"] = &RaidAq20ActionContext::rajaxx_pull_wave_from_andorov;

        creators["aq20 buru kite to egg"] = &RaidAq20ActionContext::buru_kite_to_egg;
        creators["aq20 buru mark egg as skull"] = &RaidAq20ActionContext::buru_mark_egg_as_skull;
        creators["aq20 buru clear egg mark"] = &RaidAq20ActionContext::buru_clear_egg_mark;
        creators["aq20 buru recall pet"] = &RaidAq20ActionContext::buru_recall_pet;
        creators["aq20 buru nature resistance"] = &RaidAq20ActionContext::buru_nature_resistance;

        creators["aq20 moam drain mana"] = &RaidAq20ActionContext::moam_drain_mana;
        creators["aq20 moam avoid trample"] = &RaidAq20ActionContext::moam_avoid_trample;

        creators["aq20 ayamiss nature resistance"] = &RaidAq20ActionContext::ayamiss_nature_resistance;
        creators["aq20 ayamiss mark larva as skull"] = &RaidAq20ActionContext::ayamiss_mark_larva_as_skull;

        creators["aq20 use crystal"] = &RaidAq20ActionContext::use_crystal;
    }

private:
    static Action* kurinnaxx_avoid_sand_trap(PlayerbotAI* botAI) { return new Aq20KurinnaxxAvoidSandTrapAction(botAI); }
    static Action* kurinnaxx_avoid_wide_slash(PlayerbotAI* botAI) { return new Aq20KurinnaxxAvoidWideSlashAction(botAI); }
    static Action* kurinnaxx_tank_swap(PlayerbotAI* botAI) { return new Aq20KurinnaxxTankSwapAction(botAI); }
    static Action* rajaxx_pull_wave_from_andorov(PlayerbotAI* botAI) { return new Aq20RajaxxPullWaveFromAndorovAction(botAI); }
    static Action* buru_kite_to_egg(PlayerbotAI* botAI) { return new Aq20BuruKiteToEggAction(botAI); }
    static Action* buru_mark_egg_as_skull(PlayerbotAI* botAI) { return new Aq20BuruMarkEggAsSkullAction(botAI); }
    static Action* buru_clear_egg_mark(PlayerbotAI* botAI) { return new Aq20BuruClearEggMarkAction(botAI); }
    static Action* buru_recall_pet(PlayerbotAI* botAI) { return new Aq20BuruRecallPetAction(botAI); }
    static Action* buru_nature_resistance(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "buru the gorger"); }
    static Action* moam_drain_mana(PlayerbotAI* botAI) { return new Aq20MoamDrainManaAction(botAI); }
    static Action* moam_avoid_trample(PlayerbotAI* botAI) { return new Aq20MoamAvoidTrampleAction(botAI); }
    static Action* ayamiss_nature_resistance(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "ayamiss the hunter"); }
    static Action* ayamiss_mark_larva_as_skull(PlayerbotAI* botAI) { return new Aq20AyamissMarkLarvaAsSkullAction(botAI); }
    static Action* use_crystal(PlayerbotAI* botAI) { return new Aq20UseCrystalAction(botAI); }
};

#endif
