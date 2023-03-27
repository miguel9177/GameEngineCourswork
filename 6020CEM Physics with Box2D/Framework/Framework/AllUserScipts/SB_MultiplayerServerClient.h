#pragma once
#include "../ScriptBehaviour.h"
#include "../Vector2.h"

class SB_MultiplayerServerClient : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10004;
	
public:
#pragma region Engine Functions

	SB_MultiplayerServerClient();
	void Start() override;
	void Update() override;

	inline SB_MultiplayerServerClient* Clone() override
	{
		return new SB_MultiplayerServerClient(*this);
	}

#pragma endregion
};

