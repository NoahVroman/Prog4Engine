#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent : public Component, public Subject
	{
	public:

		HealthComponent(GameObject* const pParent, int lives);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void Render() const override {};
		void Update() override {};
		void FixedUpdate() override {};

		void SetLives(int lives)
		{
			m_Lives = lives;
			Notify(Event::LivesChanged);
		};
		int GetLives() const { return m_Lives; }

		void TakeLives(int damage);

		private:
			int m_Lives{};
			int m_MaxLives{};
		
	};

}

