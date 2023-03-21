#pragma once
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

class EventQueue
{
private:
    static EventQueue* instance;
    
    EventQueue();

    ~EventQueue();
public:

    enum class voidEvents { shoot, test };
    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static EventQueue* GetInstance();

    void SubscribeToVoidEvent(voidEvents eventToSubscribeTo, void (*functionToCallBack)());
    void UnsubscribeToVoidEvent(voidEvents eventToSubscribeTo, void (*functionToCallBack)());

    void SubscribeToKeyPressEvent(sf::Keyboard::Key, void (*functionToCallBack)());
    void UnsubscribeToKeyPressEvent(sf::Keyboard::Key, void (*functionToCallBack)());

    void SubscribeToKeyReleaseEvent(sf::Keyboard::Key, void (*functionToCallBack)());
    void UnsubscribeToKeyReleaseEvent(sf::Keyboard::Key, void (*functionToCallBack)());

    void InvokeVoidEvents(voidEvents eventToSubscribeTo);
    void InvokeKeyPressedEvents(sf::Keyboard::Key);
    void InvokeKeyReleasedEvents(sf::Keyboard::Key);
private:
    std::map<voidEvents, std::vector<void (*)()>> allSubscribedVoidEvents;
    std::map<sf::Keyboard::Key, std::vector<void (*)()>> allSubscribedOnKeyPressEvent;
    std::map<sf::Keyboard::Key, std::vector<void (*)()>> allSubscribedOnKeyReleaseEvent;
};

