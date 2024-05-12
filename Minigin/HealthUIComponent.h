#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class HealthUIComponent final : public Component, public Observer
	{
		public:
		HealthUIComponent(GameObject* const pParent, int StartingLives);
		virtual ~HealthUIComponent() = default;
		HealthUIComponent(const HealthUIComponent& other) = delete;
		HealthUIComponent(HealthUIComponent&& other) = delete;
		HealthUIComponent& operator=(const HealthUIComponent& other) = delete;
		HealthUIComponent& operator=(HealthUIComponent&& other) = delete;

		void Render() const override;
		void Update() override;
		void FixedUpdate() override;

		void NotifyObserver(Subject* const gameObject, Event currentEvent) override;
		
		private:
			TextComponent* m_pTextComponent{};

			void UpdateText(int Lives);
	};
}

