#include "RaidMcStrategy.h"

#include "Strategy.h"

void RaidMcStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Magmadar
    // TODO: Fear ward / tremor totem, or general anti-fear strat development. Same as King Dred (Drak'Tharon) and faction commander (Nexus).
    triggers.push_back(
        new TriggerNode("mc magmadar fire resistance trigger",
                        NextAction::array(0, new NextAction("mc magmadar fire resistance action", ACTION_RAID), nullptr)));

    // Baron Geddon
    triggers.push_back(
        new TriggerNode("mc baron geddon fire resistance trigger",
                        NextAction::array(0, new NextAction("mc baron geddon fire resistance action", ACTION_RAID), nullptr)));
    triggers.push_back(
        new TriggerNode("mc living bomb debuff",
                        NextAction::array(0, new NextAction("mc check should move from group", ACTION_RAID), nullptr)));
    triggers.push_back(
        new TriggerNode("mc baron geddon inferno",
                        NextAction::array(0, new NextAction("mc move from baron geddon", ACTION_RAID), nullptr)));
}
