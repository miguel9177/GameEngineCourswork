#include "SB_CameraFollowPlayer.h"
#include "../GameEngine.h"

SB_CameraFollowPlayer::SB_CameraFollowPlayer() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

//starts, runs once when the component is added to the object
void SB_CameraFollowPlayer::Start()
{
}

//updates every frame
void SB_CameraFollowPlayer::Update()
{
	//moves the camera to the player position
	GameEngine::GetInstance()->MoveCamera(gameObject->GetPosition());
}
