#pragma once
#include "Component.h"
#include "GameObject.h"
#include <Box2D/Box2D.h>

//this is a parent of all the user scripts
class ScriptBehaviour : public Component, public b2ContactListener
{
public:
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int minimumUniqueComponentIdIdentifier = 10000;
	/// <summary>
	/// script behaviour constructor that accepts a unique id identifier that goes from 10000 to infinity
	/// </summary>
	/// <param name="uniqueIdIdentifier_">In here put a unique script id, CANT BE REPEATED, goes from 10000 to infinity</param>
	ScriptBehaviour(unsigned int uniqueIdIdentifier_);
	//starts, runs once when the component is added to the object
	virtual void Start();
	//updates every frame
	virtual void Update();
	//waits for everyobject to be called and calls the late start, if the gameobject is created in runtime the late start will never be called to that gameobject
	virtual void LateStart(){};
	//this lets the script loader manager to create a instance of this script
	virtual ScriptBehaviour* Clone() = 0;

	//on collision enter
	virtual void BeginContact(b2Contact* contact) override;
	//on collision exit
	virtual void EndContact(b2Contact* contact) override;
};

