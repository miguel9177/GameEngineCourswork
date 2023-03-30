#pragma once
#include "../ScriptBehaviour.h"

class SB_CameraFollowPlayer : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10003;
public:
#pragma region Engine Functions

	SB_CameraFollowPlayer();
	void Start() override;
	void Update() override;

	inline SB_CameraFollowPlayer* Clone() override
	{
		return new SB_CameraFollowPlayer(*this);
	}

#pragma endregion

};