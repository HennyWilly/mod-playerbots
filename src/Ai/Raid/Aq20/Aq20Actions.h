/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONS_H
#define PLAYERBOTS_AQ20ACTIONS_H

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

class Aq20MoamDrainManaAction : public Action
{
public:
    Aq20MoamDrainManaAction(PlayerbotAI* botAI) : Action(botAI, "aq20 moam drain mana") {}
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
