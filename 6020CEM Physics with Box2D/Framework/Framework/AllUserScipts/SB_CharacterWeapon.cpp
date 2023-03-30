#include "SB_CharacterWeapon.h"
#include <iostream>
#include "../EventQueue.h"
#include "../Shape_Box.h"
#include "../Com_Mesh.h"
#include "../RigidBody.h"
#include "../SquareCollider.h"
#include "../EngineFunctionalityManager.h"
#include "../Scene.h"


SB_CharacterWeapon::SB_CharacterWeapon() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

SB_CharacterWeapon::~SB_CharacterWeapon()
{
	EventQueue::GetInstance()->UnsubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);
}

void SB_CharacterWeapon::Start()
{
	
}

void SB_CharacterWeapon::Update()
{
	
}

void SB_CharacterWeapon::LateStart()
{
	mousePressCallback = std::bind(&SB_CharacterWeapon::WeaponShot, this);
	EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);
}

void SB_CharacterWeapon::WeaponShot()
{
	if (EngineFunctionalityManager::GetInstance()->GetEngineState() == EngineFunctionalityManager::State::editMode)
		return;

	GameObject* bullet = new GameObject("Bullet", new Transform(gameObject->GetPosition(), 0, Vector2(1, 1)));

	Shape_Box* shapeBoxOfBullet = new Shape_Box();

	Com_Mesh* Com_MeshOfBullet = new Com_Mesh();

	RigidBodySettings bodySettingsOfBullet = RigidBodySettings(dynamicBody, 1, 1, false, true, false, false, 0);
	RigidBody* rbOfBullet = new RigidBody(bodySettingsOfBullet);

	SquareCollider* squareCollOfBullet = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

	Com_MeshOfBullet->SetTexture("../Textures/Bullet.png");
	Com_MeshOfBullet->SetShape(shapeBoxOfBullet);

	bullet->AddComponent(Com_MeshOfBullet);
	bullet->AddComponent(rbOfBullet);
	bullet->AddComponent(squareCollOfBullet);

	//add an object to the scene
	Scene::GetInstance()->AddObject(bullet);
	
	Vector2 dir = InputsEngine::GetInstance()->GetMouseWorldPosition() - bullet->GetPosition();
	dir.Normalize();
	bullet->SetPosition(gameObject->GetPosition() + (dir * 0.32));

	if (bullet->TryGetRigidBody() != nullptr)
		bullet->TryGetRigidBody()->AddForceToCenter(dir * 25);
}