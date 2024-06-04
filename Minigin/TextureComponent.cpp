#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "TransfomComponent.h"

dae::TextureComponent::TextureComponent(GameObject* const pParentObject,const std::string& path, const SpriteInfo& spriteInfo)
	: Component(pParentObject)
	, m_Filename{ path }
	, m_Texture{ ResourceManager::GetInstance().LoadTexture(path) }
	, m_SpriteInfo{ spriteInfo }
{
}

dae::TextureComponent::~TextureComponent()
{
	m_Texture = nullptr;
}

void dae::TextureComponent::Render() const
{
	if (isHidden)
		return;

	const auto& pos = GetOwnerObject()->GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y,m_SpriteInfo.width,m_SpriteInfo.height,m_SpriteInfo.SrcX,m_SpriteInfo.SrcY,m_SpriteInfo.SrcWidth,m_SpriteInfo.SrcHeight);
}

void dae::TextureComponent::Update()
{

}

void dae::TextureComponent::FixedUpdate()
{

}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Filename = filename;
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}
