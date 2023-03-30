#include "GameEngine.h"
#include "EngineFunctionalityManager.h"
#include "UiEngine.h"
#include "Scene.h"
#include "AllUserScipts/ScriptLoaderManager.h"
#include "EngineJsonReader.h"

GameEngine* GameEngine::instance;

GameEngine::GameEngine()
{
	//create the graphics engine window
    graphicsEngine = new GraphicsEngine();
}

GameEngine::~GameEngine()
{

}

//returns the instance, since this is a singleton
GameEngine* GameEngine::GetInstance()
{
    if (!instance)
    {
        instance = new GameEngine();
    }
    return instance;
}

void GameEngine::InitializeEngine(float width, float height)
{
    //this initializes the graphics engine window
    graphicsEngine->InitializeWindow(width, height);
    //starts the physics world
    PhysicsEngine::GetInstance()->StartPhysicsWorld();
    //gets all user scripts, creating a copy of them, so that then the engine knows which user scripts exist
    ScriptLoaderManager::GetInstance()->InitializeVectorOfScripts();
    //loads the editor scene
    EngineJsonReader::GetInstance()->LoadEditorScene();
    //starts the engine fiunctionality manager
    EngineFunctionalityManager::GetInstance()->Start();
}

void GameEngine::Update()
{
    //updates the window events
    UpdateWindowEvents();
    //updates the physcsi world
    PhysicsEngine::GetInstance()->Update();
    //updates the input engine, since the windoe, since he needs access to it
    InputsEngine::GetInstance()->Update(graphicsEngine->GetEngineWindow());
    //updates the scene (this then calls update on other components
    Scene::GetInstance()->Update();
    //updates the engine functionality
    EngineFunctionalityManager::GetInstance()->Update();
    //updates the ui
    UiEngine::GetInstance()->Update();
}

void GameEngine::Render()
{
    //tells the graphics engine to renders
    graphicsEngine->Render();
}

bool GameEngine::isGameEngineRunning()
{
    //if the graphics engine is not open, we returen false
    if (!graphicsEngine->GetEngineWindow()->isOpen())
       return false;

    return true;
}

void GameEngine::UpdateWindowEvents()
{
    //this clears all the inputs engine input that were received from the window
    InputsEngine::GetInstance()->ClearInputsReceivedFromWindow();

    //thile the window has events to poll
    while (graphicsEngine->GetEngineWindow()->pollEvent(windowEvents))
    {
        //if the event was a resize, we update the camera, so that we dont have an stretched engine
        if (windowEvents.type == sf::Event::Resized)
        {
            //since the camera has been resized, we get the new width and new height, and resize it
            float newCameraWidth = windowEvents.size.width;
            float newCameraHeight = windowEvents.size.height;
            //we change the camera sice to the new width and height
            graphicsEngine->SetCameraSize(Vector2(newCameraWidth, newCameraHeight));

            //if the engine is in edit mode, we move the camera to meet the camera position, this fixes the resizing
            if (EngineFunctionalityManager::GetInstance()->GetEngineState() == EngineFunctionalityManager::State::editMode)
                graphicsEngine->MoveCamera(graphicsEngine->GetCameraPosition());
        }
        //if the window was closed, closse the window
        else if (windowEvents.type == sf::Event::Closed)
            graphicsEngine->GetEngineWindow()->close();

        //sends the window events to the input engine
        InputsEngine::GetInstance()->ReceiveInputFromWindow(windowEvents);
    }    
}

#pragma region public functionality functions

void GameEngine::MoveCamera(Vector2 _newPos)
{
    graphicsEngine->MoveCamera(_newPos);
}

//this gets the camera world position
Vector2 GameEngine::GetCameraPosition()
{
    return graphicsEngine->GetCameraPosition();
}

//this gets the camera sfml position
Vector2 GameEngine::GetCameraSfmlPosition()
{
    return graphicsEngine->GetCameraSfmlPosition();
}

Vector2 GameEngine::GetCameraSize()
{
    return graphicsEngine->GetCameraSize();
}
#pragma endregion
