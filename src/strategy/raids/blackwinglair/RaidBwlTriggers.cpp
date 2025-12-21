#include "RaidBwlTriggers.h"

#include "RaidBwlHelpers.h"

using namespace BwlHelpers;

bool BwlSuppressionDeviceTrigger::IsActive()
{
    if (bot->getClass() == CLASS_ROGUE || botAI->HasCheat(BotCheatMask::raid))
        return GetSuppressionDeviceWithinRange(botAI) != nullptr;
    return false;
}

bool BwlRazorgoreP2FireResistanceTrigger::IsActive()
{
    if (BossFireResistanceTrigger::IsActive())
        return !AreRazorgoreEggsAlive(bot);
    return false;
}

bool BwlRazorgoreP2TriggerMarkTarget::IsActive()
{
    // Only tanks may mark targets.
    if (PlayerbotAI::IsTank(bot))
    {
        Unit* boss = AI_VALUE2(Unit*, "find target", "razorgore the untamed");
        if (boss && boss->IsAlive() && !boss->IsFriendlyTo(bot))
            return !AreRazorgoreEggsAlive(bot);
    }
    return false;
}

bool BwlAfflictionBronzeTrigger::IsActive()
{
    return bot->HasAura(SPELL_BROOD_AFFLICTION_BRONZE);
}
