#include "RaidBwlActions.h"

#include "Playerbots.h"
#include "RaidBwlHelpers.h"
#include "RtiTargetValue.h"

using namespace BwlHelpers;

bool BwlRazorgoreMarkBossSkullAction::Execute(Event event)
{
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "razorgore the untamed"))
    {
        if (Group* group = bot->GetGroup())
        {
            ObjectGuid currentSkullGuid = group->GetTargetIcon(RtiTargetValue::skullIndex);
            if (currentSkullGuid.IsEmpty() || currentSkullGuid != boss->GetGUID())
            {
                group->SetTargetIcon(RtiTargetValue::skullIndex, bot->GetGUID(), boss->GetGUID());
                return true;
            }
        }
    }
    return false;
}

bool BwlOnyxiaScaleCloakAuraCheckAction::Execute(Event event)
{
    // TODO Only enable in cheat mode?
    bot->AddAura(SPELL_ONYXIA_SCALE_CLOAK, bot);
    return true;
}

bool BwlOnyxiaScaleCloakAuraCheckAction::isUseful()
{
    return !bot->HasAura(SPELL_ONYXIA_SCALE_CLOAK);
}

bool BwlTurnOffSuppressionDeviceAction::Execute(Event event)
{
    if (auto suppressionDevice = GetSuppressionDeviceWithinRange(botAI))
    {
        suppressionDevice->SetGoState(GO_STATE_ACTIVE);
        return true;
    }
    return false;
}

bool BwlUseHourglassSandAction::Execute(Event event)
{
    // TODO Only use if Hourglass Sand in inventory?
    return botAI->CastSpell(SPELL_HOURGLASS_SAND, bot);
}
