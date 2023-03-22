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
void EventQueue::SubscribeToVoidEvent(EventQueue::voidEvents eventToSubscribeTo, std::function<void()> function)
{
    allSubscribedVoidEvents[eventToSubscribeTo].push_back(std::make_shared<std::function<void()>>(function));
}

//this unsubscribes an event
void EventQueue::UnsubscribeToVoidEvent(voidEvents eventToUnSubscribeTo, std::function<void()> function)
{
    auto& subscribers = allSubscribedVoidEvents[eventToUnSubscribeTo];
    auto function_ptr = std::make_shared<std::function<void()>>(function);
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function_ptr), subscribers.end());
}

void EventQueue::SubscribeToKeyPressEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    allSubscribedOnKeyPressEvent[_key].push_back(std::make_shared<std::function<void()>>(function));
}

void EventQueue::UnsubscribeToKeyPressEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    auto& subscribers = allSubscribedOnKeyPressEvent[_key];
    auto function_ptr = std::make_shared<std::function<void()>>(function);
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function_ptr), subscribers.end());
}

void EventQueue::SubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    allSubscribedOnKeyReleaseEvent[_key].push_back(std::make_shared<std::function<void()>>(function));
}

void EventQueue::UnsubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    auto& subscribers = allSubscribedOnKeyReleaseEvent[_key];
    auto function_ptr = std::make_shared<std::function<void()>>(function);
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function_ptr), subscribers.end());
}

void EventQueue::SubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    allSubscribedOnMouseKeyPressEvent[_mouseButton].push_back(std::make_shared<std::function<void()>>(function));
}

void EventQueue::UnsubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    auto& subscribers = allSubscribedOnMouseKeyPressEvent[_mouseButton];
    auto function_ptr = std::make_shared<std::function<void()>>(function);
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function_ptr), subscribers.end());
}

void EventQueue::SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    allSubscribedOnMouseKeyReleaseEvent[_mouseButton].push_back(std::make_shared<std::function<void()>>(function));
}

void EventQueue::UnsubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    auto& subscribers = allSubscribedOnMouseKeyReleaseEvent[_mouseButton];
    auto function_ptr = std::make_shared<std::function<void()>>(function);
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function_ptr), subscribers.end());
}

void EventQueue::SubscribeToMouseMovedEvent(std::function<void(Vector2 _pos)> function)
{
    allSubscribedOnMouseMovedEvent.push_back(std::function<void(Vector2)>(function));
}

void EventQueue::UnsubscribeToMouseMovedEvent(std::function<void(Vector2 _pos)> function)
{
    for (unsigned int i = 0; i < allSubscribedOnMouseMovedEvent.size();)
    {
        if (allSubscribedOnMouseMovedEvent[i] != nullptr && getAddress(allSubscribedOnMouseMovedEvent[i]) == getAddress(function))
        {
            allSubscribedOnMouseMovedEvent.erase(allSubscribedOnMouseMovedEvent.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void EventQueue::SubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function)
{
    allSubscribedOnMouseWheelScrolledEvent.push_back(std::make_shared<std::function<void(float)>>(function));
}

void EventQueue::UnsubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function)
{
    auto& subscribers = allSubscribedOnMouseWheelScrolledEvent;
    auto function_ptr = std::make_shared<std::function<void(float _delta)>>(function);
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function_ptr), subscribers.end());
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
            (*callback)();
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
            (*callback)();
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
           (*callback)();
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
            (*callback)();
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
           (*callback)();
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
            (*callback)(_mouseWheelDelta);
        }
    }
}

#pragma endregion

