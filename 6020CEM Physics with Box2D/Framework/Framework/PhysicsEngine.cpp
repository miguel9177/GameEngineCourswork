#include "PhysicsEngine.h"

PhysicsEngine* PhysicsEngine::instance;

PhysicsEngine::PhysicsEngine()
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

void PhysicsEngine::Update()
{

}