#include "RaidZGMultipliers.h"

#include "ChooseTargetActions.h"
#include "Playerbots.h"
#include "RaidZGActions.h"
#include "RaidZGTriggers.h"

float MarliMultiplier::GetValue(Action* action)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priestess mar'li");
    if (boss)
    {
        if (!boss->HasAura(SPELL_SPIDER_FORM)) // troll form
        {
            bool spiderFound = false;
            for (const auto& target : AI_VALUE(GuidVector, "possible targets no los"))
            {
                Unit* unit = botAI->GetUnit(target);
                if (unit && unit->GetEntry() == NPC_SPAWN_OF_MARLI)
                {
                    spiderFound = true;
                    break;
                }
            }

            // Only prevent assist actions if there are spiders.
            if (spiderFound)
            {
                if (PlayerbotAI::IsDps(bot) && dynamic_cast<DpsAssistAction*>(action))
                    return 0.0f;
                if (PlayerbotAI::IsRangedDps(bot) && dynamic_cast<DropTargetAction*>(action))
                    return 0.0f;

                // If there are spiders, ignore the position action to get into range if necessary!
                if (PlayerbotAI::IsRanged(bot) && dynamic_cast<ZgMarliTrollFormPositionAction*>(action))
                    return 0.0f;
            }
        }
        else // spider form
        {
            // TODO New AssistTank (after first switch) will still try to attack the boss...
            // if (PlayerbotAI::IsAssistTank(bot) && dynamic_cast<TankAssistAction*>(action))
            if (PlayerbotAI::IsAssistTank(bot) && dynamic_cast<AttackAction*>(action))
                return 0.0f;
        }
    }
    return 1.0f;
}
