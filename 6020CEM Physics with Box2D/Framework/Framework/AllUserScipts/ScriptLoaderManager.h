#pragma once
#include "../ScriptBehaviour.h"
#include <vector>

//this class stores all user scripts, this lets the engine json reader have access to the user made scripts
class ScriptLoaderManager
{
private:
	//stores an instance of all user scripts
	std::vector<ScriptBehaviour*> allUserScriptBehaviours;

	//since this is a singleton we need an instance of it
	static ScriptLoaderManager* instance;

	ScriptLoaderManager();

	~ScriptLoaderManager();

public:
	//this gives the instance of the ScriptLoaderManager engine, and if theres no instance of it, it creates one
	static ScriptLoaderManager* GetInstance();

	//this gets the requested script
	ScriptBehaviour* GetScript(unsigned int uniqueIdIdentifier);

	//AS A USER PLEASE ADD ALL YOUR SCRIPTS IN HERE
	void InitializeVectorOfScripts();
	
};

