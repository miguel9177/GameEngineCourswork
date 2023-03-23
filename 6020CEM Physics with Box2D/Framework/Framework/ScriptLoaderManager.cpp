#include "ScriptLoaderManager.h"
#include "AllUserScipts/SB_TestScript.h"

ScriptLoaderManager* ScriptLoaderManager::instance;

ScriptLoaderManager::ScriptLoaderManager()
{
}

ScriptLoaderManager::~ScriptLoaderManager()
{
}

ScriptLoaderManager* ScriptLoaderManager::GetInstance()
{
    if (!instance)
    {
        instance = new ScriptLoaderManager();
    }
    return instance;
}

//this gets the script requested (not for user interaction)
ScriptBehaviour ScriptLoaderManager::GetScript(unsigned int uniqueIdIdentifier)
{
    for (ScriptBehaviour currentScript : allUserScriptBehaviours)
    {
        if (currentScript.GetUniqueIdIdentifier() == uniqueIdIdentifier)
            return currentScript;
    }
}

////////////////////
//USER PLEASE ADD ALL OF YOUR SCRIPTS IN HERE, JUST PUSH AN EMPTY VERSION OF THEM AND THE ENGINE DOES THE REST
void ScriptLoaderManager::InitializeVectorOfScripts()
{
    allUserScriptBehaviours.push_back(SB_TestScript());
}
////////////////////