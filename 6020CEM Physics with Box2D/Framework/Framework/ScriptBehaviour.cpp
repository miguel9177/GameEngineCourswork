#include "ScriptBehaviour.h"
#include <iostream>

ScriptBehaviour::ScriptBehaviour(unsigned int uniqueIdIdentifier_) : Component(Component::typeOfComponent::ScriptBehaviour, uniqueIdIdentifier_)
{
	
}

void ScriptBehaviour::Start()
{
}

void ScriptBehaviour::Update()
{
}

void ScriptBehaviour::BeginContact(b2Contact* contact)
{
	
}

void ScriptBehaviour::EndContact(b2Contact* contact)
{
}
