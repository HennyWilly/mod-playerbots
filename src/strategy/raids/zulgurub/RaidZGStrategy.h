#ifndef _PLAYERBOT_RAIDZGSTRATEGY_H
#define _PLAYERBOT_RAIDZGSTRATEGY_H

#include "AiObjectContext.h"
#include "Multiplier.h"
#include "Strategy.h"

class RaidZGStrategy : public Strategy
{
public:
    RaidZGStrategy(PlayerbotAI* ai) : Strategy(ai) {}
    std::string const getName() override { return "zg"; }
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    void InitMultipliers(std::vector<Multiplier*> &multipliers) override;
};

#endif
