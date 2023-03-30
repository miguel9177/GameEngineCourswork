#include "ScriptLoaderManager.h"
#include "SB_TestScript.h"
#include "SB_CameraFollowPlayer.h"
#include "SB_CharacterMovement.h"
#include "SB_MultiplayerServerClient.h"
#include "SB_CharacterWeapon.h"
#include "SB_BulletFunctionality.h"
#include <iostream>

ScriptLoaderManager* ScriptLoaderManager::instance;

ScriptLoaderManager::ScriptLoaderManager()
{
}

ScriptLoaderManager::~ScriptLoaderManager()
{
    for (ScriptBehaviour* currentScript : allUserScriptBehaviours) {
        delete currentScript;
    }
    allUserScriptBehaviours.clear();
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
ScriptBehaviour* ScriptLoaderManager::GetScript(unsigned int uniqueIdIdentifier)
{
    for (ScriptBehaviour* currentScript : allUserScriptBehaviours)
    {
        if (currentScript->GetUniqueIdIdentifier() == uniqueIdIdentifier)
            return currentScript->Clone();
    }
    std::cout << "ERROR: unique id given does not represent a real script, probably the user forgot to add the script to the InitializeVectorOfScripts function" << std::endl;
    return nullptr;
}

////////////////////
//USER PLEASE ADD ALL OF YOUR SCRIPTS IN HERE, JUST PUSH AN EMPTY VERSION OF THEM AND THE ENGINE DOES THE REST
void ScriptLoaderManager::InitializeVectorOfScripts()
{
    allUserScriptBehaviours.push_back(new SB_TestScript());
    allUserScriptBehaviours.push_back(new SB_CharacterMovement());
    allUserScriptBehaviours.push_back(new SB_CameraFollowPlayer());
    allUserScriptBehaviours.push_back(new SB_MultiplayerServerClient());
    allUserScriptBehaviours.push_back(new SB_CharacterWeapon());
    allUserScriptBehaviours.push_back(new SB_BulletFunctionality());
}
////////////////////