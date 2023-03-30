#pragma once
#include "../ScriptBehaviour.h"
#include <functional>
class SB_CharacterWeapon : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10005;
	std::function<void()> mousePressCallback;
	GameObject* bullet;
	float timer = 0;
public:
#pragma region Engine Functions

	SB_CharacterWeapon();
	~SB_CharacterWeapon();
	void Start() override;
	void Update() override;
	void LateStart() override;

	inline SB_CharacterWeapon* Clone() override
	{
		return new SB_CharacterWeapon(*this);
	}

#pragma endregion

	void WeaponShot();
};

