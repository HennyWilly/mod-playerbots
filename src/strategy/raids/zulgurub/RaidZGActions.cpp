#include "RaidZGActions.h"

#include "Playerbots.h"
#include "RaidZGTriggers.h"

bool ZgVenoxisPhaseOneTankAttackAction::isUseful() { return PlayerbotAI::IsTank(bot); }

bool ZgVenoxisPhaseOneTankAttackAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priest venoxis");
    if (!boss)
        return false;

    // main tank → attack boss
    if (PlayerbotAI::IsMainTank(bot))
        return Attack(boss);

    // other tank(s) → only attack boss if there are no cobras left
    for (const auto& target : AI_VALUE(GuidVector, "possible targets no los"))
    {
        Unit* unit = botAI->GetUnit(target);
        if (unit && unit->GetEntry() == NPC_RAZZASHI_COBRA)
        {
            Player* targetOfCobra = botAI->GetPlayer(unit->GetTarget());
            if (targetOfCobra && !PlayerbotAI::IsAssistTank(targetOfCobra))
                return Attack(unit); // prioritize cobras not attacking assist tank(s)
        }
    }
    return false;
}

bool ZgVenoxisPhaseOnePositionAction::Execute(Event event)
{
    const Unit* boss = AI_VALUE2(Unit*, "find target", "high priest venoxis");
    if (!boss)
        return false;

    if (PlayerbotAI::IsMainTank(bot))
    {
        if (boss->GetTarget() == bot->GetGUID())
            return MoveTo(bot->GetMapId(), ZG_VENOXIS_PHASE1_TANK_POSITION.GetPositionX(),
                          ZG_VENOXIS_PHASE1_TANK_POSITION.GetPositionY(), bot->GetPositionZ(), false, false,
                          false, false, MovementPriority::MOVEMENT_COMBAT);
        return false;
    }

    if (PlayerbotAI::IsRanged(bot))
    {
        constexpr float radius = 10.0f;
        constexpr float distanceExtra = 2.0f;

        for (auto& member : AI_VALUE(GuidVector, "group members"))
        {
            if (bot->GetGUID() == member)
                continue;

            Unit* unit = botAI->GetUnit(member);
            if (unit && unit->IsAlive() && bot->GetExactDist2d(unit) < radius + distanceExtra)
                return MoveAway(unit, radius + distanceExtra - bot->GetExactDist2d(unit));
        }
    }
    return false;
}

bool ZgJeklikPhaseOnePositionAction::isUseful() { return PlayerbotAI::IsRanged(bot); }

bool ZgJeklikPhaseOnePositionAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess jeklik");
    if (!boss)
        return false;

    constexpr float sonicBoomRadius = 20.0f;
    constexpr float distanceExtra = 1.0f;

    float distanceToBoss = bot->GetExactDist2d(boss);
    if (distanceToBoss < sonicBoomRadius + distanceExtra)
    {
        bot->AttackStop();
        bot->InterruptNonMeleeSpells(false);
        return MoveAway(boss, sonicBoomRadius + distanceExtra - distanceToBoss);
    }

    return false;
}

bool ZgMarliTrollFormAttackAddsAction::isUseful() { return PlayerbotAI::IsDps(bot); }

bool ZgMarliTrollFormAttackAddsAction::Execute(Event event)
{
    // Attack living spiders. Priority: "Full Grown" >> "Growth" >> without any aura
    Unit* grownSpider = nullptr;
    Unit* mediumSpider = nullptr;
    Unit* smallSpider = nullptr;
    for (const auto& target : AI_VALUE(GuidVector, "possible targets no los"))
    {
        Unit* unit = botAI->GetUnit(target);
        if (unit && unit->GetEntry() == NPC_SPAWN_OF_MARLI)
        {
            if (unit->HasAura(SPELL_FULL_GROWN))
                grownSpider = unit;
            else if (unit->HasAura(SPELL_GROWTH))
                mediumSpider = unit;
            else
                smallSpider = unit;
        }
    }

    if (grownSpider)
        return Attack(grownSpider);
    if (mediumSpider)
        return Attack(mediumSpider);
    if (smallSpider)
        return Attack(smallSpider);
    return false;
}

bool ZgMarliTrollFormPositionAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li");
    if (!boss)
        return false;

    if (PlayerbotAI::IsMainTank(bot))
    {
        if (boss->GetTarget() == bot->GetGUID())
            return MoveTo(bot->GetMapId(), ZG_MARLI_TANK_POSITION.GetPositionX(),
                          ZG_MARLI_TANK_POSITION.GetPositionY(), bot->GetPositionZ(), false, false,
                          false, false, MovementPriority::MOVEMENT_COMBAT);
        return false;
    }

    // Out-range Poison Bolt Volley.
    if (PlayerbotAI::IsRanged(bot))
    {
        constexpr float poisonBoltVolleyRadius = 30.0f;
        constexpr float distanceExtra = 2.0f;

        float distanceToBoss = bot->GetExactDist2d(boss);
        if (distanceToBoss < poisonBoltVolleyRadius + distanceExtra)
            return MoveAway(boss, poisonBoltVolleyRadius + distanceExtra - distanceToBoss);
    }
    return false;
}

bool ZgMarliSpiderFormSetMainTankAction::isUseful() { return PlayerbotAI::IsTank(bot); }

// TODO What about real players as main tanks?
bool ZgMarliSpiderFormSetMainTankAction::Execute(Event event)
{
    Player* newMainTank = nullptr;
    if (PlayerbotAI::IsMainTank(bot) && bot->HasAura(SPELL_ENVELOPING_WEB))
    {
        for (const auto& member : AI_VALUE(GuidVector, "group members"))
        {
            Player* player = botAI->GetPlayer(member);
            if (player && player->IsAlive() && PlayerbotAI::IsTank(player, true)
                && !player->HasAura(SPELL_ENVELOPING_WEB))
            {
                newMainTank = player;
                break;
            }
        }
    }
    else if (PlayerbotAI::IsAssistTank(bot) && !bot->HasAura(SPELL_ENVELOPING_WEB))
    {
        Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li");
        if (boss && boss->GetTarget() == bot->GetGUID())
            newMainTank = bot; // In case a taunt failed.
    }

    if (!newMainTank)
        return false;

    Group* group = bot->GetGroup();
    if (!group)
        return false;

    // Unflag everyone from main tank
    for (auto& member : AI_VALUE(GuidVector, "group members"))
    {
        Player* player = botAI->GetPlayer(member);
        if (player && PlayerbotAI::IsMainTank(player))
            group->SetGroupMemberFlag(player->GetGUID(), false, MEMBER_FLAG_MAINTANK);
    }

    // Assign the single main tank
    group->SetGroupMemberFlag(newMainTank->GetGUID(), true, MEMBER_FLAG_MAINTANK);

    return true;
}

bool ZgMarliSpiderFormTankAttackAction::isUseful() { return PlayerbotAI::IsAssistTank(bot); }

// TODO Redundant now?
bool ZgMarliSpiderFormTankAttackAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li");
    if (!boss)
        return false;

    Unit* mainTank = nullptr;
    for (auto& member : AI_VALUE(GuidVector, "group members"))
    {
        Player* player = botAI->GetPlayer(member);
        if (player && player->IsAlive() && PlayerbotAI::IsMainTank(player))
        {
            mainTank = player;
            break;
        }
    }

    if (!mainTank || mainTank->HasAura(SPELL_ENVELOPING_WEB))
        return Attack(boss); // Main tank dead or webbed

    return false;
}

bool ZgMarliSpiderFormPositionAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li");
    if (!boss)
        return false;

    bool isMainTank = false;
    bool isSpareTank = false;
    if (PlayerbotAI::IsMainTank(bot))
        isMainTank = true;
    else if (PlayerbotAI::IsAssistTank(bot))
    {
        Unit* mainTank = nullptr;
        for (auto& member : AI_VALUE(GuidVector, "group members"))
        {
            Player* player = botAI->GetPlayer(member);
            if (player && player->IsAlive() && PlayerbotAI::IsMainTank(player))
            {
                mainTank = player;
                break;
            }
        }

        if (!mainTank || mainTank->HasAura(SPELL_ENVELOPING_WEB))
            isMainTank = true; // While the main tank is webbed, we are the new main tank.
        else
            isSpareTank = true;
    }

    if (isMainTank)
    {
        if (boss->GetTarget() == bot->GetGUID())
            return MoveTo(bot->GetMapId(), ZG_MARLI_TANK_POSITION.GetPositionX(),
                          ZG_MARLI_TANK_POSITION.GetPositionY(), bot->GetPositionZ(), false, false,
                          false, false, MovementPriority::MOVEMENT_COMBAT);
        return false;
    }

    constexpr float envelopingWebsRadius = 10.0f;
    constexpr float distanceExtra = 2.0f;

    if (isSpareTank)
    {
        Unit* closestRanged = nullptr;
        for (auto& member : AI_VALUE(GuidVector, "group members"))
        {
            Player* player = botAI->GetPlayer(member);
            if (player && player->IsAlive() && PlayerbotAI::IsRanged(player))
            {
                if (player->GetExactDist2d(boss) < envelopingWebsRadius + distanceExtra)
                    continue;
                if (!closestRanged || bot->GetExactDist2d(player) < bot->GetExactDist2d(closestRanged))
                    closestRanged = player;
            }
        }

        if (closestRanged)
            return MoveTo(bot->GetMapId(), closestRanged->GetPositionX(), closestRanged->GetPositionY(),
                          bot->GetPositionZ(), false, false, false, false,
                          MovementPriority::MOVEMENT_COMBAT);
        // If no closest ranged bot found, just move away.
    }

    // Out-range Enveloping Webs.
    if (PlayerbotAI::IsRanged(bot) || isSpareTank)
    {
        // Prevent bot from running away from boss if attacked.
        if (boss->GetTarget() != bot->GetGUID())
        {
            float distanceToBoss = bot->GetExactDist2d(boss);
            if (distanceToBoss < envelopingWebsRadius + distanceExtra)
                return MoveAway(boss, envelopingWebsRadius + distanceExtra - distanceToBoss);
        }
    }
    return false;
}
