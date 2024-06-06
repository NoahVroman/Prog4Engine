#include "ScoreUIComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"

dae::ScoreUIComponent::ScoreUIComponent(GameObject* const pParent, int StartingScore) : Component(pParent)

{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pTextComponent = GetOwnerObject()->AddComponent<TextComponent>("Score: ", font);
	UpdateText(StartingScore);
}


void dae::ScoreUIComponent::NotifyObserver(GameObject* const Gameobj, Event currentEvent)
{
    if (currentEvent == Event::ScoreUpdated) {
        auto scoreComponent = Gameobj->GetComponent<ScoreComponent>();
        if (scoreComponent) {
            UpdateText(scoreComponent->GetScore());
        }
    }
}

void dae::ScoreUIComponent::UpdateText(int Score)
{
	m_pTextComponent->SetText("Score: " + std::to_string(Score));
}
