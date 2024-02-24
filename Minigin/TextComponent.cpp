#include "TextComponent.h"
#include <iostream>
#include "GameTime.h"
dae::TextComponent::TextComponent():
	Component(),
	m_NeedsUpdate{ false }
{

	

}
dae::TextComponent::~TextComponent()
{

}

void dae::TextComponent::Update()
{
	std::cout << "deltatime: " << GameTime::GetInstance().GetDeltaTime() << std::endl;
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}


void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_Font = std::move(font);
    m_NeedsUpdate = true;
}
