/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Strategy.h"

#include "Aq20Multipliers.h"
#include "Playerbots.h"

void RaidAq20Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Kurinnaxx
    triggers.push_back(new TriggerNode("aq20 kurinnaxx sand trap nearby", {
        NextAction("aq20 kurinnaxx avoid sand trap", ACTION_RAID + 4) }));
    triggers.push_back(new TriggerNode("aq20 kurinnaxx positioning", {
        NextAction("aq20 kurinnaxx avoid wide slash", ACTION_MOVE + 4) }));
    // TODO Tank switch on N stacks of Mortal Wound

    // General Rajaxx
    // TODO Do we need a strategy here?

    // Buru the Gorger
    // TODO P1: kite boss to egg -> kill egg while boss is near it (maybe pre-damage it till X%) -> repeat until ~20%
    // TODO P2: burn down the boss; maybe safe CDs for P2 because of Creeping Plague?

    // Moam
    // TODO P1: Drain mana with Viper Sting, Mana Burn, and Drain Mana
    // TODO P1: Maybe: ranged stay away because of Trample?
    // TODO P2: Ignore boss and kill adds

    // Ayamiss the Hunter
    triggers.push_back(new TriggerNode("aq20 ayamiss nature resistance", {
        NextAction("aq20 ayamiss nature resistance", ACTION_RAID) }));
    triggers.push_back(new TriggerNode("aq20 ayamiss larva found", {
        NextAction("aq20 ayamiss mark larva as skull", ACTION_RAID) }));
    // TODO P1+P2: Maybe stay close to altar to kill the larva?

    // Ossirian the Unscarred
    triggers.push_back(new TriggerNode("aq20 move to crystal", {
        NextAction("aq20 use crystal", ACTION_RAID) }));
    // TODO Strategy improvements?
}

void RaidAq20Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new KurinnaxxTankMultiplier(botAI));
}

void RaidAq20Strategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type)
{
    if (type != TargetValueExclusionType::Dps && type != TargetValueExclusionType::Tank)
        return;

    Unit* bot = botAI->GetBot();
    Player* playerBot = bot ? bot->ToPlayer() : nullptr;
    if (!playerBot || !PlayerbotAI::IsMelee(playerBot))
        return;

    AiObjectContext* context = botAI->GetAiObjectContext();
    Unit* boss = AI_VALUE2(Unit*, "find target", "ayamiss the hunter");
    if (!boss || boss->GetHealthPct() <= 70)
        return;

    exclusions.insert(boss->GetGUID());
}
