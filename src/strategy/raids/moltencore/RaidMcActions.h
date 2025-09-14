#ifndef _PLAYERBOT_RAIDMCACTIONS_H
#define _PLAYERBOT_RAIDMCACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"

// From ICC DBS
class McAttackHighestHealthCoreHoundAction : public AttackAction
{
public:
    McAttackHighestHealthCoreHoundAction(PlayerbotAI* botAI, const std::string& name = "mc attack highest health core hound")
        : AttackAction(botAI, name) {}
    bool Execute(Event event) override;

    Unit* FindPriorityTarget() const;
    bool UpdateSkullMarker(const Unit* priorityTarget) const;
};

class McCheckShouldMoveFromGroupAction : public Action
{
public:
    McCheckShouldMoveFromGroupAction(PlayerbotAI* botAI, const std::string& name = "mc check should move from group")
        : Action(botAI, name) {}
    bool Execute(Event event) override;
};

class McMoveFromBaronGeddonAction : public MovementAction
{
public:
    McMoveFromBaronGeddonAction(PlayerbotAI* botAI, const std::string& name = "mc move from baron geddon")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

#endif
