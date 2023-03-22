#include "EngineFunctionalityManager.h"
#include "UiScreenView_Text.h"
#include "UiScreenView_Image.h"
#include "UiScreenView_btnImage.h"
#include "UiScreenView_btnText.h"
#include "GameEngine.h"

EngineFunctionalityManager* EngineFunctionalityManager::instance;

EngineFunctionalityManager::EngineFunctionalityManager()
{
    CreateEngineUI();
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
}

#pragma region Functionality functions

void EngineFunctionalityManager::CreateEngineUI()
{
    /*UiScreenView_Text* ui_txtText1 = new UiScreenView_Text("string 1 working on UiEngine", new Transform(Vector2(0.5f, 0.0f), 0, Vector2(1, 1)));
    ui_txtText1->AddUiToScreen();*/

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
    
}

void EngineFunctionalityManager::OnDebugButtonClicked()
{
    GameEngine::GetInstance()->isDebugMode = !GameEngine::GetInstance()->isDebugMode;
}

void EngineFunctionalityManager::OnStopButtonClicked()
{
    
}

void EngineFunctionalityManager::OnSaveButtonClicked()
{
    std::cout << "Save button pressed " << std::endl;
}

#pragma endregion

