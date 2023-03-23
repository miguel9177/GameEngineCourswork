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
	RigidBodyType type = RigidBodyType::dynamicBody;
	float drag = 0.5f; // adds drag to the body (reducing its speed over time)
	float angularDrag = 0.5f; // adds Angular drag to the body (reducing its rotating speed over time)
	
	/*When Box2D determines that a body (or group of bodies) has come to rest, the body enters a sleep state which 
	has very little CPU overhead. If a body is awake and collides with a sleeping body, then the sleeping body wakes 
	up. Bodies will also wake up if a joint or contact attached to them is destroyed. You can also wake a body 
	manually.The body definition lets you specify whether a body can sleep and whether a body is created sleeping.*/
	bool allowSleep = true; //basically if this is false the body will never sleep

	
	bool awake = true; //Is this body awake or sleeping ?
	bool freezeRotation = false; // if true dont let the object rotate
	bool important = false; // enable continuous collision detection or disable it
	float gravityScale = 1.0f; // Gravity scale
	
	RigidBodySettings()
		: type(RigidBodyType::dynamicBody),
		drag(0.5f),
		angularDrag(0.5f),
		allowSleep(true),
		awake(true),
		freezeRotation(false),
		important(false),
		gravityScale(1.0f)
	{
	}

	RigidBodySettings(RigidBodyType _type, float _drag, float _angularDrag, bool _allowSleep, bool _awake, bool _freezeRotation, bool _important, float _gravityScale)
		: type(_type),
		drag(_drag),
		angularDrag(_angularDrag),
		allowSleep(_allowSleep),
		awake(_awake),
		freezeRotation(_freezeRotation),
		important(_important),
		gravityScale(_gravityScale)
	{
	}

	b2BodyType ConvertTypeToBox2DType(RigidBodyType type)
	{
		switch (type)
		{
		case staticBody:
			return b2_staticBody;
		case kinematicBody:
			return b2_kinematicBody;
		case dynamicBody:
			return b2_dynamicBody;
		default:
			return b2_staticBody; // or some other default value
		}
	}
};

class RigidBody : public Component
{
	//this stores the body of this rb, the b2Body is pratically the same as rigidbody on unity.
	b2Body* body;

	//this stores the settings of this rb
	RigidBodySettings bodySettings;

	//this stores every colliders of the rigidbody
	std::vector<Com_Collider*> allColliders;

public:
	static const unsigned int uniqueComponentIdIdentifier = 200;
	bool useGravity = false;

	RigidBody(RigidBodySettings _bodySettings = RigidBodySettings());

	//RigidBody(Vector2 _pos, RigidBodySettings _bodySettings = RigidBodySettings());
	~RigidBody();

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
		
		//DEBUG GETTERS
		inline b2Body* Debug_GetB2Body() { return body; }

		//ALL THIS FUNCTIONS ARE MEARLY CONVERSIONS OF THE BOX 2D DOCUMENTATION: https://box2d.org/documentation/classb2_body.html#a942be8e1cd2bcd06f53c4638c45a9525
	

		inline float GetInertia() { return body->GetInertia(); }

		inline float GetMass() { return body->GetMass(); }

		inline RigidBodyType GetRbType() { return bodySettings.type; }

		inline void SetRbType(RigidBodyType type_) 
		{ 
			bodySettings.type = type_;
			body->SetType(bodySettings.ConvertTypeToBox2DType(type_)); 
		}

		inline float GetDrag() { return bodySettings.drag; }

		inline void SetDrag(float _drag) 
		{ 
			bodySettings.drag = _drag; 
			body->SetLinearDamping(_drag);
		}

		inline float GetAngularDrag() { return bodySettings.angularDrag; }

		inline void SetAngularDrag(float _angularDrag)
		{
			bodySettings.angularDrag = _angularDrag;
			body->SetAngularDamping(_angularDrag);
		}

		inline bool GetAllowSleep() { return bodySettings.allowSleep; }

		inline void SetAllowSleep(bool _allowSleep) 
		{ 
			bodySettings.allowSleep = _allowSleep; 
			body->SetSleepingAllowed(_allowSleep);
		}

		inline bool GetAwake() { return bodySettings.awake; }

		inline void SetAwake(bool _awake)
		{
			bodySettings.awake = _awake;
			body->SetAwake(_awake);
		}

		inline bool GetFreezedRotation() { return bodySettings.freezeRotation; }

		inline void SetFreezeRotation(bool _freezeRotation)
		{
			bodySettings.freezeRotation = _freezeRotation;
			body->SetFixedRotation(_freezeRotation);
		}

		inline bool IsImportant() { return bodySettings.important; }

		//if this is setted to true it will improve the physics collision detection (makes game slower)
		inline void SetImportant(bool _important)
		{
			bodySettings.important = _important;
			body->SetBullet(_important);
		}

		inline float GetGravityScale() { return bodySettings.gravityScale; }

		inline void SetGravityScale(float _gravityScale)
		{
			bodySettings.gravityScale = _gravityScale;
			body->SetGravityScale(_gravityScale);
		}

		inline Vector2 GetLinearVelocity() { return body->GetLinearVelocity(); }

		inline void SetLinearVelocity(const Vector2 _newVel) { body->SetLinearVelocity(_newVel); }

		inline float GetAngularVelocity(){ return body->GetAngularVelocity(); }

		inline void SetAngularVelocity(float _newAngularVelocity) { body->SetAngularVelocity(_newAngularVelocity); }

		inline void SetActive(bool isEnabled) { body->SetActive(isEnabled); }

		inline bool IsActive() { return body->IsActive(); }

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

