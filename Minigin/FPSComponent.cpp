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

}

void dae::FPSComponent::FixedUpdate()
{

}

void dae::FPSComponent::Render() const
{
	
}


