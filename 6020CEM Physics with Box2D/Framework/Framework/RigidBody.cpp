#include "RigidBody.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include <Box2D/Box2D.h>
#include "GameEngineMathHelper.h"
#include "Com_Collider.h"

RigidBody::RigidBody(b2BodyType _typeOfRb) : Component(Component::typeOfComponent::Physics, uniqueComponentIdIdentifier)
{
	//creates a temp body defenition so that we can create a rigidbody
	b2BodyDef bodyDef;
	bodyDef.type = _typeOfRb;

	//creates the rigidbody
	body = PhysicsEngine::GetInstance()->CreateRigidBody(&bodyDef);
}

RigidBody::RigidBody(b2BodyType _typeOfRb, Vector2 pos_) : Component(Component::typeOfComponent::Physics, uniqueComponentIdIdentifier)
{
	//creates a temp body defenition so that we can create a rigidbody
	b2BodyDef bodyDef;
	bodyDef.type = _typeOfRb;
	bodyDef.position = pos_;

	//creates the rigidbody
	body = PhysicsEngine::GetInstance()->CreateRigidBody(&bodyDef);
}

RigidBody::~RigidBody()
{
	
}

void RigidBody::Start()
{
	body->SetTransform(gameObject->GetPosition(), DegreesToRadians(gameObject->GetRotation()));
}

void RigidBody::Update()
{
	//since we have a rigidbody, we need to update the gameobject position to the rigidbody posiiton
	gameObject->SetPosition(body->GetPosition(), false);
	gameObject->SetRotation(RadiansToDegree(body->GetAngle()));
}

#pragma region Getters And Setters

Vector2 RigidBody::GetPosition()
{
	return body->GetPosition();
}

void RigidBody::SetPosition(Vector2 _position)
{
	body->SetActive(false);
	body->SetTransform(_position, body->GetAngle());
	body->SetActive(true);
}

float RigidBody::GetRotation()
{
	float bodyRotationDegrees = RadiansToDegree(body->GetAngle());
	return bodyRotationDegrees;
}

void RigidBody::SetRotation(float _rot)
{
	float bodyRotationRadians = DegreesToRadians(_rot);
	body->SetTransform(body->GetPosition(), bodyRotationRadians);
}

void RigidBody::SetPositionAndRotation(Vector2 _position, float _rot)
{
	float bodyRotationRadians = DegreesToRadians(_rot);
	body->SetTransform(_position, _rot);
}

#pragma endregion

#pragma region Collider Functions

//this adds a collider to the rigidbody
void RigidBody::AddCollider(Com_Collider* _coll)
{
	//adds the item to the list
	allColliders.push_back(_coll);
	//gets the collider defenition
	body->CreateFixture(_coll->GetColliderBox2dDefenition());
}

std::vector<Com_Collider*>* RigidBody::GetAllColliders()
{
	return &allColliders;
}

#pragma endregion