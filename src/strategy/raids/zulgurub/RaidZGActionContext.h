#ifndef _PLAYERBOT_RAIDZGACTIONCONTEXT_H
#define _PLAYERBOT_RAIDZGACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidZGActions.h"

class RaidZGActionContext : public NamedObjectContext<Action>
{
public:
    RaidZGActionContext()
    {
        // creators["mc check should move from group"] = &RaidZGActionContext::check_should_move_from_group;
    }

private:
    // static Action* check_should_move_from_group(PlayerbotAI* ai) { return new McCheckShouldMoveFromGroupAction(ai); }
};

#endif
