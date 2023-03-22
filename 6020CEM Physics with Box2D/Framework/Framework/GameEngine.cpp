#include "GameEngine.h"
#include "EngineFunctionalityManager.h"

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
        InputsEngine::GetInstance()->ReceiveInputFromWindow(windowEvents);
    }    
}