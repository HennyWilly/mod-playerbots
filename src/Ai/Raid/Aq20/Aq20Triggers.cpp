/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Triggers.h"

#include "Aq20Helpers.h"
#include "Playerbots.h"
#include "ThreatHelpers.h"

using namespace Aq20Helpers;

bool Aq20KurinnaxxSandTrapNearbyTrigger::IsActive()
{
    if (!FindThreatTarget(bot, "kurinnaxx"))
        return false;
    return GetNearestSandTrap(bot);
}

bool Aq20KurinnaxxPositioningTrigger::IsActive()
{
    // Prevent non-tanks from rotating the boss.
    if (Unit* boss = FindThreatTarget(bot, "kurinnaxx"))
        return boss->GetVictim() != bot;
    return false;
}

bool Aq20KurinnaxxTankMortalWoundTrigger::IsActive()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = FindThreatTarget(bot, "kurinnaxx");
    if (!boss)
        return false;

    Unit* victim = boss->GetVictim();
    if (!victim || victim == bot)
        return false;

    return HasSwapMortalWoundStacks(victim) && !HasSwapMortalWoundStacks(bot);
}

bool Aq20RajaxxWaveOnAndorovTrigger::IsActive()
{
    return PlayerbotAI::IsTank(bot) && FindCloseAndorovAttacker(bot);
}

bool Aq20MoamCanDrainManaTrigger::IsActive()
{
    uint8 botClass = bot->getClass();
    if (botClass == CLASS_HUNTER || botClass == CLASS_WARLOCK || botClass == CLASS_PRIEST)
    {
        Unit* boss = FindThreatTarget(bot, "moam");
        // Skip during the stone phase => killing the Mana Fiends takes priority
        if (boss && boss->IsAlive() && boss->GetPower(POWER_MANA) > 0 && !IsMoamStonePhase(boss))
        {
            if (botClass == CLASS_HUNTER)
                return !boss->HasAura(static_cast<uint32>(Aq20Spells::SPELL_HUNTER_VIPER_STING), bot->GetGUID()) &&
                    botAI->CanCastSpell(static_cast<uint32>(Aq20Spells::SPELL_HUNTER_VIPER_STING), boss);

            // Healers keep their mana for healing.
            if (botClass == CLASS_PRIEST)
                return !PlayerbotAI::IsHeal(bot) && botAI->CanCastSpell("mana burn", boss);

            return !boss->HasAura(static_cast<uint32>(Aq20Spells::SPELL_WARLOCK_DRAIN_MANA), bot->GetGUID()) &&
                botAI->CanCastSpell(static_cast<uint32>(Aq20Spells::SPELL_WARLOCK_DRAIN_MANA), boss);
        }
    }
    return false;
}

bool Aq20MoamRangedInTrampleRangeTrigger::IsActive()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* boss = FindThreatTarget(bot, "moam");
    return boss && boss->IsAlive() &&
        boss->GetVictim() != bot && // The current target would only drag the boss along.
        bot->IsWithinDistInMap(boss, MOAM_TRAMPLE_SAFE_DISTANCE);
}

bool Aq20AyamissLarvaFoundTrigger::IsActive()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0))
        return false;

    if (!FindThreatTarget(bot, "ayamiss the hunter"))
        return false;

    return FindHiveZaraLarva(botAI) != nullptr;
}

bool Aq20MoveToCrystalTrigger::IsActive()
{
    if (Unit* boss = FindThreatTarget(bot, "ossirian the unscarred"))
    {
        if (boss->IsInCombat())
        {
            // if buff is active move to crystal
            if (IsOssirianBuffActive(boss))
                return true;

            // if buff is not active a debuff will be, buff becomes active once debuff expires
            // so move to crystal when debuff almost done, or based debuff time left and
            // distance bot is from crystal (ie: start moving early enough to make it)
            int32 debuffTimeRemaining = GetOssirianDebuffTimeRemaining(boss);
            if (debuffTimeRemaining < 5000)
                return true;
            if (debuffTimeRemaining < 30000)
            {
                if (GameObject* crystal = GetNearestCrystal(boss))
                {
                    float botDist = bot->GetDistance(crystal);
                    float timeToReach = botDist / bot->GetSpeed(MOVE_RUN);
                    // bot should ideally activate crystal a ~5 seconds early (due to time it takes for crystal
                    // to activate) so aim to get there in time to do so
                    return debuffTimeRemaining - 5 * IN_MILLISECONDS < timeToReach * IN_MILLISECONDS;
                }
            }
        }
    }
    return false;
}
