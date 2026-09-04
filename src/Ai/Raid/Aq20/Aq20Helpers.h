/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20UTILS_H
#define PLAYERBOTS_AQ20UTILS_H

#include "GameObject.h"

namespace Aq20Helpers
{
    enum class Aq20Spells : uint32
    {
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
        // Ossirian the Unscarred
        GO_OSSIRIAN_CRYSTAL = 180619
    };

    enum class Aq20NPCs : uint32
    {
        // TODO
    };

    bool IsOssirianBuffActive(Unit const* ossirian);
    int32 GetOssirianDebuffTimeRemaining(Unit const* ossirian);
    GameObject* GetNearestCrystal(Unit const* ossirian);
}

#endif
