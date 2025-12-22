#include "RaidBwlStrategy.h"

#include "RaidBwlMultipliers.h"
#include "Strategy.h"

void RaidBwlStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Common
    triggers.push_back(
        new TriggerNode("bwl suppression device",
                        NextAction::array(0, new NextAction("bwl turn off suppression device", ACTION_RAID), NULL)));
    triggers.push_back(
        new TriggerNode("often",
                        NextAction::array(0, new NextAction("bwl check onyxia scale cloak", ACTION_RAID), NULL)));

    // Razorgore
    // TODO P1 - Attack adds that attack Razorgore.
    // TODO P1 - Don't attack Razorgore if not controlled. (Only tank, no dps)
    // TODO P1 - Control Razorgore if the real player dies? (Fallback)
    // TODO P2 - War Stomp: Keep ranged bots away
    triggers.push_back(
        new TriggerNode("bwl razorgore fire resistance",
                        NextAction::array(0, new NextAction("bwl razorgore fire resistance", ACTION_RAID), nullptr)));
    triggers.push_back(
        new TriggerNode("bwl razorgore phase 2 mark target",
                        NextAction::array(0, new NextAction("bwl razorgore mark boss skull", ACTION_RAID), nullptr)));

    // Vaelastrasz
    triggers.push_back(
        new TriggerNode("bwl vaelastrasz fire resistance",
                        NextAction::array(0, new NextAction("bwl vaelastrasz fire resistance", ACTION_RAID), nullptr)));
    triggers.push_back(
        new TriggerNode("bwl vaelastrasz dragon positioning",
                        NextAction::array(0, new NextAction("rear flank", ACTION_MOVE + 4), nullptr)));
    triggers.push_back(
        new TriggerNode("bwl vaelastrasz burning adrenaline",
                        NextAction::array(0, new NextAction("bwl vaelastrasz move from group", ACTION_RAID + 1), nullptr)));
    // TODO Tank swap if main tank has Burning Adrenaline

    // Lashlayer
    // TODO Tank positioning (knock back)
    // TODO Positioning of everyone else (cleave)
    // TODO Positioning melee (blast wave)

    // Firemaw
    // TODO Positioning (Flame Buffet + Wing Buffet + Shadow Flame cone)

    // Ebonroc
    // TODO Positioning (Wing Buffet + Shadow Flame cone)
    // TODO Tank swap on Shadow of Ebonroc

    // Flamegor
    // TODO Positioning (Wing Buffet + Shadow Flame cone)
    // TODO Remove frenzy (hunter) other wise he spams fire nova

    // Chromaggus
    triggers.push_back(
        new TriggerNode("bwl affliction bronze",
                        NextAction::array(0, new NextAction("bwl use hourglass sand", ACTION_RAID), NULL)));
    // TODO Handle breaths (handle Time Lapse too)
    // TODO Remove frenzy (hunter)
    // TODO Handle shimmering skin

    // Nefarian
    // TODO P1 - Handle adds (priority)
    // TODO P2 - Dragon strategy for breath/cleave and tail sweep
    // TODO P2 - Fear (strategy or out range)
    // TODO P2 - Handle class calls
    // TODO P3 - Handle Bone Constructs
}

void RaidBwlStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new VaelastraszMultiplier(botAI));
}
