#include "RaidBwlStrategy.h"

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
    // TODO Control Razorgore if the real player dies? (Fallback)

    // Vaelastrasz
    // TODO Fire resistence
    // TODO Dragon strategy for breath/cleave and tail sweep
    // TODO Tank swap if main tank has Burning Adrenaline
    // TODO Move away fron raid before exploding

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
