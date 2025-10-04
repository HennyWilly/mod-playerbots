#ifndef _PLAYERBOT_RAIDZGTRIGGERS_H
#define _PLAYERBOT_RAIDZGTRIGGERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

enum ZulGurubCreatureIDs
{
    // Venoxis
    NPC_RAZZASHI_COBRA              = 11373
};

class ZgVenoxisPhaseOneTrigger : public Trigger
{
public:
    ZgVenoxisPhaseOneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg venoxis phase one") {}
    bool IsActive() override;
};

#endif
