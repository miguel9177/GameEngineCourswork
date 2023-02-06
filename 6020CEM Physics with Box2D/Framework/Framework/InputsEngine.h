#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicsEngine.h"

//this is a singleton, and stores the Inputs Engine script
class InputsEngine
{
 private:
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event events;
    static InputsEngine* instance;

    InputsEngine();
    ~InputsEngine();
public:
    //this gives the instance of the inputs engine, and if theres no instance of it, it creates one
    static InputsEngine* GetInstance();

    void Update();

    sf::Event GetEvents();
};


