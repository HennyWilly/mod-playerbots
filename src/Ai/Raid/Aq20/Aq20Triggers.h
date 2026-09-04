/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERS_H
#define PLAYERBOTS_AQ20TRIGGERS_H

#include "PlayerbotAI.h"
#include "Trigger.h"

class Aq20KurinnaxxSandTrapNearbyTrigger : public Trigger
{
public:
    Aq20KurinnaxxSandTrapNearbyTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 kurinnaxx sand trap nearby") {}
    bool IsActive() override;
};

class Aq20KurinnaxxPositioningTrigger : public Trigger
{
public:
    Aq20KurinnaxxPositioningTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 kurinnaxx positioning") {}
    bool IsActive() override;
};

class Aq20MoveToCrystalTrigger : public Trigger
{
public:
    Aq20MoveToCrystalTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 move to crystal") {}
    bool IsActive() override;
};
#endif
