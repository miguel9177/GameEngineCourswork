#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::instance;

GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{

}


GraphicsEngine* GraphicsEngine::GetInstance()
{
    if (!instance)
    {
        instance = new GraphicsEngine();
    }
    return instance;
}

sf::RenderWindow* GraphicsEngine::InitializeWindow(float width, float height)
{
    gameEngineWindow.create(sf::VideoMode(width, height), "Vami Reloaded Engine");
    return &gameEngineWindow;
}

void GraphicsEngine::Render()
{
    // Clear the window
    gameEngineWindow.clear(sf::Color::Black);

    // Display the window
    gameEngineWindow.display();
}

sf::RenderWindow* GraphicsEngine::GetEngineWindow()
{
    return &gameEngineWindow;
}