#pragma once
#include <map>
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
    void InvokeVoidEvents(voidEvents eventToSubscribeTo);
private:
    std::map<voidEvents, void (*)()> allSubscribedEvents;
    
};

