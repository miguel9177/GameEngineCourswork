#include "EngineFunctionalityManager.h"
#include "UiScreenView_Text.h"
#include "UiScreenView_Image.h"
#include "UiScreenView_btnImage.h"
#include "UiScreenView_btnText.h"
#include "GameEngine.h"
#include "EngineJsonReader.h"
#include "EventQueue.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include "Scene.h"

EngineFunctionalityManager* EngineFunctionalityManager::instance;

EngineFunctionalityManager::EngineFunctionalityManager()
{

    //this subscribes to the left mouse click event, in order for it to call the function UserPressedLeftMouseButton everytime the user presses left mouse button
    std::function<void()> mousePressCallback = std::bind(&EngineFunctionalityManager::LeftMousePressed, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);

    //this subscribes to the left mouse release event, in order for it to call the function LeftMouseReleased everytime the user releases left mouse button
    std::function<void()> mouseReleasedCallback = std::bind(&EngineFunctionalityManager::LeftMouseReleased, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Left, mouseReleasedCallback);

    //this subscribes to the midle mouse click event, in order for it to call the function MiddleMousePressed everytime the user presses midle mouse button
    std::function<void()> midleMousePressCallback = std::bind(&EngineFunctionalityManager::MiddleMousePressed, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Middle, midleMousePressCallback);

    //this subscribes to the midle mouse release event, in order for it to call the function MiddleMouseReleased everytime the user releases midle mouse button
    std::function<void()> midleMouseReleasedCallback = std::bind(&EngineFunctionalityManager::MiddleMouseReleased, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Middle, midleMouseReleasedCallback);
}

EngineFunctionalityManager::~EngineFunctionalityManager()
{
}

//this gets the instance of the engine, since the engine is a singleton
EngineFunctionalityManager* EngineFunctionalityManager::GetInstance()
{
    if (!instance)
    {
        instance = new EngineFunctionalityManager();
    }
    return instance;
}

void EngineFunctionalityManager::Update()
{
    //we leave if we are in play mode, since we dont want to be able to drag neither posiiton the camera on update
    if (state != State::editMode)
        return;

    //if we are dragging an object, move him to mouse pos world
    if (objBeingDragged != nullptr)
    {
        objBeingDragged->SetPosition(InputsEngine::GetInstance()->GetMouseWorldPosition());
    }
    //if we are pressing midle mouse move the camera
    if (InputsEngine::GetInstance()->GetMouseState().pressingMiddleButton)
    {
        GameEngine::GetInstance()->MoveCamera(GameEngine::GetInstance()->GetCameraPosition() + InputsEngine::GetInstance()->GetMouseState().velocity);
    }
}

void EngineFunctionalityManager::Start()
{
    //creates engine ui
    CreateEngineUI();
}

#pragma region Functionality functions

void EngineFunctionalityManager::CreateEngineUI()
{
    //creates the left and top ui
    CreateLeftBarUi();
    CreateTopBarUi();
}

#pragma endregion

#pragma region Event dependent functions

void EngineFunctionalityManager::OnPlayButtonClicked()
{
    //we leve if we are in play mode, since the user can click play mode while already in play mode
    if (state == State::playMode)
        return;
    
    //we change the satte so the engine knows we are in gameplay mode
    state = State::playMode;

    //we restart the physics world, since we are going to load everything again
    PhysicsEngine::GetInstance()->StopPhysicsWorld();
    PhysicsEngine::GetInstance()->StartPhysicsWorld();
    //we invoke the entered play mode event
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::EnteredPlayMode);
    //after all that we load the scene to play
    EngineJsonReader::GetInstance()->LoadSceneToPlay();

    //we change the texture of the play button, so that the user knows we are in play mode
    sf::Texture clickedTexture = sf::Texture();
    clickedTexture.loadFromFile("../Textures/PlayButtonClicked.png");
    uiBtnImg_PlayButton->SetTexture(clickedTexture);

}

void EngineFunctionalityManager::OnDebugButtonClicked()
{
    //if we click on the debug button we change the debug state
    GameEngine::GetInstance()->isDebugMode = !GameEngine::GetInstance()->isDebugMode;

    //if on debug mode, we change the debug mode texture
    if (GameEngine::GetInstance()->isDebugMode)
    {
        sf::Texture clickedTexture = sf::Texture();
        clickedTexture.loadFromFile("../Textures/DebugButtonClicked.png");
        uiBtnImg_DebugButton->SetTexture(clickedTexture);
    }
    //if not debug mode we change the debug button texture
    else
    {
        sf::Texture clickedTexture = sf::Texture();
        clickedTexture.loadFromFile("../Textures/DebugButton.png");
        uiBtnImg_DebugButton->SetTexture(clickedTexture);
    }
}

void EngineFunctionalityManager::OnStopButtonClicked()
{
    //we stop the physics world
    PhysicsEngine::GetInstance()->StopPhysicsWorld();
    //we tell everything that we entered edit mode
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::EnteredEditMode);
    //we restart the engine to avoid memory leaks
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::RestartEngine);
    //we change the state to edit mode
    state = State::editMode;
}

void EngineFunctionalityManager::OnSaveButtonClicked()
{
    std::cout << "Save button pressed " << std::endl;
    //we save the scene on the json file
    EngineJsonReader::GetInstance()->SaveScene();
}

void EngineFunctionalityManager::LeftMousePressed()
{
    //if left moude pressed and edit mode on, get the object being dragged
    if (state == State::editMode)
    {
        objBeingDragged = GetObjectAtMousePos();
    }
}

void EngineFunctionalityManager::LeftMouseReleased()
{
    //if left moude released we put the pointer to null
    objBeingDragged = nullptr;
}

void EngineFunctionalityManager::MiddleMousePressed()
{
    
}

void EngineFunctionalityManager::MiddleMouseReleased()
{

}

void EngineFunctionalityManager::GameObjectButtonClicked(GameObject* _objButtonClicked)
{
    
}

#pragma endregion

#pragma region Helper functions

GameObject* EngineFunctionalityManager::GetObjectAtMousePos()
{
    //we loop through all meshes on the scene
    for (Com_Mesh* currentMesh : *Scene::GetInstance()->GetAllMeshes())
    {
        //get the screen mouse position
        Vector2 screenMousePos = InputsEngine::GetInstance()->GetMouseState().position;
        //get the view center (its basicaly the camera)
        Vector2 viewCenter = GameEngine::GetInstance()->GetCameraSfmlPosition();
        //get the camera size
        Vector2 viewSize = GameEngine::GetInstance()->GetCameraSize();

        //get the world mouse position 
        sf::Vector2f worldMousePos = sf::Vector2f(screenMousePos.x + viewCenter.x - viewSize.x / 2.0f, screenMousePos.y + viewCenter.y - viewSize.y / 2.0f);

        //we get the bounds of the mesh
        sf::FloatRect buttonBounds = currentMesh->GetMeshToRender()->getGlobalBounds();

        //if the bounds of the mesh contain the mouse pos, it meaans we are hovering the mesh, so we return the mesh
        if (buttonBounds.contains(worldMousePos))
            return currentMesh->gameObject;
    }
    return nullptr;
}

//we create the top bar ui
void EngineFunctionalityManager::CreateTopBarUi()
{
    //this creates the top navbar
    sf::Texture* ui_TopWhiteNavbar = new sf::Texture();
    if (!ui_TopWhiteNavbar->loadFromFile("../Textures/Navbar.png"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }
    UiScreenView_Image* uiImg_TopNavbar = new UiScreenView_Image(ui_TopWhiteNavbar, new Transform(Vector2(0.5f, 0), 0, Vector2(40, 1.5)));
    uiImg_TopNavbar->SetUiPosition(Vector2(0.5f, 0), Vector2(0, 38));
    uiImg_TopNavbar->AddUiToScreen();


#pragma region Creation of 4 UI buttons (Play, Debug, Stop, Save Button)

    {
        //this code creates a new button in this case the play button
        sf::Texture* uiTexture_PlayButton = new sf::Texture();
        if (!uiTexture_PlayButton->loadFromFile("../Textures/PlayButton.png"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }
        uiBtnImg_PlayButton = new UiScreenView_btnImage(uiTexture_PlayButton, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)));
        uiBtnImg_PlayButton->SetUiPosition(Vector2(0.5f, 0), Vector2(-25, 38));
        //this subscribes to the on play button press callback
        std::function<void()> onPlayButtonPressedCallback = std::bind(&EngineFunctionalityManager::OnPlayButtonClicked, this);
        uiBtnImg_PlayButton->SubscribeToBtnOnPressEvent(onPlayButtonPressedCallback);
        //ads the button to the ui
        uiBtnImg_PlayButton->AddUiToScreen();
    }

    {
        //this code creates a new button in this case the debug button
        sf::Texture* uiTexture_DebugButton = new sf::Texture();
        if (!uiTexture_DebugButton->loadFromFile("../Textures/DebugButton.png"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }
        uiBtnImg_DebugButton = new UiScreenView_btnImage(uiTexture_DebugButton, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)));
        uiBtnImg_DebugButton->SetUiPosition(Vector2(0.5f, 0), Vector2(55, 38));
        //this subscribes to the on debug button press callback
        std::function<void()> onDebugButtonPressedCallback = std::bind(&EngineFunctionalityManager::OnDebugButtonClicked, this);
        uiBtnImg_DebugButton->SubscribeToBtnOnPressEvent(onDebugButtonPressedCallback);
        //adds the button to the ui
        uiBtnImg_DebugButton->AddUiToScreen();
    }

    {
        //this code creates a new button in this case the stop button
        sf::Texture* uiTexture_StopButton = new sf::Texture();
        if (!uiTexture_StopButton->loadFromFile("../Textures/StopButton.png"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }

        uiBtnImg_StopButton = new UiScreenView_btnImage(uiTexture_StopButton, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)));
        uiBtnImg_StopButton->SetUiPosition(Vector2(0.5f, 0), Vector2(-105, 38));
        //this subscribes to the on debug button press callback
        std::function<void()> onStopButtonPressedCallback = std::bind(&EngineFunctionalityManager::OnStopButtonClicked, this);
        uiBtnImg_StopButton->SubscribeToBtnOnPressEvent(onStopButtonPressedCallback);
        //adds the button to the screem
        uiBtnImg_StopButton->AddUiToScreen();
    }

    {
        //this code creates a new button in this case the stop button
        sf::Texture* uiTexture_SaveButton = new sf::Texture();
        if (!uiTexture_SaveButton->loadFromFile("../Textures/SaveSceneButton.png"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }

        uiBtnImg_SaveButton = new UiScreenView_btnImage(uiTexture_SaveButton, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)));
        uiBtnImg_SaveButton->SetUiPosition(Vector2(0, 0), Vector2(25, 38));
        //this subscribes to the on debug button press callback
        std::function<void()> onSaveButtonPressedCallback = std::bind(&EngineFunctionalityManager::OnSaveButtonClicked, this);
        uiBtnImg_SaveButton->SubscribeToBtnOnPressEvent(onSaveButtonPressedCallback);
        //adds the button to the screem
        uiBtnImg_SaveButton->AddUiToScreen();
    }
#pragma endregion
}

void EngineFunctionalityManager::CreateLeftBarUi()
{
    //this creates the left navbar
    sf::Texture* ui_LeftWhiteNavbar = new sf::Texture();
    if (!ui_LeftWhiteNavbar->loadFromFile("../Textures/LeftNavbar.png"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }
    UiScreenView_Image* uiImg_LeftNavbar = new UiScreenView_Image(ui_LeftWhiteNavbar, new Transform(Vector2(0.5f, 0.5f), 0, Vector2(5, 40)));
    uiImg_LeftNavbar->SetUiPosition(Vector2(0, 0.5), Vector2(120,0));
    uiImg_LeftNavbar->AddUiToScreen();

#pragma region Creating every GameObject UI list

    float yOffset = 55.f; 
    
    //gets all gameobjects on the scene
    std::vector<GameObject*> gameObjects = *Scene::GetInstance()->GetAllObjects();
    //this does a loop through all gameobjects and draws a button for it
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        //gets the texture for the button
        sf::Texture* ui_textureForButtons = new sf::Texture();
        if (!ui_textureForButtons->loadFromFile("../Textures/whiteSquare.png"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }

        //creates the text for the button
        UiScreenView_Text* ui_txtText = new UiScreenView_Text(gameObjects.at(i)->name, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)));
        //creates the button 
        UiScreenView_btnText* ui_btnText = new UiScreenView_btnText(ui_textureForButtons, new Transform(Vector2(0.5, 0), 0, Vector2(5, 1)), gameObjects.at(i)->name, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)), ui_txtText);

        ui_btnText->SetFontSize(25);
        ui_btnText->SetTextColor(sf::Color::Black);
        ui_btnText->SetUiPosition(Vector2(0, 0), Vector2(120, 100 + yOffset * i));
        ui_btnText->SetTextUiPosition(Vector2(0, 0), Vector2(120, 100 + (yOffset * i)));
        ui_btnText->SetTextUiScale(Vector2(1, 1));
        ui_btnText->AddUiToScreen();

        //this subscribes to the btn pressed, so that we know which button was pressed
        ui_btnText->SubscribeToBtnOnPressEvent(gameObjects.at(i), std::bind(&EngineFunctionalityManager::GameObjectButtonClicked, this, std::placeholders::_1));
    }

#pragma endregion

}

#pragma endregion
