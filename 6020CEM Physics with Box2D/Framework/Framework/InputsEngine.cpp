#include "InputsEngine.h"
#include "EventQueue.h"

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
        if (keyState.second.pressing)
        {
            keyState.second.pressing = false;
            EventQueue::GetInstance()->InvokeKeyReleasedEvents(keyState.first);
        }
    }
}

void InputsEngine::ClearInputsReceivedFromWindow()
{
    sfmlEvents.clear();
}

void InputsEngine::ReceiveInputFromWindow(sf::Event event_)
{
    sfmlEvents.push_back(event_);

    //if window lost focus, we clear the key states
    if (event_.type == sf::Event::LostFocus)
        ClearKeyStates();

    //user is pressing key
    if (event_.type == sf::Event::KeyPressed && !keysState[event_.key.code].pressing)
    {
        keysState[event_.key.code].pressing = true; 
        EventQueue::GetInstance()->InvokeKeyPressedEvents(event_.key.code);
    }
    //user released key
    else if (event_.type == sf::Event::KeyReleased && keysState[event_.key.code].pressing)
    {
        keysState[event_.key.code].pressing = false;
        EventQueue::GetInstance()->InvokeKeyReleasedEvents(event_.key.code);
    }
}

std::vector<sf::Event>* InputsEngine::GetAllEvents()
{
    return &sfmlEvents;
}