#pragma once
#include "../ScriptBehaviour.h"

class SB_CameraFollowPlayer : public ScriptBehaviour
{
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 10003;
public:
#pragma region Engine Functions

	SB_CameraFollowPlayer();
	//starts, runs once when the component is added to the object
	void Start() override;
	//updates every frame
	void Update() override;

	//this lets the script loader manager to create a instance of this script
	inline SB_CameraFollowPlayer* Clone() override
	{
		return new SB_CameraFollowPlayer(*this);
	}

#pragma endregion

};