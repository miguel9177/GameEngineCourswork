#pragma once
#include "../ScriptBehaviour.h"
#include <functional>
class SB_CharacterWeapon : public ScriptBehaviour
{
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 10005;
	//stores the mouse press callback function
	std::function<void()> mousePressCallback;
	//stores the bullet gameobject
	GameObject* bullet;
	//stores the timer
	float timer = 0;
public:
#pragma region Engine Functions

	SB_CharacterWeapon();
	~SB_CharacterWeapon();
	//starts, runs once when the component is added to the object
	void Start() override;
	//updates every frame
	void Update() override;
	//late start is runned once at the beigining of the gameplay, if the script is added at runtime, this wont be called 
	void LateStart() override;

	//this lets the script loader manager to create a instance of this script
	inline SB_CharacterWeapon* Clone() override
	{
		return new SB_CharacterWeapon(*this);
	}

#pragma endregion

	//this will be called at the mouse clicked
	void WeaponShot();
};

