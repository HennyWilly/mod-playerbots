#include "RaidZGTriggers.h"

#include "SharedDefines.h"

bool ZgVenoxisPhaseOneTrigger::IsActive()
{
    if (const Unit* boss = AI_VALUE2(Unit*, "find target", "high priest venoxis"))
        return boss->GetHealthPct() > 50;
    return false;
}

bool ZgJeklikPhaseOneTrigger::IsActive()
{
    if (const Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess jeklik"))
        return boss->GetHealthPct() > 50;
    return false;
}

bool ZgMarliTrollFormTrigger::IsActive()
{
    if (const Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li"))
        return !boss->HasAura(SPELL_SPIDER_FORM);
    return false;
}

bool ZgMarliSpiderFormTrigger::IsActive()
{
    if (const Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li"))
        return boss->HasAura(SPELL_SPIDER_FORM);
    return false;
}
