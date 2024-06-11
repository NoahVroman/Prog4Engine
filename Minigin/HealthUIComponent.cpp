#include "HealthUIComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "HealthComponent.h"
#include "Subject.h"
dae::HealthUIComponent::HealthUIComponent(GameObject* const pParent, int StartingLives)
	: Component(pParent)
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pTextComponent = GetOwnerObject()->AddComponent<TextComponent>("# Lives: ", font);

	UpdateText(StartingLives);
}


void dae::HealthUIComponent::Render() const
{

}

void dae::HealthUIComponent::Update()
{
}

void dae::HealthUIComponent::FixedUpdate()
{
}

void dae::HealthUIComponent::NotifyObserver(GameObject* const pGameobj , Event currentEvent)
{
	if (currentEvent == Event::LivesChanged)
	{
		auto healthComponent = pGameobj->GetComponent<HealthComponent>();
		if (healthComponent)
		{
			UpdateText(healthComponent->GetLives());
		}
	}

}

void dae::HealthUIComponent::UpdateText(int Lives)
{
	m_pTextComponent->SetText("# Lives: " + std::to_string(Lives));
}
