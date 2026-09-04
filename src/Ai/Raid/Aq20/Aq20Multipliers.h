/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20MULTIPLIERS_H
#define PLAYERBOTS_AQ20MULTIPLIERS_H

#include "Multiplier.h"

class KurinnaxxTankMultiplier : public Multiplier
{
public:
    KurinnaxxTankMultiplier(
        PlayerbotAI* botAI) : Multiplier(botAI, "kurinnaxx tank multiplier") {}
    float GetValue(Action* action) override;
};

#endif
