#include "PhysicsEngine.h"

PhysicsEngine* PhysicsEngine::instance;

PhysicsEngine::PhysicsEngine() : gravity(0.0f, -9.81f), world(gravity)
{
}

PhysicsEngine::~PhysicsEngine()
{

}

PhysicsEngine* PhysicsEngine::GetInstance()
{
    if (!instance)
    {
        instance = new PhysicsEngine();
    }
    return instance;
}

b2Body* PhysicsEngine::CreateRigidBody(b2BodyDef* bodyDefenition_)
{
    return world.CreateBody(bodyDefenition_);
}

void PhysicsEngine::Update()
{

}