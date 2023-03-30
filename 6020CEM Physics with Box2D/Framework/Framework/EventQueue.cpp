#include "EventQueue.h"
#include "Vector2.h"

EventQueue* EventQueue::instance;

EventQueue::EventQueue()
{

}

EventQueue::~EventQueue()
{

}

//this returns the instacne since its a singleton
EventQueue* EventQueue::GetInstance()
{
    if (!instance)
    {
        instance = new EventQueue();
    }
    return instance;
}

#pragma region Subscribing and unsubscribing events

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToVoidEvent(EventQueue::voidEvents eventToSubscribeTo, std::function<void()> function)
{
    allSubscribedVoidEvents[eventToSubscribeTo].push_back(std::function<void()>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToVoidEvent(voidEvents eventToUnSubscribeTo, std::function<void()> function)
{
    //find the event type to unsubscribe
    auto mapIt = allSubscribedVoidEvents.find(eventToUnSubscribeTo);
    //loop through all events of the type
    if (mapIt != allSubscribedVoidEvents.end())
    {
        //get all the subscribers
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        //loop through all the subvscribers
        for (unsigned int i = 0; i < subscribers.size();)
        {
            //if the subscriber is the one given, erase the subscriber from the list
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

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToKeyPressEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    allSubscribedOnKeyPressEvent[_key].push_back(std::function<void()>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToKeyPressEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    //find the event type to unsubscribe
    auto mapIt = allSubscribedOnKeyPressEvent.find(_key);
    //loop through all events of the type
    if (mapIt != allSubscribedOnKeyPressEvent.end())
    {
        //get all the subscribers
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        //loop through all the subvscribers
        for (unsigned int i = 0; i < subscribers.size();)
        {
            //if the subscriber is the one given, erase the subscriber from the list
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

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    allSubscribedOnKeyReleaseEvent[_key].push_back(std::function<void()>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToKeyReleasedEvent(sf::Keyboard::Key _key, std::function<void()> function)
{
    //find the event type to unsubscribe
    auto mapIt = allSubscribedOnKeyReleaseEvent.find(_key);
    //loop through all events of the type
    if (mapIt != allSubscribedOnKeyReleaseEvent.end())
    {
        //get all the subscribers
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        //loop through all the subvscribers
        for (unsigned int i = 0; i < subscribers.size();)
        {
            //if the subscriber is the one given, erase the subscriber from the list
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

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    allSubscribedOnMouseKeyPressEvent[_mouseButton].push_back(std::function<void()>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToMouseKeyPressEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    //find the event type to unsubscribe
    auto mapIt = allSubscribedOnMouseKeyPressEvent.find(_mouseButton);
    //loop through all events of the type
    if (mapIt != allSubscribedOnMouseKeyPressEvent.end())
    {
        //get all the subscribers
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        //loop through all the subvscribers
        for (unsigned int i = 0; i < subscribers.size();)
        {
            //if the subscriber is the one given, erase the subscriber from the list
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

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    allSubscribedOnMouseKeyReleaseEvent[_mouseButton].push_back(std::function<void()>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToMouseKeyReleasedEvent(sf::Mouse::Button _mouseButton, std::function<void()> function)
{
    //find the event type to unsubscribe
    auto mapIt = allSubscribedOnMouseKeyReleaseEvent.find(_mouseButton);
    //loop through all events of the type
    if (mapIt != allSubscribedOnMouseKeyReleaseEvent.end())
    {
        //get all the subscribers
        std::vector<std::function<void()>>& subscribers = mapIt->second;

        //loop through all the subvscribers
        for (unsigned int i = 0; i < subscribers.size();)
        {
            //if the subscriber is the one given, erase the subscriber from the list
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

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToMouseMovedEvent(std::function<void(Vector2 _pos)> function)
{
    allSubscribedOnMouseMovedEvent.push_back(std::function<void(Vector2)>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToMouseMovedEvent(std::function<void(Vector2 _pos)> function)
{
    //loop through all the subvscribers
    for (unsigned int i = 0; i < allSubscribedOnMouseMovedEvent.size();)
    {
        //if the subscriber is the one given, erase the subscriber from the list
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

//this subscribes to an event at the condition describe at the function name
void EventQueue::SubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function)
{
    allSubscribedOnMouseWheelScrolledEvent.push_back(std::function<void(float)>(function));
}

//this unsubscribes an event at the condition described at function name
void EventQueue::UnsubscribeToMouseWheelScrolledEvent(std::function<void(float _delta)> function)
{
    //loop through all the subvscribers
    for (unsigned int i = 0; i < allSubscribedOnMouseWheelScrolledEvent.size();)
    {
        //if the subscriber is the one given, erase the subscriber from the list
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

//invoke the events of the condition described at the function name
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

//invoke the events of the condition described at the function name
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

//invoke the events of the condition described at the function name
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

//invoke the events of the condition described at the function name
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

//invoke the events of the condition described at the function name
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

//invoke the events of the condition described at the function name
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

//invoke the events of the condition described at the function name
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

