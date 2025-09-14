#ifndef _PLAYERBOT_RAIDMCTRIGGERS_H
#define _PLAYERBOT_RAIDMCTRIGGERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

enum SpellIdsMC
{
    // Baron Geddon
    SPELL_BARON_GEDDON_INFERNO = 19695,
    SPELL_BARON_GEDDON_LIVING_BOMB = 20475,
};

class McLivingBombDebuffTrigger : public Trigger
{
public:
    McLivingBombDebuffTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc living bomb debuff") {}
    bool IsActive() override;
};

class McBaronGeddonInfernoTrigger : public Trigger
{
public:
    McBaronGeddonInfernoTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc baron geddon inferno") {}
    bool IsActive() override;
};

#endif
