#pragma once
#include "Com_Collider.h"
#include "Vector2.h"

class b2FixtureDef;
class SquareCollider : public Com_Collider
{
private:
	//coll settings
	Vector2 halfSize;
	Vector2 posOffset;
	float offsetAngle;
	//stores the coll of the box 2d
	b2FixtureDef coll;
	//creates teh collider
	void CreateCollider();
public:
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 101;

	b2FixtureDef* GetColliderBox2dDefenition() override;

	void Start() override;

#pragma region Constructors

	//normal constructor
	SquareCollider(Vector2 _halfSize);
	SquareCollider(Vector2 _halfSize, Vector2 _offsetPos);
	SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _offsetAngle);

	//constructors with physic material
	SquareCollider(Vector2 _halfSize, float _mass, float _friction, float _bouciness);
	SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _mass, float _friction, float _bouciness);
	SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _offsetAngle, float _mass, float _friction, float _bouciness);

#pragma endregion


#pragma region Getters

	inline Vector2 GetHalfSize() { return halfSize; };
	inline Vector2 GetPosOffset() { return posOffset; };
	inline float GetOffsetAngle() { return offsetAngle; };
	inline float GetMass() { return mass; };
	inline float GetFriction() { return friction; };
	inline float GetBouciness() { return bouciness; };

#pragma endregion
};

