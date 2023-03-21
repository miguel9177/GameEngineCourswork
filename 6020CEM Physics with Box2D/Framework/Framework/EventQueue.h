#pragma once
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class Vector2;
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

    void SubscribeToKeyReleasedEvent(sf::Keyboard::Key, void (*functionToCallBack)());
    void UnsubscribeToKeyReleasedEvent(sf::Keyboard::Key, void (*functionToCallBack)());

    void SubscribeToMouseKeyPressEvent(sf::Mouse::Button, void (*functionToCallBack)());
    void UnsubscribeToMouseKeyPressEvent(sf::Mouse::Button, void (*functionToCallBack)());

    void SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button, void (*functionToCallBack)());
    void UnsubscribeToMouseKeyReleasedEvent(sf::Mouse::Button, void (*functionToCallBack)());

    void SubscribeToMouseMovedEvent(void (*functionToCallBack)(Vector2 _pos));
    void UnsubscribeToMouseMovedEvent(void (*functionToCallBack)(Vector2 _pos));

    void SubscribeToMouseWheelScrolledEvent(void (*functionToCallBack)(float _delta));
    void UnsubscribeToMouseWheelScrolledEvent(void (*functionToCallBack)(float _delta));

    void InvokeVoidEvents(voidEvents eventToSubscribeTo);
    void InvokeKeyPressedEvents(sf::Keyboard::Key);
    void InvokeKeyReleasedEvents(sf::Keyboard::Key);
    void InvokeMouseKeyPressedEvents(sf::Mouse::Button _mouseButton);
    void InvokeMouseKeyReleasedEvents(sf::Mouse::Button _mouseButton);
    void InvokeMouseMovedEvents(Vector2 _pos);
    void InvokeMouseWheelScrolledEvents(float _mouseWheelDelta);
private:
    std::map<voidEvents, std::vector<void (*)()>> allSubscribedVoidEvents;
    std::map<sf::Keyboard::Key, std::vector<void (*)()>> allSubscribedOnKeyPressEvent;
    std::map<sf::Keyboard::Key, std::vector<void (*)()>> allSubscribedOnKeyReleaseEvent;
    std::map<sf::Mouse::Button, std::vector<void (*)()>> allSubscribedOnMouseKeyPressEvent;
    std::map<sf::Mouse::Button, std::vector<void (*)()>> allSubscribedOnMouseKeyReleaseEvent;
    std::vector<void (*)(Vector2 _pos)> allSubscribedOnMouseMovedEvent;
    std::vector<void (*)(float _delta)> allSubscribedOnMouseWheelScrolledEvent;
};

