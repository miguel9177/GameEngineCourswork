#pragma once
#include "../ScriptBehaviour.h"
#include "../Vector2.h"

class RigidBody;
class SB_CharacterMovement : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10002;
	Vector2 characterUserInput;
	RigidBody* rb;
	float amountOfForceToApply = 0.1f;
public:
#pragma region Engine Functions

	SB_CharacterMovement();
	void Start() override;
	void Update() override;

	inline SB_CharacterMovement* Clone() override
	{
		return new SB_CharacterMovement(*this);
	}

#pragma endregion

};