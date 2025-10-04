#include "RaidZGStrategy.h"

#include "Strategy.h"

void RaidZGStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Venoxis
    // P2 - Poison Cloud: Bots automatically move out of aoe.
    triggers.push_back(new TriggerNode(
        "zg venoxis phase one",
        NextAction::array(0, new NextAction("zg venoxis phase one tank attack", ACTION_RAID + 2), nullptr)));
    triggers.push_back(new TriggerNode(
        "zg venoxis phase one",
        NextAction::array(0, new NextAction("zg venoxis phase one position", ACTION_RAID + 1), nullptr)));

    // Jeklik
    // P1 - Swoop (cleave): Melee bots already position themselves behind the boss.
    // P1 - Charge: Can be face-tanked without much issue.
    // P2 - Greater Heal: Bots automatically interrupt.
    triggers.push_back(new TriggerNode(
        "zg jeklik phase one",
        NextAction::array(0, new NextAction("zg jeklik phase one position", ACTION_RAID + 1), nullptr)));
}
