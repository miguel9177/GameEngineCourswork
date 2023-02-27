#include "Com_Collider.h"

Com_Collider::Com_Collider(ColliderType type_) : Component(Component::typeOfComponent::Collider, uniqueComponentIdIdentifier)
{
	typeOfCollider = type_;
}

Com_Collider::ColliderType Com_Collider::GetColliderType()
{
	return typeOfCollider;
}

void Com_Collider::Start()
{

}
