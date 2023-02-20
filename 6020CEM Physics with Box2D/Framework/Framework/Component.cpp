#include "Component.h"

Component::Component(typeOfComponent typeOfComponent_, const unsigned int _uniqueComponentIdIdentifier) : uniqueComponentIdIdentifier(_uniqueComponentIdIdentifier)
{
	enabled = true;
	componentType = typeOfComponent_;

}


Component::~Component()
{
}

void Component::Start()
{
}

Component::typeOfComponent Component::GetTypeOfComponent()
{
	return componentType;
}

//this returns the unique component id identifier
const unsigned int Component::GetUniqueIdIdentifier()
{
	return uniqueComponentIdIdentifier;
}