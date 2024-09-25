#include "MapMgr.h"
#include "MpDataStore.h"
#include "ObjectMgr.h"
#include "MpLogger.h"
#include "MythicPlus.h"
#include "ScriptMgr.h"
#include "Log.h"

class MythicPlus_AllCreatureScript : public AllCreatureScript
{
public:
    MythicPlus_AllCreatureScript() : AllCreatureScript("MythicPlus_AllCreatureScript")
    {

    }

    // void OnBeforeCreatureSelectLevel(const CreatureTemplate* /*creatureTemplate*/, Creature* creature, uint8& level) override
    // {
    // }

    // When a new creature is added into a mythic+ map add it to the list of creatures to scale later.
    void OnCreatureAddWorld(Creature* creature) override
    {
        Map* map = creature->GetMap();
        if (!sMythicPlus->IsMapEligible(map)) {
            // MpLogger::debug("Map: {} is not eligible to adjust so creature was skipped: Creature {}", map->GetMapName(), creature->GetName());
            return;
        }

        // if we have instance data about zone then just scale the creature otherwise add to be scaled once we do.
        MpInstanceData* instanceData = sMpDataStore->GetInstanceData(map->GetId(), map->GetInstanceId());
        if(instanceData) {
            sMythicPlus->AddScaledCreature(creature, instanceData);
        } else {
            sMythicPlus->AddCreatureForScaling(creature);
        }
    }

    // void OnAllCreatureUpdate(Creature* creature, uint32 diff) override
    // {
    // }

    // Cleanup the creature from custom data used for mythic+ mod
    void OnCreatureRemoveWorld(Creature* creature) override
    {
        sMythicPlus->RemoveCreature(creature);
    }
};

void Add_MP_AllCreatureScripts()
{
    MpLogger::debug("Add_MP_AllCreatureScripts");
    new MythicPlus_AllCreatureScript();
}
