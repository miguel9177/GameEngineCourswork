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
    allSubscribedEvents.insert({ eventToSubscribeTo, functionToCallBack });
}

void EventQueue::InvokeVoidEvents(EventQueue::voidEvents eventToCall)
{
    for (auto const& x : allSubscribedEvents)
    {
        if (x.first == eventToCall)
        {
            x.second();
        }
    }
}
