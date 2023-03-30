#include "Com_Collider.h"
#include <Box2D/Box2D.h>

//construcctor with type
Com_Collider::Com_Collider(ColliderType type_, unsigned int uniqueComponentIdIdentifier) : Component(Component::typeOfComponent::Collider, uniqueComponentIdIdentifier)
{
	typeOfCollider = type_;
	mass = 1;
	friction = 0.5f;
	bouciness = 0.4f;
}

//construcctor with type and settings
Com_Collider::Com_Collider(ColliderType type_, float _mass, float _friction, float _bouciness, unsigned int uniqueComponentIdIdentifier) : Component(Component::typeOfComponent::Collider, uniqueComponentIdIdentifier)
{
	typeOfCollider = type_;
	mass = _mass;
	friction = _friction;
	bouciness = _bouciness;
}

Com_Collider::ColliderType Com_Collider::GetColliderType()
{
	return typeOfCollider;
}

void Com_Collider::Start()
{

}
