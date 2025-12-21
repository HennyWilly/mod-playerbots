#include "RaidBwlHelpers.h"

#include "Playerbots.h"

static constexpr float SUPPRESSION_DEVICE_DISTANCE = 15.0f;
static constexpr float RAZORGORE_EGG_CHECK_DISTANCE = 200.0f;

namespace BwlHelpers
{
    bool AreRazorgoreEggsAlive(const Player* bot)
    {
        return bot->FindNearestGameObject(GO_BLACK_DRAGON_EGG, RAZORGORE_EGG_CHECK_DISTANCE, true);
    }

    GameObject* GetSuppressionDeviceWithinRange(PlayerbotAI* botAI)
    {
        for (auto const& objectGuid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest game objects")->Get())
        {
            if (GameObject* go = botAI->GetGameObject(objectGuid))
            {
                if (go->GetEntry() == GO_SUPPRESSION_DEVICE &&
                    go->GetDistance(botAI->GetBot()) < SUPPRESSION_DEVICE_DISTANCE &&
                    go->GetGoState() == GO_STATE_READY)
                    return go;
            }
        }
        return nullptr;
    }
}
