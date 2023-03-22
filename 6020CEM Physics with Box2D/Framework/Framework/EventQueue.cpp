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
    allSubscribedVoidEvents[eventToSubscribeTo].push_back(std::function<void()>(function));
}

//this unsubscribes an event
void EventQueue::UnsubscribeToVoidEvent(voidEvents eventToUnSubscribeTo, std::function<void()> function)
{
    auto mapIt = allSubscribedVoidEvents.find(eventToUnSubscribeTo);
    if (mapIt != allSubscribedVoidEvents.end())
    {
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        for (unsigned int i = 0; i < subscribers.size();)
        {
            if (subscribers[i] != nullptr && getAddress(subscribers[i]) == getAddress(function))
            {
                subscribers.erase(subscribers.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

void EventQueue::SubscribeToKeyPressEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    allSubscribedOnKeyPressEvent[_key].push_back(std::function<void()>(function));
}

void EventQueue::UnsubscribeToKeyPressEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    auto mapIt = allSubscribedOnKeyPressEvent.find(_key);
    if (mapIt != allSubscribedOnKeyPressEvent.end())
    {
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        for (unsigned int i = 0; i < subscribers.size();)
        {
            if (subscribers[i] != nullptr && getAddress(subscribers[i]) == getAddress(function))
            {
                subscribers.erase(subscribers.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

void EventQueue::SubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    allSubscribedOnKeyReleaseEvent[_key].push_back(std::function<void()>(function));
}

void EventQueue::UnsubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    auto mapIt = allSubscribedOnKeyReleaseEvent.find(_key);
    if (mapIt != allSubscribedOnKeyReleaseEvent.end())
    {
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        for (unsigned int i = 0; i < subscribers.size();)
        {
            if (subscribers[i] != nullptr && getAddress(subscribers[i]) == getAddress(function))
            {
                subscribers.erase(subscribers.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

void EventQueue::SubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    allSubscribedOnMouseKeyPressEvent[_mouseButton].push_back(std::function<void()>(function));
}

void EventQueue::UnsubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    auto mapIt = allSubscribedOnMouseKeyPressEvent.find(_mouseButton);
    if (mapIt != allSubscribedOnMouseKeyPressEvent.end())
    {
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        for (unsigned int i = 0; i < subscribers.size();)
        {
            if (subscribers[i] != nullptr && getAddress(subscribers[i]) == getAddress(function))
            {
                subscribers.erase(subscribers.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

void EventQueue::SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    allSubscribedOnMouseKeyReleaseEvent[_mouseButton].push_back(std::function<void()>(function));
}

void EventQueue::UnsubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    auto mapIt = allSubscribedOnMouseKeyReleaseEvent.find(_mouseButton);
    if (mapIt != allSubscribedOnMouseKeyReleaseEvent.end())
    {
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        for (unsigned int i = 0; i < subscribers.size();)
        {
            if (subscribers[i] != nullptr && getAddress(subscribers[i]) == getAddress(function))
            {
                subscribers.erase(subscribers.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }

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
    allSubscribedOnMouseWheelScrolledEvent.push_back(std::function<void(float)>(function));
}

void EventQueue::UnsubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function)
{
    for (unsigned int i = 0; i < allSubscribedOnMouseWheelScrolledEvent.size();)
    {
        if (allSubscribedOnMouseWheelScrolledEvent[i] != nullptr && getAddress(allSubscribedOnMouseWheelScrolledEvent[i]) == getAddress(function))
        {
            allSubscribedOnMouseWheelScrolledEvent.erase(allSubscribedOnMouseWheelScrolledEvent.begin() + i);
        }
        else
        {
            i++;
        }
    }
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

