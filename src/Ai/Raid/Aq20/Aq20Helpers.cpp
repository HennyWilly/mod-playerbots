/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Helpers.h"

#include "InstanceScript.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "SpellAuras.h"
#include "ThreatHelpers.h"
#include <algorithm>

namespace Aq20Helpers
{
    // AltarPos in boss_ayamiss.cpp
    const Position AYAMISS_ALTAR_POSITION = { -9717.18f, 1517.72f, 27.4677f };
    // The egg spawns in order around the room, except the one next to Buru's spawn that forces a detour
    const std::array<Position, 5> BURU_KITE_ROUTE = { {
        { -9300.19f, 1266.67f, -63.7427f },
        { -9270.39f, 1243.90f, -63.7673f },
        { -9243.43f, 1280.50f, -63.5938f },
        { -9263.01f, 1295.24f, -63.8081f },
        { -9300.07f, 1305.08f, -63.6971f },
    } };

    static constexpr Aq20Spells OSSIRIAN_DEBUFFS[] = {
        Aq20Spells::SPELL_FIRE_WEAKNESS,
        Aq20Spells::SPELL_FROST_WEAKNESS,
        Aq20Spells::SPELL_NATURE_WEAKNESS,
        Aq20Spells::SPELL_ARCANE_WEAKNESS,
        Aq20Spells::SPELL_SHADOW_WEAKNESS
    };

    GameObject* GetNearestSandTrap(Unit const* bot)
    {
        return bot ?
            bot->FindNearestGameObject(static_cast<uint32>(Aq20GameObjects::GO_SAND_TRAP), KURINNAXX_SAND_TRAP_DISTANCE) :
            nullptr;
    }

    bool HasSwapMortalWoundStacks(Unit const* unit)
    {
        Aura* aura = unit ?
            unit->GetAura(static_cast<uint32>(Aq20Spells::SPELL_MORTAL_WOUND)) :
            nullptr;
        return aura && aura->GetStackAmount() >= KURINNAXX_MORTAL_WOUND_SWAP_STACKS;
    }

    Unit* FindCloseAndorovAttacker(Player* bot)
    {
        InstanceScript* instance = bot->GetInstanceScript();
        if (!instance)
            return nullptr;

        ObjectGuid const andorovGuid =
            instance->GetGuidData(static_cast<uint32>(Aq20InstanceData::DATA_ANDOROV));
        Creature* andorov = andorovGuid ? bot->GetMap()->GetCreature(andorovGuid) : nullptr;
        if (!andorov || !andorov->IsAlive() || !bot->IsWithinDistInMap(andorov, RAJAXX_ANDOROV_ASSIST_DISTANCE))
            return nullptr;

        for (Unit* attacker : andorov->getAttackers())
        {
            // Wait for the wave to reach Andorov rather than running out to meet it.
            if (attacker && attacker->IsAlive() &&
                attacker->IsWithinDistInMap(andorov, RAJAXX_ANDOROV_ATTACKER_DISTANCE) &&
                !attacker->GetThreatMgr().IsThreatenedBy(bot))
                return attacker;
        }
        return nullptr;
    }

    bool IsBuruTransformed(Unit const* buru)
    {
        return buru && buru->HasAura(static_cast<uint32>(Aq20Spells::SPELL_BURU_TRANSFORM));
    }

    Unit* FindUntransformedBuru(Player* bot)
    {
        Unit* buru = FindThreatTarget(bot, "buru the gorger");
        return buru && buru->IsAlive() && !IsBuruTransformed(buru) ? buru : nullptr;
    }

    Creature* FindKiteEgg(Player const* bot, Unit const* buru)
    {
        std::list<Creature*> eggs;
        bot->GetCreatureListWithEntryInGrid(
            eggs, static_cast<uint32>(Aq20NPCs::NPC_BURU_EGG), BURU_EGG_SEARCH_DISTANCE);

        Creature* best = nullptr;
        float bestDistance = 0.0f;
        bool bestAhead = false;
        for (Creature* egg : eggs)
        {
            if (!egg->IsAlive())
                continue;

            float const distance = bot->GetExactDist2d(egg);
            bool const ahead = distance < buru->GetExactDist2d(egg); // Don't run past Buru.
            if (!best || (ahead && !bestAhead) || (ahead == bestAhead && distance < bestDistance))
            {
                best = egg;
                bestDistance = distance;
                bestAhead = ahead;
            }
        }
        return best;
    }

    Creature* GetMarkedEgg(Player* bot)
    {
        Group* group = bot->GetGroup();
        ObjectGuid const guid = group ? group->GetTargetIcon(RtiTargetValue::skullIndex) : ObjectGuid::Empty;
        if (guid.GetEntry() != static_cast<uint32>(Aq20NPCs::NPC_BURU_EGG))
            return nullptr;

        Creature* egg = bot->GetMap()->GetCreature(guid);
        return egg && egg->IsAlive() ? egg : nullptr;
    }

    Creature* FindEggToMark(Player* bot)
    {
        Unit* buru = FindUntransformedBuru(bot);
        if (!buru)
            return nullptr;

        Creature* marked = GetMarkedEgg(bot);
        if (marked && buru->GetExactDist2d(marked) <= BURU_EGG_EXPLOSION_RADIUS)
            return marked;

        Unit* victim = buru->GetVictim();
        Player* player = victim ? victim->ToPlayer() : nullptr;
        return player ? FindKiteEgg(player, buru) : nullptr;
    }

    bool IsEggToKill(Player* bot, Unit const* buru, Unit const* egg)
    {
        Group* group = bot->GetGroup();
        if (!group || group->GetTargetIcon(RtiTargetValue::skullIndex) != egg->GetGUID())
            return false;

        float const distance = buru->GetExactDist2d(egg);
        if (distance <= BURU_EGG_KILL_DISTANCE)
            return true;

        // Leaves room for lingering damage like DoTs, so the egg doesn't die while Buru is away.
        return egg->GetHealthPct() > std::min(distance * BURU_EGG_HOLD_PCT_PER_YARD, BURU_EGG_MAX_HOLD_PCT);
    }

    Creature* FindPetOnWrongEgg(Player* bot)
    {
        Pet* pet = bot->GetPet();
        Unit* victim = pet ? pet->GetVictim() : nullptr;
        if (!victim || victim->GetEntry() != static_cast<uint32>(Aq20NPCs::NPC_BURU_EGG))
            return nullptr;

        Unit* buru = FindUntransformedBuru(bot);
        return buru && !IsEggToKill(bot, buru, victim) ? pet : nullptr;
    }

    bool IsMoamStonePhase(Unit const* moam)
    {
        return moam && moam->HasAura(static_cast<uint32>(Aq20Spells::SPELL_ENERGIZE));
    }

    Unit* FindHiveZaraLarva(PlayerbotAI* botAI)
    {
        AiObjectContext* context = botAI->GetAiObjectContext();

        // Detect incoming larvae (not on aggro table); the one closest to the altar feeds first.
        Unit* closest = nullptr;
        float closestDistance = 0.0f;
        GuidVector targets = AI_VALUE(GuidVector, "possible targets no los");
        for (auto& target : targets)
        {
            Unit* unit = botAI->GetUnit(target);
            if (!unit || unit->GetEntry() != static_cast<uint32>(Aq20NPCs::NPC_HIVE_ZARA_LARVA))
                continue;

            float const distance = unit->GetExactDist2d(AYAMISS_ALTAR_POSITION);
            if (!closest || distance < closestDistance)
            {
                closest = unit;
                closestDistance = distance;
            }
        }
        return closest;
    }

    bool IsAyamissAirborne(Unit const* ayamiss, Unit const* bot)
    {
        return ayamiss && bot && ayamiss->GetPositionZ() - bot->GetPositionZ() > AYAMISS_AIRBORNE_HEIGHT;
    }

    bool IsOssirianBuffActive(Unit const* ossirian)
    {
        return ossirian && ossirian->HasAura(static_cast<uint32>(Aq20Spells::SPELL_STRENGTH_OF_OSSIRIAN));
    }

    int32 GetOssirianDebuffTimeRemaining(Unit const* ossirian)
    {
        int32 retVal = 0xffffff;
        if (ossirian)
        {
            for (Aq20Spells debuff : OSSIRIAN_DEBUFFS)
            {
                if (AuraApplication* auraApplication = ossirian->GetAuraApplication(static_cast<uint32>(debuff)))
                {
                    if (Aura* aura = auraApplication->GetBase())
                    {
                        int32 duration = aura->GetDuration();
                        if (retVal > duration)
                            retVal = duration;
                    }
                }
            }
        }
        return retVal;
    }

    GameObject* GetNearestCrystal(Unit const* ossirian)
    {
        return ossirian ?
            ossirian->FindNearestGameObject(static_cast<uint32>(Aq20GameObjects::GO_OSSIRIAN_CRYSTAL), 200.0f) :
            nullptr;
    }
}
