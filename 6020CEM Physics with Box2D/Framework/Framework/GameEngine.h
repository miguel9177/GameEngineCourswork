#pragma once
#include "PhysicsEngine.h"
#include "GraphicsEngine.h"
#include "InputsEngine.h"

class GameEngine
{
private:
    static GameEngine* instance;
    GraphicsEngine* graphicsEngine;
    sf::Event windowEvents;

    //game engine constructor
    GameEngine();
    ~GameEngine();

    //this will update the window events
    void GameEngine::UpdateWindowEvents();

public:

    bool isDebugMode = false;

    //this gives the instance of the Game engine, and if theres no instance of it, it creates one
    static GameEngine* GetInstance();

    void InitializeEngine(float width, float height);

    void Update();

    void Render();

    //this returns if the game engine is running
    bool isGameEngineRunning();

    inline sf::Vector2u GetWindowSize() { return graphicsEngine->GetEngineWindow()->getSize(); };
};

