#include "MovementComponent.h"
#include "GameTime.h"
#include "TransfomComponent.h"

dae::MovementComponent::MovementComponent(GameObject* const parent)
	: Component(parent)
{
}


void dae::MovementComponent::MoveTo(glm::vec2 direction, float speed)
{
	glm::vec2 addedPosition{ glm::normalize(direction) * speed * GameTime::GetInstance().GetDeltaTime() };
	
	GetOwnerObject()->GetTransform()->SetLocalPosition(GetOwnerObject()->GetTransform()->GetLocalPosition() + addedPosition);
}
