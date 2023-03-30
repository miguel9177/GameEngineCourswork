#pragma once
#include "PhysicsEngine.h"
#include "GraphicsEngine.h"
#include "InputsEngine.h"

class GameEngine
{
private:
    //this returns the instance of the gameengine, sincce this is a singleton
    static GameEngine* instance;
    //stores the graphics engine 
    GraphicsEngine* graphicsEngine;
    //stores the window events
    sf::Event windowEvents;

    //game engine constructor
    GameEngine();
    ~GameEngine();

    //this will update the window events
    void GameEngine::UpdateWindowEvents();
    
public:

    //if this is true it means we are in debug mode
    bool isDebugMode = false;

    //this gives the instance of the Game engine, and if theres no instance of it, it creates one
    static GameEngine* GetInstance();

    //this intializes the engine (only runed once)
    void InitializeEngine(float width, float height);

    //this updates the engine (runs every frame)
    void Update();

    //this renders the engine (runs every frame)
    void Render();

    //this returns true if the game engine is running
    bool isGameEngineRunning();

    //this gets the window size
    inline sf::Vector2u GetWindowSize() { return graphicsEngine->GetEngineWindow()->getSize(); };
    //this allows for the user to move the camera
    void MoveCamera(Vector2 _newPos);
    //this returns the camera world position
    Vector2 GetCameraPosition();
    //this returns the camera sfml position
    Vector2 GetCameraSfmlPosition();
    //this returns the camera size
    Vector2 GetCameraSize();
    
};

