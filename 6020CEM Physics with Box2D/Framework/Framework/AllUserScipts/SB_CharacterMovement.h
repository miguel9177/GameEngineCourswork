#pragma once
#include "../ScriptBehaviour.h"
#include "../Vector2.h"

class RigidBody;
class AudioPlayer;
class SB_CharacterMovement : public ScriptBehaviour
{
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 10002;
	//stores the user input
	Vector2 characterUserInput;
	//stores the rb of the gamoeobjec
	RigidBody* rb;
	//stores an audio source
	AudioPlayer* audioSource;
	//stores the amount of force to apply when moving
	float amountOfForceToApply = 0.1f;
public:
#pragma region Engine Functions

	SB_CharacterMovement();
	//starts, runs once when the component is added to the object
	void Start() override;
	//updates every frame
	void Update() override;

	//this lets the script loader manager to create a instance of this script
	inline SB_CharacterMovement* Clone() override
	{
		return new SB_CharacterMovement(*this);
	}

#pragma endregion

	//called back at mouse press
	void LeftMousePressed();
};