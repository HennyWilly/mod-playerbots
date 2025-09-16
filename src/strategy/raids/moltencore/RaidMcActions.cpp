#include "RaidMcActions.h"

#include "Playerbots.h"
#include "RaidMcTriggers.h"

bool McAttackHighestHealthCoreHoundAction::Execute(Event event)
{
    if (!AI_VALUE2(Unit*, "find target", "core hound"))
        return false;

    // This action is only for melee
    if (!PlayerbotAI::IsMelee(bot))
        return false;

    Unit* priorityTarget = FindHighestHealthCoreHound();

    // Update raid target icons if needed
    return UpdateSkullMarker(priorityTarget);
}

Unit* McAttackHighestHealthCoreHoundAction::FindHighestHealthCoreHound() const
{
    Unit* priorityTarget = nullptr;

    // Check for alive core hounds
    for (const ObjectGuid& targetGuid : AI_VALUE(GuidVector, "possible targets no los"))
    {
        Unit* unit = botAI->GetUnit(targetGuid);
        if (unit && unit->IsAlive() && unit->IsInCombat() && unit->GetEntry() == NPC_CORE_HOUND && !unit->HasAura(SPELL_CORE_HOUND_PLAY_DEAD))
        {
            if (priorityTarget == nullptr || priorityTarget->GetHealth() < unit->GetHealth())
                priorityTarget = unit;
        }
    }

    return priorityTarget;
}

bool McAttackHighestHealthCoreHoundAction::UpdateSkullMarker(const Unit* priorityTarget) const
{
    if (!priorityTarget)
        return false;

    Group* group = bot->GetGroup();
    if (!group)
        return false;

    constexpr uint8_t skullIconId = 7;

    // Get current skull target
    ObjectGuid currentSkull = group->GetTargetIcon(skullIconId);
    Unit* currentSkullUnit = botAI->GetUnit(currentSkull);

    // Determine if skull marker needs updating
    bool needsUpdate = !currentSkullUnit || !currentSkullUnit->IsAlive() || currentSkullUnit != priorityTarget;

    // Update if needed
    if (needsUpdate)
        group->SetTargetIcon(skullIconId, bot->GetGUID(), priorityTarget->GetGUID());
    return needsUpdate;
}

bool McCheckShouldMoveFromGroupAction::Execute(Event event)
{
    if (bot->HasAura(SPELL_BARON_GEDDON_LIVING_BOMB)) // baron geddon's living bomb
    {
        if (!botAI->HasStrategy("move from group", BOT_STATE_COMBAT))
        {
            // add/remove from both for now as it will make it more obvious to
            // player if this strat remains on after fight somehow
            botAI->ChangeStrategy("+move from group", BOT_STATE_NON_COMBAT);
            botAI->ChangeStrategy("+move from group", BOT_STATE_COMBAT);
            return true;
        }
    }
    else if (botAI->HasStrategy("move from group", BOT_STATE_COMBAT))
    {
        // add/remove from both for now as it will make it more obvious to
        // player if this strat remains on after fight somehow
        botAI->ChangeStrategy("-move from group", BOT_STATE_NON_COMBAT);
        botAI->ChangeStrategy("-move from group", BOT_STATE_COMBAT);
        return true;
    }
    return false;
}

bool McMoveFromBaronGeddonAction::Execute(Event event)
{
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "baron geddon"))
    {
        constexpr float radius = 25.0f; // more than should be needed but bots keep trying to run back in
        long distToTravel = radius - bot->GetDistance(boss);
        if (distToTravel > 0)
        {
            // Stop current spell first
            botAI->InterruptSpell();

            // float angle = bot->GetAngle(boss) + M_PI;
            // return Move(angle, distToTravel);
            return MoveAway(boss, distToTravel);
        }
    }
    return false;
}
