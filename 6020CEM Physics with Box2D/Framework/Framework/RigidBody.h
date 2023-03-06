#pragma once
#include <Box2D/Box2D.h>
#include "Component.h"
#include <vector>
#include "Vector2.h"

class Com_Collider;


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
		inline float RigidBody::GetAngularVelocity()
		{
			return body->GetAngularVelocity();
		}

		inline float RigidBody::GetInertia()
		{
			return body->GetInertia();
		}

		inline Vector2 RigidBody::GetLinearVelocity()
		{
			return body->GetLinearVelocity();
		}

		inline float RigidBody::GetMass()
		{
			return body->GetMass();
		}

		inline bool RigidBody::IsAwake()
		{
			return body->IsAwake();
		}

		inline void RigidBody::SetAngularVelocity(float _newAngularVelocity)
		{
			body->SetAngularVelocity(_newAngularVelocity);
		}

		inline void RigidBody::SetActive(bool isEnabled)
		{
			body->SetActive(isEnabled);
		}

		inline void RigidBody::FreezeRotation(bool _freeze)
		{
			body->SetFixedRotation(_freeze);
		}

		inline bool RigidBody::IsFreezeRotiation()
		{
			return body->IsFixedRotation();
		}

		inline void RigidBody::SetLinearVelocity(const Vector2 _newVel)
		{
			body->SetLinearVelocity(_newVel);
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

