#include "SB_CharacterWeapon.h"
#include <iostream>
#include "../EventQueue.h"
#include "../Shape_Box.h"
#include "../Com_Mesh.h"
#include "../RigidBody.h"
#include "../SquareCollider.h"
#include "../EngineFunctionalityManager.h"
#include "../Scene.h"
#include "SB_BulletFunctionality.h"


SB_CharacterWeapon::SB_CharacterWeapon() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

SB_CharacterWeapon::~SB_CharacterWeapon()
{
	EventQueue::GetInstance()->UnsubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);
}

//starts, runs once when the component is added to the object
void SB_CharacterWeapon::Start()
{
	
}

//updates every frame
void SB_CharacterWeapon::Update()
{
	timer = timer + PhysicsEngine::GetInstance()->GetDeltaTime();
	if (timer > 0.35f)
		bullet->SetPosition(Vector2(99.f, 99.f));
}

//late start is runned once at the beigining of the gameplay, if the script is added at runtime, this wont be called 
void SB_CharacterWeapon::LateStart()
{
	//creates a new bullet object
	bullet = new GameObject("Bullet", new Transform(gameObject->GetPosition(), 0, Vector2(1, 1)));

	bullet->name = "Bullet";

	//creates a shape box for the bullet
	Shape_Box* shapeBoxOfBullet = new Shape_Box();
	//creates the com mesh
	Com_Mesh* Com_MeshOfBullet = new Com_Mesh();

	//creates a rb, with its settings 
	RigidBodySettings bodySettingsOfBullet = RigidBodySettings(dynamicBody, 1, 1, false, true, false, false, 0);
	RigidBody* rbOfBullet = new RigidBody(bodySettingsOfBullet);

	//stores the square collider
	SquareCollider* squareCollOfBullet = new SquareCollider(Vector2(0.122, 0.122), Vector2(0, 0));

	//creates a new bullet script
	SB_BulletFunctionality* bulletScript = new SB_BulletFunctionality();

	//sets the bullet texture
	Com_MeshOfBullet->SetTexture("../Textures/Bullet.png");
	Com_MeshOfBullet->SetShape(shapeBoxOfBullet);

	//adds the ccomponents to the bullet 
	bullet->AddComponent(Com_MeshOfBullet);
	bullet->AddComponent(rbOfBullet);
	bullet->AddComponent(squareCollOfBullet);
	bullet->AddComponent(bulletScript);

	//sets the bullet position
	bullet->SetPosition(Vector2(99.f, 99.f));

	//add an object to the scene
	Scene::GetInstance()->AddObject(bullet);

	//sets the mouse press callback
	mousePressCallback = std::bind(&SB_CharacterWeapon::WeaponShot, this);
	EventQueue::GetInstance()->SubscribeToMouseKeyPressEvent(sf::Mouse::Left, mousePressCallback);
}

void SB_CharacterWeapon::WeaponShot()
{
	//if on edit mode leave
	if (EngineFunctionalityManager::GetInstance()->GetEngineState() == EngineFunctionalityManager::State::editMode)
		return;

	//reset the bullet timer
	timer = 0;

	//get the bullet direction
	Vector2 dir = InputsEngine::GetInstance()->GetMouseWorldPosition() - gameObject->GetPosition();
	//normalize it
	dir.Normalize();
	//posiiton the bullet correctly
	bullet->SetPosition(gameObject->GetPosition() + (dir * 0.38));

	//if rb, add force
	if (bullet->TryGetRigidBody() != nullptr)
		bullet->TryGetRigidBody()->AddForceToCenter(dir * 25);

}