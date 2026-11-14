/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20HELPERS_H
#define PLAYERBOTS_AQ20HELPERS_H

#include "PlayerbotAI.h"

namespace Aq20Helpers
{
    enum class Aq20Spells : uint32
    {
        // Kurinnaxx
        SPELL_MORTAL_WOUND = 25646,

        // Moam
        SPELL_HUNTER_VIPER_STING = 3034,
        SPELL_WARLOCK_DRAIN_MANA = 5138,
        SPELL_ENERGIZE = 25685,

        // Ossirian the Unscarred
        SPELL_STRENGTH_OF_OSSIRIAN = 25176,
        SPELL_FIRE_WEAKNESS = 25177,
        SPELL_FROST_WEAKNESS = 25178,
        SPELL_NATURE_WEAKNESS = 25180,
        SPELL_ARCANE_WEAKNESS = 25181,
        SPELL_SHADOW_WEAKNESS = 25183
    };

    enum class Aq20GameObjects : uint32
    {
        // Kurinnaxx
        GO_SAND_TRAP = 180647,

        // Ossirian the Unscarred
        GO_OSSIRIAN_CRYSTAL = 180619
    };

    // See ruins_of_ahnqiraj.h
    enum class Aq20InstanceData : uint32
    {
        DATA_ANDOROV = 15
    };

    enum class Aq20NPCs : uint32
    {
        // Ayamiss the Hunter
        NPC_HIVE_ZARA_LARVA = 15555
    };

    constexpr float KURINNAXX_SAND_TRAP_DISTANCE = 10.0f;
    constexpr uint8 KURINNAXX_MORTAL_WOUND_SWAP_STACKS = 5;
    constexpr float RAJAXX_ANDOROV_ASSIST_DISTANCE = 50.0f;
    constexpr float RAJAXX_ANDOROV_ATTACKER_DISTANCE = 20.0f;
    constexpr float MOAM_TRAMPLE_SAFE_DISTANCE = 13.0f; // 10 yards + margin.

    GameObject* GetNearestSandTrap(Unit const* bot);
    bool HasSwapMortalWoundStacks(Unit const* unit);
    Unit* FindCloseAndorovAttacker(Player* bot);
    Unit* FindHiveZaraLarva(PlayerbotAI* botAI);
    bool IsOssirianBuffActive(Unit const* ossirian);
    int32 GetOssirianDebuffTimeRemaining(Unit const* ossirian);
    GameObject* GetNearestCrystal(Unit const* ossirian);
}

#endif
