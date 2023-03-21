#pragma once
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <vector>
#include <unordered_map>

//this is a singleton, and stores the Inputs Engine script
class InputsEngine
{
public:
    struct KeyPressInformation
    {
        bool pressing = false;
    };

 private:
    // check all the window's events that were triggered since the last iteration of the loop
    static InputsEngine* instance;
    std::vector<sf::Event> sfmlEvents;

    std::unordered_map<sf::Keyboard::Key, KeyPressInformation> keysState;

    InputsEngine();
    ~InputsEngine();

    void ClearKeyStates();
public:
    //this gives the instance of the inputs engine, and if theres no instance of it, it creates one
    static InputsEngine* GetInstance();

    void Update();

    void ClearInputsReceivedFromWindow();
    void ReceiveInputFromWindow(sf::Event event_);

    std::vector<sf::Event>* GetAllEvents();
    inline std::unordered_map<sf::Keyboard::Key, KeyPressInformation> GetKeyStates() { return keysState; };
};


