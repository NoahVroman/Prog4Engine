#pragma once
#include "Component.h"
#include "Subject.h"
namespace dae
{
	class ScoreComponent : public Component,public Subject
	{
		public:
		ScoreComponent(GameObject* const pParent, int StartingScore);
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;


		void Render() const override {};
		void Update() override {};
		void FixedUpdate() override {};



		void AddScore(int score)
		{
			m_Score += score;
			Notify(Event::ScoreUpdated);
		}
		int GetScore() const { return m_Score; }
		void ResetScore() { m_Score = 0; }

		private:
			int m_Score{};
	};

}

