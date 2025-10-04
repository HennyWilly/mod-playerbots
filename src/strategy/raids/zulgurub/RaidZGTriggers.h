#ifndef _PLAYERBOT_RAIDZGTRIGGERS_H
#define _PLAYERBOT_RAIDZGTRIGGERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

enum ZulGurubCreatureIDs
{
    // Venoxis
    NPC_RAZZASHI_COBRA        = 11373,

    // Mar'li
    NPC_SPAWN_OF_MARLI        = 15041
};

enum ZulGurubSpellIDs
{
    // Mar'li
    SPELL_GROWTH              = 24086,
    SPELL_FULL_GROWN          = 24088,
    SPELL_SPIDER_FORM         = 24084,
    SPELL_ENVELOPING_WEB      = 24110
};

class ZgVenoxisPhaseOneTrigger : public Trigger
{
public:
    ZgVenoxisPhaseOneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg venoxis phase one") {}
    bool IsActive() override;
};

class ZgJeklikPhaseOneTrigger : public Trigger
{
public:
    ZgJeklikPhaseOneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg jeklik phase one") {}
    bool IsActive() override;
};

class ZgMarliTrollFormTrigger : public Trigger
{
public:
    ZgMarliTrollFormTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg mar'li troll form") {}
    bool IsActive() override;
};

class ZgMarliSpiderFormTrigger : public Trigger
{
public:
    ZgMarliSpiderFormTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg mar'li spider form") {}
    bool IsActive() override;
};

#endif
