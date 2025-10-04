#include "RaidZGStrategy.h"

#include "Strategy.h"
#include "RaidZGMultipliers.h"

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

    // Mar'li
    triggers.push_back(new TriggerNode(
        "zg mar'li troll form",
        NextAction::array(0, new NextAction("zg mar'li troll form attack adds", ACTION_RAID + 1), nullptr)));
    triggers.push_back(new TriggerNode(
        "zg mar'li troll form",
        NextAction::array(0, new NextAction("zg mar'li troll form position", ACTION_RAID + 2), nullptr)));
    triggers.push_back(new TriggerNode(
       "zg mar'li spider form",
       NextAction::array(0, new NextAction("zg mar'li spider form set main tank", ACTION_RAID + 3), nullptr)));
    triggers.push_back(new TriggerNode(
       "zg mar'li spider form",
       NextAction::array(0, new NextAction("zg mar'li spider form tank attack", ACTION_RAID + 2), nullptr)));
    triggers.push_back(new TriggerNode(
       "zg mar'li spider form",
       NextAction::array(0, new NextAction("zg mar'li spider form position", ACTION_RAID + 1), nullptr)));
}

void RaidZGStrategy::InitMultipliers(std::vector<Multiplier*> &multipliers)
{
    multipliers.push_back(new MarliMultiplier(botAI));
}
