#include "GraphicsEngine.h"
#include <iostream>
#include "Scene.h"
#include "Com_Mesh.h"

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

    // Iterate through allMeshes
    for (std::vector<Com_Mesh*>::iterator it = Scene::GetInstance()->GetAllMeshes()->begin(); it != Scene::GetInstance()->GetAllMeshes()->end(); ++it) 
    {
        // do something with each Com_Mesh in the vector
        Com_Mesh* mesh = *it;
        
        //std::cout << mesh->gameObject->name;
        if(mesh->GetShape() != nullptr)
            window.draw(*mesh->GetMeshToRender());
    }

    // Display the window
    window.display();
}

sf::RenderWindow* GraphicsEngine::GetEngineWindow()
{
    return &window;
}