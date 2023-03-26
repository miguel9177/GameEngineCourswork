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

    //Creates the camera view
    cameraView = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    //make the window use the new created view
    window.setView(cameraView);
    MoveCamera(Vector2(0, 0));
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
            window.draw(*mesh->Debug_GetOriginPointToRender());
        }
    }

    //if we are on debug mode, draw the colliders and the origin points of the meshes
    if (GameEngine::GetInstance()->isDebugMode)
        DrawDebugModeInformation();

    UiEngine::GetInstance()->DrawAllUi(&window);

    if(GameEngine::GetInstance()->isDebugMode)
        Debug_WriteDebugInformation();

    // Display the window
    window.display();
}

sf::RenderWindow* GraphicsEngine::GetEngineWindow()
{
    return &window;
}

#pragma region Functionality functions

//this moves the camera to the selected position
void GraphicsEngine::MoveCamera(Vector2 _newPos)
{
    cameraPos = _newPos;
    cameraView.setCenter(_newPos * 200);
    //cameraView.move(_newPos);
    window.setView(cameraView);
}

Vector2 GraphicsEngine::GetCameraPosition()
{
    return cameraPos;
}

Vector2 GraphicsEngine::GetCameraSfmlPosition()
{
    return Vector2(cameraView.getCenter().x, cameraView.getCenter().y);
}

Vector2 GraphicsEngine::GetCameraSize()
{
    return Vector2(cameraView.getSize().x, cameraView.getSize().y);
}

void GraphicsEngine::SetCameraSize(Vector2 _newSize)
{
    cameraView.setSize(_newSize.x, _newSize.y);
}

void GraphicsEngine::SetCameraViewPort(sf::FloatRect _newViewPort)
{
    cameraView.setViewport(_newViewPort);
}

#pragma endregion

#pragma region Debug

void GraphicsEngine::DrawDebugModeInformation()
{
    //if the mesh has a rigidbody, draw the colliders
    for (std::vector<RigidBody*>::iterator it = Scene::GetInstance()->GetAllRigidBodys()->begin(); it != Scene::GetInstance()->GetAllRigidBodys()->end(); ++it)
    {
        RigidBody* rb = *it;
        b2Fixture* fixture = rb->Debug_GetB2Body()->GetFixtureList();
        Debug_DrawCollider(fixture, sf::Color::Green);
    }
    //goes through every mesh on the scene and draws it
    for (std::vector<Com_Mesh*>::iterator it = Scene::GetInstance()->GetAllMeshes()->begin(); it != Scene::GetInstance()->GetAllMeshes()->end(); ++it)
    {
        Com_Mesh* mesh = *it;
        //if the mesh has a shape
        if (mesh->GetShape() != nullptr)
        {
            //draw the origin point
            window.draw(*mesh->Debug_GetOriginPointToRender());
        }
    }
}

void GraphicsEngine::Debug_WriteDebugInformation()
{
#pragma region Drawing Garbage Collection Information Text
    {
        //this creates a new text object that will store the memory management information
        sf::Text garbageCollectionText;
        garbageCollectionText.setFont(gameEngineFont);
        garbageCollectionText.setString(GarbageCollector::GetMemoryUsageText());
        garbageCollectionText.setCharacterSize(15);
        garbageCollectionText.setFillColor(sf::Color::Black);
        garbageCollectionText.setStyle(sf::Text::Regular);

        //this positions the text at the top right corner
        float textRightPadding = 20; 
        Vector2 txtPosition = Vector2(window.getSize().x - garbageCollectionText.getLocalBounds().width - textRightPadding, textRightPadding);
        //adjust the position of the ui depending on the camera position
        txtPosition.x += cameraView.getCenter().x - window.getSize().x / 2.0f;
        txtPosition.y += cameraView.getCenter().y - window.getSize().y / 2.0f;
        garbageCollectionText.setPosition(txtPosition.x, txtPosition.y);

        window.draw(garbageCollectionText);
    }
#pragma endregion
}

#pragma endregion

