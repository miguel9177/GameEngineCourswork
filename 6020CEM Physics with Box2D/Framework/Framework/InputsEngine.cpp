#include "InputsEngine.h"
#include "EventQueue.h"
#include "Com_Mesh.h"
#include <iostream>

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

void InputsEngine::Update(sf::Window* window_)
{
    CalculateMouseVelocity(window_);
    UpdateMouseState(window_);
    mouseState.wheelDelta = lastWheelDelta;
    lastWheelDelta = 0;
}

Vector2 InputsEngine::GetMouseWorldPosition()
{
    float x = mouseState.position.x / Com_Mesh::scalingFactor;
    float y = mouseState.position.y / Com_Mesh::scalingFactor;
    
    return Vector2(x, y);


}

std::vector<sf::Event>* InputsEngine::GetAllEvents()
{
    return &sfmlEvents;
}

#pragma region Input Handling

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

    //Update the mouseWheel delta value, if mouse wheel scrolled
    if (event_.type == sf::Event::MouseWheelScrolled)
    {
        lastWheelDelta = event_.mouseWheelScroll.delta;
        EventQueue::GetInstance()->InvokeMouseWheelScrolledEvents(lastWheelDelta);
    }
}

#pragma endregion

#pragma region Utility Functions

void InputsEngine::UpdateMouseState(sf::Window* window_)
{
    bool _leftButton = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool _rightButton = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    bool _middleButton = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
    Vector2 _position = sf::Mouse::getPosition(*window_);

    if (_leftButton != mouseState.pressingLeftButton)
    {
        if (_leftButton)
            EventQueue::GetInstance()->InvokeMouseKeyPressedEvents(sf::Mouse::Left);
        else
            EventQueue::GetInstance()->InvokeMouseKeyReleasedEvents(sf::Mouse::Left);

        mouseState.pressingLeftButton = _leftButton;
    }
    if (_rightButton != mouseState.pressingRightButton)
    {
        if (_rightButton)
            EventQueue::GetInstance()->InvokeMouseKeyPressedEvents(sf::Mouse::Right);
        else
            EventQueue::GetInstance()->InvokeMouseKeyReleasedEvents(sf::Mouse::Right);

        mouseState.pressingRightButton = _rightButton;
    }
    if (_middleButton != mouseState.pressingMiddleButton)
    {
        if (_middleButton)
            EventQueue::GetInstance()->InvokeMouseKeyPressedEvents(sf::Mouse::Middle);
        else
            EventQueue::GetInstance()->InvokeMouseKeyReleasedEvents(sf::Mouse::Middle);

        mouseState.pressingMiddleButton = _middleButton;
    }
    if (_position.x != mouseState.position.x || _position.y != mouseState.position.y)
    {
        EventQueue::GetInstance()->InvokeMouseMovedEvents(_position);
        mouseState.position = _position;
    }
}

void InputsEngine::CalculateMouseVelocity(sf::Window* window_)
{
    mouseState.velocity = (mouseState.position - sf::Mouse::getPosition(*window_)) / PhysicsEngine::GetInstance()->GetDeltaTime();
    mouseState.velocity = (mouseState.velocity / Com_Mesh::scalingFactor) / mouseVelociyReducer;
}

#pragma endregion
