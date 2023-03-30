#pragma once
#include "../ScriptBehaviour.h"

class SB_BulletFunctionality : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10006;

public:
#pragma region Engine Functions

	SB_BulletFunctionality();
	void Start() override;
	void Update() override;
	void LateStart() override;
	inline SB_BulletFunctionality* Clone() override
	{
		return new SB_BulletFunctionality(*this);
	}

#pragma endregion
};