#pragma once
#include <SFML/Graphics.hpp>
//this is a singleton, and stores the graphics engine script
class GraphicsEngine
{
private:
    static GraphicsEngine* instance;
    
    //this stores the game engine window
    sf::RenderWindow gameEngineWindow;

    GraphicsEngine();

    ~GraphicsEngine();

public:

    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static GraphicsEngine* GetInstance();
   
    //this is only called once and it creates and returns the Game Engine Window
    sf::RenderWindow* InitializeWindow(float width, float height);

    void Render();

    sf::RenderWindow* GetEngineWindow();
};

