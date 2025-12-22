#ifndef _PLAYERBOT_RAIDBWLTRIGGERS_H
#define _PLAYERBOT_RAIDBWLTRIGGERS_H

#include "BossAuraTriggers.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

class BwlSuppressionDeviceTrigger : public Trigger
{
public:
    BwlSuppressionDeviceTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "bwl suppression device") { }
    bool IsActive() override;
};

class BwlRazorgoreP2FireResistanceTrigger : public BossFireResistanceTrigger
{
public:
    BwlRazorgoreP2FireResistanceTrigger(PlayerbotAI* botAI)
        : BossFireResistanceTrigger(botAI, "razorgore the untamed") { }
    bool IsActive() override;
};

class BwlRazorgoreP2TriggerMarkTarget : public Trigger
{
public:
    BwlRazorgoreP2TriggerMarkTarget(PlayerbotAI* botAI)
        : Trigger(botAI, "bwl razorgore phase 2 mark target") { }
    bool IsActive() override;
};

class BwlVaelastraszDragonPositioningTrigger : public Trigger
{
public:
    BwlVaelastraszDragonPositioningTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "bwl vaelastrasz dragon positioning") { }
    bool IsActive() override;
};

class BwlVaelastraszBurningAdrenalineTrigger : public Trigger
{
public:
    BwlVaelastraszBurningAdrenalineTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "bwl vaelastrasz burning adrenaline") { }
    bool IsActive() override;
};

class BwlAfflictionBronzeTrigger : public Trigger
{
public:
    BwlAfflictionBronzeTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "bwl affliction bronze") { }
    bool IsActive() override;
};

#endif
