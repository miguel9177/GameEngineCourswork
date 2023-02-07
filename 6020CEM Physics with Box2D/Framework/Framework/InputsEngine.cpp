#include "InputsEngine.h"

InputsEngine* InputsEngine::instance;

InputsEngine::InputsEngine()
{

}

InputsEngine::~InputsEngine()
{

}

InputsEngine* InputsEngine::GetInstance()
{
    if (!instance)
    {
        instance = new InputsEngine();
    }
    return instance;
}

void InputsEngine::Update()
{
    while (GraphicsEngine::GetInstance()->GetEngineWindow()->pollEvent(events))
    {
       
    }
}

sf::Event InputsEngine::GetEvents()
{
    return events;
}
