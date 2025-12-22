#ifndef _PLAYERBOT_RAIDBWLMULTIPLIERS_H
#define _PLAYERBOT_RAIDBWLMULTIPLIERS_H

#include "Multiplier.h"

class VaelastraszMultiplier : public Multiplier
{
public:
    VaelastraszMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "bwl vaelastrasz multiplier") {}
    float GetValue(Action* action) override;
};

#endif
