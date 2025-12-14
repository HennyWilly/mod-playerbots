#include "RaidBwlTriggers.h"

#include "RaidBwlHelpers.h"

using namespace BwlHelpers;

bool BwlSuppressionDeviceTrigger::IsActive()
{
    // TODO Only rogues?
    return GetSuppressionDeviceWithinRange(botAI) != nullptr;
}

bool BwlAfflictionBronzeTrigger::IsActive()
{
    return bot->HasAura(SPELL_BROOD_AFFLICTION_BRONZE);
}
