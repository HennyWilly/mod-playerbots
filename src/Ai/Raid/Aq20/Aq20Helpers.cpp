/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Helpers.h"
#include "SpellAuras.h"

namespace Aq20Helpers
{
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
