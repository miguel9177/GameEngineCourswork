#pragma once
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <vector>
#include <unordered_map>
#include "Vector2.h"

//this is a singleton, and stores the Inputs Engine script
class InputsEngine
{
public:
    struct KeyPressInformation
    {
        bool pressing = false;
    };

    struct MouseState 
    {
        bool pressingLeftButton = false;
        bool pressingRightButton = false;
        bool pressingMiddleButton = false;
        Vector2 position;
        float wheelDelta = 0;
    };

 private:
    
    float lastWheelDelta = 0;
    // check all the window's events that were triggered since the last iteration of the loop
    static InputsEngine* instance;
    std::vector<sf::Event> sfmlEvents;

    std::unordered_map<sf::Keyboard::Key, KeyPressInformation> keysState;
    MouseState mouseState;

    InputsEngine();
    ~InputsEngine();

    void ClearKeyStates();

    void UpdateMouseState(sf::Window* window_);

public:
    //this gives the instance of the inputs engine, and if theres no instance of it, it creates one
    static InputsEngine* GetInstance();

    void Update(sf::Window* window_);

    void ClearInputsReceivedFromWindow();
    void ReceiveInputFromWindow(sf::Event event_);

    std::vector<sf::Event>* GetAllEvents();
    inline std::unordered_map<sf::Keyboard::Key, KeyPressInformation> GetKeyStates() { return keysState; };
    inline MouseState GetMouseState() { return mouseState; };
};


