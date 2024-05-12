#include "ButtonComponent.h"
#include <iostream>

dae::ButtonComponent::ButtonComponent(GameObject* const pParent, const std::string& text, std::shared_ptr<Font> font)
	:Component(pParent)

{
	m_pTextComponent = pParent->AddComponent<TextComponent>(text, font);
	}

dae::ButtonComponent::~ButtonComponent()
{
}

void dae::ButtonComponent::Update()
{
}

void dae::ButtonComponent::Render() const
{
	m_pTextComponent->Render();
}


void dae::ButtonComponent::FixedUpdate()
{
}

void dae::ButtonComponent::Selected()
{
	m_IsSelected = true;

}

void dae::ButtonComponent::Deselected()
{
		m_IsSelected = false;
}

void dae::ButtonComponent::Press()
{
	if (m_IsSelected == false)
	{
		return;
	}

	std::cout << "Button Pressed" << std::endl;

}
