#include "RaidBwlMultipliers.h"

#include "MovementActions.h"
#include "RaidBwlActions.h"
#include "RaidBwlHelpers.h"
#include "ReachTargetActions.h"

using namespace BwlHelpers;

float VaelastraszMultiplier::GetValue(Action* action)
{
    // No check for Vaelastrasz, because bots may have burning adrenaline even after Vaelastrasz died.
    if (bot->HasAura(SPELL_BURNING_ADRENALINE))
    {
        if (dynamic_cast<MovementAction*>(action) &&
                !dynamic_cast<BwlVaelastraszMoveFromGroupAction*>(action))
            return 0.0f;
        if (dynamic_cast<CastReachTargetSpellAction*>(action))
            return 0.0f;
    }

    return 1.0f;
}
