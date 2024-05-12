#pragma once
#include "GameObject.h"
#include "GameTime.h"
#include "Renderer.h"
#include "TransfomComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

namespace dae 
{
	class Component;
	class RotatorComponent : public Component
	{
		public:
		RotatorComponent(GameObject* parent);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override;

		private:
		float m_Angle{ 0.0f };
		float m_Speed{ 180.0f };
	};

}

