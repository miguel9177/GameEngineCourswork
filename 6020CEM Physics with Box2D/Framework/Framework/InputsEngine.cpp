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

}

void InputsEngine::ClearInputsReceivedFromWindow()
{
    sfmlEvents.clear();
}


void InputsEngine::ReceiveInputFromWindow(sf::Event event_)
{
    sfmlEvents.push_back(event_);
}

std::vector<sf::Event>* InputsEngine::GetInputEvents()
{
    return &sfmlEvents;
}