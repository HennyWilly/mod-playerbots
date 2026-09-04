/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Strategy.h"

#include "Aq20Multipliers.h"

void RaidAq20Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("aq20 kurinnaxx sand trap nearby", {
        NextAction("aq20 kurinnaxx avoid sand trap", ACTION_RAID + 4) }));
    triggers.push_back(new TriggerNode("aq20 kurinnaxx positioning", {
        NextAction("aq20 kurinnaxx avoid wide slash", ACTION_MOVE + 4) }));

    triggers.push_back(new TriggerNode("aq20 move to crystal", {
        NextAction("aq20 use crystal", ACTION_RAID) }));

}
void RaidAq20Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new KurinnaxxTankMultiplier(botAI));
}
