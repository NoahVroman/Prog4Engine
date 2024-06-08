#include "TextComponent.h"
#include <iostream>
#include "GameTime.h"
#include <SDL_events.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TransfomComponent.h"
dae::TextComponent::TextComponent(GameObject* const pParent, const std::string& text, std::shared_ptr<Font> font):
	Component(pParent)
	,m_NeedsUpdate{ true }
	,m_Text{text}
	, m_Font{font}
	
{
	
	

}
dae::TextComponent::~TextComponent()
{

}

void dae::TextComponent::Render() const
{
    if (m_TextTexture != nullptr)
    {
        const glm::vec2& pos = GetOwnerObject()->GetTransform()->GetWorldPosition();
        Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
    }
}

void dae::TextComponent::Update()
{
    //m_Text = m_Text;
    if (m_NeedsUpdate)
    {

        // Free old texture if exists
        if (m_TextTexture)
        {
            SDL_DestroyTexture(m_TextTexture->GetSDLTexture());
            m_TextTexture = nullptr;
        }

        const SDL_Color color = { 255, 255, 255, 255 }; // White color
        const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
        }
        auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            SDL_FreeSurface(surf); // Free surface on error
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }
        SDL_FreeSurface(surf); // Free surface after texture creation
        m_TextTexture = std::make_shared<Texture2D>(texture);
        m_NeedsUpdate = false;
    }

}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::SetText(const std::string& text)
{
    
	m_NeedsUpdate = true;
	m_Text = text;
}


void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
    m_NeedsUpdate = true;
	m_Font = std::move(font);
}
