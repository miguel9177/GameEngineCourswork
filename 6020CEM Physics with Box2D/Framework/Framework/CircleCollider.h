#pragma once
#include "Com_Collider.h"
#include "Vector2.h"

class b2FixtureDef;
class CircleCollider : public Com_Collider
{
private:
	//coll settings
	float radius;
	Vector2 posOffset;
	float offsetAngle;
	//Data
	b2FixtureDef coll;

	void CreateCollider();
public:
	static const unsigned int uniqueComponentIdIdentifier = 102;
	b2FixtureDef* GetColliderBox2dDefenition() override;

	void Start() override;

#pragma region Constructors

	//normal constructor
	CircleCollider(float radius);
	CircleCollider(float radius, Vector2 _offsetPos);
	CircleCollider(float radius, Vector2 _offsetPos, float _offsetAngle);

	//constructors with physic material
	CircleCollider(float radius, float _mass, float _friction, float _bouciness);
	CircleCollider(float radius, Vector2 _offsetPos, float _mass, float _friction, float _bouciness);
	CircleCollider(float radius, Vector2 _offsetPos, float _offsetAngle, float _mass, float _friction, float _bouciness);

#pragma endregion

#pragma region Getters

	inline float GetRadius() { return radius; };
	inline Vector2 GetPosOffset() { return posOffset; };
	inline float GetOffsetAngle() { return offsetAngle; };
	inline float GetMass() { return mass; };
	inline float GetFriction() { return friction; };
	inline float GetBouciness() { return bouciness; };

#pragma endregion
};

