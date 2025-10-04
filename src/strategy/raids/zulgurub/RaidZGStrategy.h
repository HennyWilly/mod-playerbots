#ifndef _PLAYERBOT_RAIDZGSTRATEGY_H
#define _PLAYERBOT_RAIDZGSTRATEGY_H

#include "AiObjectContext.h"
#include "Multiplier.h"
#include "Strategy.h"

class RaidZGStrategy : public Strategy
{
public:
    RaidZGStrategy(PlayerbotAI* ai) : Strategy(ai) {}
    virtual std::string const getName() override { return "zg"; }
    virtual void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    // virtual void InitMultipliers(std::vector<Multiplier*> &multipliers) override;
};

#endif
