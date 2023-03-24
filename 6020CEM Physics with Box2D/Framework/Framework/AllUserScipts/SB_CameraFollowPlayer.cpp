#include "SB_CameraFollowPlayer.h"
#include "../GameEngine.h"

SB_CameraFollowPlayer::SB_CameraFollowPlayer() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

void SB_CameraFollowPlayer::Start()
{
}

void SB_CameraFollowPlayer::Update()
{
	GameEngine::GetInstance()->MoveCamera(gameObject->GetPosition());
}
