#include "PhysicsEngine.h"
#include "RigidBody.h"
#include <vector>
#include "Scene.h"

PhysicsEngine* PhysicsEngine::instance;

PhysicsEngine::PhysicsEngine() : gravity(0.0f, 0.0f), world(gravity)
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
    // Iterate through all rigidbodies
    for (std::vector<RigidBody*>::iterator it = Scene::GetInstance()->GetAllRigidBodys()->begin(); it != Scene::GetInstance()->GetAllRigidBodys()->end(); ++it)
    {
        // Update the rigidBodies
        RigidBody* rb = *it;

        if (rb != nullptr)
            rb->Update();
    }

    world.Step(timeStep, velocityIterations, positionIterations);
}