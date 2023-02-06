#include "GameEngine.h"

GameEngine::GameEngine(float windowWidth, float windowHeight)
{
	//create the graphics engine window
	gameEngineWindow = GraphicsEngine::GetInstance()->InitializeWindow(windowWidth, windowHeight);
}

GameEngine::~GameEngine()
{

}

void GameEngine::Update()
{

}

void GameEngine::Render()
{
    //update the graphics engine
    GraphicsEngine::GetInstance()->Render();
}

bool GameEngine::isGameEngineRunning()
{
    if (!gameEngineWindow->isOpen())
        return false;

    return true;
}