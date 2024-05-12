#pragma once
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class MovementComponent final : public Component
	{

	public:
		MovementComponent(GameObject* const parent);

		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		void MoveTo(glm::vec2 direction,float speed);
	};

}

