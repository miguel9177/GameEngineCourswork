#include "SB_TestScript.h"
#include <iostream>
#include "../GameObject.h"

SB_TestScript::SB_TestScript() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

void SB_TestScript::Start()
{
	//std::cout << "Started test script for gameobject named " << gameObject->name << std::endl;
}

void SB_TestScript::Update()
{
	//std::cout << "Updated test script for gameobject named " << gameObject->name << std::endl;
}
