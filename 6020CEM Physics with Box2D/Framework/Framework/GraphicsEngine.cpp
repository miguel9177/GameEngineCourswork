#include "GraphicsEngine.h"
#include <iostream>
#include "Scene.h"
#include "Com_Mesh.h"
#include "RigidBody.h"

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
    window.clear(sf::Color::Black);

    //goes through every mesh on the scene and draws it
    for (std::vector<Com_Mesh*>::iterator it = Scene::GetInstance()->GetAllMeshes()->begin(); it != Scene::GetInstance()->GetAllMeshes()->end(); ++it) 
    {
        Com_Mesh* mesh = *it;
        
        //if the mesh has a shape
        if (mesh->GetShape() != nullptr)
        {
            //draw the mesh
            window.draw(*mesh->GetMeshToRender());
            
            //if we are on debug mode, draw the colliders and the origin points of the meshes
            if (GameEngine::GetInstance()->isDebugMode) 
            {
                b2Fixture* fixture = mesh->gameObject->TryGetRigidBody()->Debug_GetB2Body()->GetFixtureList();
                Debug_DrawCollider(fixture, sf::Color::Green);
                window.draw(*mesh->Debug_GetOriginPointToRender());
            }
        }
    }

    // Display the window
    window.display();
}

sf::RenderWindow* GraphicsEngine::GetEngineWindow()
{
    return &window;
}