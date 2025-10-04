#ifndef _PLAYERBOT_RAIDZGACTIONS_H
#define _PLAYERBOT_RAIDZGACTIONS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "MovementActions.h"
#include "AttackAction.h"

const Position ZG_VENOXIS_PHASE1_TANK_POSITION{-11993.113f, -1712.2234f};

class ZgVenoxisPhaseOneTankAttackAction : public AttackAction
{
public:
    ZgVenoxisPhaseOneTankAttackAction(PlayerbotAI* ai) : AttackAction(ai, "zg venoxis phase one tank attack") {}
    bool isUseful() override;
    bool Execute(Event event) override;
};

class ZgVenoxisPhaseOnePositionAction : public MovementAction
{
public:
    ZgVenoxisPhaseOnePositionAction(PlayerbotAI* ai) : MovementAction(ai, "zg venoxis phase one position") {}
    bool Execute(Event event) override;
};

#endif
