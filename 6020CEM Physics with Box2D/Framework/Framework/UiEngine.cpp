#include "UiEngine.h"

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
