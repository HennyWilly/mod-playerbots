/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONS_H
#define PLAYERBOTS_AQ20ACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"
#include "PlayerbotAI.h"

class Aq20KurinnaxxAvoidSandTrapAction : public MovementAction
{
public:
    Aq20KurinnaxxAvoidSandTrapAction(PlayerbotAI* botAI, std::string const& name = "aq20 kurinnaxx avoid sand trap") : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class Aq20KurinnaxxAvoidWideSlashAction : public MovementAction
{
public:
    Aq20KurinnaxxAvoidWideSlashAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq20 kurinnaxx avoid wide slash") {}
    bool Execute(Event event) override;
};

class Aq20KurinnaxxTankSwapAction : public AttackAction
{
public:
    Aq20KurinnaxxTankSwapAction(PlayerbotAI* botAI) : AttackAction(botAI, "aq20 kurinnaxx tank swap") {}
    bool Execute(Event event) override;
};

class Aq20RajaxxPullWaveFromAndorovAction : public AttackAction
{
public:
    Aq20RajaxxPullWaveFromAndorovAction(PlayerbotAI* botAI) : AttackAction(botAI, "aq20 rajaxx pull wave from andorov") {}
    bool Execute(Event event) override;
};

class Aq20BuruKiteToEggAction : public MovementAction
{
public:
    Aq20BuruKiteToEggAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq20 buru kite to egg") {}
    bool Execute(Event event) override;

private:
    bool KiteAroundRoom(Unit* buru);
};

class Aq20BuruMarkEggAsSkullAction : public Action
{
public:
    Aq20BuruMarkEggAsSkullAction(PlayerbotAI* botAI) : Action(botAI, "aq20 buru mark egg as skull") {}
    bool Execute(Event event) override;
};

class Aq20BuruClearEggMarkAction : public Action
{
public:
    Aq20BuruClearEggMarkAction(PlayerbotAI* botAI) : Action(botAI, "aq20 buru clear egg mark") {}
    bool Execute(Event event) override;
};

class Aq20BuruRecallPetAction : public Action
{
public:
    Aq20BuruRecallPetAction(PlayerbotAI* botAI) : Action(botAI, "aq20 buru recall pet") {}
    bool Execute(Event event) override;
};

class Aq20MoamDrainManaAction : public Action
{
public:
    Aq20MoamDrainManaAction(PlayerbotAI* botAI) : Action(botAI, "aq20 moam drain mana") {}
    bool Execute(Event event) override;
};

class Aq20MoamAvoidTrampleAction : public MovementAction
{
public:
    Aq20MoamAvoidTrampleAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq20 moam avoid trample") {}
    bool Execute(Event event) override;
};

class Aq20AyamissMarkLarvaAsSkullAction : public Action
{
public:
    Aq20AyamissMarkLarvaAsSkullAction(PlayerbotAI* botAI) : Action(botAI, "aq20 ayamiss mark larva as skull") {}
    bool Execute(Event event) override;
};

class Aq20UseCrystalAction : public MovementAction
{
public:
    Aq20UseCrystalAction(PlayerbotAI* botAI, std::string const& name = "aq20 use crystal") : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};
#endif
