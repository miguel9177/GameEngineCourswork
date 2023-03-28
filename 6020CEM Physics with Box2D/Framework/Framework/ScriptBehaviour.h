#pragma once
#include "Component.h"
#include "GameObject.h"

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
	//waits for everyobject to be called and calls the late start, if the gameobject is created in runtime the late start will never be called to that gameobject
	virtual void LateStart(){};
	virtual ScriptBehaviour* Clone() = 0;
};

