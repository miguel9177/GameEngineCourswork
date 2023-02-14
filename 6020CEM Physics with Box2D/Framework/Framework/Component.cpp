#include "Component.h"

Component::Component(typeOfComponent typeOfComponent_)
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