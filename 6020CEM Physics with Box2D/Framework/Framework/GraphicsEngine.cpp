#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{

}

sf::RenderWindow* GraphicsEngine::InitializeWindow(float width, float height)
{
    window.create(sf::VideoMode(width, height), "Vami Reloaded Engine");
    return &window;
}

void GraphicsEngine::Render()
{
    // Clear the window
    window.clear(sf::Color::Black);

    // Display the window
    window.display();
}

sf::RenderWindow* GraphicsEngine::GetEngineWindow()
{
    return &window;
}