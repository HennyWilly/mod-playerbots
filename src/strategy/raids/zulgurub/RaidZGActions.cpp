#include "RaidZGActions.h"

#include "Playerbots.h"

// bool McCheckShouldMoveFromGroupAction::Execute(Event event)
// {
//     if (bot->HasAura(20475))  // barron geddon's living bomb
//     {
//         if (!botAI->HasStrategy("move from group", BotState::BOT_STATE_COMBAT))
//         {
//             // add/remove from both for now as it will make it more obvious to
//             // player if this strat remains on after fight somehow
//             botAI->ChangeStrategy("+move from group", BOT_STATE_NON_COMBAT);
//             botAI->ChangeStrategy("+move from group", BOT_STATE_COMBAT);
//             return true;
//         }
//     }
//     else if (botAI->HasStrategy("move from group", BotState::BOT_STATE_COMBAT))
//     {
//         // add/remove from both for now as it will make it more obvious to
//         // player if this strat remains on after fight somehow
//         botAI->ChangeStrategy("-move from group", BOT_STATE_NON_COMBAT);
//         botAI->ChangeStrategy("-move from group", BOT_STATE_COMBAT);
//         return true;
//     }
//     return false;
// }
