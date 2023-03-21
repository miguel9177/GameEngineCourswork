#include "EventQueue.h"
#include "Vector2.h"

EventQueue* EventQueue::instance;

EventQueue::EventQueue()
{

}

EventQueue::~EventQueue()
{

}

EventQueue* EventQueue::GetInstance()
{
    if (!instance)
    {
        instance = new EventQueue();
    }
    return instance;
}

#pragma region Subscribing and unsubscribing events

//this subscribes to an event
void EventQueue::SubscribeToVoidEvent(EventQueue::voidEvents eventToSubscribeTo, void(*functionToCallBack)())
{
    allSubscribedVoidEvents[eventToSubscribeTo].push_back(functionToCallBack);
}

//this unsubscribes an event
void EventQueue::UnsubscribeToVoidEvent(voidEvents eventToUnSubscribeTo, void(*functionToCallBack)())
{
    auto& subscribers = allSubscribedVoidEvents[eventToUnSubscribeTo];
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), functionToCallBack), subscribers.end());
}

void EventQueue::SubscribeToKeyPressEvent(sf::Keyboard::Key _key, void(*function)())
{
    allSubscribedOnKeyPressEvent[_key].push_back(function);
}

void EventQueue::UnsubscribeToKeyPressEvent(sf::Keyboard::Key _key, void(*function)())
{
    auto& subscribers = allSubscribedOnKeyPressEvent[_key];
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function), subscribers.end());
}

void EventQueue::SubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, void(*function)())
{
    allSubscribedOnKeyReleaseEvent[_key].push_back(function);
}

void EventQueue::UnsubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, void(*function)())
{
    auto& subscribers = allSubscribedOnKeyReleaseEvent[_key];
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function), subscribers.end());
}

void EventQueue::SubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, void(*function)())
{
    allSubscribedOnMouseKeyPressEvent[_mouseButton].push_back(function);
}

void EventQueue::UnsubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, void(*function)())
{
    auto& subscribers = allSubscribedOnMouseKeyPressEvent[_mouseButton];
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function), subscribers.end());
}

void EventQueue::SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, void(*function)())
{
    allSubscribedOnMouseKeyReleaseEvent[_mouseButton].push_back(function);
}

void EventQueue::UnsubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, void(*function)())
{
    auto& subscribers = allSubscribedOnMouseKeyReleaseEvent[_mouseButton];
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function), subscribers.end());
}

void EventQueue::SubscribeToMouseMovedEvent(void(*function)(Vector2 _pos))
{
    allSubscribedOnMouseMovedEvent.push_back(function);
}

void EventQueue::UnsubscribeToMouseMovedEvent(void(*function)(Vector2 _pos))
{
    auto it = std::remove(allSubscribedOnMouseMovedEvent.begin(), allSubscribedOnMouseMovedEvent.end(), function);
    allSubscribedOnMouseMovedEvent.erase(it, allSubscribedOnMouseMovedEvent.end());
}

void EventQueue::SubscribeToMouseWheelScrolledEvent(void(*function)(float _delta))
{
    allSubscribedOnMouseWheelScrolledEvent.push_back(function);
}

void EventQueue::UnsubscribeToMouseWheelScrolledEvent(void(*function)(float _delta))
{
    auto it = std::remove(allSubscribedOnMouseWheelScrolledEvent.begin(), allSubscribedOnMouseWheelScrolledEvent.end(), function);
    allSubscribedOnMouseWheelScrolledEvent.erase(it, allSubscribedOnMouseWheelScrolledEvent.end());
}

#pragma endregion

#pragma region Invoke events functions

void EventQueue::InvokeVoidEvents(EventQueue::voidEvents eventToCall)
{
    auto it = allSubscribedVoidEvents.find(eventToCall);
    if (it != allSubscribedVoidEvents.end())
    {
        for (auto const& callback : it->second)
        {
            callback();
        }
    }
}

void EventQueue::InvokeKeyPressedEvents(sf::Keyboard::Key _key)
{
    auto it = allSubscribedOnKeyPressEvent.find(_key);
    if (it != allSubscribedOnKeyPressEvent.end())
    {
        for (auto const& callback : it->second)
        {
            callback();
        }
    }
}

void EventQueue::InvokeKeyReleasedEvents(sf::Keyboard::Key _key)
{
    auto it = allSubscribedOnKeyReleaseEvent.find(_key);
    if (it != allSubscribedOnKeyReleaseEvent.end())
    {
        for (auto const& callback : it->second)
        {
            callback();
        }
    }
}

void EventQueue::InvokeMouseKeyPressedEvents(sf::Mouse::Button _mouseButton)
{
    auto it = allSubscribedOnMouseKeyPressEvent.find(_mouseButton);
    if (it != allSubscribedOnMouseKeyPressEvent.end())
    {
        for (auto const& callback : it->second)
        {
            callback();
        }
    }
}

void EventQueue::InvokeMouseKeyReleasedEvents(sf::Mouse::Button _mouseButton)
{
    auto it = allSubscribedOnMouseKeyReleaseEvent.find(_mouseButton);
    if (it != allSubscribedOnMouseKeyReleaseEvent.end())
    {
        for (auto const& callback : it->second)
        {
            callback();
        }
    }
}

void EventQueue::InvokeMouseMovedEvents(Vector2 _pos)
{
    for (auto& callback : allSubscribedOnMouseMovedEvent)
    {
        if (callback != nullptr)
        {
            callback(_pos);
        }
    }
}

void EventQueue::InvokeMouseWheelScrolledEvents(float _mouseWheelDelta)
{
    for (auto& callback : allSubscribedOnMouseWheelScrolledEvent)
    {
        if (callback != nullptr)
        {
            callback(_mouseWheelDelta);
        }
    }
}

#pragma endregion

