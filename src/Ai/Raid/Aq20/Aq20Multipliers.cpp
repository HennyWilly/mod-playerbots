/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Multipliers.h"

#include "Aq20Actions.h"
#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "HunterActions.h"
#include "MovementActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"
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

float BuruMultiplier::GetValue(Action* action)
{
    bool const isCooldown = EncounterHelpers::IsDpsCooldownAction(bot, action);
    // Charge, Intercept and Feral Charge are reach spells, not movement actions.
    bool const isOtherMovement = (dynamic_cast<MovementAction*>(action) &&
        !dynamic_cast<Aq20BuruKiteToEggAction*>(action)) || dynamic_cast<CastReachTargetSpellAction*>(action);
    if (!isCooldown && !isOtherMovement)
        return 1.0f;

    Unit* buru = Aq20Helpers::FindUntransformedBuru(bot); // Buru phase 1
    if (!buru)
        return 1.0f;

    // Save cooldowns for the burn after the transformation.
    if (isCooldown)
        return 0.0f;

    // The fixated bot waits at the egg it kites Buru to.
    return buru->GetVictim() == bot ? 0.0f : 1.0f;
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
