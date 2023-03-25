#pragma once
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <memory>
#include "Vector2.h"

class EventQueue
{
private:
    static EventQueue* instance;
    
    EventQueue();

    ~EventQueue();
public:

    enum class voidEvents { shoot, test, EnteredEditMode, EnteredPlayMode, RestartEngine};
    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static EventQueue* GetInstance();

    void SubscribeToVoidEvent(voidEvents eventToSubscribeTo, std::function<void()> function);
    void UnsubscribeToVoidEvent(voidEvents eventToSubscribeTo, std::function<void()> function);

    void SubscribeToKeyPressEvent(sf::Keyboard::Key, std::function<void()> function);
    void UnsubscribeToKeyPressEvent(sf::Keyboard::Key, std::function<void()> function);

    void SubscribeToKeyReleasedEvent(sf::Keyboard::Key, std::function<void()> function);
    void UnsubscribeToKeyReleasedEvent(sf::Keyboard::Key, std::function<void()> function);

    void SubscribeToMouseKeyPressEvent(sf::Mouse::Button, std::function<void()> function);
    void UnsubscribeToMouseKeyPressEvent(sf::Mouse::Button, std::function<void()> function);

    void SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button, std::function<void()> function);
    void UnsubscribeToMouseKeyReleasedEvent(sf::Mouse::Button, std::function<void()> function);

    void SubscribeToMouseMovedEvent(std::function<void(Vector2 _pos)> function);
    void UnsubscribeToMouseMovedEvent(std::function<void(Vector2 _pos)> function);

    void SubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function);
    void UnsubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function);

    void InvokeVoidEvents(voidEvents eventToSubscribeTo);
    void InvokeKeyPressedEvents(sf::Keyboard::Key);
    void InvokeKeyReleasedEvents(sf::Keyboard::Key);
    void InvokeMouseKeyPressedEvents(sf::Mouse::Button _mouseButton);
    void InvokeMouseKeyReleasedEvents(sf::Mouse::Button _mouseButton);
    void InvokeMouseMovedEvents(Vector2 _pos);
    void InvokeMouseWheelScrolledEvents(float _mouseWheelDelta);

    //this was taken from https://stackoverflow.com/questions/20833453/comparing-stdfunctions-for-equality
    //it basically gets the function adrees so that we can easaly compare it
    template<typename T, typename... U>
    static inline size_t getAddress(std::function<T(U...)> f) {
        typedef T(fnType)(U...);
        fnType** fnPointer = f.template target<fnType*>();
        return (size_t)*fnPointer;
    }
private:
    std::map<voidEvents, std::vector<std::function<void()>>> allSubscribedVoidEvents;
    std::map<sf::Keyboard::Key, std::vector<std::function<void()>>> allSubscribedOnKeyPressEvent;
    std::map<sf::Keyboard::Key, std::vector<std::function<void()>>> allSubscribedOnKeyReleaseEvent;
    std::map<sf::Mouse::Button, std::vector<std::function<void()>>> allSubscribedOnMouseKeyPressEvent;
    std::map<sf::Mouse::Button, std::vector<std::function<void()>>> allSubscribedOnMouseKeyReleaseEvent;
    std::vector<std::function<void(Vector2 _pos)>> allSubscribedOnMouseMovedEvent;
    std::vector<std::function<void(float _delta)>> allSubscribedOnMouseWheelScrolledEvent;

};

