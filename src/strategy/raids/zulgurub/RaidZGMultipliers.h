#ifndef _PLAYERRBOT_RAIDZGMULTIPLIERS_H
#define _PLAYERRBOT_RAIDZGMULTIPLIERS_H

#include "Multiplier.h"

class MarliMultiplier : public Multiplier
{
public:
    MarliMultiplier(PlayerbotAI* ai) : Multiplier(ai, "high priestess mar'li") { }

    float GetValue(Action* action) override;
};

#endif
