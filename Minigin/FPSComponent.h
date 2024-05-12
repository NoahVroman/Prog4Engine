#pragma once
#include "Component.h"
namespace dae
{
	class GameObject;
	class TextComponent;
	class FPSComponent : public Component
	{
		public:
		FPSComponent(GameObject* parent);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override;

		private:
		TextComponent* m_pTextComponent{};
		float m_Delay{ 0.0f };
		float m_Count{ 0.0f };
		float m_maxDelay{ 1.0f };
	};

}

