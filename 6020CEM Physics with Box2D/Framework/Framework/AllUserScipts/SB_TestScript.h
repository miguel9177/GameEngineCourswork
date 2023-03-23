#pragma once
#include "../ScriptBehaviour.h"

class SB_TestScript : public ScriptBehaviour
{
	static const unsigned int uniqueComponentIdIdentifier = 10001;
public:
	SB_TestScript();
	void Start() override;
	void Update() override;

	inline SB_TestScript* Clone() override 
	{
		return new SB_TestScript(*this);
	}
};

