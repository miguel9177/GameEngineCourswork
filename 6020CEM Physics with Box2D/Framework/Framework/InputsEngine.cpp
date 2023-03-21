#include "InputsEngine.h"

InputsEngine* InputsEngine::instance;

InputsEngine::InputsEngine()
{
    //this initializes the key state unordered map for him to have all keyboard keys
    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        KeyPressInformation _keyState;
        _keyState.pressing = false;
        keysState[static_cast<sf::Keyboard::Key>(i)] = _keyState;
    }
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

//this is called when the window loses focus and resets every key press
void InputsEngine::ClearKeyStates()
{
    for (auto& keyState : keysState)
    {
        keyState.second.pressing = false;
    }
}

void InputsEngine::ClearInputsReceivedFromWindow()
{
    sfmlEvents.clear();
}


void InputsEngine::ReceiveInputFromWindow(sf::Event event_)
{
    sfmlEvents.push_back(event_);

    if (event_.type == sf::Event::LostFocus)
        ClearKeyStates();

    //user is pressing key
    if (event_.type == sf::Event::KeyPressed)
    {
        keysState[event_.key.code].pressing = true; 
    }
    //user released key
    else if (event_.type == sf::Event::KeyReleased)
    {
        keysState[event_.key.code].pressing = false;
    }
}

std::vector<sf::Event>* InputsEngine::GetAllEvents()
{
    return &sfmlEvents;
}