#pragma once
#include "../ScriptBehaviour.h"

class SB_BulletFunctionality : public ScriptBehaviour
{
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 10006;

public:
#pragma region Engine Functions

	SB_BulletFunctionality();
	//starts, runs once when the component is added to the object
	void Start() override;
	//updates every frame
	void Update() override;
	//late start is runned once at the beigining of the gameplay, if the script is added at runtime, this wont be called 
	void LateStart() override;
	//on collision
	void BeginContact(b2Contact* contact) override;
	//on end collision
	void EndContact(b2Contact* contact) override;

	//this lets the script loader manager to create a instance of this script
	inline SB_BulletFunctionality* Clone() override
	{
		return new SB_BulletFunctionality(*this);
	}
#pragma endregion
};