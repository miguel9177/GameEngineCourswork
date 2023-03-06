#pragma once
#include <Box2D/Box2D.h>
#include "Component.h"
#include <vector>
#include "Vector2.h"

class Com_Collider;

//conversion of the b2BodyType https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_dynamics.html#autotoc_md57
enum RigidBodyType
{
	/*A static body does not move under simulation and behaves as if it has infinite 
	mass. Internally, Box2D stores zero for the mass and the inverse mass. 
	Static bodies can be moved manually by the user. A static body has zero velocity. 
	Static bodies do not collide with other static or kinematic bodies.*/
	staticBody,
	/* A kinematic body moves under simulation according to its velocity. 
	Kinematic bodies do not respond to forces. They can be moved manually by the user,
	but normally a kinematic body is moved by setting its velocity. A kinematic body 
	behaves as if it has infinite mass, however, Box2D stores zero for the mass and 
	the inverse mass. Kinematic bodies do not collide with other kinematic or static bodies.
	*/
	kinematicBody,
	/* A dynamic body is fully simulated. They can be moved manually by the user, but normally they move according to 
	forces. A dynamic body can collide with all body types. A dynamic body always has finite, non-zero mass. 
	If you try to set the mass of a dynamic body to zero, it will automatically acquire a mass of one kilogram and 
	it won't rotate.
	*/
	dynamicBody
};

struct RigidBodySettings
{
	RigidBodyType type;
	float drag = 0.5f; // adds drag to the body (reducing its speed over time)
	float angularDrag = 0.5f; // adds Angular drag to the body (reducing its rotating speed over time)
	/*When Box2D determines that a body (or group of bodies) has come to rest, the body enters a sleep state which 
	has very little CPU overhead. If a body is awake and collides with a sleeping body, then the sleeping body wakes 
	up. Bodies will also wake up if a joint or contact attached to them is destroyed. You can also wake a body 
	manually.The body definition lets you specify whether a body can sleep and whether a body is created sleeping.*/
	bool allowSleep = true; 

	//TODO ACABAR DE COMENTAR ISTO E FAZER O RB USAR ESTE STRUCT E O ENUM EM CIMA
	bool awake = true; // Initially awake
	bool freezeRotation = false; // Allow rotation
	bool important = false; // Disable continuous collision detection
	float gravityScale = 1.0f; // Gravity scale
};

class RigidBody : public Component
{
	//this stores the body of this rb, the b2Body is pratically the same as rigidbody on unity.
	b2Body* body;
	//this stores every colliders of the rigidbody
	std::vector<Com_Collider*> allColliders;
public:
	static const unsigned int uniqueComponentIdIdentifier = 200;
	bool useGravity = false;
	
	RigidBody(b2BodyType _typeOfRb);
	RigidBody(b2BodyType _typeOfRb, Vector2 _pos);
	~RigidBody();

	// Inherited via Component
	void Start() override;

	void Update();

#pragma region Getters and Setters
	
	Vector2 GetPosition();
	void SetPosition(Vector2 _position);
	float GetRotation();
	void SetRotation(float _rot);
	void SetPositionAndRotation(Vector2 _position, float _rot);

#pragma endregion

#pragma region Collider Functions

	void AddCollider(Com_Collider* _coll);

	std::vector<Com_Collider*>* GetAllColliders();

#pragma endregion

#pragma region Inline Functions

	#pragma region Getters and setters
		
		//ALL THIS FUNCTIONS ARE MEARLY CONVERSIONS OF THE BOX 2D DOCUMENTATION: https://box2d.org/documentation/classb2_body.html#a942be8e1cd2bcd06f53c4638c45a9525
		inline float GetAngularVelocity()
		{
			return body->GetAngularVelocity();
		}

		inline float GetInertia()
		{
			return body->GetInertia();
		}

		inline Vector2 GetLinearVelocity()
		{
			return body->GetLinearVelocity();
		}

		inline float GetMass()
		{
			return body->GetMass();
		}

		inline bool IsAwake()
		{
			return body->IsAwake();
		}

		inline void SetAwake(bool awake)
		{
			body->SetAwake(awake);
		}

		inline void SetAngularVelocity(float _newAngularVelocity)
		{
			body->SetAngularVelocity(_newAngularVelocity);
		}

		inline void SetActive(bool isEnabled)
		{
			body->SetActive(isEnabled);
		}

		inline bool IsActive()
		{
			return body->IsActive();
		}

		inline void FreezeRotation(bool _freeze)
		{
			body->SetFixedRotation(_freeze);
		}

		inline bool IsFreezeRotiation()
		{
			return body->IsFixedRotation();
		}

		inline void SetLinearVelocity(const Vector2 _newVel)
		{
			body->SetLinearVelocity(_newVel);
		}

		//if this is setted to true it will improve the physics collision detection (makes game slower)
		inline void SetImportant(bool _important)
		{
			body->SetBullet(_important);
		}

		inline bool IsImportant()
		{
			return body->IsBullet();
		}

	#pragma endregion

	#pragma region Apply Forces Functions
		//ALL THIS FUNCTIONS ARE MEARLY CONVERSIONS OF THE BOX 2D DOCUMENTATION: https://box2d.org/documentation/classb2_body.html#a942be8e1cd2bcd06f53c4638c45a9525
		inline void AddAngularImpulse(float impulse)
		{
			body->ApplyAngularImpulse(impulse, true);
		}

		inline void AddForce(const Vector2 force, const Vector2 point)
		{
			body->ApplyForce(force, point, true);
		}

		inline void AddForceToCenter(const Vector2 force)
		{
			body->ApplyForceToCenter(force, true);
		}

		inline void AddLinearImpulse(const Vector2 impulse, const Vector2 point)
		{
			body->ApplyLinearImpulse(impulse, point, true);
		}

		inline void AddLinearImpulseToCenter(const Vector2 impulse)
		{
			body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
		}

		inline void AddTorque(float torque)
		{
			body->ApplyTorque(torque, true);
		} 
	#pragma endregion

#pragma endregion


};

