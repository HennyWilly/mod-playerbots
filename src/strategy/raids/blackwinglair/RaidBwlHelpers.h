#ifndef _PLAYERBOT_RAIDBWLHELPERS_H
#define _PLAYERBOT_RAIDBWLHELPERS_H

#include "PlayerbotAI.h"

namespace BwlHelpers
{
    enum BwlSpells
    {
        // Vaelastrasz
        SPELL_BURNING_ADRENALINE = 18173,

        // Chromaggus
        SPELL_HOURGLASS_SAND = 23645,
        SPELL_BROOD_AFFLICTION_BRONZE = 23170,

        // Nefarian
        SPELL_ONYXIA_SCALE_CLOAK = 22683
    };
    enum BwlGameObjects
    {
        GO_BLACK_DRAGON_EGG = 177807,
        GO_SUPPRESSION_DEVICE = 179784
    };

    bool AreRazorgoreEggsAlive(const Player* bot);
    GameObject* GetSuppressionDeviceWithinRange(PlayerbotAI* botAI);
}

#endif
