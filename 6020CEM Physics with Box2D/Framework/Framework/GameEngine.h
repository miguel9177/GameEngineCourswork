#pragma once
#include "PhysicsEngine.h"
#include "GraphicsEngine.h"
#include "InputsEngine.h"

class GameEngine
{
    sf::RenderWindow* gameEngineWindow;

public:
    //game engine constructor
    GameEngine(float windowWidth, float windowHeight);

    ~GameEngine();

    void Update();

    void Render();

    //this returns if the game engine is running
    bool isGameEngineRunning();

};

