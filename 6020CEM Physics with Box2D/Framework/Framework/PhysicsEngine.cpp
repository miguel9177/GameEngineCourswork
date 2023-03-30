#include "PhysicsEngine.h"
#include "RigidBody.h"
#include <vector>
#include "Scene.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "EngineFunctionalityManager.h"
#include "ScriptBehaviour.h"

PhysicsEngine* PhysicsEngine::instance;

PhysicsEngine::PhysicsEngine() : gravity(0.0f, 0.0f)
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
    if (world == nullptr)
    {
        std::cout << "Error: trying to create a rigidbody in a not initialized physics world, please call the functions startPhyscisWorld!" << std::endl;
        return nullptr;
    }
    return world->CreateBody(bodyDefenition_);
}

void PhysicsEngine::Update()
{
    //calculates the delta times
    deltaTime = clock.restart().asSeconds();

    if (world == nullptr || EngineFunctionalityManager::GetInstance()->GetEngineState() == EngineFunctionalityManager::State::editMode)
        return;
    
    //goes trough all rbs
    for (std::vector<RigidBody*>::iterator it = Scene::GetInstance()->GetAllRigidBodys()->begin(); it != Scene::GetInstance()->GetAllRigidBodys()->end(); ++it)
    {
        //updates all rbs
        RigidBody* rb = *it;

        if (rb != nullptr)
            rb->Update();
    }

    //tell the box2d world to update
    world->Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsEngine::StartPhysicsWorld()
{
    world = new b2World(gravity);
}

void PhysicsEngine::StopPhysicsWorld()
{
    delete world;
    world = nullptr;
}

void PhysicsEngine::SubscribeRbToCollisionDetectionCallbacks(ScriptBehaviour* scriptToCall, RigidBody* rb)
{
   // world->SetContactListener(scriptToCall);
}
