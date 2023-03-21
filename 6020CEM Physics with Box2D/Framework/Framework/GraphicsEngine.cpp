#include "GraphicsEngine.h"
#include <iostream>
#include "Scene.h"
#include "Com_Mesh.h"
#include "RigidBody.h"
#include "GarbageCollector.h"
#include "UiEngine.h"

sf::Font GraphicsEngine::gameEngineFont;


GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{

}

sf::RenderWindow* GraphicsEngine::InitializeWindow(float width, float height)
{
    window.create(sf::VideoMode(width, height), "Vami Reloaded Engine");

    if (!gameEngineFont.loadFromFile("../TextFonts/Roboto-Regular.ttf"))
    {
        std::cout << "Font did not load!" << "\n" << std::endl;
    }

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
            UiEngine::GetInstance()->DrawAllUi(&window);
            
            //if we are on debug mode, draw the colliders and the origin points of the meshes
            if (GameEngine::GetInstance()->isDebugMode) 
            {
                b2Fixture* fixture = mesh->gameObject->TryGetRigidBody()->Debug_GetB2Body()->GetFixtureList();
                Debug_DrawCollider(fixture, sf::Color::Green);
                window.draw(*mesh->Debug_GetOriginPointToRender());
                Debug_WriteDebugInformation();
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

#pragma region Debug

void GraphicsEngine::Debug_WriteDebugInformation()
{
#pragma region Drawing Garbage Collection Information Text
    {
        //this creates a new text object that will store the memory management information
        sf::Text garbageCollectionText;
        garbageCollectionText.setFont(gameEngineFont);
        garbageCollectionText.setString(GarbageCollector::GetMemoryUsageText());
        garbageCollectionText.setCharacterSize(15);
        garbageCollectionText.setFillColor(sf::Color::Green);
        garbageCollectionText.setStyle(sf::Text::Regular);

        //this positions the text at the top right corner
        float textRightPadding = 20; 
        garbageCollectionText.setPosition(window.getSize().x - garbageCollectionText.getLocalBounds().width - textRightPadding, textRightPadding);

        window.draw(garbageCollectionText);
    }
#pragma endregion
}

#pragma endregion

