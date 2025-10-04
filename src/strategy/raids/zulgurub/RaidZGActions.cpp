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
            if (unit && bot->GetExactDist2d(unit) < radius + distanceExtra)
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
