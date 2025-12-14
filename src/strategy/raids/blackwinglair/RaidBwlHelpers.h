#ifndef _PLAYERBOT_RAIDBWLHELPERS_H
#define _PLAYERBOT_RAIDBWLHELPERS_H

#include "PlayerbotAI.h"

namespace BwlHelpers
{
    enum BwlSpells
    {
        // Chromaggus
        SPELL_HOURGLASS_SAND = 23645,
        SPELL_BROOD_AFFLICTION_BRONZE = 23170,

        // Nefarian
        SPELL_ONYXIA_SCALE_CLOAK = 22683
    };
    enum BwlGameObjects
    {
        GO_SUPPRESSION_DEVICE = 179784
    };

    GameObject* GetSuppressionDeviceWithinRange(PlayerbotAI* botAI);
}

#endif
