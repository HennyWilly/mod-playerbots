/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Actions.h"

#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "ThreatHelpers.h"

using namespace Aq20Helpers;
using namespace EncounterHelpers;

bool Aq20KurinnaxxAvoidSandTrapAction::Execute(Event /*event*/)
{
    if (GameObject* sandTrap = GetNearestSandTrap(bot))
    {
        // Stop channeling spell first
        bot->AttackStop();
        bot->CastStop();

        return MoveAway(sandTrap, KURINNAXX_SAND_TRAP_DISTANCE);
    }
    return false;
}

// TODO Works but copy of BwlRazorgoreAvoidAoeAction::Execute...
bool Aq20KurinnaxxAvoidWideSlashAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatTarget(bot, "kurinnaxx");
    if (!boss)
        return false;

    // The current target should not move.
    // Also prevents non-tanks from rotating the boss if they have aggro.
    if (boss->GetVictim() == bot)
        return false;

    float distance = bot->GetDistance2d(boss);

    // Bot is too close and standing in Kurinnaxx' frontal cone
    if (distance <= 10.0f && boss->HasInArc(M_PI_2, bot))
    {
        // Target position: directly behind the boss with a small random fuzz
        // to prevent all bots stacking on the same spot
        float moveAngle = boss->GetOrientation() + M_PI + frand(-M_PI_4, M_PI_4);
        float kurinnaxxRadius = PlayerbotAI::IsRanged(bot) ? 15.0f : 3.0f;

        float targetMoveX = boss->GetPositionX() + kurinnaxxRadius * cos(moveAngle);
        float targetMoveY = boss->GetPositionY() + kurinnaxxRadius * sin(moveAngle);

        // Move incrementally toward the target. Allows course correction.
        float dX = targetMoveX - bot->GetPositionX();
        float dY = targetMoveY - bot->GetPositionY();
        float dist = sqrt(dX * dX + dY * dY);
        if (dist == 0.0f)
            dist = 0.1f;

        float moveX = bot->GetPositionX() + (dX / dist) * 3.0f;
        float moveY = bot->GetPositionY() + (dY / dist) * 3.0f;

        return MoveTo(boss->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false,
                      false, false, MovementPriority::MOVEMENT_COMBAT, true);
    }

    return false;
}

bool Aq20KurinnaxxTankSwapAction::Execute(Event event)
{
    Unit* boss = FindThreatTarget(bot, "kurinnaxx");
    if (!boss || boss->GetVictim() == bot)
        return false;

    // "taunt spell" casts on the current target.
    if (AI_VALUE(Unit*, "current target") != boss)
        return Attack(boss);

    return botAI->DoSpecificAction("taunt spell", event, true);
}

bool Aq20RajaxxPullWaveFromAndorovAction::Execute(Event /*event*/)
{
    // Wave mobs attack Andorov without engaging the raid, so they never appear among the bots' attackers.
    // Once the tank is on their threat list, the generic tank and dps logic takes over.
    return Attack(FindCloseAndorovAttacker(bot));
}

bool Aq20MoamDrainManaAction::Execute(Event /*event*/)
{
    uint8 botClass = bot->getClass();
    if (botClass == CLASS_HUNTER || botClass == CLASS_WARLOCK || botClass == CLASS_PRIEST)
    {
        Unit* boss = FindThreatTarget(bot, "moam");
        if (boss && boss->IsAlive())
        {
            if (botClass == CLASS_HUNTER)
                return botAI->CastSpell(static_cast<uint32>(Aq20Spells::SPELL_HUNTER_VIPER_STING), boss);

            if (botClass == CLASS_PRIEST)
                return botAI->CastSpell("mana burn", boss);

            return botAI->CastSpell(static_cast<uint32>(Aq20Spells::SPELL_WARLOCK_DRAIN_MANA), boss);
        }
    }
    return false;
}

bool Aq20MoamAvoidTrampleAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatTarget(bot, "moam");
    if (!boss)
        return false;

    float const distance = MOAM_TRAMPLE_SAFE_DISTANCE - bot->GetDistance(boss);
    return MoveAway(boss, distance);
}

bool Aq20AyamissMarkLarvaAsSkullAction::Execute(Event /*event*/)
{
    Unit* larva = FindHiveZaraLarva(botAI);
    return larva && MarkTargetWithSkull(bot, larva);
}

bool Aq20UseCrystalAction::Execute(Event /*event*/)
{
    if (Unit* boss = FindThreatTarget(bot, "ossirian the unscarred"))
    {
        if (GameObject* crystal = GetNearestCrystal(boss))
        {
            float botDist = bot->GetDistance(crystal);
            if (botDist > INTERACTION_DISTANCE)
                return MoveTo(bot->GetMapId(),
                    crystal->GetPositionX() + frand(-3.5f, 3.5f),
                    crystal->GetPositionY() + frand(-3.5f, 3.5f),
                    crystal->GetPositionZ());

            // if we're already in range just wait here until it's time to activate crystal
            SetNextMovementDelay(500);

            // don't activate crystal if boss too far or its already been activated
            if (boss->GetDistance(crystal) > 25.0f ||
                crystal->HasGameObjectFlag(GO_FLAG_IN_USE))
                return false;

            // don't activate crystal if boss doesn't have buff yet AND isn't going to have it soon
            // (though ideally bot should activate it ~5 seconds early due to time it takes for
            // crystal to activate and remove buff)
            if (!IsOssirianBuffActive(boss) && GetOssirianDebuffTimeRemaining(boss) > 5000)
                return false;

            // this makes crystal do its animation (then disappear after)
            WorldPacket data1(CMSG_GAMEOBJ_USE);
            data1 << crystal->GetGUID();
            bot->GetSession()->HandleGameObjectUseOpcode(data1);

            // this makes crystal actually remove the buff and put on debuff (took a while to figure that out)
            WorldPacket data2(CMSG_GAMEOBJ_USE);
            data2 << crystal->GetGUID();
            bot->GetSession()->HandleGameobjectReportUse(data2);

            return true;
        }
    }
    return false;
}
