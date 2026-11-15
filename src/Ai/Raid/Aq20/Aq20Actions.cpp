/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Actions.h"

#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
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

bool Aq20BuruKiteToEggAction::Execute(Event /*event*/)
{
    Unit* buru = FindUntransformedBuru(bot);
    if (!buru)
        return false;

    // Keep circling the marked egg while Buru is in reach of its explosion, until it dies.
    Creature* egg = GetMarkedEgg(bot);
    if (!egg || buru->GetExactDist2d(egg) > BURU_EGG_EXPLOSION_RADIUS ||
        bot->GetExactDist2d(egg) > BURU_EGG_STAY_DISTANCE)
        egg = FindKiteEgg(bot, buru);

    if (!egg)
    {
        // No egg left until they respawn; keep away from Buru.
        return bot->GetDistance(buru) < BURU_FLEE_DISTANCE && KiteAroundRoom(buru);
    }

    // Wait behind the egg as seen from Buru, so he passes it before he reaches the bot.
    float dirX = egg->GetPositionX() - buru->GetPositionX();
    float dirY = egg->GetPositionY() - buru->GetPositionY();
    if (std::sqrt(dirX * dirX + dirY * dirY) < 1.0f)
    {
        dirX = bot->GetPositionX() - egg->GetPositionX();
        dirY = bot->GetPositionY() - egg->GetPositionY();
    }
    float const baseAngle = std::atan2(dirY, dirX);
    bool const buruClose = bot->GetDistance(buru) < BURU_EGG_WAIT_DISTANCE;

    // If the spot behind the egg can't be reached (e.g. a wall), try spots further around it.
    for (float const offset : { 0.0f, float(M_PI_2), -float(M_PI_2), float(M_PI_4) * 3.0f, -float(M_PI_4) * 3.0f })
    {
        float const x = egg->GetPositionX() + std::cos(baseAngle + offset) * BURU_EGG_WAIT_DISTANCE;
        float const y = egg->GetPositionY() + std::sin(baseAngle + offset) * BURU_EGG_WAIT_DISTANCE;
        if (bot->GetExactDist2d(x, y) <= 1.5f)
        {
            if (!buruClose)
                return false;

            continue;
        }

        bot->CastStop();
        if (MoveTo(bot->GetMapId(), x, y, egg->GetPositionZ(), false, false, false, false,
                   MovementPriority::MOVEMENT_COMBAT))
            return true;
    }

    // Never stand still while Buru is on the bot.
    return buruClose && KiteAroundRoom(buru);
}

// Run from egg spawn to egg spawn around the room, so the bot neither runs past Buru nor up the walls.
bool Aq20BuruKiteToEggAction::KiteAroundRoom(Unit* buru)
{
    size_t const count = BURU_KITE_ROUTE.size();
    size_t nearest = 0;
    for (size_t i = 1; i < count; ++i)
    {
        if (bot->GetExactDist2d(BURU_KITE_ROUTE[i]) < bot->GetExactDist2d(BURU_KITE_ROUTE[nearest]))
            nearest = i;
    }

    // Head on to the neighbouring spawn that is further from Buru.
    Position const& next = BURU_KITE_ROUTE[(nearest + 1) % count];
    Position const& previous = BURU_KITE_ROUTE[(nearest + count - 1) % count];
    bool const nextAhead = buru->GetExactDist2d(next) > buru->GetExactDist2d(previous);

    bot->CastStop();
    for (Position const* spot : { nextAhead ? &next : &previous, nextAhead ? &previous : &next })
    {
        if (MoveTo(bot->GetMapId(), spot->GetPositionX(), spot->GetPositionY(), spot->GetPositionZ(), false,
                   false, false, false, MovementPriority::MOVEMENT_COMBAT))
            return true;
    }

    return MoveAway(buru, BURU_FLEE_DISTANCE);
}

bool Aq20BuruMarkEggAsSkullAction::Execute(Event /*event*/)
{
    Creature* egg = FindEggToMark(bot);
    return egg && MarkTargetWithSkull(bot, egg);
}

bool Aq20BuruClearEggMarkAction::Execute(Event /*event*/)
{
    return ClearStrategyTargetIcon(bot, RtiTargetValue::skullIndex, { static_cast<uint32>(Aq20NPCs::NPC_BURU_EGG) });
}

bool Aq20BuruRecallPetAction::Execute(Event /*event*/)
{
    // Killing an egg out of Buru's reach wastes it and makes him change targets.
    if (!FindPetOnWrongEgg(bot))
        return false;

    CallBackPets(bot);
    return true;
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
