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

    //this subscribes to the left mouse click event, in order for it to call the function UserPressedLeftMouseButton everytime the user presses left mouse button
    std::function<void()> mouseReleasedCallback = std::bind(&EngineFunctionalityManager::LeftMouseReleased, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Left, mouseReleasedCallback);

    //this subscribes to the left mouse click event, in order for it to call the function UserPressedLeftMouseButton everytime the user presses left mouse button
    std::function<void()> midleMousePressCallback = std::bind(&EngineFunctionalityManager::MiddleMousePressed, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Middle, midleMousePressCallback);

    //this subscribes to the left mouse click event, in order for it to call the function UserPressedLeftMouseButton everytime the user presses left mouse button
    std::function<void()> midleMouseReleasedCallback = std::bind(&EngineFunctionalityManager::MiddleMouseReleased, this);
    EventQueue::GetInstance()->SubscribeToMouseKeyReleasedEvent(sf::Mouse::Middle, midleMouseReleasedCallback);
}

EngineFunctionalityManager::~EngineFunctionalityManager()
{
}

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
    if (state != State::editMode)
        return;

    if (objBeingDragged != nullptr)
    {
        objBeingDragged->SetPosition(InputsEngine::GetInstance()->GetMouseWorldPosition());
    }
    if (InputsEngine::GetInstance()->GetMouseState().pressingMiddleButton)
    {
        GameEngine::GetInstance()->MoveCamera(GameEngine::GetInstance()->GetCameraPosition() + InputsEngine::GetInstance()->GetMouseState().velocity);
    }
}

void EngineFunctionalityManager::Start()
{
    CreateEngineUI();
}

#pragma region Functionality functions

void EngineFunctionalityManager::CreateEngineUI()
{
    /*UiScreenView_Text* ui_txtText1 = new UiScreenView_Text("string 1 working on UiEngine", new Transform(Vector2(0.5f, 0.0f), 0, Vector2(1, 1)));
    ui_txtText1->AddUiToScreen();*/

    CreateLeftBarUi();
    CreateTopBarUi();

  /*  sf::Texture ui_texture3;
    if (!ui_texture3.loadFromFile("../Textures/whiteSquare.png"))
    {
        std::cout << "Texture did not load!" << "\n" << std::endl;
    }
    UiScreenView_btnText* ui_btnText1 = new UiScreenView_btnText(&ui_texture3, new Transform(Vector2(0.5, 0.5), 0, Vector2(2, 1)), "button1", new Transform(Vector2(0.5f, 0.5f), 0, Vector2(1, 1)));
    ui_btnText1->SetFontSize(25);
    ui_btnText1->SetTextColor(sf::Color::Black);
    ui_btnText1->SetTextUiPosition(Vector2(0.5f, 0.5f), Vector2(-10, 0));
    ui_btnText1->AddUiToScreen();
    ui_btnText1->SubscribeToBtnOnPressEvent(test);
    ui_btnText1->SubscribeToBtnOnReleasedEvent(test2);*/
}

#pragma endregion

#pragma region Event dependent functions

void EngineFunctionalityManager::OnPlayButtonClicked()
{
    if (state == State::playMode)
        return;
    
    state = State::playMode;

    PhysicsEngine::GetInstance()->StopPhysicsWorld();
    PhysicsEngine::GetInstance()->StartPhysicsWorld();
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::EnteredPlayMode);
    EngineJsonReader::GetInstance()->LoadSceneToPlay();

    sf::Texture clickedTexture = sf::Texture();
    clickedTexture.loadFromFile("../Textures/PlayButtonClicked.png");
    uiBtnImg_PlayButton->SetTexture(clickedTexture);

}

void EngineFunctionalityManager::OnDebugButtonClicked()
{
    GameEngine::GetInstance()->isDebugMode = !GameEngine::GetInstance()->isDebugMode;

    if (GameEngine::GetInstance()->isDebugMode)
    {
        sf::Texture clickedTexture = sf::Texture();
        clickedTexture.loadFromFile("../Textures/DebugButtonClicked.png");
        uiBtnImg_DebugButton->SetTexture(clickedTexture);
    }
    else
    {
        sf::Texture clickedTexture = sf::Texture();
        clickedTexture.loadFromFile("../Textures/DebugButton.png");
        uiBtnImg_DebugButton->SetTexture(clickedTexture);
    }
}

void EngineFunctionalityManager::OnStopButtonClicked()
{
    PhysicsEngine::GetInstance()->StopPhysicsWorld();
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::EnteredEditMode);
    EventQueue::GetInstance()->InvokeVoidEvents(EventQueue::voidEvents::RestartEngine);
    state = State::editMode;
}

void EngineFunctionalityManager::OnSaveButtonClicked()
{
    std::cout << "Save button pressed " << std::endl;
    EngineJsonReader::GetInstance()->SaveScene();
}

void EngineFunctionalityManager::LeftMousePressed()
{
    if (state == State::editMode)
    {
        objBeingDragged = GetObjectAtMousePos();
    }
}

void EngineFunctionalityManager::LeftMouseReleased()
{
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
    for (Com_Mesh* currentMesh : *Scene::GetInstance()->GetAllMeshes())
    {
        Vector2 screenMousePos = InputsEngine::GetInstance()->GetMouseState().position;
        Vector2 viewCenter = GameEngine::GetInstance()->GetCameraSfmlPosition();
        Vector2 viewSize = GameEngine::GetInstance()->GetCameraSize();

        sf::Vector2f worldMousePos = sf::Vector2f(screenMousePos.x + viewCenter.x - viewSize.x / 2.0f, screenMousePos.y + viewCenter.y - viewSize.y / 2.0f);

        sf::FloatRect buttonBounds = currentMesh->GetMeshToRender()->getGlobalBounds();

        if (buttonBounds.contains(worldMousePos))
            return currentMesh->gameObject;
    }
    return nullptr;
}

void EngineFunctionalityManager::CreateTopBarUi()
{
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
    
    std::vector<GameObject*> gameObjects = *Scene::GetInstance()->GetAllObjects();
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        sf::Texture* ui_textureForButtons = new sf::Texture();
        if (!ui_textureForButtons->loadFromFile("../Textures/whiteSquare.png"))
        {
            std::cout << "Texture did not load!" << "\n" << std::endl;
        }

        UiScreenView_Text* ui_txtText = new UiScreenView_Text(gameObjects.at(i)->name, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)));
        UiScreenView_btnText* ui_btnText = new UiScreenView_btnText(ui_textureForButtons, new Transform(Vector2(0.5, 0), 0, Vector2(5, 1)), gameObjects.at(i)->name, new Transform(Vector2(0.5f, 0), 0, Vector2(1, 1)), ui_txtText);

        ui_btnText->SetFontSize(25);
        ui_btnText->SetTextColor(sf::Color::Black);
        ui_btnText->SetUiPosition(Vector2(0, 0), Vector2(120, 100 + yOffset * i));
        ui_btnText->SetTextUiPosition(Vector2(0, 0), Vector2(120, 100 + (yOffset * i)));
        ui_btnText->SetTextUiScale(Vector2(1, 1));
        ui_btnText->AddUiToScreen();

        ui_btnText->SubscribeToBtnOnPressEvent(gameObjects.at(i), std::bind(&EngineFunctionalityManager::GameObjectButtonClicked, this, std::placeholders::_1));
    }

#pragma endregion

}

#pragma endregion
