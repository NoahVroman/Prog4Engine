#pragma once
#include <memory>
#include <string>

namespace dae 
{
	class TextComponent;

	class ScoreAndLivesManager
	{
		public:
			static ScoreAndLivesManager& GetInstance()
			{
				static ScoreAndLivesManager instance;
				return instance;
			}
			ScoreAndLivesManager(ScoreAndLivesManager const&) = delete;
			void operator=(ScoreAndLivesManager const&) = delete;
			~ScoreAndLivesManager() = default;

			void Initialize(dae::TextComponent* scoreTextComponent,dae::TextComponent* healthTextComponent);
			void AddScore(int score);
			void AddLives(int lives);
			void RemoveLives(int lives);
			int GetScore() const { return m_Score; }
			int GetLives() const { return m_Lives; }
			void ResetScore() { m_Score = 0; }
			void ResetLives() { m_Lives = 3; }

			void UpdateScoreText();
			void UpdateHealthText();

			private:
			ScoreAndLivesManager() = default;

			dae::TextComponent* m_ScoreTextComponent{};
			dae::TextComponent* m_HealthTextComponent{};
			int m_Score{0};
			int m_Lives{3};
	};

}


