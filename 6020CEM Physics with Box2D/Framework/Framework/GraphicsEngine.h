#pragma once
#include <SFML/Graphics.hpp>

class GraphicsEngine
{    
    //this stores the game engine window
    sf::RenderWindow window;

public:

    GraphicsEngine();

    ~GraphicsEngine();

    //this is only called once and it creates and returns the Game Engine Window
    sf::RenderWindow* InitializeWindow(float width, float height);

    void Render();

    sf::RenderWindow* GetEngineWindow();
};

