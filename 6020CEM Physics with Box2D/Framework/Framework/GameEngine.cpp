#include "GameEngine.h"
#include "EngineFunctionalityManager.h"
#include "UiEngine.h"
#include "Scene.h"

GameEngine* GameEngine::instance;

GameEngine::GameEngine()
{
	//create the graphics engine window
    graphicsEngine = new GraphicsEngine();
}

GameEngine::~GameEngine()
{

}

GameEngine* GameEngine::GetInstance()
{
    if (!instance)
    {
        instance = new GameEngine();
    }
    return instance;
}

void GameEngine::InitializeEngine(float width, float height)
{
    graphicsEngine->InitializeWindow(width, height);
    EngineFunctionalityManager::GetInstance();
}

void GameEngine::Update()
{
    UpdateWindowEvents();
    PhysicsEngine::GetInstance()->Update();
    InputsEngine::GetInstance()->Update(graphicsEngine->GetEngineWindow());
    UiEngine::GetInstance()->Update();
    Scene::GetInstance()->Update();
}

void GameEngine::Render()
{
    graphicsEngine->Render();
}

bool GameEngine::isGameEngineRunning()
{
    if (!graphicsEngine->GetEngineWindow()->isOpen())
       return false;

    return true;
}

void GameEngine::UpdateWindowEvents()
{
    InputsEngine::GetInstance()->ClearInputsReceivedFromWindow();

    while (graphicsEngine->GetEngineWindow()->pollEvent(windowEvents))
    {
        if (windowEvents.type == sf::Event::Resized)
        {
            //since the camera has been resized, we get the new width and new height, and resize it
            float newCameraWidth = windowEvents.size.width;
            float newCameraHeight = windowEvents.size.height;
            graphicsEngine->SetCameraSize(Vector2(newCameraWidth, newCameraHeight));
        }
        InputsEngine::GetInstance()->ReceiveInputFromWindow(windowEvents);
    }    
}

#pragma region public functionality functions

void GameEngine::MoveCamera(Vector2 _newPos)
{
    graphicsEngine->MoveCamera(_newPos);
}

Vector2 GameEngine::GetCameraPosition()
{
    return graphicsEngine->GetCameraPosition();
}

Vector2 GameEngine::GetCameraSize()
{
    return graphicsEngine->GetCameraSize();
}
#pragma endregion
