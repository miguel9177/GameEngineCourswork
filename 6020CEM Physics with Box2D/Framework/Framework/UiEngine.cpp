#include "UiEngine.h"
#include "UiScreenView_Text.h"
#include "UiScreenView_Image.h"

UiEngine* UiEngine::instance;

UiEngine::UiEngine()
{
}

UiEngine::~UiEngine()
{
}

UiEngine* UiEngine::GetInstance()
{
    if (!instance)
    {
        instance = new UiEngine();
    }
    return instance;
}

void UiEngine::DrawAllUi(sf::RenderWindow* _GameEngineWindow)
{
    //draws all text items
    for (UiScreenView_Text* screenViewText : allScreenViewTexts) 
    {
        _GameEngineWindow->draw(screenViewText->GetComponentToDraw());
    }

    //draws all image items
    for (UiScreenView_Image* screenViewImage : allScreenViewImages)
    {
        _GameEngineWindow->draw(screenViewImage->GetComponentToDraw());
    }
}
