#include "MpLogger.h"
#include "ScriptMgr.h"

// make sure this is the new way to do this, i think it's the old busted shit
class MythicPlus_CommandScript : public CommandScript
{
public:
    MythicPlus_CommandScript() : CommandScript("MythicPlus_CommandScript")
    {
    }



};

void Add_MP_CommandScripts()
{
    MpLogger::debug("Add_MP_CommandScripts()");
}