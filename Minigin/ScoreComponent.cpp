#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* const pParent, int StartingScore)
	: Component(pParent)
	, m_Score(StartingScore)
{
}

