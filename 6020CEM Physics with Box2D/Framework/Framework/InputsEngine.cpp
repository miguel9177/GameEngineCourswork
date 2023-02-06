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
        // "close requested" event: we close the window
        if (events.type == sf::Event::Closed)
            GraphicsEngine::GetInstance()->GetEngineWindow()->close();
    }
}

sf::Event InputsEngine::GetEvents()
{
    return events;
}
