#include "ScoreAndLivesManager.h"
#include "TextComponent.h"

void dae::ScoreAndLivesManager::Initialize(dae::TextComponent* scoreTextComponent, dae::TextComponent* healthTextComponent)
{

	m_ScoreTextComponent = scoreTextComponent;
	m_HealthTextComponent = healthTextComponent;

	UpdateScoreText();
	UpdateHealthText();
}

void dae::ScoreAndLivesManager::AddScore(int score)
{
	m_Score += score;
	UpdateScoreText();
}

void dae::ScoreAndLivesManager::AddLives(int lives)
{
	m_Lives += lives;
	UpdateHealthText();

}

void dae::ScoreAndLivesManager::RemoveLives(int lives)
{
	m_Lives -= lives;
	UpdateHealthText();
}
void dae::ScoreAndLivesManager::UpdateScoreText()
{
	if (m_ScoreTextComponent) 
	{
		m_ScoreTextComponent->SetText("Score: " + std::to_string(m_Score));
	}
}

void dae::ScoreAndLivesManager::UpdateHealthText()
{
	if (m_HealthTextComponent) 
	{
		m_HealthTextComponent->SetText("Health: " + std::to_string(m_Lives));
	}

}
