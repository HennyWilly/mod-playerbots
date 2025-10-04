#ifndef _PLAYERBOT_RAIDZGACTIONS_H
#define _PLAYERBOT_RAIDZGACTIONS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "MovementActions.h"
#include "AttackAction.h"
#include "ChooseTargetActions.h"

const Position ZG_VENOXIS_PHASE1_TANK_POSITION{-11993.113f, -1712.2234f};
const Position ZG_MARLI_TANK_POSITION{-12326.371f, -1584.6284f};

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

class ZgJeklikPhaseOnePositionAction : public MovementAction
{
public:
    ZgJeklikPhaseOnePositionAction(PlayerbotAI* ai) : MovementAction(ai, "zg jeklik phase one position") {}
    bool isUseful() override;
    bool Execute(Event event) override;
};

class ZgMarliTrollFormAttackAddsAction : public AttackAction
{
public:
    ZgMarliTrollFormAttackAddsAction(PlayerbotAI* ai) : AttackAction(ai, "zg mar'li troll form attack adds") {}
    bool isUseful() override;
    bool Execute(Event event) override;
};

class ZgMarliTrollFormPositionAction : public MovementAction
{
public:
    ZgMarliTrollFormPositionAction(PlayerbotAI* ai) : MovementAction(ai, "zg mar'li troll form position") {}
    bool Execute(Event event) override;
};

class ZgMarliSpiderFormSetMainTankAction : public Action
{
public:
    ZgMarliSpiderFormSetMainTankAction(PlayerbotAI* ai) : Action(ai, "zg mar'li spider form set main tank") {}

    bool isUseful() override;
    bool Execute(Event event) override;
};

class ZgMarliSpiderFormTankAttackAction : public AttackAction
{
public:
    ZgMarliSpiderFormTankAttackAction(PlayerbotAI* ai) : AttackAction(ai, "zg mar'li spider form tank attack") {}

    bool isUseful() override;
    bool Execute(Event event) override;
};

class ZgMarliSpiderFormPositionAction : public MovementAction
{
public:
    ZgMarliSpiderFormPositionAction(PlayerbotAI* ai) : MovementAction(ai, "zg mar'li spider form position") {}
    bool Execute(Event event) override;
};

#endif
