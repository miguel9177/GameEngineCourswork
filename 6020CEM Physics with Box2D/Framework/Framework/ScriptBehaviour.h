#pragma once
#include "Component.h"

class ScriptBehaviour : public Component
{
public:
	static const unsigned int minimumUniqueComponentIdIdentifier = 10000;
	/// <summary>
	/// script behaviour constructor that accepts a unique id identifier that goes from 10000 to infinity
	/// </summary>
	/// <param name="uniqueIdIdentifier_">In here put a unique script id, CANT BE REPEATED, goes from 10000 to infinity</param>
	ScriptBehaviour(unsigned int uniqueIdIdentifier_);
	virtual void Start();
	virtual void Update();
	virtual ScriptBehaviour* Clone() = 0;
};

