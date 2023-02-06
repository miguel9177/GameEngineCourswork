#pragma once
//this is a singleton, and stores the Physics Engine script
class PhysicsEngine
{
private:
    static PhysicsEngine* instance;
    PhysicsEngine();

    ~PhysicsEngine();
public:
    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static PhysicsEngine* GetInstance();

    void Update();
};

