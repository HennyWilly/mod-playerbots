/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Multipliers.h"

#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "HunterActions.h"
#include "MovementActions.h"
#include "Playerbots.h"
#include "ThreatHelpers.h"

float KurinnaxxTankMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* boss = FindThreatTarget(bot, "kurinnaxx");
    if (!boss)
        return 1.0f;

    // Tanks not targeted by the boss don't run into the Cleave.
    if (boss->GetVictim() != bot && dynamic_cast<TankFaceAction*>(action))
        return 0.0f;

    // Don't taunt the boss back from the other tank while still carrying the Mortal Wound stacks.
    // Taunting it off a non-tank is still allowed.
    if (Aq20Helpers::HasSwapMortalWoundStacks(bot) && EncounterHelpers::IsTauntAction(bot, action))
    {
        Unit* victim = boss->GetVictim();
        Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
        if (victimPlayer && victimPlayer != bot && PlayerbotAI::IsTank(victimPlayer))
            return 0.0f;
    }
    return 1.0f;
}

float MoamMultiplier::GetValue(Action* action)
{
    // Prevent Serpent Sting and Scorpid String from overriding Viper String
    if (bot->getClass() == CLASS_HUNTER)
    {
        Unit* boss = FindThreatTarget(bot, "moam");
        if (boss && (
            dynamic_cast<CastSerpentStingAction*>(action) ||
            dynamic_cast<CastScorpidStingAction*>(action)
        ) && action->GetTarget() == boss)
            return 0.0f;
    }
    return 1.0f;
}
