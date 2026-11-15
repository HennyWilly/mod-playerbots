/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20HELPERS_H
#define PLAYERBOTS_AQ20HELPERS_H

#include "PlayerbotAI.h"
#include <array>

namespace Aq20Helpers
{
    enum class Aq20Spells : uint32
    {
        // Kurinnaxx
        SPELL_MORTAL_WOUND = 25646,

        // Buru the Gorger
        SPELL_BURU_TRANSFORM = 24721,

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
        // Buru the Gorger
        NPC_BURU_EGG = 15514,
        NPC_HIVEZARA_HATCHLING = 15521,

        // Ayamiss the Hunter
        NPC_HIVE_ZARA_LARVA = 15555
    };

    constexpr uint32 AQ20_MAP_ID = 509;
    constexpr float KURINNAXX_SAND_TRAP_DISTANCE = 10.0f;
    constexpr uint8 KURINNAXX_MORTAL_WOUND_SWAP_STACKS = 5;
    constexpr float RAJAXX_ANDOROV_ASSIST_DISTANCE = 50.0f;
    constexpr float RAJAXX_ANDOROV_ATTACKER_DISTANCE = 20.0f;
    constexpr float BURU_EGG_SEARCH_DISTANCE = 150.0f; // Covers all eggs, as in boss_buru.cpp.
    constexpr float BURU_EGG_WAIT_DISTANCE = 10.0f; // Behind the egg, so Buru passes it first.
    constexpr float BURU_EGG_EXPLOSION_RADIUS = 25.0f;
    constexpr float BURU_EGG_KILL_DISTANCE = 23.0f; // Margin to the explosion radius.
    constexpr float BURU_EGG_STAY_DISTANCE = 15.0f; // The victim keeps circling its egg within this.
    // Pre-damage the marked egg down to 0.5% health per yard Buru is away from it, at most 30%.
    constexpr float BURU_EGG_HOLD_PCT_PER_YARD = 0.5f;
    constexpr float BURU_EGG_MAX_HOLD_PCT = 30.0f;
    constexpr float BURU_FLEE_DISTANCE = 15.0f;
    constexpr float MOAM_TRAMPLE_SAFE_DISTANCE = 13.0f; // 10 yards + margin.
    constexpr float AYAMISS_AIRBORNE_HEIGHT = 5.0f;
    extern const Position AYAMISS_ALTAR_POSITION;
    extern const std::array<Position, 5> BURU_KITE_ROUTE;

    GameObject* GetNearestSandTrap(Unit const* bot);
    bool HasSwapMortalWoundStacks(Unit const* unit);
    Unit* FindCloseAndorovAttacker(Player* bot);
    bool IsBuruTransformed(Unit const* buru);
    Unit* FindUntransformedBuru(Player* bot);
    Creature* FindKiteEgg(Player const* bot, Unit const* buru);
    Creature* GetMarkedEgg(Player* bot);
    // The marked egg while Buru is in reach of its explosion, otherwise the egg his victim kites him to.
    Creature* FindEggToMark(Player* bot);
    // Only the skull-marked egg is attacked, down to a health left that grows with Buru's distance. It
    // is finished once Buru is close to it.
    bool IsEggToKill(Player* bot, Unit const* buru, Unit const* egg);
    // A pet attacking any other egg.
    Creature* FindPetOnWrongEgg(Player* bot);
    bool IsMoamStonePhase(Unit const* moam);
    Unit* FindHiveZaraLarva(PlayerbotAI* botAI);
    bool IsAyamissAirborne(Unit const* ayamiss, Unit const* bot);
    bool IsOssirianBuffActive(Unit const* ossirian);
    int32 GetOssirianDebuffTimeRemaining(Unit const* ossirian);
    GameObject* GetNearestCrystal(Unit const* ossirian);
}

#endif
