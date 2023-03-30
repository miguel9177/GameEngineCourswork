#pragma once
#include "../ScriptBehaviour.h"

class SB_CharacterWeapon : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10005;

	void WeaponShot();
public:
#pragma region Engine Functions

	SB_CharacterWeapon();
	void Start() override;
	void Update() override;
	void LateStart() override;

	inline SB_CharacterWeapon* Clone() override
	{
		return new SB_CharacterWeapon(*this);
	}

#pragma endregion

};

