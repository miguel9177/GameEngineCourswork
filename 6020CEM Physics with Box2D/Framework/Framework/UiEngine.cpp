#include "UiEngine.h"
#include "UiScreenView_Text.h"
#include "UiScreenView_Image.h"
#include "UiScreenView_btnImage.h"
#include "UiScreenView_btnText.h"


UiEngine* UiEngine::instance;

UiEngine::UiEngine()
{
}

UiEngine::~UiEngine()
{
}

//returns its own instance since this is a singleton
UiEngine* UiEngine::GetInstance()
{
    if (!instance)
    {
        instance = new UiEngine();
    }
    return instance;
}

void UiEngine::Update()
{
    //draws all image items
    for (UiScreenView_Image* screenViewImage : allScreenViewImages)
    {
        screenViewImage->Update();
    }

    //draws all button image items
    for (UiScreenView_btnImage* screenViewBtnImage : allScreenViewBtnImages)
    {
        screenViewBtnImage->Update();
    }

    //draws all button Text items
    for (UiScreenView_btnText* screenViewBtnText : allScreenViewBtnTexts)
    {
        screenViewBtnText->Update();
    }

    //draws all text items
    for (UiScreenView_Text* screenViewText : allScreenViewTexts)
    {
        screenViewText->Update();
    }
}

void UiEngine::DrawAllUi(sf::RenderWindow* _GameEngineWindow)
{
    //draws all image items
    for (UiScreenView_Image* screenViewImage : allScreenViewImages)
    {
        _GameEngineWindow->draw(screenViewImage->GetComponentToDraw());
    }

    //draws all button image items
    for (UiScreenView_btnImage* screenViewBtnImage : allScreenViewBtnImages)
    {
        _GameEngineWindow->draw(screenViewBtnImage->GetComponentToDraw());
    }

    //draws all button Text items
    for (UiScreenView_btnText* screenViewBtnText : allScreenViewBtnTexts)
    {
        _GameEngineWindow->draw(screenViewBtnText->GetComponentToDraw());
    }

    //draws all text items
    for (UiScreenView_Text* screenViewText : allScreenViewTexts)
    {
        _GameEngineWindow->draw(screenViewText->GetComponentToDraw());
    }
}
