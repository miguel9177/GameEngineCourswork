#include "RigidBody.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include <Box2D/Box2D.h>
#include "GameEngineMathHelper.h"
#include "Com_Collider.h"
#include <iostream>

RigidBody::RigidBody(RigidBodySettings _bodySettings) : Component(Component::typeOfComponent::Physics, uniqueComponentIdIdentifier)
{
	bodySettings = _bodySettings;

	//creates a temp body defenition so that we can create a rigidbody
	b2BodyDef bodyDef;
	bodyDef.type = _bodySettings.ConvertTypeToBox2DType(_bodySettings.type);
	bodyDef.linearDamping = _bodySettings.drag;
	bodyDef.angularDamping = _bodySettings.angularDrag;
	bodyDef.allowSleep = _bodySettings.allowSleep;
	bodyDef.awake = _bodySettings.awake;
	bodyDef.fixedRotation = _bodySettings.freezeRotation;
	bodyDef.bullet = _bodySettings.important;
	bodyDef.gravityScale = _bodySettings.gravityScale;
	
	//creates the rigidbody
	body = PhysicsEngine::GetInstance()->CreateRigidBody(&bodyDef);
	
}

//RigidBody::RigidBody(Vector2 pos_, RigidBodySettings _bodySettings) : Component(Component::typeOfComponent::Physics, uniqueComponentIdIdentifier)
//{
//	//creates a temp body defenition so that we can create a rigidbody
//	bodySettings = _bodySettings;
//
//	//creates a temp body defenition so that we can create a rigidbody
//	b2BodyDef bodyDef;
//	bodyDef.type = _bodySettings.ConvertTypeToBox2DType(_bodySettings.type);
//	bodyDef.linearDamping = _bodySettings.drag;
//	bodyDef.angularDamping = _bodySettings.angularDrag;
//	bodyDef.allowSleep = _bodySettings.allowSleep;
//	bodyDef.awake = _bodySettings.awake;
//	bodyDef.fixedRotation = _bodySettings.freezeRotation;
//	bodyDef.bullet = _bodySettings.important;
//	bodyDef.gravityScale = _bodySettings.gravityScale;
//	bodyDef.position = pos_;
//
//	//creates the rigidbody
//	body = PhysicsEngine::GetInstance()->CreateRigidBody(&bodyDef);
//}

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
	/*if(gameObject->name == "obj2")
	std::cout << "game object pos: " << gameObject->GetPosition().x << " ; " << gameObject->GetPosition().y << " body pos: " << body->GetPosition().x << " ; " << body->GetPosition().y << std::endl;*/
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
