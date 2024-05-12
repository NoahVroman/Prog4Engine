#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include <format>
dae::FPSComponent::FPSComponent(GameObject* parent)
	: Component(parent)
{
	m_pTextComponent = GetOwnerObject()->AddComponent<TextComponent>("0 FPS", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
}

void dae::FPSComponent::Update()
{
	m_pTextComponent->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	m_pTextComponent->SetText("FPS: " + std::format("{:.1f}", 1 / GameTime::GetInstance().GetDeltaTime()));
}

void dae::FPSComponent::FixedUpdate()
{

}

void dae::FPSComponent::Render() const
{
	
}


