#pragma once
#include <Box2D/Box2D.h>

//this is a singleton, and stores the Physics Engine script
class PhysicsEngine
{
private:
    static PhysicsEngine* instance;
    
    //time step of 1/60 seconds
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    b2Vec2 gravity;
    b2World world;

    PhysicsEngine();

    ~PhysicsEngine();
public:

    //this gives the instance of the graphics engine, and if theres no instance of it, it creates one
    static PhysicsEngine* GetInstance();

    b2Body* CreateRigidBody(b2BodyDef* bodyDefenition);

    void Update();
};

