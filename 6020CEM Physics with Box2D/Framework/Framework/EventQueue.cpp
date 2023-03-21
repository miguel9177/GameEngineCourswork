#include "EventQueue.h"
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

void EventQueue::SubscribeToKeyReleaseEvent(sf::Keyboard::Key _key, void(*function)())
{
    allSubscribedOnKeyReleaseEvent[_key].push_back(function);
}

void EventQueue::UnsubscribeToKeyReleaseEvent(sf::Keyboard::Key _key, void(*function)())
{
    auto& subscribers = allSubscribedOnKeyReleaseEvent[_key];
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), function), subscribers.end());
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


#pragma endregion

