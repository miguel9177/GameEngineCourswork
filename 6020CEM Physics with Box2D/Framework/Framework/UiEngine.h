#pragma once

//this is a singleton, and stores the Physics Engine script
class UiEngine
{
private:
    static UiEngine* instance;

    UiEngine();

    ~UiEngine();
public:

    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static UiEngine* GetInstance();

};
