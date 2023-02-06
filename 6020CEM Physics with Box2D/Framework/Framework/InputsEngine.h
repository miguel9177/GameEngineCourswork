#pragma once


//this is a singleton, and stores the Inputs Engine script
class InputsEngine
{
 private:
    static InputsEngine* instance;
    InputsEngine();
public:
    //this gives the instance of the inputs engine, and if theres no instance of it, it creates one
    static InputsEngine* GetInstance();

    void Update();
};


