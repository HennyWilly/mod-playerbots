#ifndef _PLAYERBOT_RAIDBWLACTIONS_H
#define _PLAYERBOT_RAIDBWLACTIONS_H

#include "MovementActions.h"

class BwlRazorgoreMarkBossSkullAction : public Action
{
public:
    BwlRazorgoreMarkBossSkullAction(PlayerbotAI* botAI)
        : Action(botAI, "bwl razorgore mark boss skull") {}
    bool Execute(Event event) override;
};

class BwlVaelastraszMoveFromGroupAction : public MovementAction
{
public:
    BwlVaelastraszMoveFromGroupAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "bwl vaelastrasz move from group") {}
    bool Execute(Event event) override;
};

class BwlOnyxiaScaleCloakAuraCheckAction : public Action
{
public:
    BwlOnyxiaScaleCloakAuraCheckAction(PlayerbotAI* botAI)
        : Action(botAI, "bwl onyxia scale cloak aura check") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class BwlTurnOffSuppressionDeviceAction : public Action
{
public:
    BwlTurnOffSuppressionDeviceAction(PlayerbotAI* botAI)
        : Action(botAI, "bwl turn off suppression device") {}
    bool Execute(Event event) override;
};

class BwlUseHourglassSandAction : public Action
{
public:
    BwlUseHourglassSandAction(PlayerbotAI* botAI)
        : Action(botAI, "bwl use hourglass sand") {}
    bool Execute(Event event) override;
};

#endif
