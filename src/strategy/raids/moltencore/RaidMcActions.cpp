#include "RaidMcActions.h"

#include "Playerbots.h"
#include "RaidMcTriggers.h"

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
            // float angle = bot->GetAngle(boss) + M_PI;
            // return Move(angle, distToTravel);
            return MoveAway(boss, distToTravel);
        }
    }
    return false;
}
