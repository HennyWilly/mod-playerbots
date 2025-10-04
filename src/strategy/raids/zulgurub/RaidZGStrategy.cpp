#include "RaidZGStrategy.h"

#include "Strategy.h"

void RaidZGStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Venoxis
    triggers.push_back(new TriggerNode(
        "zg venoxis phase one",
        NextAction::array(0, new NextAction("zg venoxis phase one tank attack", ACTION_RAID + 2), nullptr)));
    triggers.push_back(new TriggerNode(
        "zg venoxis phase one",
        NextAction::array(0, new NextAction("zg venoxis phase one position", ACTION_RAID + 1), nullptr)));
}
