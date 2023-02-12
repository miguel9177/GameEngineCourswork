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

void EventQueue::SubscribeToVoidEvent(EventQueue::voidEvents eventToSubscribeTo, void(*functionToCallBack)())
{
    allSubscribedEvents[eventToSubscribeTo].push_back(functionToCallBack);
}

void EventQueue::InvokeVoidEvents(EventQueue::voidEvents eventToCall)
{
    auto it = allSubscribedEvents.find(eventToCall);
    if (it != allSubscribedEvents.end())
    {
        for (auto const& callback : it->second)
        {
            callback();
        }
    }
}
