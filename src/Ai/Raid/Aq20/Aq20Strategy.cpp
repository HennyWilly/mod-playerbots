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
    triggers.push_back(new TriggerNode("aq20 buru fixated", {
        NextAction("aq20 buru kite to egg", ACTION_EMERGENCY) }));
    triggers.push_back(new TriggerNode("aq20 buru stale egg mark", {
        NextAction("aq20 buru clear egg mark", ACTION_RAID) }));
    triggers.push_back(new TriggerNode("aq20 buru egg to mark", {
        NextAction("aq20 buru mark egg as skull", ACTION_RAID) }));
    triggers.push_back(new TriggerNode("aq20 buru pet on wrong egg", {
        NextAction("aq20 buru recall pet", ACTION_RAID) }));
    triggers.push_back(new TriggerNode("aq20 buru nature resistance", {
        NextAction("aq20 buru nature resistance", ACTION_RAID) }));

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
    multipliers.push_back(new BuruMultiplier(botAI));
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

    // Eggs that are hit join the attackers; leave all but the one to kill.
    if (Unit* buru = Aq20Helpers::FindUntransformedBuru(playerBot))
    {
        bool hatchlingAlive = false;
        AiObjectContext* context = botAI->GetAiObjectContext();
        for (ObjectGuid const& guid : AI_VALUE(GuidVector, "attackers"))
        {
            Unit* unit = botAI->GetUnit(guid);
            if (!unit)
                continue;

            if (unit->GetEntry() == static_cast<uint32>(Aq20Helpers::Aq20NPCs::NPC_HIVEZARA_HATCHLING))
                hatchlingAlive = true;
            else if (unit->GetEntry() == static_cast<uint32>(Aq20Helpers::Aq20NPCs::NPC_BURU_EGG) &&
                     !Aq20Helpers::IsEggToKill(playerBot, buru, unit))
                exclusions.insert(guid);
        }

        // Hatchlings first: pause the pre-damage on the marked egg until Buru is close to it.
        // Tanks can't hold Buru anyway, so they pick the hatchlings up.
        if (hatchlingAlive)
        {
            Creature* egg = Aq20Helpers::GetMarkedEgg(playerBot);
            if (egg && buru->GetExactDist2d(egg) > Aq20Helpers::BURU_EGG_KILL_DISTANCE)
                exclusions.insert(egg->GetGUID());

            if (type == TargetValueExclusionType::TankTarget)
                exclusions.insert(buru->GetGUID());
        }
    }

    // Moam takes almost no damage during phase 2; kill the Mana Fiends instead.
    Unit* moam = FindThreatTarget(playerBot, "moam");
    if (Aq20Helpers::IsMoamStonePhase(moam))
        exclusions.insert(moam->GetGUID());

    if (!PlayerbotAI::IsMelee(playerBot))
        return;

    Unit* ayamiss = FindThreatTarget(playerBot, "ayamiss the hunter");
    if (Aq20Helpers::IsAyamissAirborne(ayamiss, playerBot))
        exclusions.insert(ayamiss->GetGUID());
}
