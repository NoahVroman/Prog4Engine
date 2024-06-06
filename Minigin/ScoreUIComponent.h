#pragma once
#include "Component.h"
#include "Observer.h"
#include "TextComponent.h"
namespace dae
{
	class ScoreUIComponent : public Component, public Observer
	{
		public:
		ScoreUIComponent(GameObject* const pParent, int StartingScore);
		virtual ~ScoreUIComponent() = default;
		ScoreUIComponent(const ScoreUIComponent& other) = delete;
		ScoreUIComponent(ScoreUIComponent&& other) = delete;
		ScoreUIComponent& operator=(const ScoreUIComponent& other) = delete;
		ScoreUIComponent& operator=(ScoreUIComponent&& other) = delete;

		void Render() const override {};
		void Update() override {};
		void FixedUpdate() override {};

		void NotifyObserver(GameObject* const pGameobj, Event currentEvent) override;
		
		private:
			TextComponent* m_pTextComponent{};

			void UpdateText(int Score);




	};

}

