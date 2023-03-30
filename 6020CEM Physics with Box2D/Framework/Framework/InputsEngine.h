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
    //stores if the key is being pressed or not
    struct KeyPressInformation
    {
        bool pressing = false;
    };

    //stores the mouse state
    struct MouseState 
    {
        bool pressingLeftButton = false;
        bool pressingRightButton = false;
        bool pressingMiddleButton = false;
        Vector2 position;
        Vector2 velocity;
        float wheelDelta = 0;
    };

    //this is a mouse velocity reducer, since the sfml mouse vvelocity is too big
    float mouseVelociyReducer = 500;

 private:
    
     //stores the mouse midle wheel delta (- if its scrolling doens, 1 if its up)
    float lastWheelDelta = 0;
    // check all the window's events that were triggered since the last iteration of the loop
    static InputsEngine* instance;
    //stores all the sfml events
    std::vector<sf::Event> sfmlEvents;

    //stores every keyboard key and its information
    std::unordered_map<sf::Keyboard::Key, KeyPressInformation> keysState;
    //stores the mosue state
    MouseState mouseState;

    InputsEngine();
    ~InputsEngine();

    //clears all the key states, for example when the window loses focus
    void ClearKeyStates();

    //this updates the mouse state
    void UpdateMouseState(sf::Window* window_);

public:
    //this gives the instance of the inputs engine, and if theres no instance of it, it creates one
    static InputsEngine* GetInstance();

    //update called on ghame engine
    void Update(sf::Window* window_);

    //this clears the input received from the window
    void ClearInputsReceivedFromWindow();
    //this receives the inputs from the window
    void ReceiveInputFromWindow(sf::Event event_);

    //this calculates the miuyse velocity
    void CalculateMouseVelocity(sf::Window* window_);
    //this converts the sfml mouse pos to my pos system
    Vector2 GetMouseWorldPosition();
    //this returns all events
    std::vector<sf::Event>* GetAllEvents();
    //we return a const reference so that we dont have to copy the key state
    inline const std::unordered_map<sf::Keyboard::Key, KeyPressInformation>& GetKeyStates() const { return keysState; };
    inline MouseState GetMouseState() { return mouseState; };
};


