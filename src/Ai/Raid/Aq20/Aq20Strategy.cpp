/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Strategy.h"

#include "Aq20Helpers.h"
#include "Aq20Multipliers.h"
#include "Playerbots.h"
#include "ThreatHelpers.h"

void RaidAq20Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Kurinnaxx
    triggers.push_back(new TriggerNode("aq20 kurinnaxx sand trap nearby", {
        NextAction("aq20 kurinnaxx avoid sand trap", ACTION_RAID + 4) }));
    triggers.push_back(new TriggerNode("aq20 kurinnaxx positioning", {
        NextAction("aq20 kurinnaxx avoid wide slash", ACTION_MOVE + 4) }));
    triggers.push_back(new TriggerNode("aq20 kurinnaxx tank mortal wound", {
        NextAction("aq20 kurinnaxx tank swap", ACTION_RAID + 1) }));

    // General Rajaxx
    triggers.push_back(new TriggerNode("aq20 rajaxx wave on andorov", {
        NextAction("aq20 rajaxx pull wave from andorov", ACTION_RAID) }));

    // Buru the Gorger
    // TODO P1: kite boss to egg -> kill egg while boss is near it (maybe pre-damage it till X%) -> repeat until ~20%
    // TODO P2: burn down the boss; maybe safe CDs for P2 because of Creeping Plague?

    // Moam
    triggers.push_back(new TriggerNode("aq20 moam can drain mana", {
        NextAction("aq20 moam drain mana", ACTION_RAID) }));
    triggers.push_back(new TriggerNode("aq20 moam ranged in trample range", {
        NextAction("aq20 moam avoid trample", ACTION_RAID + 1) })); // Above drain mana so channels start out of range

    // Ayamiss the Hunter
    triggers.push_back(new TriggerNode("aq20 ayamiss nature resistance", {
        NextAction("aq20 ayamiss nature resistance", ACTION_RAID) }));
    triggers.push_back(new TriggerNode("aq20 ayamiss larva found", {
        NextAction("aq20 ayamiss mark larva as skull", ACTION_RAID) }));
    // TODO P1+P2: Maybe stay close to altar to kill the larva?
    // TODO P1+P2: Smarter targeting strategy for larva? Maybe closest.

    // Anubisath
    // TODO Reflection
    // TODO Shadowstorm
    // TODO War Stomp

    // Ossirian the Unscarred
    triggers.push_back(new TriggerNode("aq20 move to crystal", {
        NextAction("aq20 use crystal", ACTION_RAID) })); // TODO Move in steps so the bot can still cast (e.g. heal)
    // TODO Strategy improvements?
    // TODO Improve encounter start
    // TODO Keep distance for ranges (for war thunder)
}

void RaidAq20Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new KurinnaxxTankMultiplier(botAI));
    multipliers.push_back(new MoamMultiplier(botAI));
}

void RaidAq20Strategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type)
{
    if (type != TargetValueExclusionType::DpsTarget && type != TargetValueExclusionType::TankTarget)
        return;

    Unit* bot = botAI->GetBot();
    Player* playerBot = bot ? bot->ToPlayer() : nullptr;
    if (!playerBot)
        return;

    // Moam takes almost no damage during phase 2; kill the Mana Fiends instead.
    Unit* moam = FindThreatTarget(playerBot, "moam");
    if (Aq20Helpers::IsMoamStonePhase(moam))
        exclusions.insert(moam->GetGUID());

    if (!PlayerbotAI::IsMelee(playerBot))
        return;

    Unit* ayamiss = FindThreatTarget(playerBot, "ayamiss the hunter");
    if (!ayamiss || ayamiss->GetHealthPct() <= 70)
        return;

    exclusions.insert(ayamiss->GetGUID());
}
